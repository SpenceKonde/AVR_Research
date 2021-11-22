# Memory Map and Assembly Listing processors
My cores generate memory maps and assembly listings when exporting compiled binaries. That's a very useful feature, if I do say so myself. 

## The memory map - the larger of the problems. 
The memory maps would be a great tool for shrinking sketch size, but for one tiny little problem. The formatting is such perverse garbage that the human eye can't read them and you need to practically spell it out for Excel and other spreadsheet software to get them to import without mangling anything...  There are four major factors here. 
1. nm assumes symbol names are at most 20 characters long, but even the toolchain itself ends up making many names much longer than this. Compounding that name issue is the fact that variables are names with the rather verbose titles, like "unsigned long" instead of uint32_t, and so on, making the names even longer. But it doesn't truncate the name, it just makes that cell of that column extend further, making it no longer align with the other columns... 
2. nm outputs sizes and addresses in hex, as it should, but without any prefix to indicate that. This results in, say. Excel on default settings, interpreting the ones with no digits above 9 as decimal numbers, and the rest as strings, requiring difficult repair work. 
3. The Line column is left blank, while the line number is instead appended to the file name. Furthermore, there's a tab instead of a `|` between the section and the filename, and avr-libc-supplied files have the whole longass filepath to a path that doesn't exist on the user's computer, and the files that do exist have such long path names that you either have wordwrap off and a horizontal scroll bar, or wordwrap on, amd interfere with reading of the table. 
4. It contains a shedload of useless symbols that don't belong in a memory map - or at least not one aimed at Arduino-land. Do you need to see every vector listed, even though all but one of them are not defined and point to the same address? Not really - there's only one that matters. Do you need to see the ctors/dtors/trampolines section start and end addresses... when they're empty? Or `__temp_reg__`, `__zero_reg__` or the handful of registers located in the I/O space? None of that is useful when trying to diagnose a bloated sketch. 

## clean_map.py
clean_map.py is a (very) crude sketch that takes a .map file name it's only argument. It outputs a file of the same name, in the same location, wnding in .clean.map. Bear in mind that I do not know any python as you look at the code (that's the nice thing about python, you don't have to know what the hell you're doing to bang together crappy code to get a job done). You can see that I repeatedly use methods that I'd already used when better ones were available for the task, among doubtlessly many flaws. But I don't know python, so I don't know what those are. Feel free to PR a better version!

