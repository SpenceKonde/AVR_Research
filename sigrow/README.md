# Secrets of the SIGROW
On 21 ATtiny1624's being prepared for sale by tuning, sigrow contents were logged. See the other files in this directory. The structure appears to be as follows:

I've added a sketch that you can run on any tinyAVR or Dx-series (I think) which will spit out on USART0 at 115200 baud the full sigrow contents. It's all empty except for what the datasheet says. 
We'll stick to the more interesting tinyAVR sigrow. 

There is now a sketch on here that lets you gather data - and even send it to me! (that would be lovely, Just the CSV lines is fine, that contains all the knowledge it can extract).



```
iiiiiicccccccccc ccssssssss**????
??******uu??vvvv oooooooovvvvbbbb
tttteeeeeeee**** aaaaaaaaaa******
**************** ************zzzz


i = device id: 1E942A
a = unknown constant: AEF4E3FC1F. Confirmed on 3224;. These bytes are all 0xFF on 1-series. 10101110 11111000 11100011 11111100 00011111
b = unknown constant: E0F8 on 1624's and 3224's. 0b11100000 0b11111000. These bytes are EFF8 on the 3216, which is 0b11101111 0b11111000
    These are rather striking in binary. Highly suggestive that they are a bitmask of some sort. Will be interesting 
    to compare between parts. I have some guesses... 
c = constant portion of serial over this small sample: 3041374134
s = non-constant portion of serial number

t = temp. sensor cal
e = oscillator error (not consistently documented,  but same as 0/1-series) - Maybe not anymore! The 3224's I've checked have all reported 0xFF for all 5. oxFF could be -1, or it could be just blank. 
o = OSCCAL values for internal HF.
u = OSCCAL 32k (per io header)

v = this value is always 0xFF on the ATtiny1624 - at least the ones I have. On the 3216, these are not 0xFF.

z = checksum (suspected, based on appearances and the reference in iotn1626.h to SIGROW_CHECKSUM1 being located at offset 0x2f. 
    0x2f is 0xff on all parts I checked, so it wouldn't be much of a checksum, so I think they meant 0x3f. Named like that,
    it implies that the previous byte is SIGROW_CHECKSUM0 - and this does look like a 2-byte checksum if I've ever seen one.

```
The SIGROW on DX-series parts is boring There's nothing there except what they say in the datasheet! Maybe there is information hidden elsewhere.... LAAAAAAAAAME!


### OSCERR notes:
* Average value for 16 MHz was around 1 (-3-5 and -4-5 range at 3 and 5 V observed). Average magnitude 2.65, 2.68. 62% of samples had the same value for 3V and 5V
* Average for 20 was about 1/2 at 3V, but -0.4 at 5V  (-5-5 and -6-4 range at 3 and 5 V observed). Average magnitude 2.10 and 1.97. 17% of samples had the same value for 3V and 5V
  * Both consistent with observed step size at the region of interest of 0.92% of the target frequency. We would expect then for the to be evenly distributed within a range spanning about 9 from the most negative to most positive. 
* Interesting that the error set to 16 MHz skews high by almost exactly 1 on average, while it skews high at 3V and low at 5V running at 20 MHz. Do keep in mind that this is the difference between the frequency of the oscillator at the factory cal value and the target frequency, in 1/1024ths. 
  * One would expect the average to be 0 - that is, that it will assign values slightly too low equally often compared to 
* The comparison between error terms at the two voltages is more meaningful, since the calbyte stays constant as the voltage is varied. This is hence a probe of the voltage dependance of the oscillator.
  * That dependence is really small. The F/V curves are very flat in the 3V-5V regime! 
  * The error term for the 16 MHz oscillator at 5V was never lower than at 3v. Difference was never larger than 1. This implies that between 3V and 5V, the speed of the 16 MHz oscillator increases by, at most, about a tenth of 1%. For the 20 MHz, a very small number of ones where the value at 20 was lower by 2. So the frequency drifts up ever so slightly at higher voltages. The V dependence is orders of magnitude smaller than classic AVRs! 
  * Every sample with the same error term at 3V and 5V with 20 MHz, had the same error term for the two voltages at 16 MHz. This was not expected. 

The first oddity - 16 MHz skewing high and 20 MHz, and by the same amount at 3 and 5, versus in opposite directions at 3 and 5 is easy to rationalize - the cal machine is taking into account a whole range of V and T. If the center of the voltage range or temperature range was not in the center of the frequency distribution, that'd what we would expect to find.

The second one is harder to explain. With a larger sample size the correllation may vanish. If they remain correllated, that wouldn't be surprising either - maybe a chip with "good" oscillators comes out with a shallower F/V curve. But the cal process is sorting objects based on a continuously variable property into discrete buckets... It *is* worth noting that the distribution is not uniform though!

## Mysteries:

### What is the significance of the two constants? 
One is not present at all on 1-series, while the other is very similar, but takes different value, and they have strange values with lots of 0's or 1's in a row. 

They look almost like.... BITMASKS

#### What values do they take on other parts?
This is unknown to me. 

### What are the four mystery bytes? 
They do not vary much, over a sample of 28 parts 1624's

0x0E = 0x3E-47
0x0F = 0x0C, 0x0D, or 0x0E
0x10 = 0x05, 0x06, or 0x07
0x15 = 0x05, 0x06, or 0x07 - Present on the 1-series too, along with it's adjacent OSCCAL32k byte. Related?

There seems to be little correllation between them.
0x10 and 0x15 may be correllated, but size of sample for which that was examined too small to know. The others are almost certainly not

There are two fields of 2 bytes each that are present on the 3216 that aren't present here (and likely the same is true of the rest of the 2-series and 1-series, but that remains to be verified)

And there are 4 single byte fields on the 2-series absent from the 1's 

The first varies from 0x3E (62) to 0x47 (71) in the sample, suggestive of A variation around a value that is nominally 64. 

The remaining 3 are completely opaque... What else varies between specimens? 

Maximum frequency attained while overclocking before crash is known and was measured for the same parts, and we know they do testing on them to make sure they function at rated speeds. Perhaps something is written which relates to whether it is binned as an F-spec or N-spec? I'd love to know that if so! The extended temperature range overclocks better; on Dx-series - 40 and even 48 MHz is within reach, and the E-spec overclocks better. I've turned to marking the parts with nail-polish, because there don't seem to be any marking differences ) If that is related to these bytes though, it doesn't show in this data.

For the constants, more data is required; I have a feeling that the E0 F8 pair select what features are enabled. 
Imagine that the three versions were all manufactured from the same design and contain the same dies, and they just used different packages and numbers of pins. If that is the case, it should be possible to decode at least one of these values into a pincount... It also wouldn't be surprising that there would be the public-consumption ID (in the 3 byte device ID, the middle byte is the flash size, and the last is sequential in order of releases for each flash size) and an internal representation which said what groups of pins to turn on. If this is the case, you would see three values depending on pincount. It would probably be easier to implement if the there was a bit for each group of pins, ie, the 20 pin parts have 1 extra bit set 1, the 24 pin parts have 2, and the 8-pin, if they existed, one fewer - thus producing the pattern seen in those two values when represented in binary.

We don't know whether any two sizes of flash for the 2-series share a die (it looks like the 2k and 4k 0/1-seriees parts shared a die, based on how the errata groups them, and we know that other sizes do not (different die revision). It is possible that on the 16k 2-series parts, the pincounts all have the same die inside, and would make sense based on how the datasheet groups by the flash size instead of pincount.... and it would give them more flexibility to distribute production between different pincounts.

In any event, with even a tiny sample of parts from each part number, we should be able to disprove this theory - though not prove it right.
