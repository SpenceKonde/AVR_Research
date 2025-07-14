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
* OSCTCAL seems to bump the speed by as much as changing the cal by 4 (at high TCAL) to 8 (at low TCAL)
* The TCAL levels are not spaced evenly. Particularly between 0 and 1 (or 8 and 9), there's a particularly large jump.
* At room temperature, no difference was observed between TCAL = M (where 0 <= M < 8) and TCAL = M + 8.



See appendix for full range of speeds calculated from all OSCCAL and TCAL values being used in place of factory cal:

Cal         | 0 / 8 | 1 / 9 | 2 /10 | 3 /11 | 4 /12 | 5 /13 | 6 /14 | 7 /15 |
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

`*` "Ultra Low Power" *More like Ultra Low Precision, amirite?!* "Hmm? It's not that bad..." *No more +/- 30%?* "Well they don't specify it, so I'm sure it's not flattering. But it's not like classic Tiny's with the ULP." *Few things are..* "And you can see from the values we find written to chips that OSC32K is calibrated more tightly now" *Not so tightly they'll spec it though...* "No, but look, now it's got 5 bits of calibration, up from 2.... with 32 cal settings, there isn't any space between them for 30% error.


## Appendix I: F_CPU vs OSCCAL and TCAL for 16 MHz osc on a single Tiny2 specimen.
Take with approprite volume of salt.
Sample size is 1.
Larger sample sizes are both timeconsuming to gather, and very challenging to compare because you can only make a graph with 2 dimensions, making it very challenging to make comparisons across many parts by plotting 2 or 3 dimensional graphs in an N+1 dimensional coordinate system. We can't even visualize dimensions past 4, and the data for this for even a single part requires 3 dimensions, making a passable surface chart. But you can't average them, because the surface FCPU(TCAL, CAL) for each chip is in a different location.

