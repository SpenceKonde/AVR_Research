These are files intended for testing of programming devices and techniques for AVR microcontrollers. The pattern of 3's assists in identification data going to or coming from the flash, as opposed to commmands. There are only a dozen non 0x33 bytes in here, at the start; they were generated with the python intelhex library. as shown below.

Connect an LED w/series resistor between PA7 and either groumnd or the positive supply rail (makiing sure polarity is appropriate)
The 6-word program does the following: Set direction of PA7 to output. Decrement r19 (it never initializes it, but it's the only code running - it's just being used to "prescale" the "clock" (see below). Then, there is a pair of complementary sbrs/sbrc, each o


```python
from intelhex import IntelHex
ih = IntelHex()

ih[0]=0x07 # sbi VPORTA.DIR, 7
ih[1]=0x9A
ih[2]=0x3A # decrement r3
ih[3]=0x94
ih[4]=0x33 # sbrs r3, 3
ih[5]=0xFE
ih[6]=0x0F # sbi VPORTA.OUT, 7
ih[7]=0x9A
ih[8]=0x33 # sbrc r3, 3
ih[9]=0xFC
ih[10]=0x0F # cbi VPORTA.OUT, 7
ih[11]=0x98
for x in range(12,131072):
    ih[x]=0x33
ih.write_hex_file('threes_128k.hex')

```


```python
from intelhex import IntelHex
ih = IntelHex()

ih[0]=0x07 # sbi VPORTA.DIR, 7
ih[1]=0x9A
ih[2]=0x3A # decrement r3
ih[3]=0x94
ih[4]=0x35 # sbrs r3, 5
ih[5]=0xFE
ih[6]=0x0F # sbi VPORTA.OUT, 7
ih[7]=0x9A
ih[8]=0x35 # sbrc r3, 5
ih[9]=0xFC
ih[10]=0x0F # cbi VPORTA.OUT, 7
ih[11]=0x98
for x in range(12,131072):
    ih[x]=0x33
ih.write_hex_file('threes_32k.hex')
```


```python
from intelhex import IntelHex
ih = IntelHex()

ih[0]=0x07 # sbi VPORTA.DIR, 7
ih[1]=0x9A
ih[2]=0x3A # decrement r3
ih[3]=0x94
ih[4]=0x36 # sbrs r3, 6
ih[5]=0xFE
ih[6]=0x0F # sbi VPORTA.OUT, 7
ih[7]=0x9A
ih[8]=0x36 # sbrc r3, 6
ih[9]=0xFC
ih[10]=0x0F # cbi VPORTA.OUT, 7
ih[11]=0x98
for x in range(12,131072):
    ih[x]=0x33
ih.write_hex_file('threes_16k.hex')
```
