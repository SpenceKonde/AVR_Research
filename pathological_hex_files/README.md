# Pathological Hex Files
For research, debugging, test, and development purposes, we present for your enjoyment a number of bizarre hex files. These are typically files that no compiler or assembler would generate - I made them as raw hexadecimal numbers from a python script as noted for Threes. 

## Threes (LED blink only works on modern AVRs - behavior on classic AVRs is a crap shoot)
Threes consists of a hex file made up of (almost) entirely 0x3333, in a number of sizes. The point is that it has a bitpattern of 0b00110011. This stands out like a sore thumb on a 'scope trace, whether you're writing it via ISP or UPDI. The main point is to be able to see on the screen whether it's sending data or control at a given point - and as no-nonsense way to make hex file that fills every last byte of flash. At the very start it decrements r3 sets PA7 to output and then if a bit in r3 (varies depending on the size of the flash, and hence how long it takes to go through the whole flash) is set, set PA7 high, else set it low. 0x3333 is cpi r3, 0x33, which compares the value of register 3 with the value 0x33 without changing anything. 

Execution sides along these do-nothing comparisons until it wraps around, decrements the register, and possibly toggles a pin. Rinse repeat, so it generates a fairly fast blinking pattern so you can know that it is running code. 

These files are not designed for use with a bootloader, either on modern or classic AVRs, but appropriate files could easily be generated. 

It assumes that the output register is at at 1 and direction register at 0. If that is not the the case (for example on many classic AVRs) they need those instructions modified if you want the blink to work. They can still be used to test uploads though. 

## test_hex_start_not_zero.hex
Made for debugging a suspected problem with an upload tool that was suspected of ignoring the instructions of the hex file and starting every upload from 0x0000, breaking on modern AVRs since they have files that start at 0x200 and would fail to write the first 512b. This and the padded blink can be used used to verify that this was the problem as opposed to it failing to correctly tell the bootloader the address to start from. 

```python
from intelhex import IntelHex
ih = IntelHex()

ih[0x200]=0xFF # rjmp back and retrigger the bootloader
ih[0x201]=0xCE # 0xCEFF = rjmp .-514 (jump back 257 words)
ih[0x202]=0xFE # and again, in case the 0xFFFF sled jumps over it
ih[0x203]=0xCE # 0xCEFE = rjmp .-516 (jump back 258 words)
for x in range(0x202, 0x401):
    ih[x]=0x00 # bulk it up with a bunch of nop's 
ih[0x400]=0x00 # unnecessary precaution (defend against 0xFF immediaely preceeding this potentially skipping) 
ih[0x401]=0x00 # nop
ih[0x402]=0x07 # set PA7 output
ih[0x403]=0x9A # sbi 0,7
ih[0x404]=0x0F # set PA7 high
ih[0x405]=0x9A # sbi 1,7
ih[0x406]=0xFF # and hang
ih[0x407]=0xCF # rjmp .-2 
for x in range(0x407, 0x822):
    ih[x]=0x00 # bulk it up with a bunch of nop's 
ih.write_hex_file('test_hex_start_not_zero.hex')
# Upload via optiboot. Observe the device.

# Pass: 
# On a freshly bootloaded classic AVR it should do nothing. 
# On a freshly bootloaded **modern** AVR, it should repeatedly enter the bootloader and generate the triple-blink. 

# Failure: 
# On a classic: repeatedly run the bootloader. 
# on a modern AVR: write pin PA7 high and do nothing further. 

# Under examination when you dump the flash, you should see:
# Modern AVR - data up to 0x204, then a bunch of 0's, 6 more bytes 512b further in, then 0's up until just past the 2k mark
# (0x22 bytes after specifically) - the point of this is just to bring out any failures to write all pages). 

# Classic AVR - EMPTY flash (0xFF) up to 0x200. 2 instructions, then a bunch of 0's, then another 4 bytes, then 0's up to 0x822. 
```

## padded_blink.4809.hex
Another test file for the above issue. You're smart folks, I'm sure you can figure out what this is. 
