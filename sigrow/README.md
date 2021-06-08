# Secrets of the SIGROW
On 21 ATtiny1624's being prepared for sale by tuning, sigrow contents were logged. See the other files in this directory. The structure appears to be as follows:


```
iiiiiicccccccccc ccssssssss**????
??******uu??vvvv oooooooovvvvbbbb
tttteeeeeeee**** aaaaaaaaaa******
**************** ************zzzz


i = device id: 1E942A
a = unknown constant: AEF4E3FC1F. These bytes are all 0xFF on 1-series.
b = unknown constant: E0F8. 0b11100000 0b11111000. These bytes are EFF8 on the 3216.
c = constant portion of serial: 3041374134
s = non-constant portion of serial number

t = temp. sensor cal
e = oscillator error (not consistently documented,  but same as 0/1-series)
o = OSCCAL values for internal HF.
u = OSCCAL 32k (per io header)

v = this value is always 0xFF on the ATtiny1624 - at least the ones I have. On the 3216, these are not 0xFF.

z = checksum (suspected, based on appearances and the reference in iotn1626.h to SIGROW_CHECKSUM1 being located at offset 0x2f. 
    0x2f is 0xff on all parts I checked, so it wouldn;t be much of a checksum, so I think they meant 0x3f. Named like that,
    it implies that the previous byte is SIGROW_CHECKSUM0 - and this does look like a 2-byte checksum if I've ever seen one.

```

## Mysteries:

### What is the significance of the two constants? 
One is not present at all on 1-series, while the other is very similar, but takes different value. 
#### What values do they take on other parts?

### What are the four mystery bytes? 
They do not vary much:

0x0E = 0x3E-47
0x0F = 0x0C, 0x0D, or 0x0E
0x10 = 0x05, 0x06, or 0x07
0x15 = 0x05, 0x06, or 0x07 (not the same as 0x10). Present on the 1-series too, along with it's adjacent OSCCAL32k byte. Likely related. 

There are two fields of 2 bytes each that are present on the 3216 that aren't present here (and likely the same is true of the rest of the 2-series and 1-series, but that remains to be verified)