Before:
```text

Symbols from C:\Users\Spence\AppData\Local\Temp\arduino_build_996422/sketch_nov20a.ino.elf:

Name                  Value   Class        Type         Size     Line  Section

__heap_end          |00000000|   W  |            NOTYPE|        |     |*ABS*
__TEXT_REGION_ORIGIN__|00000000|   W  |            NOTYPE|        |     |*ABS*
__tmp_reg__         |00000000|   a  |            NOTYPE|        |     |*ABS*
__zero_reg__        |00000001|   a  |            NOTYPE|        |     |*ABS*
__FUSE_REGION_LENGTH__|00000010|   A  |            NOTYPE|        |     |*ABS*
__CCP__             |00000034|   a  |            NOTYPE|        |     |*ABS*
__RAMPZ__           |0000003b|   a  |            NOTYPE|        |     |*ABS*
__SP_L__            |0000003d|   a  |            NOTYPE|        |     |*ABS*
__SP_H__            |0000003e|   a  |            NOTYPE|        |     |*ABS*
__SREG__            |0000003f|   a  |            NOTYPE|        |     |*ABS*
__EEPROM_REGION_LENGTH__|00000200|   A  |            NOTYPE|        |     |*ABS*
__vector_default    |00000200|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:61
__vectors           |00000200|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:61
__ctors_end         |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__ctors_start       |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__dtors_end         |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__dtors_start       |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__init              |000002a8|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__trampolines_end   |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__trampolines_start |000002a8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__do_copy_data      |000002b4|   T  |            NOTYPE|0000001a|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
_initThreeStuff()   |000002b4|   T  |              FUNC|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
__do_clear_bss      |000002ce|   T  |            NOTYPE|00000010|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2441
.do_clear_bss_loop  |000002d6|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2446
.do_clear_bss_start |000002d8|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2448
__bad_interrupt     |000002e2|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_1          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_10         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_11         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_12         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_13         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_14         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_15         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_16         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_17         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_18         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_19         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_2          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_20         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_21         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_22         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_23         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_24         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_25         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_26         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_27         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_28         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_29         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_3          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_30         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_32         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_33         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_34         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_35         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_36         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_37         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_38         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_39         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_4          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_40         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_41         |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_5          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_6          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_7          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_8          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
__vector_9          |000002e2|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:315
digitalWrite        |000002e4|   t  |              FUNC|0000016a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring_digital.c:348
__LOCK_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
__SIGNATURE_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
__USER_SIGNATURE_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
__vector_31         |0000044e|   T  |              FUNC|00000050|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:128
main                |0000049e|   T  |              FUNC|00000286|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:49
_exit               |00000724|   T  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2278
exit                |00000724|   W  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2278
__stop_program      |00000726|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2280
__data_load_start   |00000728|   A  |            NOTYPE|        |     |*ABS*
_etext              |00000728|   T  |            NOTYPE|        |     |.text
__data_load_end     |00000786|   A  |            NOTYPE|        |     |*ABS*
__DATA_REGION_LENGTH__|00004000|   A  |            NOTYPE|        |     |*ABS*
__stack             |00007fff|   W  |            NOTYPE|        |     |*ABS*
__RODATA_PM_OFFSET__|00008000|   A  |            NOTYPE|        |     |*ABS*
__TEXT_REGION_LENGTH__|00020000|   A  |            NOTYPE|        |     |*ABS*
__DATA_REGION_ORIGIN__|00804000|   A  |            NOTYPE|        |     |*ABS*
__data_start        |00804000|   D  |            NOTYPE|        |     |.data
digital_pin_to_bit_position|00804000|   d  |            OBJECT|00000017|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\28pin-standard/pins_arduino.h:262
digital_pin_to_port |00804017|   d  |            OBJECT|00000019|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\28pin-standard/pins_arduino.h:231
digital_pin_to_timer|00804030|   d  |            OBJECT|00000017|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\28pin-standard/pins_arduino.h:343
digital_pin_to_bit_mask|00804047|   d  |            OBJECT|00000017|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\28pin-standard/pins_arduino.h:303
__bss_start         |0080405e|   B  |            NOTYPE|        |     |.bss
__data_end          |0080405e|   D  |            NOTYPE|        |     |.data
_edata              |0080405e|   D  |            NOTYPE|        |     |.data
timer_millis        |0080405e|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:58
__bss_end           |00804062|   B  |            NOTYPE|        |     |.bss
_end                |00804062|   N  |            NOTYPE|        |     |.comment
__eeprom_end        |00810000|   N  |            NOTYPE|        |     |.comment
```
After:
```text
Program Space (flash):
Name                 |  Address | Class |  Type  |   Size   |  Section |  Line | File
__vector_default     | 0x000000 |     W | NOTYPE |          |    .text |    61 | (gcc) gcrt1.S
__vectors            | 0x000000 |     T | NOTYPE |          |    .text |    61 | (gcc) gcrt1.S
__init               | 0x0000a4 |     W | NOTYPE |          |    .text |   230 | (gcc) gcrt1.S
_initThreeStuff()    | 0x0000b0 |     T |   FUNC | 0x000012 |    .text |   162 | DxCore/megaavr/cores/dxcore/main.cpp
__do_copy_data       | 0x0000c2 |     T | NOTYPE | 0x00001a |    .text |  2373 | (gcc) lib1funcs.S
__do_clear_bss       | 0x0000dc |     T | NOTYPE | 0x000010 |    .text |  2441 | (gcc) lib1funcs.S
.do_clear_bss_loop   | 0x0000e4 |     t | NOTYPE |          |    .text |  2446 | (gcc) lib1funcs.S
.do_clear_bss_start  | 0x0000e6 |     t | NOTYPE |          |    .text |  2448 | (gcc) lib1funcs.S
__bad_interrupt      | 0x0000f0 |     T | NOTYPE |          |    .text |   315 | (gcc) gcrt1.S
digitalWrite         | 0x0000f2 |     t |   FUNC | 0x00016a |    .text |   348 | DxCore/megaavr/cores/dxcore/wiring_digital.c
__vector_30          | 0x00025c |     T |   FUNC | 0x000050 |    .text |   128 | DxCore/megaavr/cores/dxcore/wiring.c
main                 | 0x0002ac |     T |   FUNC | 0x000290 |    .text |    49 | DxCore/megaavr/cores/dxcore/main.cpp
__stop_program       | 0x00053e |     t | NOTYPE |          |    .text |  2280 | (gcc) lib1funcs.S
__data_load_start    | 0x000540 |     A | NOTYPE |          |    *ABS* |       |  
__data_load_end      | 0x00059e |     A | NOTYPE |          |    *ABS* |       |  

Data Space (SRAM):
Name                        |  Address | Class |  Type  |   Size   |  Section |  Line | File
digital_pin_to_bit_position | 0x804000 |     d | OBJECT | 0x000017 |    .data |   262 | DxCore/megaavr/variants/28pin-standard/pins_arduino.h
digital_pin_to_port         | 0x804017 |     d | OBJECT | 0x000019 |    .data |   231 | DxCore/megaavr/variants/28pin-standard/pins_arduino.h
digital_pin_to_timer        | 0x804030 |     d | OBJECT | 0x000017 |    .data |   343 | DxCore/megaavr/variants/28pin-standard/pins_arduino.h
digital_pin_to_bit_mask     | 0x804047 |     d | OBJECT | 0x000017 |    .data |   303 | DxCore/megaavr/variants/28pin-standard/pins_arduino.h
__bss_start                 | 0x80405e |     B | NOTYPE |          |     .bss |       |  
__data_end                  | 0x80405e |     D | NOTYPE |          |    .data |       |  
timer_millis                | 0x80405e |     b | OBJECT | 0x000004 |     .bss |    58 | DxCore/megaavr/cores/dxcore/wiring.c
__bss_end                   | 0x804062 |     B | NOTYPE |          |     .bss |       |  
_end                        | 0x804062 |     N | NOTYPE |          | .comment |       |  
```

