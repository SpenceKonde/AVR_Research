# info on UPDI debugging
The UPDI information is unfortunately not publically disclosed by Microchip. Except they screwed up long ago, and released a copy of the datasheet that included the OCD key and the OCD bit:

The OCD is enabled by starting a UPDI session and sending KEY `0x4F43442020202020`, ascii `OCD     `. 

Further understanding will require 

This sets bit 1 in ASI_KEY_STATUS to 1, indicating that OCD is enabled. 

Thanks to @leonerd for that info.

## Other tips
A "serial spy" could likely be used. I suspect that the someone could in under an hour figure out what baud rate mEDBG used for UPDI, likely much less with either: 
1. Scope on the UPDI line
2. Processing and grepping the hex files for writes to the USART baud register address, (almost certainly this will be a pair of STS instructions), then looking back and praying that i]n the previous few instructions, the compiler had LDI'd the value in, calculate the baud rate from that.

Either way with the baud rate all you need is a serial adapter and maybe an opamp in voltage follower mode to buffer it (it's a very weak I/O on tinyAVR), and the RX pin on any serial adapte, and you're ready to log a debug session. Starting from this microchip tooling, you could then see what it was saying. You know every message from the computer will start with 0x55 (sync). Along with a memory map and assembly listing of what you're debugging, the logs will likely be fairly straightforward to understand, as I think the functions it has are really limited - There's probably some signature is writes to ASI_RESET_REQUEST to halt code execution without losing state in order to support a "break on demand", it has two hardware breakpoints that it would need a way to set, other breakpoints have to be done in software, and it just breaks on encountering the break instruction. In any event, I don't think what it does is terribly complicated; and how it does it will be based on UPDI as we know it. 
How many of the possible UPDI opcodes are taken? (including ones reserved for future poteentially longer addresses or larger sized writes. Well - actually only half of opcodes are accounted for. All opcodes where (opcode & 0x10) == 0x10 are not used - for NVMPROG. They may well be used for operation in debug mode. Likely all the ones with a 1 there are earmarked for non-NVMPROG uses. What does the debug need to do? In needs to manually break and exit break state on demand (as I said, I suspect that this is done with ASI_RESET_STATUS), it needs to allow reading of the values of IO space and sram - presumably the read functions used on the dataspace will (as they do in nvmprog) return the values stored in those locations of memory, it needs a way to read out the program counter, the 32 working registers... and it needs a single step command....

So, we now know the key, and which bit within ASI_KEY_STATUS it sets. We already know how it will read from data and program space, so the questions left are:
* Details of initialization process. 
* How it sets breakpoints.
* How we instruct the debugger connect the break-mechanism to the breakpoint detection (ie, the on-off switch for breakpoints - which may be global, or may be separate for hardware and software breakpoints. Depending on the flexibility of hardware breakpoints, this may be simple or rather complicated. . 
* How we read from the ~34 bytes of memory that UPDI can't - the 32 working registers of the CPU, and the 2 bytes that make up the program counter. 
* How to enter and exit break state (though as I noted, I have a theory of where this is to be found, and it would be in any case trivial to figure out once you're logging the sessions)
* How to single step (likely it's own instruction?)

**I think we're pretty well along the road - a few logged sessions with carefully kept records of debugging transactions would serve to crack this wide open.**
