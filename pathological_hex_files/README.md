# Pathological Hex Files
For research, debugging, test, and development purposes, we present for your enjoyment a number of bizarre hex files. These are typically files that no compiler or assembler would generate - I made them as raw hexadecimal numbers from a python script as noted for Threes. 

## Threes (LED blink only works on modern AVRs - behavior on classic AVRs is a crap shoot)
Threes consists of a hex file made up of (almost) entirely 0x3333, in a number of sizes. The point is that it has a bitpattern of 0b00110011. This stands out like a sore thumb on a 'scope trace, whether you're writing it via ISP or UPDI. The main point is to be able to see on the screen whether it's sending data or control at a given point - and as no-nonsense way to make hex file that fills every last byte of flash. At the very start it decrements r3 sets PA7 to output and then if a bit in r3 (varies depending on the size of the flash, and hence how long it takes to go through the whole flash) is set, set PA7 high, else set it low. 0x33 compares the value of register 3 with the value 0x33 without changing anything. 

Execution sides along these donothing comparisons until it wraps around decrements the register, and possibly toggles a pin. Rinsse repeat, so it generates a fairly fast blinking pattern so you can know that it is running code. 

These files are not designed for use with a bootloader, either on modern or classic AVRs, but appropriate files could easily be generated. 

It assumes that the output register is at at 1 and direction register at 0. If that is not the the case (for example on many classic AVRs) they need those instructions modified if you want the blink to work. They can still be used to test uploads though. 

## test_uploader.hex
Made for debugging a suspected problem with an upload tool that was suspected of ignoring the instructions of the hex file and starting every upload from 0x0000, breaking on modern AVRs since they have files that start at 0x200 and would fail to write the first 512b. This and the padded blink can be used used to verify that this was the problem as opposed to it failing to correctly tell the bootloader the address to start from. 
