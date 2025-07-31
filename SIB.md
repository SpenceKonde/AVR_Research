# Contents of the System Information Block (SIB)

There is more than one way to identify a target device. Reading the device signature row is one way (and gives more and different information, and is unique per specimen). The SIB is an even cruder way, because a UPDI programmer **might not know how to access the sigrow** in the future, when significant changes are next made to the protocol - the programmer needs a way to find out what version of the NVM controller it is using, and what version of the On-Chip Debugger it's using, and what speed the UPDI oscillator is derived from)
During UPDI programming, the programmer asks the chip for it's System Information Block. The chip responds with either 8 or 16, or 32 bytes of data, depending on how much the programmer asked for. Only the 8 and 16 byte forms are documented - but pymcuprog knows about a way to get 32 bytes of data. There are a few bytes of entropy content contained in these additional 128 bits: there is the die rev (1 byte, but represented as 2 bytes of ascii characters), there is an internal manufacturer product code that can be used to split the AVRs into two broad groups, and one field of unknown semantics 1 character in length nominally storing a 0. The meaning of this, if any, will become clear only if a counterexample were to appear. A simple possibility would be that it's reserved for the future followon versions (what in the past was A's P's, PA's and PB's) - or it might be for VAOs or god knows what

Notice the NVM version jumping up:

DA/DB/DD had 2
EA had 3, but they changed it again with EB to 5, implying that the DU's are 4



