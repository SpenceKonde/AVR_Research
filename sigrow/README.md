# Secrets of the SIGROW
On 21 ATtiny1624's being prepared for sale by tuning, sigrow contents were logged. See the other files in this directory. The structure appears to be as follows:

I've added a sketch that you can run on any tinyAVR or Dx-series (I think) which will spit out on USART0 at 115200 baud the full sigrow contents. It's all empty except for what the datasheet says.
We'll stick to the more interesting tinyAVR sigrow.

There is now a sketch on here that lets you gather data - and even send it to me! (that would be lovely, Just the CSV lines is fine, that contains all the knowledge it can extract).

## Current Summary
See below.

??? = Mystery
???? = Mystery (t0/t1 only)
~STRIKETHRU~ = No longer found on hardware in the wild.
**BOLD** = Has started featuring in SIGROWs only some time after original shipments started.

SER0~SER5 do not change within a given lot. These also have restricted ranges, or appear to.

### 2-series:

|  x  | 0x0x  | 0x1x    | 0x2x    | 0x3x
|-----|-------|---------|---------|------
|  0  | ID0   | ???     | TEMCAL0 | BLANK
|  1  | ID1   | BLANK   | TEMCAL1 | BLANK
|  2  | ID2   | BLANK   |~O16MER3~| BLANK
|  3  | Ser0  | BLANK   |~O16MER5~| BLANK
|  4  | Ser1  | O32KCAL |~O20MER3~| BLANK
|  5  | Ser2  | ???     |~O20MER5~| BLANK
|  6  | Ser3  | BLANK   | BLANK   | BLANK
|  7  | Ser4  | BLANK   | BLANK   | BLANK
|  8  | Ser5  | O16MCAL | 0xAE    | BLANK
|  9  | Ser6  | O16MCAL | 0xF4    | BLANK
|  A  | Ser7  | O20MCAL | 0xE3    | BLANK
|  B  | Ser8  | O20MCAL | 0xFC    | BLANK
|  C  | Ser9  | BLANK   | 0x1F    | BLANK
|  D  | BLANK | BLANK   | BLANK   | BLANK
|  E  | ???   | 0xEF    | BLANK   | CSC
|  F  | ???   | 0xF8    | BLANK   | CSC

* Oscillator error is not programmed on 2-series during factory cal except in some of the first batches that shipped.
* OSCCAL32K was listed on an early header version. Lowest value recorded 0x0D, highest value 0x18.
* There are four mysterious calibration-like values on the 2-series. All were present with similar values on the 0/1-series.
* There are two constants of unclear purpose
  * There is one mysterious two-byte constant, which differs in the corresponding bytes from the 0/1-series by 1 nybble.
  * There is one mysterious five-byte constant.

#### OSCERR notes:
* OSCERR, supplied on the 0/1-series at 3 and 5 volts and room temperature, was apparently dropped from the 2-series shortly after they started shipping, . This was done on the 2-series only briefly.
  * Average value for 16 MHz 2-series was around 1 (-3-5 and -4-5 range at 3 and 5 V observed). Average magnitude 2.65, 2.68. 62% of samples had the same value for 3V and 5V
  * Average for 20 MHz 2-series was about 1/2 at 3V, but -0.4 at 5V  (-5-5 and -6-4 range at 3 and 5 V observed). Average magnitude 2.10 and 1.97. Only 17% of samples had the same value for 3V and 5V
  * Both are totally consistent with observed step size at the region of interest: About 0.92% of the target frequency, and consistent with the assumption that the programmed error value is correct. (ie, it will be recorded as -4 only when 1020/1024 * F<sub>target</sub> is closer to the target speed than 1019/1024 and 1021/1024)
* Interesting that the error set to 16 MHz skews high by almost exactly 1 on average, while it skews high at 3V and low at 5V running at 20 MHz. Do keep in mind that this is the difference between the frequency of the oscillator at the factory cal value and the target frequency, in 1/1024ths.
  * One would expect the average to be 0 - that is, that if I averaged internal oscillator speeds of a sample of N processors, as sample size N approached infinity,  lim F<sub>CPU</sub> = F<sub>target</sub>. There seems to be a trend contrary to this, though a larger sample size is needed to draw firm conclusions.
* The comparison between error terms at the two voltages is valuable, even if you can't get parts with the error terms calculated any more, because it's reasonable to assume that Microchip has not abruptly downgraded their software.  since the calbyte stays constant as the voltage is varied. This is hence a probe of the voltage dependance of the oscillator, *using Microchip's data!*.
  * That dependence is **really fucking small**. The F/V curve between 3V and 5V is *damned near a horizontal line.*
  * The error term for the 16 MHz oscillator at 5V was never lower than at 3v. Difference was never larger than 1. This implies that *between 3V and 5V, the speed of the 16 MHz oscillator increases by, at most, about a tenth of 1%*. For the 20 MHz, a very small number of ones where the value at 20 was lower by 2. So the frequency drifts up ever so slightly at higher voltages. The V dependence is orders of magnitude smaller than classic AVRs!
  * Every sample with the same error term at 3V and 5V with 20 MHz, **had the same error term for the two voltages at 16 MHz**. This was not expected and is very surprising! This implies that it is an imperfectly controlled process variable that determines the magnitude of dF/dV (as opposed to there simply being variation between the two oscillators). It further strengthens the theory (already supported by the V vs Cal curves, which Excel can generate a quadratic best fit line for, and get error bars too small to see) that one could potentially predict the cal settings that would give a desired speed *a priori* from just the calbytes.
* It's too bad

### 0/1-series

|  x  | 0x0x  | 0x1x    | 0x2x    | 0x3x
|-----|-------|---------|---------|------
|  0  | ID0   | ???     | TEMCAL0 | BLANK
|  1  | ID1   | BLANK   | TEMCAL1 | BLANK
|  2  | ID2   | BLANK   | O16MER3 | BLANK
|  3  | Ser0  | BLANK   | O16MER5 | BLANK
|  4  | Ser1  | O32KCAL | O20MER3 | BLANK
|  5  | Ser2  | ???     | O20MER5 | BLANK
|  6  | Ser3  | ????    | BLANK   | BLANK
|  7  | Ser4  | ????    | BLANK   | BLANK
|  8  | Ser5  | O16MCAL | BLANK   | BLANK
|  9  | Ser6  | O16MCAL | BLANK   | BLANK
|  A  | Ser7  | O20MCAL | BLANK   | BLANK
|  B  | Ser8  | O20MCAL | BLANK   | BLANK
|  C  | Ser9  | ????    | BLANK   | BLANK
|  D  | BLANK | ????    | BLANK   | BLANK
|  E  | ???   | 0xE0    | BLANK   | **CSC0**
|  F  | ???   | 0xF8    | BLANK   | **CSC1**


* OSCCAL32K was never listed officially in any capacity.
  * Nonetheless, it takes the same values on tiny 0/1-series as the 2-series, and is virtually certain to have the same function.
  * Note that I don't think this register is accessible to user code.
* There are 8 mysterious calibration-like values on the 0/1-series.
* There are no readilly apparent differences between 0-series and 1-series sigrows.
* There is one mysterious two-0yte constant, which differs in the corresponding bytes from the 2-series by 1 nybble.
* Oscillator error is programmed on all 0/1-series parts during factory cal.


