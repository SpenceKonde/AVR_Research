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
e = oscillator error (not consistently documented,  but same as 0/1-series) - Maybe not anymore! The 3224's I've checked have all reported 0xFF for 
       all 4. oxFF could be -1, or it could be just blank. My money is on the latter. 
o = oscillator calibration values loaded at startup for internal HF.
u = oscillator calibration values loaded at startup for internal 32kHz osc.

v = this value is always 0xFF on the ATtiny1624 - at least the ones I have. On the 3216, these are not 0xFF.

z = checksum (suspected, based on appearances and the reference in iotn1626.h to SIGROW_CHECKSUM1 being located at offset 0x2f. 
    0x2f is 0xff on all parts I checked, so it wouldn't be much of a checksum, so I think they meant 0x3f. Named like that,
    it implies that the previous byte is SIGROW_CHECKSUM0 - and this does look like a 2-byte checksum if I've ever seen one.

```
The SIGROW on DX-series parts is boring There's nothing there except what they say in the datasheet! Maybe there is information hidden elsewhere.... LAAAAAAAAAME!


### OSCERR notes:
* Average value for 16 MHz was around 1 (-3-5 and -4-5 range at 3 and 5 V observed). Average magnitude 2.65, 2.68. 62% of samples had the same value for 3V and 5V
* Average for 20 was about 1/2 at 3V, but -0.4 at 5V  (-5-5 and -6-4 range at 3 and 5 V observed). Average magnitude 2.10 and 1.97. Only 17% of samples had the same value for 3V and 5V
  * Both are totally consistent with observed step size at the region of interest of 0.92% of the target frequency, and consistent with the assumption that the programmed error value is correct. (ie, it will be recorded as -4 only when 1020/1024 * F<sub>target</sub> is closer to the target speed than 1019/1024 and 1021/1024)
* Interesting that the error set to 16 MHz skews high by almost exactly 1 on average, while it skews high at 3V and low at 5V running at 20 MHz. Do keep in mind that this is the difference between the frequency of the oscillator at the factory cal value and the target frequency, in 1/1024ths. 
  * One would expect the average to be 0 - that is, that if I averaged internal oscillator speeds of a sample of N processors, as sample size N approached infinity,  lim F<sub>CPU</sub> = F<sub>target</sub>. There seems to be a trend contrary to this, though a larger sample size is needed to draw firm conclusions.  
* The comparison between error terms at the two voltages is valuable, since the calbyte stays constant as the voltage is varied. This is hence a probe of the voltage dependance of the oscillator.
  * That dependence is **really fucking small**. The F/V curve between 3v and 5v is *damned near a horizontal line.*
  * The error term for the 16 MHz oscillator at 5V was never lower than at 3v. Difference was never larger than 1. This implies that *between 3V and 5V, the speed of the 16 MHz oscillator increases by, at most, about a tenth of 1%*. For the 20 MHz, a very small number of ones where the value at 20 was lower by 2. So the frequency drifts up ever so slightly at higher voltages. The V dependence is orders of magnitude smaller than classic AVRs! 
  * Every sample with the same error term at 3V and 5V with 20 MHz, had the same error term for the two voltages at 16 MHz. This was not expected - it implies that it is a process variable that is imperfectly controlled which determines the magnitude of dF/dV, and that some chips have flatter curves than others. 


Any time when a process is sorting objects based on a continuously variable property into discrete buckets, as is happening w/rt osc calibration and error values, it is always worth noting if the distribution is or is not uniform and whether, and looking for correlations between which buckets leaks information about both the cal process and the chip itself. 

## Mysteries:

### What is the significance of the two constants? 
One is not present at all on 1-series, while the other is very similar, but takes different value, and they have strange values with lots of 0's or 1's in a row. 

They look almost like.... bitmasks of some sort. 

I reckon that's what they are, and if you forced me to make a wager on it, i'd say that they have something to do with telling the part what pincount it has (since we know that is not set in silicon, since they use the same die for all 3 pincounts on the 2-series. On DA/DB, the 48/64 pin parts get one die and the 28/32 pin ones get a different die, while on DD the 14/20 pin parts get the small die annd the others the large die. In most cases, each flash size gets it's own die. tiny2 may have same die for 8 and 4k parts. 

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

Maximum frequency attained while overclocking before crash is known and was measured for the same parts, and we know they do testing on them to make sure they function at rated speeds. Perhaps something is written which relates to whether it is binned as an F-spec or N/U-spec? I'd love to know that if so! The extended temperature range overclocks better; on Dx-series - 40 and even 48 MHz is within reach, and the E-spec overclocks better. I've turned to marking the parts with nail-polish or solder mask, because there are no longer any marking differences. The temperature grade is marked on tinyAVR 0/1-series, but not on Dx or 2-series. I have complained to Microchip about this and they did not provide any enlightenment, other than to offer to ID parts based on the lot numbers `*`) If that is related to these bytes though, it doesn't show in this data.

For the constants, more data is required; I have a feeling that the E0 F8 pair select what features are enabled. 
Imagine that the three versions were all manufactured from the same design and contain the same dies, and they just used different packages and numbers of pins. If that is the case, it should be possible to decode at least one of these values into a pincount... It also wouldn't be surprising that there would be the public-consumption ID (in the 3 byte device ID, the middle byte is the flash size, and the last is sequential in order of releases for each flash size) and an internal representation which said what groups of pins to turn on. If this is the case, you would see three values depending on pincount. It would probably be easier to implement if the there was a bit for each group of pins, ie, the 20 pin parts have 1 extra bit set 1, the 24 pin parts have 2, and the 8-pin, if they existed, one fewer - thus producing the pattern seen in those two values when represented in binary.

We don't know whether any two sizes of flash for the 2-series share a die (it looks like the 2k and 4k 0/1-seriees parts shared a die, based on how the errata groups them, and we know that other sizes do not (different die revision). It is possible that on the 16k 2-series parts, the pincounts all have the same die inside, and would make sense based on how the datasheet groups by the flash size instead of pincount.... and it would give them more flexibility to distribute production between different pincounts, and the cost (in terms of semiconductor fab resources 

In any event, with even a tiny sample of parts from each part number, we should be able to disprove this theory - though not prove it right.

Another route towards learning about the dice involved would be to take, say, a 214, 414, 814, and 1614, mount them all on a PCB then file off the package and compare the sizes. (to take the really beautiful die photos, you need an electron microscope and you need to decap using fuming nitric acid, and the chip should be heated to 150C. Process is said to be quite fast. Filing away the package gets you the size but that's it.

## Footnotes

`*` This is difficult to rationalize. We know that the net effect is to bestow opportunities for easier deception by Microchip or middlemen in the industry (Imagine a turnkey PCBA provider who switched all the high temperature parts specified for cheaper low temperature ones, while still billing the customer for the F-spec parts - they'd never get off without being noticed if the parts were marked unless they went to the trouble of altering the markings on the chip (though they picked I and E as the temperature ranges for Dx-series, likely to match the rest of Microchip's products. Unfortunately, that means that even if it were marked, it would be easy for fraudulent sellers to alter the markings: you can turn an I into an E by adding lines. Changing a U into an F or N, or an N into an F is harder. It's not implausible, of course - we know that people find it worthwhile to grind the markings off of ATtiny13's, remark them at ATtiny85's and sell them as that (that's why you shouldn't buy AVR's on aliexpress `**`). The VAO parts use B/Z which have the same property as F/N and F/U in terms of being difficult to alter into eachother. The F/N/U (FUN?) lettering for tinyAVR seems to pre-date the 2016 revolution, corresponding to -40 to either 85C ("Industrial") (U), 105C (whichever term the other bin doesn't use) (N) or 125C ("Extended") (F) on classic AVRs too, most o; the 105C ("Industrial") (I) and 125C ("Extended") (E)  

`**` Aliexpress is kind of like a slot machine. When you "win" you get a discount on things, but sometimes you get garbage instead, and you never know for sure if the parts are legit. Any knockoff can be arbitrarilly similar and remain undetected - if it remains undetected forever because it is so similar that it performs equivalently, that's no big deal. So you get 1 of 5 possible results:
1. The item is legitimate and you save money. Win. 
2. The item is a very good fake that performs equivalently in your application and you save money (generally more than in case 1). Win.
3. The item is a very poor fake that is immediately obvious. Wager is lost, and perhaps a small additional sum lost in things paired with the first bad part used, at which point the issue is detected. (For example, the ATtiny13's remarked at 85's appear to be legitimate until you attempt to program them, and they report that they are ATtiny13's).
4. The item is a marginal fake, which fools the immediate analysis such that it is put into service in quantity, and the problem is only later discovered. Wager is lost, but you additionally lose a significant quantity of parts it was used with before the issue was detected. This is typical of knockoffs which were meant to perform equivalently, but manufactured shoddily, ending up with a shorter service life, worse performance under adverse conditions or improperly handled corner cases, as well as garbage that was never intended to fool anyone longer than it took to make the sale, but which is sometimes convincing enough (or testing lax enough) to be put into use and discovered later (think of the not-unusual example controllers for large SD memory chips, paired with much smaller memory, with the remaining address lines left floating - so it works until you fill the smaller device, and then everything falls over - someone who just threw it into a reader and copied a small file to it would be fooled, or wire marked with and sold as having an AWG rating typically 4 gauge larger than the wire's actual size - *with the insulation thickened to make up the difference*. (the latter is almost ubiquitous in Chinese PVC-insulated wire, which is typically 4 AWG undersize, but varies from 1 to 8 AWG undersized. FEP insulated wire on the other hand, while more expensive, is better wire in general, and is, IME, at most 1 AWG undersize).
6. The item is an exceptional fake, which while it will substitute for the original in most cases, the reverse is not true: The fakes are better than the originals!. Hence, if one designs for the superior fakes, the system may end up working only with those fakes, which (since they were mis-sold) may be hard to locate to re-order when a later order comes out as the genuine, but inferior article. Those will initially be assumed to be type 3 or 4 items, and only after considerable analysis is it recognized that the genuine part cannot perform as required. Several examples of this can be found among addressable LEDs (which have been copied by dozens of companies - who are generally re-implementing the controller to copy the advertised behavior; the original APA102 achieved the global dimming by combining two PWM signals; a clone of it used a constant current soruce, greatlyreducing situations in which the flicker is observable. 

It's hard to classify the final category as either win or loss - they're not a loss, not if the clone is better than the original and cheaper (like the LEDs mentioned earlier). Another example, the WenTai organizer bins - the brand name ones are of poor manufacturing quality, and the lids are sometimes broken upon arrival). But when you need to reorder, the supply may have vanished. 
