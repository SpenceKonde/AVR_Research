/* The below MESS will barf out on serial0 (remember to swap pins if you're using aq crtystal, 11520 baud. 
If clock source is crystal, future DxCore releases will auto-swap serial1. 

Define CSV_ONLY to just get the final line for putting into a spreadsheet. 



#include "util/delay.h"
// *INDENT-OFF* astyle check wants this to be formatted in an unreadable and useless manner.
uint8_t ROWCONTENTS[64];
uint8_t stockCal=0;
uint8_t MaxCal=0;
void wdt_enable() {
  _PROTECTED_WRITE(WDT.CTRLA,WDT_PERIOD_8KCLK_gc); // no window, 8 seconds
}

void wdt_reset() {
  __asm__ __volatile__ ("wdr"::);
}

void wdt_disable() {
  _PROTECTED_WRITE(WDT.CTRLA,0);
}

void setup() {
  if (!(RSTCTRL.RSTFR & RSTCTRL_SWRF_bm)) {
    RSTCTRL.RSTFR = RSTCTRL.RSTFR;
    #if defined(RSTCTRL_SWRST_bm)
      _PROTECTED_WRITE(RSTCTRL_SWRR, RSTCTRL_SWRST_bm);
    #endif
  }
  RSTCTRL.RSTFR = RSTCTRL.RSTFR;
  #if (defined(DX_64_PINS) || (defined(DX_32_PINS)) ) //&& defined AZDUINO
  Serial.swap(1);
  #endif
  
  Serial.begin(115200);
  #ifndef CSV_ONLY
    Serial.println();
    Serial.println("This gathers all info from your sigrow");
  #endif
  /* Even the secret fields that microchip doesnt't tell us about */
  volatile uint8_t *sigrowbyte=(volatile uint8_t*) &SIGROW;
  for (byte x = 0; x < 64; x++) {
    ROWCONTENTS[x] = *sigrowbyte++;
  }
  #if defined(MEGATINYCORE)
    stockCal=CLKCTRL_OSC20MCALIBA;
  #endif
  #ifndef CSV_ONLY
    Serial.println();
    Serial.print("Device ID: ");
    Serial.printHex(ROWCONTENTS[0]);
    Serial.printHex(ROWCONTENTS[1]);
    Serial.printHex(ROWCONTENTS[2]);
    Serial.print("  Rev: ");
    Serial.printHex(SYSCFG.REVID);
    Serial.println();
    Serial.print("S/N: ");
      #ifndef DXCORE
      for (byte i = 0; i < 10; i++ ) {
        if (i) {
          Serial.print(':');
        }
  
        Serial.printHex(ROWCONTENTS[i+3]);
      }
    #else
      for (byte i = 0; i < 16; i++ ) {
        if (i) {
          Serial.print(':');
        }
  
        Serial.printHex(ROWCONTENTS[i+16]);
      }
      
    Serial.println();
    #endif
    #ifdef MEGATINYCORE
    Serial.println();
    Serial.print("Mystery Bytes: " );
    Serial.printHex(ROWCONTENTS[0x0E]);
    Serial.print(", " );
    Serial.printHex(ROWCONTENTS[0x0F]);
    Serial.print(", " );
    Serial.printHex(ROWCONTENTS[0x10]);
    Serial.print(", and " );
    Serial.printHex(ROWCONTENTS[0x15]);
    Serial.println();
    Serial.print("Cals: T - ");
    Serial.printHex(ROWCONTENTS[0x20]);
    Serial.print(", ");
    Serial.printHex(ROWCONTENTS[0x21]);
    Serial.print("  32k Internal - ");
    Serial.printHex(ROWCONTENTS[0x14]);
    Serial.println();
    Serial.println("        16M, 20M ");
    Serial.print("OSCCAL: ");
    Serial.printHex(ROWCONTENTS[0x18]);
    Serial.print(", ");
    Serial.printHex(ROWCONTENTS[0x1A]);
    Serial.println();
    Serial.print("Temp:   ");
    Serial.printHex(ROWCONTENTS[0x19]);
    Serial.print(", ");
    Serial.printHex(ROWCONTENTS[0x1B]);
    Serial.println();
    Serial.print("Err3V:  ");
    Serial.printHex(ROWCONTENTS[0x22]);
    Serial.print(", ");
    Serial.printHex(ROWCONTENTS[0x23]);
    Serial.println();
    Serial.print("Err5V:  ");
    Serial.printHex(ROWCONTENTS[0x24]);
    Serial.print(", ");
    Serial.printHex(ROWCONTENTS[0x25]);
    Serial.println();
    Serial.println();
    Serial.print("constants: ");
    if (ROWCONTENTS[0x16] != 0xFF || ROWCONTENTS[0x17] != 0xFF) {
      Serial.printHex(ROWCONTENTS[0x16]);
      Serial.printHex(ROWCONTENTS[0x17]);
      Serial.print(", ");
    }
    if (ROWCONTENTS[0x1C] != 0xFF || ROWCONTENTS[0x1D] != 0xFF) {
      Serial.printHex(ROWCONTENTS[0x1C]);
      Serial.printHex(ROWCONTENTS[0x1D]);
      Serial.print(", ");
    }
    if (ROWCONTENTS[0x1E] != 0xFF || ROWCONTENTS[0x1F] != 0xFF) {
      Serial.printHex(ROWCONTENTS[0x1E]);
      Serial.printHex(ROWCONTENTS[0x1F]);
      Serial.print(", ");
    }
      Serial.printHex(ROWCONTENTS[0x28]);
      Serial.printHex(ROWCONTENTS[0x29]);
      Serial.printHex(ROWCONTENTS[0x2A]);
      Serial.printHex(ROWCONTENTS[0x2B]);
      Serial.printHex(ROWCONTENTS[0x2C]);
      Serial.println()
    #else
      Serial.print("MSB first (like humans) temp cal: ");
      Serial.printHex(ROWCONTENTS[0x04]);
      Serial.printHex(ROWCONTENTS[0x05]);
      Serial.print(", ");
      Serial.printHex(ROWCONTENTS[0x06]);
      Serial.printHex(ROWCONTENTS[0x07]);
    #endif
    for (byte x = 0; x < 64; x++) {
      if (!(x & 0x0F)) { // Every 16 bytesd, we print a line
        Serial.println();
      } else if (!(x & 0x07)) { // and every 8 a space.
        Serial.print(' ');
      }
      Serial.printHex(ROWCONTENTS[x]);
    }
        Serial.println();
    #ifdef MEGATINYCORE 
      Serial.println("In 10 seconds we still start attempting see how good osc is." );
    #endif
  #endif
  delay(2000);
}