## Dx and Ex series
The SIGROW on Dx/Ex-series parts is boring. There's nothing there except what they say in the headers! Maybe there is information hidden elsewhere... In the case of the DB-series, we *know* they are hiding 2-3 values *somewhere* because they state that they have factory cal values for the OPAMP are loaded at startup!
Any time when a process is sorting objects based on a continuously variable property into discrete buckets, as is happening w/rt osc calibration and error values, it is always worth noting if the distribution is or is not uniform and whether, and looking for correlations between which buckets leaks information about both the cal process and the chip itself.

It's also boring because, like, they told us the contents - unlike the tinyAVRs, they seem to have hidden anything of interest.

 | x | 0x0x  | 0x1x                     |  0x2x | 0x3x
 |---|-------|--------------------------|-------|------
 | 0 |   ID0 | SER  0 LOTNUM0           | BLANK | BLANK
 | 1 |   ID1 | SER  1 LOTNUM1           | BLANK | BLANK
 | 2 |   ID2 | SER  2 LOTNUM2           | BLANK | BLANK
 | 3 | BLANK | SER  3 LOTNUM3           | BLANK | BLANK
 | 4 |TEMP   | SER  4 LOTNUM4           | BLANK | BLANK
 | 5 | SENSE0| SER  5 LOTNUM5           | BLANK | BLANK
 | 6 |TEMP   | SER  6 RANDOM            | BLANK | BLANK
 | 7 | SENSE1| SER  7 SCRIBE            | BLANK | BLANK
 | 8 | BLANK | SER  8 XPOS0             | BLANK | BLANK
 | 9 | BLANK | SER  9 XPOS1             | BLANK | BLANK
 | A | BLANK | SER 10 YPOS0             | BLANK | BLANK
 | B | BLANK | SER 11 YPOS1             | BLANK | BLANK
 | C | BLANK | SER 12 RESERVED 0        | BLANK | BLANK
 | D | BLANK | SER 13 RESERVED 1        | BLANK | BLANK
 | E | BLANK | SER 14 RESERVED 2        | BLANK | CSC0?
 | F | BLANK | SER 15 RESERVED 3        | BLANK | CSC1?

Not much of not there.

## Mysteries:

### What is the significance of the two constants?
Seems less potentially interesting than it might have been, as it is uniform across the entire series.

`10101110'11110100'11100011'11111100'00011111`

`00011111'11111100'11100011'11110100'10101110`


and `11101111'11111000` or `1110000'11111000`

           | All 2-series| All 0/1-series? |
-----------|-------------|-----------------|
Constant A | AEF4E3FC1F  |      FFFFFFFFFF |
Constant B |       EFF8  |            E0F8 |


### What is the structure of the Serial Number?
It certainly provides markedly less entropy than would be expected from it's length.

There are 10 bytes of serial number
* Six bytes are typically the same when multiple parts are bought at the same time.
  1. Only 3 values recorded, 0x32, 0x30, and 0x51. All 2-series parts were recorded with 0x30.
  2. 7 values recorded: 0x41, 0x42, 0x43, 0x4B, 0x4D, 0x50, 0x50, 0x51,
  3. 8 values recorded: 0x33, 0x37, 0x41, 0x42, 0x48, 0x4D, 0x50, 0x53,
  4. 8 values recorded: 0x33, 0x38, 0x41, 0x43, 0x46, 0x4B, 0x4E, 0x53, 0x54,
  5. 11 values recorded: 0x32, 0x33, 0x34, 0x35, 0x38, 0x39, 0x43, 0x4B, 0x4C, 0x51, 0x53,
  6. 6 values recorded: 0x20, 0x30, 0x32, 0x38, 0x43, 0x45, 0x49,
* The fact that **all of the digits of the lot number are ASCII alphanumerics (uppercase) plus spaces** (last byte only) probably is not a coincidence.
  * Hence, the first 48 bits of the lot number will following production of around 2.1 billion (36^6) lots (I don't know how many chips are in a lot, but I gather that it's a lot. A lot at minimum is likely one wafers worth right? )
* Four which are different between parts in a lot
  * One which seems to run from very low to very high, but for each lot, may take as few as 8 values. Not only that, but only the high nybble changes; my large lot of 1624's have hexadecimal values where the first nybble is even and the second is C, and I got a bunch of sigs from 3217's that had odd first nybbles and 3 in the second. Different lots of the same part may have different patterns, though. Much larger sample sizes needed. I have a second batch of 1624 that can be processed.
    * Patterns are evenly spaced. Odd. Perhapse comparison with Dx-series value in the lot number which show similar distribution will be found, As shown above, we have names for those,
    * The serial number has not only been lengthened by 2 bytes, it has clearly been reordered, as they have a "Random" bit in the first post-lot-number serialnumber byte, while we have that wierd thing that seems to have only 8 values per lot, and random after that.
  * one 8-bit integer, appears to be totally random
    * If I have a bunch of parts in the same lot (I do) and I were to run enough of them, I'm virtually guaranteed to get a duplicate if I run enough samples (at most, 256 could be required, but the liklihood of that is 256 )
  * Two values which have not been seen exceeding 0x58 (0x5F likely the maximum), number of unique values out of 43 samples consistent with 0-0x5F or 0x58.
  * None of these are consistent with alphanumerics - these are binary, not ascii.
* Distribution of nybbles in the serial number portion shows very strong bias.



### What are the mystery bytes?
They do not vary much, and are heavily biased. That's gotta be a cal of some sort. The four on the 2-series were also were present on the 0/1-series, taking similar values. The 0 and 1-series had 4 additional mystery bytes.


* On both tiny 0/1 and tiny2:
  * 0x0E = 0x3D-47. 0x40 and 0x41 comprise half of the samples. The remaining 10 values split the rest approximately evenly.
  * 0x0F = 0x0C, 0x0D, 0x0E, 0x0F, or 0x10. 0x0E is the most common by a significant margin. May be a bias towards 0x0C and 0x0D over 0x0F and 0x10.
  * 0x10 = 0x05, 0x06, or 0x07. Ratio is about 1:1 between 05 and 06. 07 is probably a few percent.
  * 0x14 = Not a mystery, OSCCAL32K, an undocumented calibration for the 32kHz internaloscillator.
  * 0x15 = 0x05, 0x06, 0x07, 0x08 or 0x09. 0x07 is the most common, followed by 0x06, 0x08, 0x05, ending on 0x09. 0x09 only observed on 1-series, but distribution otherwise similar.
* On tiny 0/1 only (Sample size insufficient to comment on rarity of these):
  * 0x16 = 0x13 through 0x27. Appears cal-like
  * 0x17 = 0x02, 0x03, 0x04, 0x05, 0x06 known.  Appears cal-like.
  * 0x1C = 0xD2 through 0xE3 recorded. Appears cal-like.
  * 0x1D = 0x03, 0x04, 0x05, or 0x06 recorded. Appears cal-like.


A "cal-like" value has several distinctive properties visible when it's distribution is examined.
1. The field has a strongly favored value.
  * Frequency of measuring a value other than the preferred value decreases with increasing difference from the preferred value
  * The shape of the distribuion sometimes shows discontinuities for some cal values at powers of two, particularly powers of two in the middle of the span.
  * The preferred values are often powers of two, or just above or below them, and when this is the case , observed values are usually "almost entirely" on the same side.
    * OSCCAL on 2-series has a preferred value of 0x21, with significant numbers of 0x20. Very few are below 0x20, though plenty are above it.
    * OSCTCAL on 2-series parts seems to have a large preference to 0x06.
      * Plugging values into TCAL and watching the speed showed that the high bit didn't matter at room temperature (ie, there were 8 speeds, then the same 8 speeds again. Either the present hardware ignores the high bit, or the high bit toggles something relevant only at elevated temperatures)
    * OSC32kTCAL on 2-series has a preferred value of 0x11, with 0x10 being less common.

