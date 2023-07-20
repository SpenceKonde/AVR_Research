  During UPDI programming, the programmer asks the chip for it's System Information Block. The chip responds with either 8 or 16, or 32 bytes of data, depending on how much the programmer asked for. Only the 8 and 16 byte forms are documented - but pymcuprog knows about a way to get 32 bytes of data. Here are some example strings:
| Part       | SIB                               | Family| NVM | OCD | OSC | Rev  |  CODE  | ? | Note
|------------|-----------------------------------|-------|-----|-----|-----|------|--------|---|-----
| AVR8EA32   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR8EA28   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR8EA48   | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR16EA32  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR16EA28  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR16EA48  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR32EA32  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  B1  |  KV00? | 0 |
| AVR32EA28  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  B1  |  KV00? | 0 |
| AVR32EA48  | `AVR     P:3D:1-3M2 (B1.59F02.0)` | AVR   | P:3 | D:1 | 3M2 |  B1  |  59F02 | 0 | <---- This implies (supported by observations like the 20/16 MHz oscillator and other limitations) that the EA is closer to a tinyAVR than a Dx-series. That it apparently underwent a *major* die rev sort of implies that development did not progress as smoothly as imagined. Timing wise, I think they had to have the Ex in progress when the 2-series was released. 
| AVR64EA32  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR64EA28  | Please contribute                 | AVR   | P:3 | D:1 | 3M2 |  ??  |  KV00? | 0 |
| AVR64DD14  | `AVR     P:2D:1-3M2 (A1.KV00U.0)` | AVR   | P:2 | D:1 | 3M2 |  A1  |  KV00U | 0 | <---,-- Same presumed die
| AVR64DD20  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR16DD28  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die
| AVR16DD32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR32DD14  | `AVR     P:2D:1-3M2 (A1.KV00R.0)` | AVR   | P:2 | D:1 | 3M2 |  A1  |  KV00R | 0 | <---,-- Same presumed die, same 5 character code
| AVR32DD20  | `AVR     P:2D:1-3M2 (A1.KV00R.0)` | AVR   | P:2 | D:1 | 3M2 |  A1  |  KV00R | 0 | <--/
| AVR32DD28  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR32DD32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR64DD28  | 'AVR     P:2D:1-3M2 (A3.KV00K.0)  | AVR   | P:2 | D:1 | 3M2 |  A3  |  KV00K | 0 | <---,-- Same presumed die, same 5 character code
| AVR64DD32  | `AVR     P:2D:1-3M2 (A3.KV00K.0)` | AVR   | P:2 | D:1 | 3M2 |  A3  |  KV00K | 0 | <--/
| AVR32DB48  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR32DB32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die.
| AVR32DB28  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR32DB48  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR32DB32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR32DB28  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR64DB48  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR64DB32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | 
| AVR64DA64  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR64DA48  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR64DA32  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <---,-- Same presumed die,
| AVR64DA28  | Please contribute                 | AVR   | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR128DB64 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` | AVR   | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <---,-- Same presumed die, same 5 character code
| AVR128DB48 | `AVR     P:2D:1-3M2 (A5.KV00D.0)` | AVR   | P:2 | D:1 | 3M2 |  A5  |  KV00D | 0 | <--/
| AVR128DB32 | Please contribute                 | ????? | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR128DB28 | Please contribute                 | ????? | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| AVR128DA64 | `AVR     P:2D:1-3M2 (A6.KV001.0)` | AVR   | P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <---,-- Same presumed die
| AVR128DA48 | Please contribute                 | ????? | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 | <--/
| AVR128DA32 | `    AVR P:2D:1-3M2 (A6.KV001.0)` |    AVR| P:2 | D:1 | 3M2 |  A6  |  KV001 | 0 | <--- WTF on justification of the AVR field?
| AVR128DA32 | `    AVR P:2D:1-3M2 (A7.KV001.0)` |    AVR| P:2 | D:1 | 3M2 |  A7  |  KV001 | 0 | <--- A6 and A7 silicon coexists inthe wild!
| AVR128DA28 |  Please contribute                | ????? | P:2 | D:1 | 3M2 |  A?  |  KV00? | 0 |
| ATmega808  |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 | 
| ATmega809  |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| ATmega1608 |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| ATmega1609 |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| ATmega3208 |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| ATmega3209 |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| ATmega4808 | `megaAVR P:0D:1-3M2 (01.59B20.0)' |megaAVR| P:0 | D:1 | 3M2 |   B  |  59B20 | 0 | 
| ATmega4809 |  Please contribute                |megaAVR| P:0 | D:1 | 3M2 |   ?  |  59B2? | 0 |
| t202/4/6,402/4 |  Please contribute            |tinyAVR| P:0 | D:? | 3M2 |   A  |  59B?? | 0 |
| t804/6/7,407| Please contribute                |tinyAVR| P:0 | D:? | 3M2 |   A  |  59B?? | 0 |
| t1604/6/7  | Please contribute                 |tinyAVR| P:0 | D:? | 3M2 |  *A* |  59B?? | 0 |
| t212/4/6,412/4 |  Please contribute            |tinyAVR| P:0 | D:0 | 3M2 |  *A* |  59B14 | 0 |
| t212/4/6,412/4 | `tinyAVR P:0D:0-3M2 (01.59B14.0)`|tinyAVR| P:0 | D:0 | 3M2 | **B**|  59B14 | 0 |
| t212/4/6,412/4 |  Please contribute            |tinyAVR| P:0 | D:? | 3M2 | **C**|  59B14 | 0 |
| t814/6/7,417 || Please contribute              |tinyAVR| P:0 | D:? | 3M2 |   A  |  59B?? | 0 |
| t1614/6/7  | Please contribute                 |tinyAVR| P:0 | D:? | 3M2 |  *A* |  59B?? | 0 |
| t1614/6/7  | Please contribute                 |tinyAVR| P:0 | D:? | 3M2 | **B**|  59B?? | 0 |
| t3216/7    | Please contribute                 |tinyAVR| P:0 | D:? | 3M2 |  *A* |  59B?? | 0 |
| t3216/7    | Please contribute                 |tinyAVR| P:0 | D:? | 3M2 | **C**|  59B?? | 0 |
| t82x/t42x  | Please contribute                 |tinyAVR| P:0 | D:1 | 3M2 |   A  |  59B?? | 0 |
| t1624/6/7  | `tinyAVR P:0D:1-3M2 (04.59B0D.0)` |tinyAVR| P:0 | D:1 | 3M2 |   E  |  59B0D | 0 |
| t3226/3227 | `tinyAVR P:0D:1-3M2 (00.59B0E.0)` |tinyAVR| P:0 | D:1 | 3M2 |   A  |  59B0E | 0 |