Much better, no? 

## Assembly listings
The assembly listings are a lot more usable (unless using Optiboot board def with DxCore, but that's a separate issue)
There is are only two problems here, first, it sometimes expresses offsets and addresses very unhelpfully, finding the least-useful sympbol to express addresses relative to, for example,this direct store to address 0x800A01:
```text
"40a:	90 93 01 0a 	sts	0x0A01, r25	; 0x800a01 <__TEXT_REGION_LENGTH__+0x7e0a01>
```
Now, that's a peripheral control register (being betweeen 0x003F and 0x103F - while it'd be sweet to know that it relates to TCA - just showing something like <Peripheral register 0x0A0> would be a lot better than that. And really, it wouldn't even be that hard to make it do like <TCA0 + 0x0001> (the trick is that they aren't changing where they put the peripherals on modern AVRs - on any post-2016 AVR, 0x0A00 to 0x0A40 is TCA0). Sometimes the values are nonsensical. "`__LOCK_REGIOMN_LENGTH__` which is 0x400 apparently. Which means it makes loads of sense to express the destination of that relative jump that lands at 0x520 as `__LOCK_REGION_LENGTH__ + 0x120` There ain't no section of memory on those things that has any clearly deliniated area 1024 bytes in size! Where did they get 0x400 from. Unless the lock region is everything from the NVMCTRL registers starting at 0x1000 to the EEPROM at 0x3400? *shrug* Whatever the case may be, it's not of practical use. These should ideally give the offset from the peripheral if they're under 0x1040, and if they're in RAM and got a useless offset, it should be replaced with a useful one if possible. Addresses in flash are the hardest, since ideally you'd want to have it find the destination, then iterate upwards until it found a line with no spaces ending in `()`, then move down until you found the first instruction, and subtract that from the destination yielding the output that avr-objdump is supposed to.

