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

Either way with the baud rate all you need is a serial adapter and maybe an opamp in voltage follower mode to buffer it (it's a very weak I/O on tinyAVR), and the RX pin on any serial adapte, and you're ready to log a debug session. You know that every message from the debugger will start with 0x55, making it considerably easier to follow what's going on. I suspect you would want a memory map and disassembly of it too to interpret what it's doing. I don't think what it does is terribly complicated; and will borrow heavily from public parts of UPDI. 

