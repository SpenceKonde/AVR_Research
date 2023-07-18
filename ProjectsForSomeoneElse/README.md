# A collection of projects that would be great for the AVR community, but whivh I do not have time to do.

## Revere emgmeering libraries withot sourcecode
There are a number of libraries for which one very dearly wold like to use with Arduino, that are available only precompiled for a small number of parts. Often the implementation is bloated in the extreme, eg, even the brifest glance over the source code shows that they are using far too many flosting point values, or they're using a uint64_t with a bitmask
### Bosch BMP680 AQI
There is a library for the ATmega2560 that suppports calculating the AQI. It i inconveivable to me that that much flash is truly reqired. Dump the assembly from the precompiled files, and you will gain valueable knowledge on how to use this sensor to find an air quality index.  Reimplement, iwth some possible loss in precision, in C (or asm if needed). Your name (or psedonym if you're smart) will be praised worldwide. The fact tat it would increase Bosch's sales might not keep their legal team from trying to hassle you; post it anonymosly beyond the reach of the Westen legal system.
### AVR Q-touch and PTC
These have been getting this treatment. I expect to see a touch library for ATtiny 81x, 161x, and 321x in the near future, and while there's an arduino compatible library from official sources coming for the PTC on DA-series, from what I know about it it will call the pre-compiled library, which at least one individual working on a library like that responded to the effect of "Great, that'll be a great source"

## Live assembly console for Dx-series
Taking advantage of word writes, a console could run from an abnormally large bootloader section which parsed assembly into opcodes, and then wrote them to flash, A command could then "run" it: Write a RET immediately after the point at which the user gave the run command. Then, push every register onto the stack, relocate the stack poimter to te test-code stack pointer address, pop all the registers that were pushed after running the previous assembly block back, except for the Z pointer reqired to icall the code beng tested. (And the first instruction of the code block would of course be silently preceeded by a few to restore those too).

After the test code returns, push all the registers onto the stack, then relocate the stack pointer to the console stack pointer, and *voila*

To minimize flash wear, youd'd want to have the address after that ret stored, and dedicate as much flash as possible to this, using it like a ring buffer. Maybe have it stop just before the last page, so the last page could be written to a constant jmp back to the start of the first page). You would thus be able to dump the flash and see a record of your last several uploads "for free"

The result for the user would be a stellar way to learn AVR assembly I reckon.

And for the author who had a basic understanding of avr asm (which I hope such an author would have) this would give them a much deeper understanding of it. The implementation would very quickly drive home the profound differences in the number of opcodes that fall under the same instruction. (std, ldd, the 6 immediates rcall, and rjmp each take 1/16th of all possible instructions. 4096 each! In/Out together take another 16th. 11/16ths of opcodes are allocated to just 12 instructions,

### Errata note
In late 2021, a "Datasheet clarification" was issued regarding flash endurance. This usage of the word "clarification" is somewhat unusual - normally it means that part of a document was confusing or unclear, and they've made it easier to understand. However the datasheet here was never unclear - the part at issue is a single number listed even in the summary section: 10,000 erase/rewrite cycles became "1,000 rewrite cycles". That's not what I would describe as clarifying. They absolutely though their parts were good for 10k writes, and only later discovered that they were not.

That initially sounds really bad. My initial pondering on that one led me to the conclusion that it was implausible that the 10k spec wasn't experimentally verified at least under favorable conditions; I suspected that it was only a problem under extremes of temperature (the E-spec parts do go all the way up to 125C, and the maximum temperature is the worst case scenario
