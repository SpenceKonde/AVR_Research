# AVR_Research
Investigations of AVR microcontrollers


This is where I will put anything I turn up while digging around maintaining my cores that I think may be of wider interest.

## The secrets of the signature row
Many of the undocumented bytes of the 64-byte sigrow on the tinyAVR 0/1/2-series parts are 0xFF (blank). There appears to be a 16-bit checksum. 
While preparing [ATtiny1624 boards for sale](https://www.tindie.com/products/17598/), I ran the tuning sketch on all of them - and had it log the full sigrow. There are two unknown constants, and four unknown bytes with non-blank values on the ATtiny1624.


[known information](sigrow/README.md)

## Mysteries
These are things not adequately explained or where there is an inconsistency within the datasheet, and I am not aware of anyone having tried to sort out how the part(s) actually behave. This is concerned primarilly with the modern AVR parts in general, though a few notes relating to classic tinyAVR devices may be listed. 

Be sure to let me know if you know anything about this, and I'll move it to a solved mysteries page, with the answer and - if you want it - your name and a link to your website. If not specified, I'll credit github usernames. 

[Unsolved Mystery list](UnsolvedMysteries.md)

Anyone providing a proper investigation of the 828 ADC mystery has definitely earned some hardware, in addition to the prestige.