The other issue is more of a nitpick - but everything that comes from the avr-gcc .S files get the linenumber included for every single instruction. 
How is this:
```
000000c2 <__do_copy_data>:
__do_copy_data():
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
  c2:	10 e4       	ldi	r17, 0x40	; 64
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2374
  c4:	a0 e0       	ldi	r26, 0x00	; 0
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2375
  c6:	b0 e4       	ldi	r27, 0x40	; 64
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2376
  c8:	e0 e4       	ldi	r30, 0x40	; 64
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2377
  ca:	f5 e0       	ldi	r31, 0x05	; 5
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2378
  cc:	00 e0       	ldi	r16, 0x00	; 0
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2379
  ce:	0b bf       	out	0x3b, r16	; 59
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2380
  d0:	02 c0       	rjmp	.+4      	; 0xd6 <__do_copy_data+0x14>
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2382
  d2:	07 90       	elpm	r0, Z+
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2383
  d4:	0d 92       	st	X+, r0
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2385
  d6:	ae 35       	cpi	r26, 0x5E	; 94
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2386
  d8:	b1 07       	cpc	r27, r17
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2387
  da:	d9 f7       	brne	.-10     	; 0xd2 <__do_copy_data+0x10>

000000dc <__do_clear_bss>:
__do_clear_bss():
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2441
  dc:	20 e4       	ldi	r18, 0x40	; 64
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2442
  de:	ae e5       	ldi	r26, 0x5E	; 94
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2443
  e0:	b0 e4       	ldi	r27, 0x40	; 64
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2444
  e2:	01 c0       	rjmp	.+2      	; 0xe6 <.do_clear_bss_start>

000000e4 <.do_clear_bss_loop>:
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2446
  e4:	1d 92       	st	X+, r1

000000e6 <.do_clear_bss_start>:
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2448
  e6:	a2 36       	cpi	r26, 0x62	; 98
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2449
  e8:	b2 07       	cpc	r27, r18
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2450
  ea:	e1 f7       	brne	.-8      	; 0xe4 <.do_clear_bss_loop>
.do_clear_bss_start():
../../../../crt1/gcrt1.S:314
  ec:	df d0       	rcall	.+446    	; 0x2ac <main>
../../../../crt1/gcrt1.S:315
  ee:	26 c2       	rjmp	.+1100   	; 0x53c <_exit>
```
more useful than this:
```
000000c2 <__do_copy_data>:
__do_copy_data():
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
  c2:	10 e4       	ldi	r17, 0x40	; 64
  c4:	a0 e0       	ldi	r26, 0x00	; 0
  c6:	b0 e4       	ldi	r27, 0x40	; 64
  c8:	e0 e4       	ldi	r30, 0x40	; 64
  ca:	f5 e0       	ldi	r31, 0x05	; 5
  cc:	00 e0       	ldi	r16, 0x00	; 0
  ce:	0b bf       	out	0x3b, r16	; 59
  d0:	02 c0       	rjmp	.+4      	; 0xd6 <__do_copy_data+0x14>
  d2:	07 90       	elpm	r0, Z+
  d4:	0d 92       	st	X+, r0
  d6:	ae 35       	cpi	r26, 0x5E	; 94
  d8:	b1 07       	cpc	r27, r17
  da:	d9 f7       	brne	.-10     	; 0xd2 <__do_copy_data+0x10>

000000dc <__do_clear_bss>:
__do_clear_bss():
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2441
  dc:	20 e4       	ldi	r18, 0x40	; 64
  de:	ae e5       	ldi	r26, 0x5E	; 94
  e0:	b0 e4       	ldi	r27, 0x40	; 64
  e2:	01 c0       	rjmp	.+2      	; 0xe6 <.do_clear_bss_start>

000000e4 <.do_clear_bss_loop>:
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2446
  e4:	1d 92       	st	X+, r1

000000e6 <.do_clear_bss_start>:
/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2448
  e6:	a2 36       	cpi	r26, 0x62	; 98
  e8:	b2 07       	cpc	r27, r18
  ea:	e1 f7       	brne	.-8      	; 0xe4 <.do_clear_bss_loop>
.do_clear_bss_start():
../../../../crt1/gcrt1.S:314
  ec:	df d0       	rcall	.+446    	; 0x2ac <main>
  ee:	26 c2       	rjmp	.+1100   	; 0x53c <_exit>
```
But the first one is harder to read - and assembly listings were too easy to read right?

I would also like to make it count up how many times each instruction was used (ie, ld was used 50 times, ldd was used 60 times, std was used 102 times and so on), and what variation (eg, ST X, ST Y+, and so on. Then I'll try to convince the masses (you all) to run it on your code, and send me the stats on code you've written (or code others have written, just keep it separate) so I can  do statistics on them, and see what instructions are used most and least, and how "clumpy" different instructions are (indications from 2 test sketchs are that instruction usage is likely to be very clumpy - with some code using certain instructions extensively, and others not touching them. This is mostly for curiosity, and the sake of pretty graphs... 
The real prize would be to get a big fat wad of listings *written without Arduino or anything that uses Arduino cores*, so we could see how the general inefficiency of Arduino manifests in the instruction usage. My guess is push and pop will be way overused on Arduino sketches. Even doing just 2 cketches answered my idle question "So AVRxt does push and ST faster, but LDS slower. I run into that LDS thing a lot when writing assembly, was that penalty really worth it? (answer: yes, by a landslide. LDS is overrepresented in assembly that humans set eyes on, and is actually rather rare in the wild; while the most common instructions are push, pop and std, which are underrepresented in such code.