I have suspicions about the mystery bytes; in order:
* Unknown cal value related to voltage references. Takes a value between 0x00 and 0x80, but values aroun 0x40 are by far the most common. I suspect 0x40 = 0.
* As above. except this one is much smaller in value, and likely does not have relavant sign to it.
* Destination of 0x10 unknown entirely, not made easier by the common values and limited variation.
* 0x15 is something clock-related, and very clearly a tuning value. Considering the low values- maybe TCAL for the 32k OSC?
* (following tinyAVR 0/1-series only)
  * Cal-like value centered at or just below 0x20.
  * Cal like value known only between 2 and 6
  * Cal-like value centered around 0xD8-0xE0
  * Another cal-like value sililar to 0x17, though only seen between 2 and 6.
  * I think the two pairs are for two instances of the same peripheral, based on the fact that the symmetry of observed values: One seems to be centered at 0x18ish, the other around 0xD8, which is 0x100-0x18
    * There are no peripherals which the 0/1-series have two of, yet the 2-series have 0 of.
    * Could this be associated with AC's and their DACREFs? Why then is it on 0's too? How could it be, they don't have those functions.... Unless the 0-series and 1-series are sharing dice? But the errata is different. So they're not.
    * There is not an unambiguouslty matching pair of mystery cal values.



I cannot rationalize why the 0-series would have extra calbytes like that. If they were only on the 0/1, I'd suspect it was to do with the DACREF.

Probably the two values betwen BOD and VREF are related to reference voltages. I imagine they'd need to trim it somehow. Though that doesn't explain why it's the same on the two series, even though the 2 uses good reference voltages and the 0/1 used terribad ones.

### OSCCAL notes
2-series, though same concepts apply to 0/1.

TCAL has 16 valid values. At room temperature, the high bit makes negligible difference. It probably does something at elevated temperature, or it's actually a reserved bit because they decided they didn't need that much cal range. Considering how little variation they use

Specifying F_CPU(N, M) where N is normal cal and M is tcal, at room temperature, andgiving clock speeds in Megahertz
* `F_CPU(X,A)/F_CPU(X,B) = F_CPU(Y,A)/F_CPU(Y,B)` to a very high degree of precision
* For constant M, `F_CPU(X,M) = a * X^2 + b * X + c`. Excel easily finds trendlines that have negligble error for any given chip.
  * a takes values on the order of 0.0001, with some chip-to-chip variation, and is smallest at low TCAL values and the 16 MHz clock.
  * c is determinable as the speed when set OSCCAL to 0.
  *
* OSCTCAL
* The TCAL levels are not spaced evenly. Particularly between 0 and 1 (or 8 and 9), there's a particularly large jump.
* At room temperature, no difference was observed between TCAL = M (where 0 <= M < 8) and TCAL = M + 8.

Early 2-series chips were shipping with a CRAZY oscillator cal range; these parts were capable of unreal overclocking out of the box (they would often *run* past 32 MHz!).
I suspect that as they got more data, they reduced the stringency of their testing process. See the before and after




Cal         | 0     | 1     | 2     | 3     | 4     | 5     | 6     | 7     |
------------|-------|-------|-------|-------|-------|-------|-------|-------|
OSCCAL = 0  |  8.07 |  8.74 |  9.19 |  9.53 |  9.81 | 10.11 | 10.34 | 10.57 |
OSCCAL = FF | 21.21 | 23.13 | 24.46 | 25.54 | 26.44 | 27.32 | 28.05 | 28.68 |
Range       | 13.14 | 14.39 | 15.27 | 16.01 | 16.63 | 17.21 | 17.71 | 18.11 |

Notice that the ratio if the minimum and maximum speeds is essentially constant.


There are strong correlations between the 16 MHz and 20 MHz cals:
* OSC16CAL and OSC20CAL are tightly correlated.
* When TCAL is considered, correlations even stronger:
  * 21/30 parts showed OSC16CAL exactly 1 greater than OSC20CAL. Every one of these showed the same TCAL value for 16 and 20 MHz.
    * Only chip with the same TCAL value didn't have a factory 16 MHz cal 1 higher than the 20 MHz cal, and on that one it was 2 higher.
  * All cases where OSC16CAL was more than 2 larger than OSC20CAL, OSC20TCAL was 1 lower than OSC16TCAL
  * In all cases where OSC16CAL was less that OSC20CAL, OSC20TCAL was 1 higher than OSC16TCAL
  * No parts with the same OSC16CAL and OSC20CAL were encountered, even though the most common values were the same.


#### Do we have any guesses on what the MCU does with them>
A few have been matched with low-numbered registers

Byte | Destination | Peripheral
-----|-------------|------------
0x0E | 0x0091      | Between BOD (0x80-0x8F) and VREF (0xA0-0xAF).   Not writable by user code.
0x0F | 0x0092      | Between BOD (0x80-0x8F) and VREF (0xA0-0xAF).  Not writable by user code.
0x10 | 0x0082      | Unknown  Not writable by user code.
0x14 | 0x0079      | CLKCTRL, OSCCAL32K Admitted by early datasheet to be OSCCAL32k (cal for the apx. 32 kHz ULP `* ` oscillator).   Writable with `_PROTECTED_WRITE()`
0x15 | 0x0075      | CLKCTRL. Maybe temp calibrpration for 32k osc? Not writable by user code.
0x16 | ??????      | Not copied into any obvious registers
0x17 | ??????      | Not copied into any obvious registers
0x1C | ??????      | Not copied into any obvious registers
0x1D | ??????      | Not copied into any obvious registers

`*` "Ultra Low Power" *More like Ultra Low Precision, amirite?!* "Hmm? It's not that bad..." *No more +/- 30%?* "Well they don't specify it, so I'm sure it's not flattering. But it's not like classic Tiny's with the ULP." *Few things are..* "And you can see from the values we find written to chips that OSC32K is calibrated more tightly now" *Not so tightly they'll spec it though...* "No, but look, now it's got 5 bits of calibration, there isn't space between them for 30% error. *Yeah, the 2 bit cal on the classic 841 was... I just didn't know what to say.* "Profanity normally works well"


## Appendix I: F_CPU vs OSCCAL and TCAL
Conveniently represented in kilohertz; this is, of course, for my convenience. Don't want to have any more passes through excel than already necessary, so you want to print the same number you do the math as afterwards and which is amenable to printing, even when gathering data from a tiny424 (which rules out floating point numbers and hence megahertz). As it happens, the tuning sketch always did it this way: It measures the duration (with pulsein) of .  It's done by counting processor clock cycles with pulseIn (the working version, not the "standard" one with the bug) while receiving a 1kHz square wave.

Very early tiny2's (typical results), don't seem to have one immediately at hand to get full data from:

| 6@16  | 6@20  |
|-------|-------|
| 11493 | 14673 |
| 11641 | 14844 |
| 11766 | 15033 |
| 11922 | 15185 |
| 12035 | 15373 |
| 12195 | 15528 |
| 12308 | 15708 |
| 12457 | 15871 |
| 12589 | 16054 |
| 12734 | 16224 |
| 12857 | 16411 |
| 13013 | 16566 |
| 13141 | 16763 |
| 13287 | 16915 |
| 13421 | 17122 |
| 13571 | 17293 |
| 13717 | 17491 |
| 13874 | 17632 |
| 13985 | 17830 |
| 14137 | 18003 |
| 14283 | 18202 |
| 14435 | 18343 |
| 14550 | 18536 |
| 14705 | 18676 |
| 14819 | 18878 |
| 14973 | 19042 |
| 15101 | 19217 |
| 15255 | 19373 |
| 15383 | 19580 |
| 15529 | 19763 |
| 15676 | 19953 |
| 15833 | 20133 |
| 15971 | 20323 |
| 16127 | 20482 |
| 16257 | 20696 |
| 16415 | 20877 |
| 16555 | 21071 |
| 16713 | 21269 |
| 16871 | 21463 |
| 17029 | 21621 |
| 17154 | 21819 |
| 17311 | 22030 |
| 17477 | 22227 |
| 17631 | 22411 |
| 17775 | 22615 |
| 17922 | 22790 |
| 18076 | 22985 |
| 18233 | 23163 |
| 18376 | 23360 |
| 18533 | 23530 |
| 18665 | 23732 |
| 18833 | 23894 |
| 18951 | 24082 |
| 19111 | 24254 |
| 19239 | 24461 |
| 19401 | 24657 |
| 19553 | 24871 |
| 19727 | 25038 |
| 19847 | 25228 |
| 20013 | 25393 |
| 20139 | 25595 |
| 20307 | 25755 |
| 20432 | 25976 |
| 20599 | 26143 |
| 20747 | 26363 |
| 20905 | 26556 |
| 21062 | 26765 |
| 21222 | 26913 |
| 21343 | 27115 |
| 21509 | 27298 |
| 21651 | 27489 |
| 21816 | 27685 |
| 21943 | 27887 |
| 22115 | 28066 |
| 22256 | 28282 |
| 22433 | 28467 |
| 22567 | 28679 |
| 22747 | 28911 |
| 22918 | 29115 |
| 23081 | 29319 |
| 23247 | 29531 |
| 23412 | 29704 |
| 23535 | 29880 |
| 23693 | 30073 |
| 23837 | 30313 |
| 24023 | 30515 |
| 24184 | 30708 |
| 24355 | 30905 |
| 24506 | 31132 |
| 24673 | 31303 |
| 24817 | 31522 |
| 24982 | 31704 |
| 25133 | 31926 |
| 25307 | 32113 |
| 25460 | 32328 |
| 25627 | 32544 |
| 25795 | 32765 |
| 25968 | 32966 |
| 26125 | 33189 |
| 26301 | 33376 |
| 26439 | 33581 |
| 26612 | 33773 |
| 26757 | 33984 |
| 26922 | 34196 |
| 27087 | 34418 |
| 27259 | 34634 |
| 27438 | 34866 |
| 27611 | 35066 |
| 27776 | 35288 |
| 27947 | 35521 |
| 28125 | 35738 |
| 28293 | 35934 |
| 28457 | - |
| 28625 | - |
| 28788 | - |
| 28959 | - |
| 29090 | - |
| 29280 | - |
| 29421 | - |
| 29596 | - |
| 29737 | - |
| 29908 | - |
| 30065 | - |
| 30250 | - |
| 30406 | - |
| 30587 | - |
| 30761 | - |
| 30941 | - |

New-tuning clock speeds:
Notice: 16 and 20 are virtually the same.

The new-cal ones have the TCAL normally set to 2-3, versus 5-6 for the old-cal ones, but that does not account for the entirety of the difference, and they crap out at much lower speeds.

32 MHz chips are now in fact quite rare. Interestingly, they are either using a worse process/fab for them now, or they've drastically lowered their standards for what ships (considering how much they were exceeding spec by, I can't blame them for wanting to cut costs, yaknow. It's not like they're charging ATmegabucks for these.)