| Part       | SIB                               | Family  | NVM | OCD | OSC | Rev  |  CODE  | ? |
|------------|-----------------------------------|---------|-----|-----|-----|------|--------|---|-----
| AVR16EB32  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59B?? | 0 | <---/ Same presumed die, PDID
| AVR16EB28  | `AVR     P:5D:1-3M2 (A0.59B1D.0)` | AVR     | P:5 | D:1 | 3M2 |  A0  |  59B1D | 0 | <--/
| AVR16EB20  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59B?? | 0 | <-/
| AVR16EB14  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59B?? | 0 | </
| AVR32EB32  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59??? | 0 | <---/ Same presumed die, PDID
| AVR32EB28  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59??? | 0 | <--/
| AVR32EB20  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59??? | 0 | <-/
| AVR32EB14  | Please contribute                 | AVR     | P:5 | D:1 | 3M2 |  A0  |  59??? | 0 | </
| AVR16DU32  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <---/ Same presumed die
| AVR16DU28  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <--/
| AVR16DU20  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <-/
| AVR16DU14  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | </
| AVR32SD48  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <---/ Same presumed die
| AVR32SD32  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <--/
| AVR32SD28  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <-/
| AVR32SD20  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | </
| AVR32DU32  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <---/ Same presumed die
| AVR32DU28  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <--/
| AVR32DU20  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <-/
| AVR32DU14  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | </
| AVR64DU32  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <---/ Same presumed die
| AVR64DU28  | Please contribute                 | AVR     | P:4?| D:1 | 3M2 |  ??  |  KV0?? | 0 | <--/
| AVR16EA48  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <---/ Same presumed die
| AVR16EA32  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <--/
| AVR16EA28  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <-/
| AVR32EA32  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <---/ Same presumed die
| AVR32EA48  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <--/
| AVR32EA28  | Please contribute                 | AVR     | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 | <-/
| AVR64EA28  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR     | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 | <---/ Same presumed die
| AVR64EA32  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR     | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 | <-/
| AVR64EA48  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR     | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 | </    <---- This implies similar genesis for EA and TinyAVR and distinct from Dx-series.
| AVR16DD14  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die
| AVR16DD20* | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR16DD28* | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die
| AVR16DD32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR32DD14  | `AVR     P:2D:1-3M2 (A1.KV00R.0)` |  AVR    | P:2 | D:1 | 3M2 |  A1  |  KV00R | 0 | <---,-- Same presumed die, same 5 character code
| AVR32DD20  | `AVR     P:2D:1-3M2 (A1.KV00R.0)` |  AVR    | P:2 | D:1 | 3M2 |  A1  |  KV00R | 0 | <--/
| AVR32DD28* | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR32DD32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR64DD14  | `AVR     P:2D:1-3M2 (A1.KV00U.0)` |  AVR    | P:2 | D:1 | 3M2 |  A1  |  KV00U | 0 | <---,-- Same presumed die
| AVR64DD20  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A1  |  KV00U | 0 | <--/
| AVR64DD28* | `AVR     P:2D:1-3M2 (A3.KV00K.0)` |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00K | 0 | <---,-- Same presumed die, same 5 character code
| AVR64DD32  | `AVR     P:2D:1-3M2 (A3.KV00K.0)` |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00K | 0 | <--/
| AVR32DB48  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die.
| AVR32DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR32DB28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <-/
| AVR32DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <----,-- Same presumed die,
| AVR32DB28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---/
| AVR64DB48  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00? | 0 | <--/
| AVR64DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00? | 0 | <-/
| AVR32DA48  |  Please contribute                |  ?????  | P:2 | D:1 | 3M2 |  A3? |  ????? | 0 | <----,- Same presumed die
| AVR32DA32  |  Please contribute                |  ?????  | P:2 | D:1 | 3M2 |  A3? |  ????? | 0 | <---/
| AVR32DA28  |  Please contribute                |  ?????  | P:2 | D:1 | 3M2 |  A3? |  ????? | 0 | <--/
| AVR32DA48S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <----,- Same presumed die
| AVR32DA32S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <---/
| AVR32DA28S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <--/
| AVR64DA64  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <--\
| AVR64DA48  | `AVR     P:2D:1-3M2 (A3.KV00E.0)` |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E | 0 | <---|
| AVR64DA32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <---,-- Same presumed die,
| AVR64DA28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <--/
| AVR64DA64S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <----,- Same presumed die
| AVR64DA48S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <---/
| AVR64DA32S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <--/
| AVR64DA28S |  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <-/
| AVR128DB64 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` |  AVR    | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <----,- Same presumed die, same 5 character code
| AVR128DB48 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` |  AVR    | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <---/
| AVR128DB32 | Please contribute                 |  ?????  | P:2 | D:1 | 3M2 |  A5  |  KV00D?| 0 | <--/
| AVR128DB28 | Please contribute                 |  ?????  | P:2 | D:1 | 3M2 |  A5  |  KV00D?| 0 | <-/
| AVR128DA64 | `AVR     P:2D:1-3M2 (A6.KV001.0)` |`AVR    `| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <----,-- Same presumed die
| AVR128DA48 | `    AVR P:2D:1-3M2 (A6.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <---/
| AVR128DA32 | `    AVR P:2D:1-3M2 (A6.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <--/  <--- WTF on justification of the AVR field?
| AVR128DA32 | `    AVR P:2D:1-3M2 (A7.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A7  |  KV001 | 0 | <-/   <--- A6 and A7 silicon coexists inthe wild!
| AVR128DA28 |  Please contribute                |  ?????  | P:2 | D:1 | 3M2 |  A?  |  KV001 | 0 |
| AVR128DA64S|  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <----,- Same presumed die
| AVR128DA48S|  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <---/
| AVR128DA32S|  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <--/
| AVR128DA28S|  Please contribute                |  ?????  | P:2?| D:1 | 3M2 |  AB? |  ????? | 0 | <-/
| ATmega808  |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega809  |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega1608 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega1609 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega3208 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| ATmega3209 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| ATmega3208 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   D  |  59B2? | 0 |
| ATmega3209 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   D  |  59B2? | 0 |
| ATmega4808 | `megaAVR P:0D:1-3M2 (01.59B20.0)` | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B20 | 0 |
| ATmega4809 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| t82x/t42x  | `tinyAVR P:0D:1-3M2 (01.59B0F.0)` | tinyAVR | P:0 | D:1 | 3M2 |   B  |  59B0F | 0 |
| t1624/6/7  | `tinyAVR P:0D:1-3M2 (04.59B0D.0)` | tinyAVR | P:0 | D:1 | 3M2 |   E  |  59B0D | 0 |
| t3224/6/7  | `tinyAVR P:0D:1-3M2 (00.59B0E.0)` | tinyAVR | P:0 | D:1 | 3M2 |   A  |  59B0E | 0 |
| t202/4/6,402/4 | `tinyAVR P:0D:0-3M2 (01.59B14.0)` | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B14 | 0 | **402 has same ID as 412!!**
| t804/6/7,407| Please contribute                | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B?? | 0 |
| t1604/6/7  | `tinyAVR P:0D:0-3M2 (00.59B03.0)` | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B03 | 0 |
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (00.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B14 | 0 | Unconfirmed in the wild
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (01.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 | **B**|  59B14 | 0 |
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (02.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 | **C**|  59B14 | 0 | Unconfirmed in the wild
| t814/6/7,417 | Please contribute               | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B16 | 0 | 59B16 is a guess.
| t1614/6/7  | `tinyAVR P:0D:0-3M2 (00.59B15.0)` | tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B15 | 0 |
| t1614/6/7  | `tinyAVR P:0D:0-3M2 (01.59B15.0)` | tinyAVR | P:0 | D:0 | 3M2 | **B**|  59B15 | 0 | Unconfirmed in the wild
| t3216/7    | `tinyAVR P:0D:0-3M2 (00.59B17.0)` | tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B17 | 0 | Unconfirmed in the wild
| t3216/7    | `tinyAVR P:0D:0-3M2 (02.59B17.0)` | tinyAVR | P:0 | D:0 | 3M2 | **C**|  59B17 | 0 |


Pymcuprog lists the P:# as the version of the NVM controller it uses (P for programming), and the D:# is the version of the on-chip debugger (consistent with the datasheet) and the 3M2 is in reference to the "PDI oscillator" (does that mean the base clock speed is apx. 32 MHz? It's plausible, as the options we have for clock speed are 4, 8, 16, and 32 MHz, which would be what you'd naturally do if you were willing to allocate two bits to representing it, and were starting with a 32 MHz clock, right?). Then we get to the parens containing likely the most interesting information.... First, there's the die rev right there, without having to dig for it! Second, there's a cryptic 5 hex-digit value. I belive this identifies the die design. Devices widely belived to share a die all give the same value here. If this is the case, it jumps out that there are two bases - KV00 (the Dx-series, ie, good parts) and 59___, the Ex-series/tinyAVR (the generally lower end parts).

The first two characters are the SILICON DIE REV, represented as two hexadecimal digits, or so it appears

After that some representation of the design in 5 character, unique per die, followed by .0 is seen.

It appears that Dx-series parts have identifiers starting with KV0, and tinyAVR and Ex have values starting with 59B for tinyAVR and 59F for Ex, confirming that the Ex-series are not Dx-series parts that have evolved to have lower pincounts, but tinyAVR series parts that are evolving in the direction of more expansive features.

One curious thing is that the DA and DB parts appear to only have one ID per flash size. If this tracks die designs, then what happened to all those peripherals on the 32 and 28 pin parts? I can't imagine that they'd let that much silicon go to waste, especially when there so clearly appeared to be a division between 32/28 and the big ones. But I guess there is only one set of errata. So it's gotta just be one die right? That implies that they just lopped off 2 CCL units and 2 event channels just to to make the advantages of their larger, more expensive brothers more significant? And a TCA that could have been used with the CCL or for any number of other applications is just sitting there disconnected in every DA/DB 32? Did that really make economic sense? I mean, I guess maybe not since the EA's only spanned 28:48 and came in 1 die per size. But the DD which spanned 14:32 is split into two dies, one for the 14-20 pin parts and one for the big ones. I suspect when we next see 64-pin parts, there will be a 64/48 pin die and a 32/28-pin die - unless they've gone nuts and released something that goes all the way from 14 to 64 pins in one family, in which case it'd probably be 3 dies. That isn't as insane as it sounds, either: the Dx family is almost that. It's not hard to imagine that when they finally think they've gotten AVR's house in order, they'll release a new family (or a budget family and feature family, or budget/feature/usb) that offers a similar set of features across the range of 14-64 pins, with three dies per flash size. Eg, the AVR8FA14/20, AVR16FA14/20, AVR32FA14/20, AVR8FU14/20, AVR16FU14/20, AVR32FU14/20, AVR16FB14/20, AVR32FB14/20, AVR64FB14/20, AVR8FA28/32, AVR16FA28/32, AVR32FA28/32, AVR16FU28/32, AVR32FU28/32, AVR64FU28/32, AVR16FA48/64, AVR32FA48/64, AVR64FA48/64, AVR32FU48/64, AVR64FU48/64, AVR128FU48/64, AVR32FB48/64, AVR64FB48/64, AVR128FB48/64

### Table notes:
* Data is text encoded as an ascii c string, with a nul terminator - I think perversely placed in the middle of the string or something. In any event the point is that most methods to print the SIB for debugging fail if you don't strip out the nul, but other than that... yeah it's just ASCII. Microchip or at least the part of it that was once Atmel, likes hiding ASCII in things people look at as hex:
  * The UPDI KEY protected interfaces
    * The KEY to enable nvm programming is, uh, `NVMProg `
    * The KEY to enable USERROW programming of a locked chip is... `NVMUs&te` (the `&` is probably used as an abbreviation symbol, NVMUs~er row wri~te )
    * The KEY to perform a chip erase to unlock a chip is `NVMErase`
    * The KEY to enter OCD mode is `OCD     `
  * Some fields of part serial numbers.
  * Many AVR programming protocols chose the commands based on the first ascii letter in the function.
* Cases where pieces of the 5-digit codes can easily be deduced have been and ?'s left in place of the unknown letters.
* Cases where we know the P (always), D (non- 0/1), or OSC value (always 3M2) have been filled in, as have cases where there isnt any question about the what the family will be (so some DA/DB are left as ?'s, since they are inconsistent in how they justify the letters in "AVR"
  * `    AVR` - Padding on the left (and "coincidentally" the same length as the text that was there, as if they'd just changed the lessers to ascii 0x20's.
  * `AVR    ` - Probably what is intended
  * What's whacky is that both justification styles are seen. I wonder what the statistics are like? Maybe they;re created as balanced pairs of chips and antichips,
* On all parts except 0/1 tinyAVRs it is known that the parts use OCD v1 not v0. It is not yet known if any of them advanced to OCDv1.
* NVM numbers are 0: paged write without NRWW and fully mapped flash. 1:
* In the rare event that more than one die rev is known to exist in the wild, the ones belived to currently be in broad distribution are in **bold** and the ones that are old enough that few of them remain that have not been used in something in *itallics*
* For devices not yet released, we assumed the Ex's would continue to be 59'ers, and DU would be KV's. It is expected that flash writes on EB will be like the EA only hopefully with less errata, and that the DU will be a word-write part like the other Dx's, and that OCD version was unlikely to change (there are a few things that a debugger really needs to do. there are very few "nice to haves" that might be added on later though). And it was assumed that the Dx and Ex series would continue to use the 3M2 PDI oscillator.

## Help understand these by submitting the strings like the ones in the second column.
It will be printed by SerialUPDI when any programming atempt is made and verbose outout enabled, and will show info for the connected chip, (so you can read the SIB without writing anything by selecting a chip that doesn't match the chip you connect and then tryingto program it with verbose mode enabled using SerialUPDI).

To gather the data, it is sufficient to attempt a SerialUPDI upload to a correctly wired chip that is not the one you have selected in the IDE - it'll still print the full SIB (though it may error after that in current github DxCore version, because I need to tighten up the serial number printing code to work with the general case).


## Further notes:
I just realzed when I stopped by here top add a few notes that the SIB allows an upload tool to know what version of the hardware a chip is uploading to, in other words, the die rev.

A sufficiently dedicated - and mad - individual could make the following changed
0. Upload tool replaced by a script to mediate it's operation
1. Upload tool checks SIB in database, determining silicon rev.
2. Upload tool takes an additional command line parameter, specifying the minimum die rev.
3. In the event that the die rev specified on the command line parameter is wrong, and error code is returned. Upon receiving this error code, the script would then print "Old silivon rev detected. Recompiling with workarounds.".
4. until now, every step described is non-challenging. Now the hard part (which is where 99% of the payoff is. Upload tool must now, through means of unknown viability or even plausiblity somehow execute the compilation command with -DERRATAMODE=ERRATA_REVA6 or something added to the relevant commands.
5. Proceed to upload the recompiled binary.

How is this relevant? Mainly because it makes checkErrata() compiletime known and foldable because you assume avalue instead of reading SYSCFG.REVID, which takes 3 clock cycles, then another 3 to compare it and act (including a jump or time spent notjumping), and you have to check it every time.


```

if (checkErrata(SOME_IMPORTANT_BUG)) {
  // Errata present
  //
} else {
  //do fast way
}

Let us consider the impact of checking errata.

OT to be the overhead in time (cycles per invocation) and OS to be the overhead in instruction words per invocation.

```

What's the overhead of doing that?
Let's presume the relevant process without errata takex X CPU cyclys, and it takes Y CPU cycles to do the same task with the workaround. And that CheckErrata should take 6 - 3 for the 2 word 3 clock lds iinstruction to load from SYSCFG.REVID, amd then there's a CPI and a branch of some sort, right? That sounds like a total of 6 clocks to me. 6 clocks per time executed, 8 bytes of flash for 4 words per location of the test.

Because of this, and since we don't know it at compile time, only bugs that matter get tested like this internally, and in most cases, we just assume the bug is there if the part ever had it. In some cases, the test of revid takes twice as long as the workaround (this is the case for two irritating USART bugs present almost everywhere. Even though hardly anyone is going to encounter them, if you want to support autobaud, you have to have the ISR check and clear ISFIF, and if it was set, then the RX module off and back on.)

Simple stuff, at least in principle. The problem is that you only know at runtime, so you can't be like "compile the ISR with handling for the Sync Field erratum only if the bug isn't known to be fixed" because it doesn't know that until it is running and reads REVID. That means every time the erratum would be encountered, you have to check the revid. That's only 6 clocks counting the branch, but the ISR limits the capability of the device if it doesn't return in ~80 clocks, because the speed at which the RX ISR needs to run to receive things at the maximum hardware-supported baud rate; that ISR has two erratum-fixes in it. We just barely squeak in under the time limit; and the fix is equally fast as testing for the errata



If I'm being honest, fixing the outstanding errata on modern AVRs is nearly as disruptive as it's presence in the first place, If they could have sloooowed down a bit you know. Made sure Blink ran on the AVR32DA parts before the shipped? considered functionality of anything other than the 48-pin version (DA128 has some unique bugs, specific exactly to pins not present on 48 pin parts but present on 64 pin ones, for example, the eventsystem doesn't work on the 2 pins each on ports E and B that were gainedon going to 64 pio are disconnected from EBSYS (oops!) Amd the TCA1 mappiings specific to 64-pin parts weren't tested and didn't work. All the other Dx parts have fixed those bugs, even smaller DA's. DB's had a tiny run of one version. I don't know who signed off on that. All I know is, I had DB's from before the preliminary datasheet was available, and they were already the second rev that had been released. , tried running blink on an AVR32DA.


### Another shit method
This only works if there are only a small num