So, with great difficulty (this requires 1024 measurements, which we repeat 8 times, repeated with both fuse settings.

|OSCCAL| 0/8   | 1/9   | 2/10  | 3/11  | 4/12  | 5/13  | 6/14  | 7/15  |
|------|-------|-------|-------|-------|-------|-------|-------|-------|
| 0x00 |  8.07 |  8.74 |  9.19 |  9.53 |  9.81 | 10.11 | 10.34 | 10.57 |
| 0x01 |  8.16 |  8.84 |  9.28 |  9.64 |  9.95 | 10.23 | 10.48 | 10.70 |
| 0x02 |  8.28 |  8.94 |  9.40 |  9.76 | 10.04 | 10.35 | 10.61 | 10.83 |
| 0x03 |  8.37 |  9.03 |  9.52 |  9.88 | 10.17 | 10.48 | 10.74 | 10.96 |
| 0x04 |  8.47 |  9.15 |  9.62 |  9.98 | 10.30 | 10.59 | 10.86 | 11.08 |
| 0x05 |  8.57 |  9.23 |  9.71 | 10.08 | 10.43 | 10.70 | 10.95 | 11.19 |
| 0x06 |  8.66 |  9.33 |  9.83 | 10.18 | 10.54 | 10.84 | 11.08 | 11.34 |
| 0x07 |  8.73 |  9.44 |  9.96 | 10.33 | 10.62 | 10.95 | 11.24 | 11.44 |
| 0x08 |  8.82 |  9.57 | 10.07 | 10.44 | 10.78 | 11.09 | 11.37 | 11.57 |
| 0x09 |  8.93 |  9.67 | 10.15 | 10.56 | 10.89 | 11.17 | 11.46 | 11.70 |
| 0x0A |  9.03 |  9.75 | 10.28 | 10.65 | 11.02 | 11.31 | 11.62 | 11.85 |
| 0x0B |  9.14 |  9.88 | 10.38 | 10.76 | 11.12 | 11.46 | 11.74 | 11.99 |
| 0x0C |  9.24 |  9.99 | 10.48 | 10.88 | 11.26 | 11.55 | 11.84 | 12.09 |
| 0x0D |  9.33 | 10.09 | 10.58 | 11.03 | 11.35 | 11.70 | 12.00 | 12.26 |
| 0x0E |  9.41 | 10.18 | 10.69 | 11.13 | 11.50 | 11.78 | 12.13 | 12.38 |
| 0x0F |  9.52 | 10.29 | 10.81 | 11.21 | 11.62 | 11.95 | 12.21 | 12.52 |
| 0x10 |  9.61 | 10.39 | 10.94 | 11.34 | 11.73 | 12.07 | 12.35 | 12.63 |
| 0x11 |  9.68 | 10.50 | 11.05 | 11.45 | 11.85 | 12.17 | 12.46 | 12.77 |
| 0x12 |  9.82 | 10.61 | 11.18 | 11.57 | 11.98 | 12.34 | 12.63 | 12.91 |
| 0x13 |  9.91 | 10.73 | 11.28 | 11.73 | 12.11 | 12.45 | 12.78 | 13.02 |
| 0x14 | 10.00 | 10.82 | 11.37 | 11.84 | 12.22 | 12.57 | 12.87 | 13.17 |
| 0x15 | 10.10 | 10.93 | 11.52 | 11.93 | 12.35 | 12.66 | 13.03 | 13.26 |
| 0x16 | 10.20 | 11.04 | 11.63 | 12.07 | 12.48 | 12.83 | 13.16 | 13.44 |
| 0x17 | 10.29 | 11.15 | 11.75 | 12.19 | 12.60 | 12.96 | 13.29 | 13.57 |
| 0x18 | 10.40 | 11.26 | 11.86 | 12.31 | 12.72 | 13.07 | 13.41 | 13.67 |
| 0x19 | 10.46 | 11.34 | 11.98 | 12.43 | 12.81 | 13.22 | 13.52 | 13.85 |
| 0x1A | 10.56 | 11.44 | 12.06 | 12.55 | 12.93 | 13.34 | 13.68 | 13.97 |
| 0x1B | 10.69 | 11.57 | 12.19 | 12.66 | 13.10 | 13.47 | 13.80 | 14.08 |
| 0x1C | 10.76 | 11.68 | 12.30 | 12.78 | 13.20 | 13.60 | 13.95 | 14.25 |
| 0x1D | 10.86 | 11.75 | 12.38 | 12.90 | 13.30 | 13.73 | 14.06 | 14.38 |
| 0x1E | 10.98 | 11.90 | 12.56 | 13.04 | 13.49 | 13.85 | 14.20 | 14.54 |
| 0x1F | 11.09 | 12.03 | 12.65 | 13.12 | 13.61 | 14.01 | 14.36 | 14.68 |
| 0x20 | 11.20 | 12.16 | 12.82 | 13.32 | 13.77 | 14.17 | 14.51 | 14.85 |
| 0x21 | 11.33 | 12.23 | 12.94 | 13.44 | 13.85 | 14.29 | 14.67 | 14.96 |
| 0x22 | 11.44 | 12.34 | 13.04 | 13.57 | 14.03 | 14.44 | 14.81 | 15.11 |
| 0x23 | 11.54 | 12.50 | 13.18 | 13.69 | 14.11 | 14.57 | 14.93 | 15.27 |
| 0x24 | 11.61 | 12.58 | 13.28 | 13.82 | 14.26 | 14.69 | 15.09 | 15.40 |
| 0x25 | 11.75 | 12.71 | 13.42 | 13.94 | 14.36 | 14.84 | 15.23 | 15.55 |
| 0x26 | 11.82 | 12.84 | 13.51 | 14.06 | 14.53 | 14.98 | 15.36 | 15.65 |
| 0x27 | 11.91 | 12.95 | 13.64 | 14.19 | 14.67 | 15.11 | 15.50 | 15.82 |
| 0x28 | 12.03 | 13.05 | 13.77 | 14.28 | 14.74 | 15.19 | 15.62 | 15.96 |
| 0x29 | 12.15 | 13.14 | 13.89 | 14.41 | 14.89 | 15.32 | 15.76 | 16.09 |
| 0x2A | 12.19 | 13.25 | 13.98 | 14.53 | 15.02 | 15.46 | 15.87 | 16.16 |
| 0x2B | 12.29 | 13.31 | 14.09 | 14.64 | 15.12 | 15.58 | 16.00 | 16.36 |
| 0x2C | 12.42 | 13.47 | 14.16 | 14.76 | 15.27 | 15.72 | 16.09 | 16.43 |
| 0x2D | 12.48 | 13.58 | 14.32 | 14.89 | 15.37 | 15.79 | 16.27 | 16.61 |
| 0x2E | 12.61 | 13.70 | 14.45 | 15.02 | 15.50 | 16.00 | 16.42 | 16.73 |
| 0x2F | 12.69 | 13.80 | 14.57 | 15.13 | 15.64 | 16.13 | 16.50 | 16.90 |
| 0x30 | 12.78 | 13.89 | 14.68 | 15.26 | 15.78 | 16.25 | 16.68 | 17.04 |
| 0x31 | 12.93 | 14.01 | 14.74 | 15.38 | 15.91 | 16.38 | 16.81 | 17.18 |
| 0x32 | 13.02 | 14.14 | 14.92 | 15.51 | 16.01 | 16.49 | 16.96 | 17.33 |
| 0x33 | 13.14 | 14.22 | 14.99 | 15.58 | 16.18 | 16.59 | 17.04 | 17.47 |
| 0x34 | 13.24 | 14.33 | 15.16 | 15.76 | 16.31 | 16.73 | 17.24 | 17.61 |
| 0x35 | 13.35 | 14.48 | 15.28 | 15.89 | 16.44 | 16.91 | 17.31 | 17.75 |
| 0x36 | 13.45 | 14.56 | 15.37 | 16.01 | 16.54 | 17.06 | 17.50 | 17.86 |
| 0x37 | 13.52 | 14.66 | 15.53 | 16.14 | 16.70 | 17.20 | 17.60 | 17.98 |
| 0x38 | 13.67 | 14.80 | 15.64 | 16.28 | 16.84 | 17.28 | 17.80 | 18.14 |
| 0x39 | 13.72 | 14.90 | 15.74 | 16.37 | 16.98 | 17.48 | 17.94 | 18.34 |
| 0x3A | 13.86 | 15.02 | 15.91 | 16.53 | 17.11 | 17.61 | 18.05 | 18.45 |
| 0x3B | 13.98 | 15.17 | 16.02 | 16.66 | 17.23 | 17.75 | 18.23 | 18.62 |
| 0x3C | 14.06 | 15.25 | 16.13 | 16.77 | 17.31 | 17.87 | 18.35 | 18.75 |
| 0x3D | 14.17 | 15.40 | 16.22 | 16.90 | 17.48 | 17.96 | 18.49 | 18.90 |
| 0x3E | 14.24 | 15.47 | 16.31 | 17.02 | 17.61 | 18.14 | 18.63 | 19.04 |
| 0x3F | 14.38 | 15.62 | 16.49 | 17.14 | 17.71 | 18.24 | 18.77 | 19.18 |
| 0x40 | 14.45 | 15.68 | 16.61 | 17.27 | 17.86 | 18.35 | 18.90 | 19.32 |
| 0x41 | 14.53 | 15.84 | 16.70 | 17.39 | 18.00 | 18.53 | 19.03 | 19.46 |
| 0x42 | 14.69 | 15.96 | 16.79 | 17.47 | 18.13 | 18.67 | 19.18 | 19.57 |
| 0x43 | 14.79 | 16.07 | 16.97 | 17.65 | 18.24 | 18.81 | 19.32 | 19.68 |
| 0x44 | 14.89 | 16.18 | 17.08 | 17.77 | 18.39 | 18.92 | 19.45 | 19.89 |
| 0x45 | 14.95 | 16.28 | 17.16 | 17.89 | 18.52 | 19.02 | 19.59 | 20.03 |
| 0x46 | 15.03 | 16.34 | 17.29 | 17.98 | 18.61 | 19.16 | 19.65 | 20.06 |
| 0x47 | 15.17 | 16.48 | 17.41 | 18.11 | 18.67 | 19.24 | 19.80 | 20.28 |
| 0x48 | 15.25 | 16.58 | 17.46 | 18.22 | 18.85 | 19.42 | 19.89 | 20.36 |
| 0x49 | 15.37 | 16.66 | 17.63 | 18.34 | 18.92 | 19.56 | 20.09 | 20.52 |
| 0x4A | 15.48 | 16.86 | 17.79 | 18.44 | 19.15 | 19.74 | 20.27 | 20.72 |
| 0x4B | 15.61 | 16.97 | 17.88 | 18.64 | 19.30 | 19.88 | 20.40 | 20.80 |
| 0x4C | 15.69 | 17.10 | 18.05 | 18.76 | 19.41 | 19.95 | 20.58 | 21.04 |
| 0x4D | 15.83 | 17.16 | 18.17 | 18.90 | 19.56 | 20.09 | 20.72 | 21.14 |
| 0x4E | 15.94 | 17.27 | 18.27 | 19.03 | 19.70 | 20.30 | 20.79 | 21.33 |
| 0x4F | 16.04 | 17.43 | 18.42 | 19.09 | 19.78 | 20.43 | 20.99 | 21.41 |
| 0x50 | 16.09 | 17.53 | 18.52 | 19.25 | 19.95 | 20.56 | 21.12 | 21.58 |
| 0x51 | 16.21 | 17.64 | 18.60 | 19.35 | 20.09 | 20.63 | 21.25 | 21.70 |
| 0x52 | 16.28 | 17.66 | 18.73 | 19.49 | 20.15 | 20.80 | 21.30 | 21.79 |
| 0x53 | 16.42 | 17.84 | 18.85 | 19.59 | 20.29 | 20.91 | 21.46 | 21.97 |
| 0x54 | 16.51 | 17.90 | 18.97 | 19.74 | 20.40 | 21.07 | 21.59 | 22.15 |
| 0x55 | 16.57 | 18.07 | 19.05 | 19.87 | 20.59 | 21.20 | 21.80 | 22.30 |
| 0x56 | 16.73 | 18.19 | 19.18 | 20.00 | 20.68 | 21.29 | 21.94 | 22.45 |
| 0x57 | 16.84 | 18.28 | 19.28 | 20.06 | 20.85 | 21.49 | 22.01 | 22.60 |
| 0x58 | 16.94 | 18.41 | 19.46 | 20.24 | 20.96 | 21.55 | 22.23 | 22.74 |
| 0x59 | 17.05 | 18.54 | 19.58 | 20.36 | 21.12 | 21.70 | 22.37 | 22.89 |
| 0x5A | 17.16 | 18.66 | 19.71 | 20.44 | 21.25 | 21.83 | 22.46 | 23.04 |
| 0x5B | 17.24 | 18.77 | 19.84 | 20.65 | 21.40 | 22.05 | 22.63 | 23.16 |
| 0x5C | 17.36 | 18.90 | 19.97 | 20.79 | 21.55 | 22.21 | 22.83 | 23.36 |
| 0x5D | 17.44 | 19.00 | 20.10 | 20.92 | 21.68 | 22.30 | 22.97 | 23.50 |
| 0x5E | 17.60 | 19.15 | 20.19 | 21.05 | 21.83 | 22.50 | 23.14 | 23.68 |
| 0x5F | 17.71 | 19.21 | 20.36 | 21.12 | 21.92 | 22.60 | 23.29 | 23.83 |
| 0x50 | 17.78 | 19.38 | 20.48 | 21.31 | 22.11 | 22.78 | 23.38 | 23.96 |
| 0x61 | 17.91 | 19.50 | 20.55 | 21.45 | 22.16 | 22.93 | 23.51 | 24.11 |
| 0x62 | 18.01 | 19.62 | 20.72 | 21.55 | 22.31 | 23.03 | 23.72 | 24.27 |
| 0x63 | 18.13 | 19.69 | 20.82 | 21.72 | 22.44 | 23.17 | 23.87 | 24.43 |
| 0x64 | 18.25 | 19.79 | 21.00 | 21.79 | 22.68 | 23.37 | 23.96 | 24.58 |
| 0x65 | 18.36 | 19.98 | 21.08 | 21.95 | 22.82 | 23.52 | 24.19 | 24.75 |
| 0x66 | 18.45 | 20.10 | 21.22 | 22.08 | 22.87 | 23.66 | 24.31 | 24.90 |
| 0x67 | 18.57 | 20.21 | 21.31 | 22.27 | 23.02 | 23.77 | 24.41 | 24.98 |
| 0x68 | 18.62 | 20.32 | 21.50 | 22.31 | 23.16 | 23.94 | 24.62 | 25.19 |
| 0x69 | 18.75 | 20.43 | 21.62 | 22.52 | 23.35 | 24.03 | 24.67 | 25.34 |
| 0x6A | 18.90 | 20.57 | 21.76 | 22.67 | 23.47 | 24.16 | 24.86 | 25.49 |
| 0x66 | 19.00 | 20.69 | 21.87 | 22.77 | 23.65 | 24.38 | 24.98 | 25.66 |
| 0x6C | 19.06 | 20.78 | 22.00 | 22.95 | 23.73 | 24.54 | 25.15 | 25.80 |
| 0x6D | 19.22 | 20.94 | 22.10 | 23.08 | 23.89 | 24.63 | 25.37 | 25.98 |
| 0x6E | 19.31 | 21.03 | 22.28 | 23.22 | 23.99 | 24.77 | 25.53 | 26.14 |
| 0x6F | 19.42 | 21.18 | 22.42 | 23.35 | 24.22 | 24.98 | 25.68 | 26.21 |
| 0x70 | 19.54 | 21.28 | 22.52 | 23.39 | 24.30 | 25.09 | 25.80 | 26.41 |
| 0x71 | 19.57 | 21.32 | 22.65 | 23.60 | 24.48 | 25.22 | 25.85 | 26.46 |
| 0x72 | 19.68 | 21.52 | 22.78 | 23.74 | 24.62 | 25.28 | 26.10 | 26.72 |
| 0x73 | 19.84 | 21.62 | 22.91 | 23.84 | 24.76 | 25.53 | 26.19 | 26.88 |
| 0x74 | 19.89 | 21.69 | 22.99 | 23.94 | 24.85 | 25.63 | 26.36 | 26.94 |
| 0x75 | 19.98 | 21.84 | 23.09 | 24.10 | 24.94 | 25.71 | 26.51 | 27.13 |
| 0x76 | 20.12 | 21.92 | 23.26 | 24.24 | 25.06 | 25.92 | 26.56 | 27.30 |
| 0x77 | 20.27 | 22.08 | 23.33 | 24.31 | 25.26 | 26.07 | 26.81 | 27.46 |
| 0x78 | 20.32 | 22.22 | 23.54 | 24.54 | 25.35 | 26.25 | 27.00 | 27.64 |
| 0x79 | 20.51 | 22.29 | 23.62 | 24.66 | 25.59 | 26.40 | 27.15 | 27.80 |
| 0x7A | 20.57 | 22.49 | 23.81 | 24.74 | 25.68 | 26.55 | 27.29 | 27.96 |
| 0x7B | 20.67 | 22.61 | 23.94 | 24.94 | 25.89 | 26.70 | 27.45 | 28.12 |
| 0x7C | 20.84 | 22.68 | 24.08 | 25.11 | 26.00 | 26.85 | 27.64 | 28.25 |
| 0x7D | 20.92 | 22.86 | 24.22 | 25.24 | 26.18 | 27.00 | 27.70 | 28.44 |
| 0x7E | 21.10 | 23.00 | 24.37 | 25.41 | 26.27 | 27.17 | 27.97 | 28.61 |
| 0x7F | 21.21 | 23.13 | 24.46 | 25.54 | 26.44 | 27.32 | 28.05 | 28.68 |




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
