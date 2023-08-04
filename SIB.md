# Contents of the System Information Block (SIB)

There is more than one way to identify a target device. Reading the device signature row is one way (and gives more and different information, and is unique per specimen). The SIB is an even cruder way, because a UPDI programmer **might not know how to access the sigrow** in the future, when significant changes are next made to the protocol - the programmer needs a way to find out what version of the NVM controller it is using, and what version of the On-Chip Debugger it's using, and what speed the UPDI oscillator is derived from)
During UPDI programming, the programmer asks the chip for it's System Information Block. The chip responds with either 8 or 16, or 32 bytes of data, depending on how much the programmer asked for. Only the 8 and 16 byte forms are documented - but pymcuprog knows about a way to get 32 bytes of data. There are a few bytes of entropy content contained in these additional 128 bits: there is the die rev (1 byte, but represented as 2 bytes of ascii characters), there is an internal manufacturer product code that can be used to split the AVRs into two broad groups, and one field of unknown semantics 1 character in length nominally storing a 0. The meaning of this, if any, will become clear only if a counterexample were to appear. A simple possibility would be that it's reserved for the future followon versions (what in the past was A's P's, PA's and PB's) - or it might be for VAOs or god knows what

| Part       | SIB                               | Family| NVM | OCD | OSC | Rev  |  CODE  | ? | Note
|------------|-----------------------------------|-------|-----|-----|-----|------|--------|---|-----
| AVR8EB32   | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR8EB28   | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR8EB20   | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR8EB14   | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR16EB32  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR16EB28  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR16EB20  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR16EB14  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR32EB32  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR32EB28  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR32EB20  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR32EB14  | Please contribute                 | AVR   | P:3 | D:1?| 3M2 |  ??  |  59??? | 0 | Not yet released
| AVR16DU32  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR16DU28  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR16DU20  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR16DU14  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR32DU32  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR32DU28  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR32DU20  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR32DU14  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR64DU32  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR64DU28  | Please contribute                 | AVR   | P:2?| D:1?| 3M2 |  ??  |  KV0?? | 0 | Not yet released
| AVR8EA48   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  59F0? | 0 | Not yet released
| AVR8EA32   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  59F0? | 0 | Not yet released
| AVR8EA28   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  59F0? | 0 | Not yet released
| AVR16EA48  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 |
| AVR16EA32  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 |
| AVR16EA28  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 |
| AVR32EA32  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 |
| AVR32EA48  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  A0  |  59F0? | 0 |
| AVR64EA28  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR   | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 |
| AVR64EA32  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR   | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 |
| AVR64EA48  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR   | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 | <---- This implies (supported by observations like the 20/16 MHz oscillator and other limitations) that the EA is closer to a tinyAVR than a Dx-series. That it apparently underwent a *major* die rev sort of implies that development did not progress as smoothly as planned (which is consistent with the high revision number seen on the 2-series - Timing wise, I think they had to have the Ex in progress when the 2-series was released, and they share the new ADC, which is the likely cause of revisions). 
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
| AVR32DB48  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR32DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die.
| AVR32DB28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR32DB48  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR32DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR32DB28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR64DB48  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00? | 0 |
| AVR64DB32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00? | 0 | 
| AVR64DA64  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <---,-- Same presumed die,
| AVR64DA48  | `AVR     P:2D:1-3M2 (A3.KV00E.0)` |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E | 0 | <--/
| AVR64DA32  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <---,-- Same presumed die,
| AVR64DA28  | Please contribute                 |  AVR    | P:2 | D:1 | 3M2 |  A3  |  KV00E?| 0 | <--/
| AVR128DB64 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` |  AVR    | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <---,-- Same presumed die, same 5 character code
| AVR128DB48 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` |  AVR    | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <--/
| AVR128DB32 | Please contribute                 |  ?????  | P:2 | D:1 | 3M2 |  A5  |  KV00D?| 0 |
| AVR128DB28 | Please contribute                 |  ?????  | P:2 | D:1 | 3M2 |  A5  |  KV00D?| 0 |
| AVR128DA64 | `AVR     P:2D:1-3M2 (A6.KV001.0)` |`AVR    `| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <---,-- Same presumed die
| AVR128DA48 | `    AVR P:2D:1-3M2 (A6.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <--/
| AVR128DA32 | `    AVR P:2D:1-3M2 (A6.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <--- WTF on justification of the AVR field?
| AVR128DA32 | `    AVR P:2D:1-3M2 (A7.KV001.0)` |`    AVR`| P:2 | D:1 | 3M2 |  A7  |  KV001 | 0 | <--- A6 and A7 silicon coexists inthe wild!
| AVR128DA28 |  Please contribute                |  ?????  | P:2 | D:1 | 3M2 |  A?  |  KV001 | 0 |
| ATmega808  |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 | 
| ATmega809  |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega1608 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega1609 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   A  |  59B2? | 0 |
| ATmega3208 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| ATmega3209 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| ATmega3208 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   D  |  59B2? | 0 |
| ATmega3209 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   D  |  59B2? | 0 |
| ATmega4808 | `megaAVR P:0D:1-3M2 (01.59B20.0)' | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B20 | 0 | 
| ATmega4809 |  Please contribute                | megaAVR | P:0 | D:1 | 3M2 |   B  |  59B2? | 0 |
| t82x/t42x  | `tinyAVR P:0D:1-3M2 (01.59B0F.0)` | tinyAVR | P:0 | D:1 | 3M2 |   B  |  59B0F | 0 |
| t1624/6/7  | `tinyAVR P:0D:1-3M2 (04.59B0D.0)` | tinyAVR | P:0 | D:1 | 3M2 |   E  |  59B0D | 0 |
| t3224/6/7  | `tinyAVR P:0D:1-3M2 (00.59B0E.0)` | tinyAVR | P:0 | D:1 | 3M2 |   A  |  59B0E | 0 | 
| t202/4/6,402/4 |  Please contribute            | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B?? | 0 |
| t804/6/7,407| Please contribute                | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B?? | 0 |
| t1604/6/7  | Please contribute                 | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B?? | 0 |
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (00.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B14 | 0 | Unconfirmed in the wild
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (01.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 | **B**|  59B14 | 0 |
|t212/4/6,412/4|`tinyAVR P:0D:0-3M2 (02.59B14.0)`| tinyAVR | P:0 | D:0 | 3M2 | **C**|  59B14 | 0 | Unconfirmed in the wild
| t814/6/7,417 | Please contribute               | tinyAVR | P:0 | D:0 | 3M2 |   A  |  59B16 | 0 | 59B16 is a guess. 
| t1614/6/7  | `tinyAVR P:0D:0-3M2 (00.59B15.0)` | tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B15 | 0 | 
| t1614/6/7  | `tinyAVR P:0D:0-3M2 (01.59B15.0)` | tinyAVR | P:0 | D:0 | 3M2 | **B**|  59B15 | 0 | Unconfirmed in the wild
| t3216/7    | `tinyAVR P:0D:0-3M2 (00.59B17.0)` | tinyAVR | P:0 | D:0 | 3M2 |  *A* |  59B17 | 0 | Unconfirmed in the wild
| t3216/7    | `tinyAVR P:0D:0-3M2 (02.59B17.0)` | tinyAVR | P:0 | D:0 | 3M2 | **C**|  59B17 | 0 |

* These have been ordered with the intent of reading the SIB and sigrows (hell, probaly the whole data space that isn't SRAM is likely going to be dumped and recorded), then the encapsulation will be filed off, crappy die photos will be taken on a $30 digital microscope, and the dimensions and appearance of the dies compared. Another interesting comparison would be the 3217 vs 1617 (or 1616 - which should be the same die as the 1617 as I understand and less material to file away) - the 3217 has 32k of flash and 2k of SRAM. The 161x has 16k of flash **and 2k of SRAM** And an 817, would not only have smaller flash and ram, it would also be missing a chunk of peripherals. It will be interesting to see if I can use what I know about the chips to infer functionality associated with different areas of the die (there should be a sort of homogenous area that is twice as big in the 3217 vs 1617 for the flash, while the RAM will be the same size. Between the DD28 and 16/32DD20 parts, I should also be able to calculate which  

Pymcuprog lists the P:# as the version of the NVM controller it uses (P for programming), and the D:# is the version of the on-chip debugger (consistent with the datasheet) and the 3M2 is in reference to the "PDI oscillator" (does that mean the base clock speed is apx. 32 MHz? It's plausible, as the options we have for clock speed are 4, 8, 16, and 32 MHz, which would be what you'd naturally do if you were willing to allocate two bits to representing it, and were starting with a 32 MHz clock, right?). Then we get to the parens containing likely the most interesting information.... First, there's the die rev right there, without having to dig for it! Second, there's a cryptic 5 hex-digit value. I belive this identifies the die design. Devices widely belived to share a die all give the same value here. If this is the case, it jumps out that there are two bases - KV00 (the Dx-series, ie, good parts) and 59___, the Ex-series/tinyAVR (the generally lower end parts).

The first two characters are the SILICON DIE REV in represented as two hexadecimal digits, or so it appears

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
* On all parts except 0/1 tinyAVRs it is known that the parts use OCD v1 not v0. It is not yet known if any of them advanced to OCDv1.
* NVM numbers are 0: paged write without NRWW and fully mapped flash. 1: Not used (if I was guessing, I'd say they were toying with the possibility of releasing a device with paged writes, no RWW/NRWW, but with too much flash to fit it all in the data space - they may have even been thinking they were going to need to use it on the ATmega6408/9 (which doesn't exist, but the 4808/9 have a device ID (the one you read from sigrow) byte 2 that indicates a 64k part - so maybe (pure speculation) those parts were going to be 64k with a modified write procedure, but they were getting nervous as this was a critical moment for the company and product line, and the nvm controller development was not going well. Management lost patience before engineering had fixed the problems, canceled NVMctrl v1, told the appropriate parts of the team to move the mapped flash boundary down to 0x4000 and squeeze everything in, chopping off 16k of flash to make room. Meanwhile, it would appear that the group of engineers who was failing to deliver nvmctrl v1 was just reassigned to to v3, and while they finished, at least, the results are rather sad (see errata). I don't know how Microchip forgot how to make flash memory, but they seem to have.
* In the rare event that more than one die rev is known to exist in the wild, the ones belived to currently be in broad distribution are in **bold** and the ones that are old enough that few of them remain that have not been used in something in *itallics*
* For devices not yet released, we assumed the Ex's would continue to be 59'ers, and DU would be KV's. It is expected that flash writes on EB will be like the EA only hopefully with less errata, and that the DU will be a word-write part like the other Dx's, and that OCD version was unlikely to change (there are a few things that a debugger really needs to do. there are very few "nice to haves" that might be added on later though). And it was assumed that the Dx and Ex series would continue to use the 3M2 PDI oscillator. Not exactly profound, but it gives some idea of how much we know vs how much we don't know and how much we suspect but are not certain of, and how many we could become certain of as readers using parts we didn't have recorded SIBs for

## Help understand these by submitting the strings like the ones in the second column. 
It will be printed by SerialUPDI when any programming atempt is made and verbose outout enabled, and will show info for the connected chip, (so you can read the SIB without writing anything by selecting a chip that doesn't match the chip you connect and then tryingto program it with verbose mode enabled using SerialUPDI). 

To gather the data, it is sufficient to attempt a SerialUPDI upload to a correctly wired chip that is not the one you have selected in the IDE - it'll still print the full SIB (though it may error after that in current github DxCore version, because I need to tighten up the serial number printing code to work with the general case). 
