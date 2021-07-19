#include <Logic.h>
// for TinyAVR

void setup() {
  VPORTA.DIR=0x60; //Set the PA5 and PA6 pins to outputs - these can be monitored to see which state it is in for debugging.
  #ifdef MEGATINYCORE
    //pinMode(PIN_SPI_SS, INPUT_PULLUP);
    // Note - above line would not work on pre-2.4.0 versions of megaTinyCore due to a defect identified in the variant files,
    // which incorrectly reported PA0 to be the SS pin on all parts. In fact, PA4 is the SS pin except on 8-pin parts.
    // For the case of tinyAVR 0/1/2-series devices, we'll use the CCL and event system to monitor the SS pin, and turn 
    // on the builtin LED (assuming there is one in the default position of PA7) whenever SS is asserted as a further aid
    // to debugging. 
    pinMode(PIN_PA4, INPUT_PULLUP);
    #ifdef EVSYS_ASYNCCH0
      // handle the 0 and 1 series parts, with the wacky beta version of EVSYS
      EVSYS.ASYNCCH0=0x0E; //PA4, the SS pin.
      EVSYS.ASYNCUSER3=0x03; //use ASYNCCH0 for CCL LUT 1 event 0/a
    #else // 2-series has the good version of EVSYS
      EVSYS.CHANNEL0 = EVSYS_CHANNEL0_PORTA_PIN4_gc; //PA4, the SS pin.
      EVSYS.USERCCLLUT1A = 0x01; // Point LUT0 event input A at channel 0, ie, the SS pin.
    #endif
    /* Logic1 - CCL LUT1 */
    Logic1.enable = true;                     // Enable logic block 1
    Logic1.input0 = in::event_a;              // event carrying SS pin input
    Logic1.input1 = in::masked;               // masked
    Logic1.input2 = in::masked;               // masked
    Logic1.output = out::enable;              // Enable logic block 1 output pin on PA7
    Logic1.truth = 0x01;                      // Set truth table: Invert, HIGH if input0 LOW
    Logic1.init();                            // Initialize logic block 1
    Logic::start();                           // Start the CCL hardware
  #else
    /* depending which SPI PORTMUX option you are using, additional configuration must be done 
     * to support other parts. They will need the MISO pin set to output, at minimum. 
     * Also, other parts will require you to take a similar step to use the CCL to give you
     * an indication of activity on the SS pin, if you want that - however none of these 
     * are particularly challenging hurdles to overcome; you just need to do it. */ 
     //set SS INPUT_PULLUP
  #endif
  // Everything we get over SPI will be printed to serial. 
  // Use a high baud rate; this is the highest that some adapters work reliably at, so I use that. 
  // If your adapter can do it, you should be able to crank it to 1/8th of the system clock speed.
  // The baud rate must be at least 25% higher than the SPI clock rate to ensure no data is lost
  // during sustained transfers from the SPI device. 
  Serial.begin(921600); // The HardwareSerial class is used ONLY to set baud rate and pinMode
  Serial.println("SPI2UART online");  // and send this message.
  Serial.println();     // Extra line between initial message and whatever we get over SPI.
  Serial.flush();       // finish sending it all before we axe normal serial functionality. 
  USART0.CTRLA=0;       // all interrupts off, we will poll DRE and disable RX.
  USART0.CTRLB &= ~USART_RXEN_bm;     // Disable receive. 
  initSPISlave();       // Enable SPI in buffered slave mode.
}

void loop() {
  uint8_t data;
  VPORTA.OUT |= (1 << 5);   // Raise PA5 to indicate that we're waiting for data to send. 
  while (!(SPI0.INTFLAGS & SPI_RXCIF_bm));    // busywait for received SPI data.
  VPORTA.OUT &= ~(1 << 5);  // Lower PA5 to indicate that we got it,
  data=SPI0.DATA;           // read the byte
  VPORTA.OUT |= 1 << 6;     // raise PA6 when waiting for USART data ready. 
  while (!(USART0.STATUS & USART_DREIF_bm));  // busywait for DRE - if we're waiting here, we are at high risk for losing data!
  VPORTA.OUT &= ~(1 << 6);  // lower PA6 when DRE flag is raised. 
  USART0.TXDATAL=data;      // and send that byte

}

void initSPISlave() {
  SPI0.CTRLB = SPI_BUFEN_bm | SPI_BUFWR_bm; // Buffered, wait for receive, mode 0
  SPI0.INTCTRL = 0;                         // polled operation.
  SPI0.CTRLA = SPI_ENABLE_bm;               // Enable. Slave mode, DORD = 0 (MSB first), rest applies to master only. 
}