void loop() {
  #if defined(MEGATINYCORE)
    wdt_enable();
    
      #ifndef CSV_ONLY
        Serial.println("Testing the max stable oscillator setting");
      #endif
      volatile unsigned long microcount = micros();
      Serial.flush();
    _PROTECTED_WRITE(WDT_CTRLA, 0x0B);
    _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 3); //prescale enabled, div by 4
    #if MEGATINYCORE_SERIES==2
      byte x = (FUSE.OSCCFG == 1)? 0x60 : 0x40;
      for (; x < 128; x++)  // 128 possible settings for 2-series
    #else
      for (x = 0x15; x < 64; x++)   //  64 for 0/1-series
    #endif
    {
      wdt_reset();
      Serial.flush();
      _PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, x); /* Switch to new clock - prescale of 4 already on */
      _NOP();
      _NOP();
      _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 2);   //prescale disabled, div by 4
      _NOP();
      _NOP();
      _delay_ms(1);
      unsigned long startmicros = micros();
      do {
        microcount = micros();// write to main memory
      } while ((microcount - startmicros) < 2500);
      _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 3); //prescale enabled, div by 4
      _NOP();
      _PROTECTED_WRITE(CLKCTRL_OSC20MCALIBA, stockCal);
      _NOP();
      _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 2); //prescale disabled, div by 4
      _NOP();
      _NOP();
      _delay_ms(1);
      if (microcount - startmicros < 2500 || (microcount - startmicros > 3000 ))  {
        #ifndef CSV_ONLY
          Serial.print(" Max. OSCCAL: ");
          Serial.printHex((uint8_t)(x | ((FUSE.OSCCFG == 1)? 0x80 : 0x00)));
        #endif
        MaxCal=x - 1;
        break;
      } else {
        if ((x & 15) == 15) {
          Serial.println();
        }
      }
    }
    #if  (!defined(CSV_ONLY))
      #if (MEGATINYCORE_SERIES==2)
        if (x == 0x80) {
          MaxCal=0x79;
          Serial.println("All oscillator speeds stable");
          if ((FUSE.OSCCFG == 1)) {
            Serial.println("Not unexpected on 16 MHz osc.");
          } else {
            Serial.println("Rare on 20 MHz");
          }
        }
      #else
        if (x == 0x40) {
          MaxCal=0x39;
          Serial.println("All oscillator speeds stable");
          if ((FUSE.OSCCFG == 1)) {
            Serial.println("Not unexpected on 16 MHz osc.";)
          } else {
            Serial.println("Rare on 20 MHz");
          }
        }
      #endif
    #endif
    wdt_disable();
  #endif
  #if  (!defined(CSV_ONLY))
    Serial.println("Combine last line w/that line from other parts in a text file, save as .csv, Import to excel or google sheets");
  #endif
  /* column headers - put on first line of CSV - it's a doozy of a line. Currently this does not get the max and min frequency measurements (but the tuning sketch does) It is suggested to keep terminal logging, and run wuth CSV_ONLY defined  if you're systematically doing this. Ip This sketch should be run at 16 bHz and 20 MHz
   Max OSCCAL16, Max OSCCAL20, Min Freq 16, MAx Freq 16, Min Freq 20, MAx Freq 20, DEVICEID0, DEVICEID1, DEVICEID2, SERNUM0, SERNUM1, SERNUM2, SERNUM3, SERNUM4, SERNUM5, SERNUM6, SERNUM7, SERNUM8, SERNUM9, reserved_1_01, MYSTERY_BYTES0, MYSTERY_BYTES1, MYSTERY_BYTES2, reserved_1_05, reserved_1_06, reserved_1_07, OSCCAL32K, MYSTERY_BYTE, reserved_1_10, reserved_1_11, OSCCAL16M0, OSCCAL16M1, OSCCAL20M0, OSCCAL20M1, reserved_2_01, reserved_2_02, reserved_2_03, reserved_2_04, TEMPSENSE0, TEMPSENSE1, OSC16ERR3V, OSC16ERR5V, OSC20ERR3V, OSC20ERR5V, reserved_3_05, reserved_3_06, reserved_3_07, reserved_3_08, reserved_3_09, reserved_3_10, reserved_3_11, reserved_3_12, reserved_3_13, reserved_3_14, reserved_3_15, reserved_3_16, reserved_3_17, reserved_3_18, reserved_3_19, reserved_3_20, reserved_3_21, reserved_3_22, reserved_3_23, reserved_3_24, reserved_3_25, reserved_3_26, reserved_3_27, reserved_3_28, SIGROW_CHECKSUM0, SIGROW_CHECKSUM1
   They're fiest to make it Easier to fill those in from tuning data - though it may be possible to deduce the tuning by calculaqting the terms of the polynomioal line of bext firt and using that
   */
  Serial.println();
  #if defined(MEGATINYCORE)
    if ((FUSE.OSCCFG == 1)){
      Serial.print(MaxCal);
      Serial.print(",,,,,,");
    } else {
      Serial.print(',');
      Serial.print(MaxCal);
      Serial.print(",,,,,");
    }
    #endif
    for ( byte m = 0; m<64; m++) {
      if (ROWCONTENTS[m] != 0xFF) {
        Serial.print(ROWCONTENTS[m]);
      }
      Serial.print(',');
  }
  while(1);
}