|  0@16 |  1@16 |  2@16 |  3@15 |  4@16 |  5@16 |  6@16 |  7@16 |  0@20 |  1@20 |  2@20 |  3@15 |  4@20 |  5@20 |  6@20 |  7@20 |
|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|-------|
|  8023 |  8646 |  9073 |  9420 |  9701 |  9943 | 10141 | 10338 |  8046 |  8693 |  9122 |  9493 |  9805 | 10062 | 10246 | 10473 |
|  8113 |  8742 |  9176 |  9529 |  9815 | 10059 | 10261 | 10463 |  8130 |  8786 |  9229 |  9604 |  9917 | 10178 | 10371 | 10593 |
|  8209 |  8844 |  9279 |  9638 |  9929 | 10179 | 10384 | 10592 |  8209 |  8886 |  9344 |  9728 | 10031 | 10300 | 10499 | 10719 |
|  8294 |  8939 |  9381 |  9750 | 10042 | 10295 | 10505 | 10717 |  8320 |  8984 |  9470 |  9856 | 10151 | 10423 | 10624 | 10840 |
|  8394 |  9046 |  9490 |  9859 | 10162 | 10420 | 10633 | 10846 |  8417 |  9088 |  9590 |  9975 | 10267 | 10546 | 10752 | 10971 |
|  8482 |  9140 |  9596 |  9973 | 10272 | 10540 | 10755 | 10970 |  8500 |  9213 |  9690 | 10084 | 10384 | 10656 | 10880 | 11097 |
|  8575 |  9243 |  9706 | 10085 | 10398 | 10661 | 10880 | 11103 |  8589 |  9318 |  9797 | 10194 | 10503 | 10779 | 11008 | 11220 |
|  8668 |  9342 |  9809 | 10196 | 10509 | 10778 | 11003 | 11223 |  8704 |  9414 |  9899 | 10316 | 10624 | 10900 | 11136 | 11351 |
|  8760 |  9447 |  9919 | 10307 | 10630 | 10906 | 11135 | 11361 |  8796 |  9515 | 10012 | 10427 | 10752 | 11017 | 11262 | 11464 |
|  8848 |  9543 | 10023 | 10418 | 10741 | 11023 | 11253 | 11485 |  8877 |  9611 | 10113 | 10530 | 10875 | 11136 | 11382 | 11596 |
|  8942 |  9640 | 10130 | 10531 | 10855 | 11145 | 11384 | 11615 |  8968 |  9728 | 10240 | 10648 | 10983 | 11264 | 11504 | 11714 |
|  9035 |  9748 | 10245 | 10662 | 10989 | 11282 | 11524 | 11755 |  9088 |  9855 | 10368 | 10766 | 11128 | 11392 | 11639 | 11855 |
|  9135 |  9852 | 10354 | 10778 | 11116 | 11409 | 11651 | 11886 |  9192 |  9956 | 10488 | 10882 | 11237 | 11520 | 11765 | 11991 |
|  9231 |  9959 | 10468 | 10903 | 11235 | 11541 | 11783 | 12017 |  9284 | 10061 | 10587 | 11008 | 11361 | 11648 | 11896 | 12119 |
|  9325 | 10060 | 10578 | 11011 | 11358 | 11665 | 11905 | 12154 |  9375 | 10165 | 10694 | 11136 | 11472 | 11776 | 12013 | 12242 |
|  9419 | 10159 | 10687 | 11123 | 11480 | 11787 | 12031 | 12280 |  9472 | 10262 | 10796 | 11249 | 11589 | 11900 | 12132 | 12365 |
|  9508 | 10262 | 10792 | 11242 | 11600 | 11912 | 12160 | 12405 |  9589 | 10368 | 10906 | 11359 | 11709 | 12019 | 12261 | 12486 |
|  9579 | 10338 | 10877 | 11330 | 11692 | 12003 | 12257 | 12503 |  9644 | 10458 | 11008 | 11442 | 11786 | 12104 | 12344 | 12576 |
|  9671 | 10446 | 10999 | 11448 | 11817 | 12130 | 12385 | 12635 |  9747 | 10563 | 11118 | 11557 | 11906 | 12222 | 12470 | 12704 |
|  9759 | 10543 | 11093 | 11556 | 11931 | 12248 | 12500 | 12751 |  9855 | 10655 | 11210 | 11649 | 12032 | 12328 | 12580 | 12819 |
|  9853 | 10646 | 11208 | 11675 | 12054 | 12373 | 12631 | 12885 |  9947 | 10754 | 11321 | 11776 | 12158 | 12456 | 12709 | 12949 |
|  9962 | 10767 | 11340 | 11813 | 12196 | 12518 | 12793 | 13037 | 10065 | 10881 | 11452 | 11905 | 12288 | 12597 | 12859 | 13100 |
| 10056 | 10872 | 11456 | 11934 | 12319 | 12642 | 12908 | 13163 | 10150 | 11005 | 11557 | 12032 | 12416 | 12718 | 12987 | 13234 |
| 10139 | 10971 | 11561 | 12039 | 12419 | 12758 | 13025 | 13283 | 10240 | 11094 | 11651 | 12144 | 12519 | 12825 | 13088 | 13345 |
| 10238 | 11082 | 11672 | 12159 | 12549 | 12885 | 13154 | 13413 | 10352 | 11193 | 11776 | 12261 | 12635 | 12953 | 13215 | 13476 |
| 10329 | 11186 | 11783 | 12275 | 12670 | 13001 | 13278 | 13542 | 10445 | 11295 | 11900 | 12365 | 12751 | 13068 | 13338 | 13598 |
| 10430 | 11289 | 11898 | 12398 | 12792 | 13131 | 13402 | 13673 | 10532 | 11395 | 12002 | 12491 | 12874 | 13194 | 13459 | 13730 |
| 10515 | 11391 | 12002 | 12505 | 12903 | 13252 | 13522 | 13791 | 10624 | 11515 | 12098 | 12585 | 12976 | 13312 | 13572 | 13846 |
| 10613 | 11505 | 12119 | 12621 | 13027 | 13372 | 13647 | 13924 | 10740 | 11618 | 12211 | 12703 | 13099 | 13440 | 13702 | 13977 |
| 10695 | 11594 | 12212 | 12729 | 13138 | 13477 | 13758 | 14036 | 10805 | 11700 | 12293 | 12800 | 13195 | 13563 | 13824 | 14082 |
| 10796 | 11696 | 12335 | 12847 | 13258 | 13605 | 13884 | 14167 | 10903 | 11804 | 12417 | 12928 | 13313 | 13680 | 13952 | 14218 |
| 10885 | 11804 | 12442 | 12961 | 13373 | 13725 | 14008 | 14288 | 11008 | 11904 | 12537 | 13048 | 13440 | 13795 | 14080 | 14336 |
| 10991 | 11913 | 12558 | 13083 | 13498 | 13852 | 14134 | 14417 | 11110 | 12026 | 12647 | 13171 | 13568 | 13923 | 14207 | 14466 |
| 11088 | 12032 | 12673 | 13193 | 13614 | 13971 | 14265 | 14551 | 11199 | 12132 | 12757 | 13280 | 13691 | 14042 | 14332 | 14595 |
| 11188 | 12131 | 12790 | 13316 | 13740 | 14102 | 14395 | 14682 | 11296 | 12231 | 12866 | 13385 | 13817 | 14168 | 14463 | 14729 |
| 11280 | 12240 | 12896 | 13431 | 13860 | 14223 | 14514 | 14812 | 11392 | 12333 | 12969 | 13504 | 13937 | 14282 | 14589 | 14863 |
| 11384 | 12351 | 13018 | 13555 | 13981 | 14349 | 14652 | 14942 | 11505 | 12433 | 13080 | 13618 | 14051 | 14410 | 14716 | 14991 |
| 11461 | 12440 | 13107 | 13645 | 14077 | 14452 | 14752 | 15042 | 11571 | 12541 | 13184 | 13702 | 14140 | 14507 | 14809 | 15104 |
| 11565 | 12550 | 13216 | 13765 | 14198 | 14577 | 14875 | 15177 | 11659 | 12641 | 13301 | 13824 | 14263 | 14635 | 14939 | 15232 |
| 11671 | 12659 | 13337 | 13883 | 14325 | 14697 | 15004 | 15310 | 11776 | 12739 | 13410 | 13952 | 14380 | 14759 | 15071 | 15360 |
| 11765 | 12767 | 13450 | 14006 | 14447 | 14825 | 15135 | 15442 | 11877 | 12840 | 13523 | 14078 | 14500 | 14884 | 15197 | 15493 |
| 11861 | 12864 | 13548 | 14113 | 14557 | 14940 | 15245 | 15558 | 11955 | 12931 | 13610 | 14180 | 14598 | 14989 | 15315 | 15616 |
| 11953 | 12980 | 13669 | 14233 | 14678 | 15068 | 15377 | 15690 | 12051 | 13056 | 13723 | 14300 | 14729 | 15120 | 15442 | 15744 |
| 12050 | 13081 | 13784 | 14345 | 14793 | 15191 | 15504 | 15822 | 12159 | 13163 | 13825 | 14406 | 14848 | 15235 | 15561 | 15872 |
| 12155 | 13190 | 13890 | 14463 | 14919 | 15311 | 15634 | 15951 | 12256 | 13264 | 13952 | 14527 | 14976 | 15368 | 15698 | 16001 |
| 12250 | 13296 | 14006 | 14573 | 15032 | 15436 | 15754 | 16072 | 12341 | 13358 | 14059 | 14637 | 15102 | 15489 | 15818 | 16128 |
| 12350 | 13406 | 14116 | 14694 | 15157 | 15558 | 15885 | 16213 | 12436 | 13460 | 14173 | 14751 | 15230 | 15616 | 15943 | 16258 |
| 12425 | 13482 | 14197 | 14780 | 15250 | 15655 | 15978 | 16302 | 12521 | 13557 | 14250 | 14848 | 15303 | 15727 | 16038 | 16380 |
| 12527 | 13590 | 14316 | 14901 | 15373 | 15781 | 16107 | 16437 | 12614 | 13667 | 14368 | 14974 | 15433 | 15860 | 16167 | 16511 |
| 12624 | 13695 | 14427 | 15014 | 15489 | 15898 | 16232 | 16562 | 12703 | 13757 | 14471 | 15092 | 15553 | 15972 | 16291 | 16640 |
| 12727 | 13803 | 14536 | 15137 | 15616 | 16029 | 16360 | 16694 | 12800 | 13859 | 14592 | 15205 | 15677 | 16103 | 16425 | 16768 |
| 12818 | 13905 | 14645 | 15253 | 15720 | 16145 | 16484 | 16819 | 12905 | 13953 | 14702 | 15317 | 15784 | 16219 | 16545 | 16896 |
| 12922 | 14013 | 14766 | 15373 | 15856 | 16277 | 16613 | 16954 | 13004 | 14080 | 14818 | 15436 | 15912 | 16350 | 16677 | 17026 |
| 13028 | 14133 | 14884 | 15496 | 15993 | 16414 | 16753 | 17095 | 13109 | 14199 | 14946 | 15559 | 16046 | 16484 | 16830 | 17181 |
| 13128 | 14241 | 15003 | 15616 | 16111 | 16542 | 16881 | 17226 | 13198 | 14305 | 15056 | 15679 | 16171 | 16621 | 16968 | 17320 |
| 13237 | 14358 | 15120 | 15740 | 16240 | 16673 | 17018 | 17370 | 13312 | 14410 | 15173 | 15805 | 16304 | 16757 | 17104 | 17467 |
| 13340 | 14461 | 15237 | 15864 | 16368 | 16798 | 17147 | 17507 | 13418 | 14517 | 15285 | 15924 | 16429 | 16887 | 17248 | 17605 |
| 13428 | 14565 | 15343 | 15977 | 16481 | 16925 | 17267 | 17628 | 13504 | 14615 | 15384 | 16031 | 16550 | 17015 | 17369 | 17731 |
| 13533 | 14674 | 15458 | 16098 | 16609 | 17054 | 17399 | 17761 | 13595 | 14720 | 15500 | 16154 | 16678 | 17145 | 17508 | 17877 |
| 13632 | 14790 | 15579 | 16225 | 16733 | 17178 | 17540 | 17905 | 13696 | 14848 | 15617 | 16283 | 16804 | 17277 | 17648 | 18025 |
| 13739 | 14897 | 15695 | 16346 | 16860 | 17308 | 17669 | 18030 | 13815 | 14968 | 15744 | 16399 | 16929 | 17408 | 17786 | 18167 |
| 13838 | 15011 | 15812 | 16472 | 16995 | 17439 | 17806 | 18168 | 13906 | 15076 | 15872 | 16525 | 17067 | 17536 | 17920 | 18304 |
| 13946 | 15125 | 15931 | 16591 | 17117 | 17574 | 17938 | 18303 | 14002 | 15182 | 15993 | 16644 | 17194 | 17666 | 18051 | 18439 |
| 14047 | 15233 | 16049 | 16713 | 17244 | 17704 | 18076 | 18449 | 14099 | 15288 | 16116 | 16776 | 17327 | 17805 | 18190 | 18581 |
| 14149 | 15344 | 16168 | 16837 | 17371 | 17833 | 18206 | 18581 | 14208 | 15393 | 16225 | 16898 | 17455 | 17939 | 18334 | 18729 |
| 14249 | 15452 | 16281 | 16954 | 17490 | 17959 | 18334 | 18712 | 14319 | 15492 | 16336 | 17025 | 17583 | 18072 | 18465 | 18870 |
| 14349 | 15566 | 16396 | 17077 | 17621 | 18089 | 18470 | 18851 | 14423 | 15615 | 16449 | 17152 | 17719 | 18203 | 18612 | 19017 |
| 14448 | 15664 | 16502 | 17190 | 17733 | 18209 | 18605 | 18982 | 14498 | 15726 | 16564 | 17278 | 17833 | 18330 | 18745 | 19150 |
| 14544 | 15776 | 16620 | 17306 | 17865 | 18337 | 18733 | 19123 | 14594 | 15836 | 16672 | 17407 | 17974 | 18477 | 18886 | 19297 |
| 14646 | 15888 | 16736 | 17436 | 17982 | 18466 | 18861 | 19257 | 14716 | 15940 | 16789 | 17534 | 18105 | 18610 | 19024 | 19439 |
| 14752 | 15993 | 16850 | 17555 | 18117 | 18604 | 18996 | 19388 | 14809 | 16050 | 16904 | 17662 | 18236 | 18746 | 19171 | 19583 |
| 14856 | 16106 | 16976 | 17682 | 18242 | 18739 | 19134 | 19528 | 14906 | 16165 | 17029 | 17792 | 18376 | 18894 | 19317 | 19713 |
| 14959 | 16225 | 17093 | 17809 | 18371 | 18867 | 19271 | 19675 | 15002 | 16271 | 17154 | 17920 | 18507 | 19034 | 19455 | 19856 |
| 15045 | 16317 | 17189 | 17910 | 18478 | 18980 | 19386 | 19799 | 15104 | 16383 | 17274 | 18030 | 18614 | 19147 | 19580 | 19984 |
| 15149 | 16422 | 17304 | 18033 | 18607 | 19117 | 19519 | 19931 | 15210 | 16495 | 17397 | 18161 | 18754 | 19287 | 19712 | 20129 |
| 15242 | 16529 | 17417 | 18148 | 18725 | 19236 | 19643 | 20054 | 15295 | 16597 | 17501 | 18272 | 18874 | 19423 | 19840 | 20259 |
| 15346 | 16638 | 17537 | 18268 | 18851 | 19373 | 19777 | 20197 | 15390 | 16698 | 17625 | 18408 | 19015 | 19561 | 19969 | 20414 |
| 15445 | 16756 | 17653 | 18394 | 18981 | 19500 | 19914 | 20338 | 15491 | 16816 | 17746 | 18538 | 19155 | 19701 | 20114 | 20561 |
| 15552 | 16863 | 17771 | 18516 | 19111 | 19636 | 20054 | 20477 | 15612 | 16922 | 17878 | 18671 | 19287 | 19840 | 20257 | 20709 |
| 15651 | 16974 | 17885 | 18639 | 19230 | 19766 | 20187 | 20613 | 15699 | 17029 | 17991 | 18790 | 19414 | 19967 | 20390 | 20845 |
| 15755 | 17084 | 17999 | 18756 | 19365 | 19892 | 20320 | 20757 | 15803 | 17152 | 18112 | 18919 | 19549 | 20096 | 20543 | 20989 |
| 15858 | 17193 | 18126 | 18882 | 19488 | 20033 | 20463 | 20899 | 15893 | 17279 | 18229 | 19046 | 19693 | 20228 | 20690 | 21120 |
| 15961 | 17305 | 18242 | 19008 | 19618 | 20165 | 20601 | 21040 | 16002 | 17397 | 18356 | 19180 | 19826 | 20363 | 20839 | 21263 |
| 16073 | 17429 | 18367 | 19143 | 19761 | 20309 | 20745 | 21195 | 16127 | 17521 | 18487 | 19321 | 19965 | 20522 | 20992 | 21426 |
| 16170 | 17539 | 18488 | 19268 | 19890 | 20448 | 20889 | 21339 | 16228 | 17634 | 18608 | 19454 | 20096 | 20656 | 21120 | 21567 |
| 16283 | 17664 | 18617 | 19403 | 20037 | 20594 | 21039 | 21502 | 16339 | 17765 | 18746 | 19584 | 20233 | 20823 | 21268 | 21740 |
| 16386 | 17773 | 18739 | 19531 | 20166 | 20731 | 21184 | 21638 | 16441 | 17878 | 18880 | 19713 | 20372 | 20962 | 21414 | 21888 |
| 16487 | 17886 | 18849 | 19653 | 20290 | 20863 | 21314 | 21784 | 16531 | 17986 | 18999 | 19840 | 20502 | 21090 | 21547 | 22016 |
| 16591 | 17995 | 18975 | 19778 | 20423 | 20996 | 21458 | 21927 | 16640 | 18097 | 19121 | 19969 | 20638 | 21237 | 21701 | 22150 |
| 16681 | 18087 | 19069 | 19885 | 20535 | 21115 | 21583 | 22052 | 16745 | 18184 | 19218 | 20094 | 20746 | 21347 | 21814 | 22273 |
| 16781 | 18204 | 19191 | 20009 | 20669 | 21249 | 21723 | 22199 | 16842 | 18312 | 19348 | 20224 | 20885 | 21497 | 21959 | 22417 |
| 16897 | 18322 | 19325 | 20151 | 20809 | 21403 | 21878 | 22364 | 16955 | 18435 | 19490 | 20358 | 21040 | 21633 | 22121 | 22581 |
| 17005 | 18434 | 19451 | 20278 | 20939 | 21536 | 22021 | 22508 | 17054 | 18560 | 19613 | 20483 | 21179 | 21764 | 22267 | 22739 |
| 17108 | 18554 | 19572 | 20409 | 21085 | 21686 | 22172 | 22658 | 17164 | 18688 | 19748 | 20622 | 21323 | 21914 | 22400 | 22894 |
| 17212 | 18670 | 19688 | 20535 | 21222 | 21823 | 22320 | 22813 | 17280 | 18814 | 19874 | 20753 | 21454 | 22055 | 22537 | 23040 |
| 17297 | 18769 | 19799 | 20647 | 21333 | 21945 | 22439 | 22943 | 17373 | 18923 | 19975 | 20867 | 21574 | 22177 | 22662 | 23167 |
| 17397 | 18881 | 19915 | 20776 | 21470 | 22084 | 22588 | 23091 | 17474 | 19038 | 20105 | 20996 | 21704 | 22317 | 22809 | 23297 |
| 17501 | 18991 | 20030 | 20899 | 21594 | 22216 | 22725 | 23233 | 17578 | 19157 | 20225 | 21121 | 21838 | 22449 | 22944 | 23437 |
| 17603 | 19105 | 20150 | 21024 | 21733 | 22361 | 22874 | 23385 | 17678 | 19271 | 20352 | 21250 | 21981 | 22589 | 23087 | 23587 |
| 17706 | 19218 | 20278 | 21155 | 21870 | 22504 | 23024 | 23523 | 17792 | 19385 | 20480 | 21385 | 22117 | 22738 | 23236 | 23739 |
| 17809 | 19325 | 20397 | 21285 | 22009 | 22650 | 23164 | 23681 | 17920 | 19504 | 20608 | 21519 | 22254 | 22881 | 23379 | 23882 |
| 17896 | 19426 | 20504 | 21390 | 22120 | 22766 | 23286 | 23803 | 17999 | 19597 | 20734 | 21632 | 22357 | 22987 | 23505 | 24003 |
| 18003 | 19539 | 20620 | 21530 | 22260 | 22912 | 23426 | 23955 | 18100 | 19718 | 20860 | 21760 | 22499 | 23135 | 23649 | 24158 |
| 18099 | 19642 | 20730 | 21642 | 22390 | 23035 | 23570 | 24093 | 18192 | 19838 | 20969 | 21888 | 22623 | 23267 | 23777 | 24294 |
| 18200 | 19760 | 20858 | 21779 | 22527 | 23181 | 23710 | 24249 | 18305 | 19964 | 21100 | 22016 | 22752 | 23402 | 23928 | 24448 |
| 18297 | 19866 | 20978 | 21907 | 22659 | 23318 | 23859 | 24384 | 18426 | 20087 | 21217 | 22144 | 22895 | 23548 | 24062 | 24576 |
| 18401 | 19978 | 21095 | 22034 | 22802 | 23465 | 24004 | 24537 | 18530 | 20195 | 21341 | 22273 | 23036 | 23680 | 24194 | 24720 |
| 18520 | 20110 | 21240 | 22187 | 22958 | 23628 | 24164 | 24703 | 18651 | 20331 | 21488 | 22412 | 23168 | 23830 | 24354 | 24894 |
| 18620 | 20230 | 21366 | 22316 | 23096 | 23771 | 24316 | 24851 | 18759 | 20446 | 21612 | 22550 | 23299 | 23966 | 24502 | 25042 |
| 18722 | 20339 | 21487 | 22447 | 23232 | 23908 | 24463 | 25010 | 18860 | 20558 | 21733 | 22682 | 23434 | 24109 | 24653 | 25204 |
| 18832 | 20457 | 21605 | 22586 | 23369 | 24055 | 24605 | 25150 | 18968 | 20679 | 21864 | 22814 | 23572 | 24252 | 24801 | 25343 |
| 18929 | 20573 | 21737 | 22721 | 23511 | 24199 | 24754 | 25292 | 19076 | 20791 | 21986 | 22941 | 23707 | 24393 | 24955 | 25474 |
| 19034 | 20687 | 21858 | 22860 | 23650 | 24341 | 24899 | 25446 | 19200 | 20912 | 22104 | 23079 | 23854 | 24544 | 25088 | 25627 |
| 19120 | 20777 | 21962 | 22960 | 23760 | 24450 | 25010 | 25566 | 19285 | 20999 | 22199 | 23174 | 23957 | 24650 | 25213 | 25742 |
| 19228 | 20892 | 22085 | 23093 | 23899 | 24593 | 25163 | 25715 | 19384 | 21122 | 22327 | 23309 | 24094 | 24793 | 25343 | 25897 |
| 19315 | 20993 | 22193 | 23211 | 24020 | 24712 | 25284 | 25840 | 19473 | 21241 | 22424 | 23426 | 24206 | 24908 | 25468 | 26016 |
| 19411 | 21112 | 22316 | 23344 | 24153 | 24860 | 25431 | 25989 | 19585 | 21356 | 22553 | 23554 | 24351 | 25061 | 25604 | 26173 |
| 19538 | 21246 | 22465 | 23494 | 24316 | 25027 | 25596 | 26164 | 19712 | 21500 | 22700 | 23704 | 24521 | 25214 | 25775 | 26358 |
| 19641 | 21367 | 22597 | 23633 | 24458 | 25168 | 25745 | 26317 | 19840 | 21620 | 22832 | 23847 | 24661 | 25349 | 25927 | 26495 |
| 19756 | 21492 | 22733 | 23782 | 24607 | 25327 | 25897 | 26462 | 19960 | 21744 | 22967 | 23979 | 24815 | 25500 | 26085 | 26652 |
| 19858 | 21606 | 22859 | 23911 | 24746 | 25465 | 26046 | 26618 | 20066 | 21861 | 23090 | 24120 | 24946 | 25651 | 26238 | 26800 |
| 19979 | 21744 | 23006 | 24063 | 24903 | 25625 | 26204 | 26779 | 20189 | 21997 | 23234 | 24271 | 25089 | 25815 | 26375 | 26972 |
| 20083 | 21861 | 23133 | 24196 | 25042 | 25763 | 26347 | 26931 | 20288 | 22110 | 23363 | 24404 | 25227 | 25970 | 26538 | 27126 |
| 20184 | 21982 | 23256 | 24323 | 25174 | 25904 | 26488 | 27071 | 20397 | 22222 | 23488 | 24528 | 25352 | 26101 | 26677 | 27261 |
| 20291 | 22099 | 23382 | 24458 | 25308 | 26049 | 26635 | 27225 | 20502 | 22342 | 23614 | 24664 | 25489 | 26239 | 26834 | 27403 |
| 20380 | 22195 | 23484 | 24574 | 25429 | 26166 | 26759 | 27353 | 20605 | 22429 | 23708 | 24781 | 25607 | 26361 | 26947 | 27529 |
| 20485 | 22316 | 23622 | 24706 | 25564 | 26311 | 26901 | 27500 | 20719 | 22549 | 23838 | 24917 | 25743 | 26498 | 27101 | 27682 |


