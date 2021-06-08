# AVR_Research
Investigations of AVR microcontrollers


This is where I will put anything I turn up while digging around maintaining my cores that I think may be of wider interest.

## The secrets of the signature row
Many of the undocumented bytes of the 64-byte sigrow on the tinyAVR 0/1/2-series parts are 0xFF (blank). There appears to be a 16-bit checksum. 
While preparing (ATtiny1624 boards for sale)[https://www.tindie.com/products/17598/], I ran the tuning sketch on all of them - and had it log the full sigrow. There are two unknown constants, and four unknown bytes with non-blank values on the ATtiny1624. 
(known information)[sigrow/README.md]
