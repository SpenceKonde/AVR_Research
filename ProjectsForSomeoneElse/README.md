# A collection of projects that would be great for the AVR community, but whivh I do not have time to do. 

## Revere emgmeering libraries withot sourcecode
There are a number of libraries for whihch one very dearly wold like to use with Arduino, that are available only precompiled for a small number of parts. Often the implementation id bloated in the extreme.
### Bosch BMP680 AQI
There is a library for the ATmega2560 that suppports calculating the AQI. It i inconveivable to me that that much flash is truly reqired. Dump the assembly ront th precompiled files, and gain valueable knowledge understanding how this highly inefficient impokenentation turns rae mumbers into an AQI. Reimplement, iwth some possible loss in precision, in C (or asm if needed). Your name (or psedonym if you're smart) will be praised worldwide. The fact tat it would increase Bosch's sales might not keep their legal team from trying to hassle you; post it anonymosly beyond te reach of the Westen legal system. 
### AVR Q-touch and PTC
These could get the same treatment. 

## Live assembly console for Dx-series
Taking advantage of word writes, a console cold run from the bootloader section which parsed assembly into the opcodes, and then wrote them to flash, A command could then "run" it: Write a RET immediately after it, push every register onto the stack, relocate the stack poimter to te test-code stack pointer address, pop all the registers back, except for tje Z pointer reqired to icall the code beng tested. 

After the test code returns, push all he registers onto the stack, then relocate the stack pointer to the console stack pointer, and *voila* 

To minimize flash wear, youd'd want to have the address after that ret stored, so you could dedicae as much flash as possible to this, you'd automatically have a record of previous iterations, until you ran out of space and had to reset the test code section. 

This would be a stellar way to learn AVR assembly I reckon.