Of the old-cal ones (24 were tested and recorded), 16 were TCAL = 6, the rest TCAL = 5. Calbyte was around 0x20-0x30

Of the new-cal ones (32 were tested and recorded):

TCAL | # parts
-----|--------
0    |      0
1    |      3
2    |      3
3    |     11 (!!)
4    |      3
5    |      5
6    |      7
7    |      0

Speed can be modeled very well using a quadratic function (eg, Ax^2 + Bx + C = F_CPU, where x is the value in the calbyte and C is the clock speed with calbyte = 0. )



## Footnotes

`*` This is difficult to rationalize. From the perspective of the customer, we're getting fucked! We can no longer verify the specs on the parts we have in our inventory - and we're left exposed to fraudulent practices by middlemen in the industry (Imagine a turnkey PCBA provider who was given a BoM listing E/F-spec parts. Those cost more! But the markings are the same! So they could just build it with cheaper U/N/I-spec ones, while still billing the customer for the E/F-spec parts - they'd never get off without being noticed if the parts were marked unless they went to the trouble of altering the markings on the chip (though they picked I and E as the temperature ranges for Dx-series, likely to match the rest of Microchip's products. Unfortunately, that means that even if it were marked, it would be easy for fraudulent operations to alter the markings.

This represents a profound reversal from the cleverly chosen markings used by Atmel. The new Microchip dogma dictates that the abbreviation are I and E. These would allow customers to distinguish between I and E parts in the absence of active decption, where the marks still etched onto the parts, but it would be less effective in the case where the perpetratators are willing to go to the effort of modifying the markings on the chip, which is known to have been done for ATtiny13's sold on the open market at ATtiny85. In contrast, ATMEL, and even the fully post-revolutionary tinyAVR 2-series, used the "F-U-N" system. U was 85C, N was 105C, and F was 125C. To change ANY of those three letters into any other, One or more lines must be erased, AND one or more must be added. It's not implausible, of course - we know that people find it worthwhile to grind the markings off of ATtiny13's, remark them, and sell them as tiny85's (that's why you shouldn't buy AVR's on aliexpress `**`). The VAO parts use B/Z which have the same property as F/N and F/U in terms of being difficult to alter into eachother. The F/N/U (FUN?) lettering for tinyAVR seems to pre-date the 2016 revolution, corresponding to -40C to either 85C ("Industrial") (U), 105C ("Industrial if other grade is F, "Extended" if the other grade is N) (N) or 125C ("Extended") (F) on classic AVRs too. Worth noting, they used a different set of three letters (ZMB) to mean the same things on the Automotive parts; none of these six letters can be modified to look like any of the other five without both adding and erasing lines. Thus, the grade marking also inhibited modifying normal parts to look like more expensive automotive ones.

Now, it is onerous to determine what kind of chip you are holding, without anyone attempting to decieve you. How is this progress?!

`**` Aliexpress is kind of like a slot machine. When you "win" you get a discount on things, but sometimes you get garbage instead, and you never know for sure if the parts are legit. Any knockoff can be arbitrarilly similar and remain undetected - if it remains undetected forever because it is so similar that it performs equivalently, that's no big deal. So you get 1 of 5 possible results:
1. The item is legitimate and you save money. Win.
2. The item is a very good fake that performs equivalently in your application and you save money (generally more than in case 1). Win.
3. The item is a very poor fake that is immediately obvious. Wager is lost, and perhaps a small additional sum lost in things paired with the first bad part used, at which point the issue is detected. (For example, the ATtiny13's remarked at 85's appear to be legitimate until you attempt to program them, and they report that they are ATtiny13's).
4. The item is a marginal fake, which fools the immediate analysis such that it is put into service in quantity, and the problem is only later discovered. Wager is lost, but you additionally lose a significant quantity of parts it was used with before the issue was detected. This is typical of knockoffs which were meant to perform equivalently, but manufactured shoddily, ending up with a shorter service life, worse performance under adverse conditions or improperly handled corner cases, as well as garbage that was never intended to fool anyone longer than it took to make the sale, but which is sometimes convincing enough (or testing lax enough) to be put into use and discovered later (think of the not-unusual example controllers for large SD memory chips, paired with much smaller memory, with the remaining address lines left floating - so it works until you fill the smaller device, and then everything falls over - someone who just threw it into a reader and copied a small file to it would be fooled. Or wire marked with and sold as having an AWG rating typically 4 gauge larger than the wire's actual size - *with the insulation thickened to make up the difference*. This is *nearly ubiquitous* in Chinese PVC-insulated wire - nearly 100% of PVC insulated wire from china is mismarked when there isn't . I am not sure I have ever gotten wire that was within 1 AWG if it had PVC insulation! But the extent of undersizing varies from 1 to 8 AWG. FEP insulated wire on the other hand, while more expensive, is better wire in general, and
 the only times I've gotten FEP wire that was even 2 AWG undersized, the seller was just an unsophisticated crook. I ordered 24 AWG, and got ~27 AWG - but it said 26 AWG on the wire, not 24. Somehow the FEP insulation also seems to keep the riff-raff out. Maybe this is because it's just harder to copy, or maybe they also expect people who are willing to kick in the extra money for FEP insulation are likely to catch them and complain, while the people who just buy "wire" won't). Anyway, this is the worst category - depending on the size of the loss, the additional collateral damage as units assembled with the bunk parts having to be discarded or reworked can range into the thousands.
5. The item is an exceptional fake, which while it will substitute for the original in most cases, the reverse is not true: The fakes are better than the originals!. Hence, if one designs for the superior fakes, the system may end up working only with those fakes, which (since they were mis-sold) may be hard to locate to re-order when a later order comes out as the genuine, but inferior article. Those will initially be assumed to be type 3 or 4 items, and only after considerable analysis is it recognized that the genuine part cannot perform as required. Several examples of this can be found among addressable LEDs (which have been copied by dozens of companies - who generally re-implementing the controller to copy the advertised behavior; the original APA102 achieved the global dimming by combining outputting the logical AND of two PWM signals. The major clone, the SK9822, got two things wrong. First, they did what the datasheet said for the protocol (the original datasheet didn't accurately describe the behavior, though) and (also following the description in the datasheet) used a constant current source rather than two overlapping PWM signals. The altered protocol is strictly better, and even though they dropped the main PWM frequency by a factor of two, the global dimming PWM was much slower than that, and hence going to the constant current driver greatly reducing situations in which the flicker is observable.

It's hard to classify the final category as either win or loss - they're not a loss, not if the clone is better than the original and cheaper (like the LEDs mentioned earlier). Another example, the WenTai organizer bins: The brand name ones are of poor manufacturing quality, and the lids are sometimes broken upon arrival. There are knockoffs of the small size available however, and the knockoffs are of of strikingly good build quality, far better than would be expected. I'm hoping they knock off the bigger sizes soon too - the 1x3 size has had some rotten quality control, and many of them don't stay together, and I'd love to replace mine with better made knockoffs. The problem with case 5 is that when you need to reorder, the supply may have vanished or it may have been replaced with a crapola knockoff, and you don't even know how ask for the good ones "Review: 1/5 - Very disappointed; parts appear to be genuine. The counterfeit ones I got last year work much better."