Pymcuprog lists the P:# as the version of the NVM controller it uses (P for programming), and the D:# is the version of the on-chip debugger (consistent with the datasheet) and the 3M2 is in reference to the "PDI oscillator" (does that mean the base clock speed is apx. 32 MHz? It's plausible, as the options we have for clock speed are 4, 8, 16, and 32 MHz, which would be what you'd naturally do if you were willing to allocate two bits to representing it, and were starting with a 32 MHz clock, right?). Then we get to the parens containing likely the most interesting information.... First, there's the die rev right there, without having to dig for it! Second, there's a cryptic 5 hex-digit value. I belive this identifies the die design. Devices widely belived to share a die all give the same value here. If this is the case, it jumps out that there are two bases - KV00 (the Dx-series, ie, good parts) and 59___, the Ex-series/tinyAVR (the generally lower end parts).

The first two characters are the SILICON DIE REV in represented as two hexadecimal digits, or so it appears

After that some representation of the design in 5 character, unique per die, followed by .0 is seen. 

It appears that Dx-series parts have identifiers starting with KV0, and tinyAVR and Ex have values starting with 59B for tinyAVR and 59F for Ex, confirming that the Ex-series are not Dx-series parts that have evolved to have lower pincounts, but tinyAVR series parts that are evolving in the direction of more expansive features. 

### Table notes:
Cases where pieces of the 5-digit codes can easily be deduced have been and ?'s left in place of the unknown letters. 
Cases where we know the P (always), D (non- 0/1), or OSC value (always 3M2) have been filled in, as have cases where there isnt any question about the what the family will be (so some DA/DB are left as ?'s, since they are inconsistent in how they justify the "AVR" (`    AVR` vs `AVR    `, the first of them being the result you get when you take "megaAVR" or "tinyAVR" and replace the first four letters with spaces.

## Help understand these by submitting of the strings like the ones in the second column. 
It will be printed by SerialUPDI when any programming atempt is made and verbose outout in, and will show info for the connected target chip) (so you can test thiserialUPDI from the currently connected target (so you can select, say, a tiny412, and then go through the whole AVR DX series or something attempting to program and getting that string in the second column above - al I need is the string and the part number of the device connected)
To gather the data, it is sufficient to attempt a SerialUPDI upload to a correctly wired chip that is not the one you have selected in the IDE - the IDE will always print this in verbose mode before it gets to where it rejects a programming attempt targeting a different part

