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

Before (It looks fine until about halfway through - exactly where the important part starts):
```text


Symbols from C:\Users\Spence\AppData\Local\Temp\arduino_build_761867/DriftAnimate_V2.ino.elf:

Name                  Value   Class        Type         Size     Line  Section

__heap_end          |00000000|   W  |            NOTYPE|        |     |*ABS*
__TEXT_REGION_ORIGIN__|00000000|   W  |            NOTYPE|        |     |*ABS*
__tmp_reg__         |00000000|   a  |            NOTYPE|        |     |*ABS*
__tmp_reg__         |00000000|   a  |            NOTYPE|        |     |*ABS*
__zero_reg__        |00000001|   a  |            NOTYPE|        |     |*ABS*
__zero_reg__        |00000001|   a  |            NOTYPE|        |     |*ABS*
__FUSE_REGION_LENGTH__|00000010|   A  |            NOTYPE|        |     |*ABS*
__CCP__             |00000034|   a  |            NOTYPE|        |     |*ABS*
__CCP__             |00000034|   a  |            NOTYPE|        |     |*ABS*
__RAMPZ__           |0000003b|   a  |            NOTYPE|        |     |*ABS*
__RAMPZ__           |0000003b|   a  |            NOTYPE|        |     |*ABS*
__SP_L__            |0000003d|   a  |            NOTYPE|        |     |*ABS*
__SP_L__            |0000003d|   a  |            NOTYPE|        |     |*ABS*
__SP_H__            |0000003e|   a  |            NOTYPE|        |     |*ABS*
__SP_H__            |0000003e|   a  |            NOTYPE|        |     |*ABS*
__SREG__            |0000003f|   a  |            NOTYPE|        |     |*ABS*
__SREG__            |0000003f|   a  |            NOTYPE|        |     |*ABS*
__EEPROM_REGION_LENGTH__|00000200|   A  |            NOTYPE|        |     |*ABS*
__vector_default    |00000200|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:61
__vectors           |00000200|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:61
__trampolines_end   |000002f4|   T  |            NOTYPE|        |     |.text
__trampolines_start |000002f4|   T  |            NOTYPE|        |     |.text
mode10Name          |000002f4|   t  |            OBJECT|00000009|     |.text
mode9Name           |000002fd|   t  |            OBJECT|00000009|     |.text
mode8Name           |00000306|   t  |            OBJECT|00000009|     |.text
mode7Name           |0000030f|   t  |            OBJECT|00000009|     |.text
mode6Name           |00000318|   t  |            OBJECT|00000009|     |.text
mode5Name           |00000321|   t  |            OBJECT|00000009|     |.text
mode4Name           |0000032a|   t  |            OBJECT|00000009|     |.text
mode3Name           |00000333|   t  |            OBJECT|00000009|     |.text
mode2Name           |0000033c|   t  |            OBJECT|00000009|     |.text
mode1Name           |00000345|   t  |            OBJECT|00000009|     |.text
mode0Name           |0000034e|   t  |            OBJECT|00000009|     |.text
mode7R2             |00000357|   t  |            OBJECT|00000008|     |.text
mode4R2             |0000035f|   t  |            OBJECT|00000008|     |.text
mode5R1             |00000367|   t  |            OBJECT|00000008|     |.text
mode2R2             |0000036f|   t  |            OBJECT|00000008|     |.text
mode1R1             |00000377|   t  |            OBJECT|00000008|     |.text
mode1R0             |0000037f|   t  |            OBJECT|00000008|     |.text
pallete10           |00000387|   t  |            OBJECT|00000008|     |.text
pallete9            |0000038f|   t  |            OBJECT|00000008|     |.text
pallete8            |00000397|   t  |            OBJECT|00000008|     |.text
pallete7            |0000039f|   t  |            OBJECT|00000008|     |.text
pallete6            |000003a7|   t  |            OBJECT|00000008|     |.text
pallete5            |000003af|   t  |            OBJECT|00000008|     |.text
pallete4            |000003b7|   t  |            OBJECT|00000008|     |.text
pallete3            |000003bf|   t  |            OBJECT|00000008|     |.text
pallete2            |000003c7|   t  |            OBJECT|00000008|     |.text
pallete1            |000003cf|   t  |            OBJECT|00000008|     |.text
pallete0            |000003d7|   t  |            OBJECT|00000008|     |.text
mode0R0             |000003df|   t  |            OBJECT|00000008|     |.text
mode1L5             |000003e7|   t  |            OBJECT|00000008|     |.text
mode1L4             |000003ef|   t  |            OBJECT|00000008|     |.text
mode1L3             |000003f7|   t  |            OBJECT|00000008|     |.text
mode1L2             |000003ff|   t  |            OBJECT|00000008|     |.text
__LOCK_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
__SIGNATURE_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
__USER_SIGNATURE_REGION_LENGTH__|00000400|   A  |            NOTYPE|        |     |*ABS*
mode1L1             |00000407|   t  |            OBJECT|00000008|     |.text
mode1L0             |0000040f|   t  |            OBJECT|00000008|     |.text
mode0L2             |00000417|   t  |            OBJECT|00000008|     |.text
mode0L1             |0000041f|   t  |            OBJECT|00000008|     |.text
mode0L0             |00000427|   t  |            OBJECT|00000008|     |.text
defaultValueRight   |0000042f|   t  |            OBJECT|00000058|     |.text
defaultValueLeft    |00000487|   t  |            OBJECT|00000058|     |.text
getModeRatio(unsigned int)::__c|000004df|   t  |            OBJECT|0000001a|     |.text
leftValues          |000004f9|   t  |            OBJECT|00000020|     |.text
getModeColors(unsigned char*, unsigned char*, unsigned char*, unsigned long)::__c|00000519|   t  |            OBJECT|0000001a|     |.text
colorPallete        |00000533|   t  |            OBJECT|00000108|     |.text
maxValueLeft        |0000063b|   t  |            OBJECT|00000058|     |.text
__vector_30::enc_states|00000693|   t  |            OBJECT|00000010|     |.text
setup::__c          |000006a3|   t  |            OBJECT|0000000f|     |.text
setup::__c          |000006b2|   t  |            OBJECT|00000012|     |.text
handleUI()::__c     |000006c4|   t  |            OBJECT|0000000b|     |.text
handleUI()::__c     |000006cf|   t  |            OBJECT|00000008|     |.text
handleUI()::__c     |000006d7|   t  |            OBJECT|0000000b|     |.text
doAttractLCD()::__c |000006e2|   t  |            OBJECT|00000010|     |.text
doAttractLCD()::__c |000006f2|   t  |            OBJECT|00000011|     |.text
doAttractLCD()::__c |00000703|   t  |            OBJECT|00000011|     |.text
doAttractLCD()::__c |00000714|   t  |            OBJECT|0000000d|     |.text
doAttractLCD()::__c |00000721|   t  |            OBJECT|0000000b|     |.text
doAttractLCD()::__c |0000072c|   t  |            OBJECT|0000000e|     |.text
doAttractLCD()::__c |0000073a|   t  |            OBJECT|0000000b|     |.text
doAttractLCD()::__c |00000745|   t  |            OBJECT|00000010|     |.text
handleLCD()::__c    |00000755|   t  |            OBJECT|00000004|     |.text
handleLCD()::__c    |00000759|   t  |            OBJECT|00000004|     |.text
modeNames           |0000075d|   t  |            OBJECT|00000016|     |.text
handleLCD()::__c    |00000773|   t  |            OBJECT|00000005|     |.text
maxSetting          |00000778|   t  |            OBJECT|00000016|     |.text
handleLCD()::__c    |0000078e|   t  |            OBJECT|00000005|     |.text
modesR              |00000793|   t  |            OBJECT|000000b0|     |.text
palleteNames        |00000843|   t  |            OBJECT|00000016|     |.text
modesL              |00000859|   t  |            OBJECT|000000b0|     |.text
pulseBrightnessTable|00000909|   t  |            OBJECT|00000040|     |.text
colorCount          |00000949|   t  |            OBJECT|0000000b|     |.text
maxValueRight       |00000954|   t  |            OBJECT|00000058|     |.text
_usart0_pins        |000009ac|   t  |            OBJECT|00000009|     |.text
__ctors_start       |000009b6|   T  |            NOTYPE|        |     |.text
__ctors_end         |000009b8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__dtors_end         |000009b8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__dtors_start       |000009b8|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__init              |000009b8|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:230
__do_copy_data      |000009c4|   T  |            NOTYPE|0000001a|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
_initThreeStuff()   |000009c4|   T  |              FUNC|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2373
__do_clear_bss      |000009de|   T  |            NOTYPE|00000010|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2441
.do_clear_bss_loop  |000009e6|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2446
.do_clear_bss_start |000009e8|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2448
__do_global_ctors   |000009ee|   T  |            NOTYPE|00000016|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2466
__bad_interrupt     |00000a0c|   T  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_1          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_10         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_11         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_12         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_13         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_14         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_15         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_16         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_17         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_18         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_19         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_2          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_20         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_24         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_25         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_26         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_27         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_28         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_29         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_3          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_32         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_33         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_34         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_35         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_36         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_37         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_38         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_39         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_4          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_40         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_41         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_42         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_43         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_45         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_46         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_47         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_48         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_49         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_5          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_50         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_51         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_52         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_53         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_54         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_55         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_56         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_57         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_58         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_59         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_6          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_60         |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_7          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_8          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
__vector_9          |00000a0c|   W  |            NOTYPE|        |     |.text	../../../../crt1/gcrt1.S:209
Print::print(char)  |00000a0e|   t  |              FUNC|0000000e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::print(__FlashStringHelper const*)|00000a1c|   t  |              FUNC|00000048|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::write(unsigned char const*, unsigned int)|00000a64|   t  |              FUNC|0000005a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::availableForWrite()|00000abe|   t  |              FUNC|0000001e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::read()   |00000adc|   t  |              FUNC|00000028|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::peek()   |00000b04|   t  |              FUNC|0000001c|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::available()|00000b20|   t  |              FUNC|00000018|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::end()    |00000b38|   t  |              FUNC|0000003a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::begin(unsigned long, unsigned int)|00000b72|   t  |              FUNC|00000252|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::_tx_data_empty_irq(UartClass&)|00000dc4|   t  |              FUNC|00000052|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::_poll_tx_data_empty()|00000e16|   t  |              FUNC|00000038|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::write(unsigned char)|00000e4e|   t  |              FUNC|00000098|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::flush()  |00000ee6|   t  |              FUNC|00000028|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::operator bool()|00000f0e|   t  |              FUNC|00000004|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
micros              |00000f12|   t  |              FUNC|0000008a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:202
delay               |00000f9c|   t  |              FUNC|00000060|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:599
millis              |00000ffc|   t  |              FUNC|00000018|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:177
hd44780::command(unsigned char)|00001014|   t  |              FUNC|0000006e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::clear() [clone .constprop.24]|00001082|   t  |              FUNC|00000008|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::setCursor(unsigned char, unsigned char)|0000108a|   t  |              FUNC|0000004c|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::write(unsigned char)|000010d6|   t  |              FUNC|00000092|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::iosetContrast(unsigned char)|00001168|   t  |              FUNC|00000006|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::iosetBacklight(unsigned char)|00001168|   t  |              FUNC|00000006|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::ioread(hd44780::iotype)|0000116e|   t  |              FUNC|00000006|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::availableForWrite()|00001174|   t  |              FUNC|00000006|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::ioinit()   |00001174|   t  |              FUNC|00000006|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getPalleteNumber()  |0000117a|   t  |              FUNC|00000012|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getTransitionFrames()|0000118c|   t  |              FUNC|00000030|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getDwellFrames()    |000011bc|   t  |              FUNC|00000022|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getDrift2Colors(unsigned char*, unsigned char*, unsigned char*, unsigned long)|000011de|   t  |              FUNC|0000019a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
pushPixel(unsigned char, unsigned char, unsigned char, unsigned char)|00001378|   t  |              FUNC|00000042|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getLeftVal(unsigned char)|000013ba|   t  |              FUNC|00000032|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
EERef::operator=(unsigned char)|000013ec|   t  |              FUNC|0000002e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
UartClass::begin(unsigned long)|0000141a|   t  |              FUNC|00000012|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::flush()      |0000142c|   t  |              FUNC|00000002|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
digitalRead         |0000142e|   t  |              FUNC|00000036|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring_digital.c:448
digitalWrite        |00001464|   t  |              FUNC|00000198|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring_digital.c:348
hd44780_pinIO::write4bits(unsigned char)|000015fc|   t  |              FUNC|00000040|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780_pinIO::iowrite(hd44780::iotype, unsigned char)|0000163c|   t  |              FUNC|000000ba|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780::command4bit(unsigned char) [clone .constprop.15]|000016f6|   t  |              FUNC|00000050|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780_pinIO::ioread(hd44780::iotype)|00001746|   t  |              FUNC|000002e6|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
hd44780_pinIO::ioinit()|00001a2c|   t  |              FUNC|000002a4|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
analogWrite         |00001cd0|   t  |              FUNC|00000208|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring_analog.c:400
hd44780_pinIO::iosetBacklight(unsigned char)|00001ed8|   t  |              FUNC|000000e2|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
random(long, long)  |00001fba|   t  |              FUNC|0000005a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
initColorsDrift2()  |00002014|   t  |              FUNC|000000a8|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::write(char const*) [clone .part.2]|000020bc|   t  |              FUNC|0000001e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore\api/Print.h:47
Print::printNumber(unsigned long, unsigned char)|000020da|   t  |              FUNC|0000008a|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::println(char const*) [clone .constprop.25]|00002164|   t  |              FUNC|00000022|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
Print::printFloat(double, unsigned char) [clone .constprop.8]|00002186|   t  |              FUNC|000001be|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
getModeColors(unsigned char*, unsigned char*, unsigned char*, unsigned long)|00002344|   t  |              FUNC|00000302|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
updatePatternWave() |00002646|   t  |              FUNC|00000066|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
initLookupDrift2()  |000026ac|   t  |              FUNC|000000c8|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
__cxa_pure_virtual  |00002774|   t  |              FUNC|00000004|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/abi.cpp:24
setMode(unsigned char)|00002778|   t  |              FUNC|0000014c|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
__vector_22         |000028c4|   T  |              FUNC|00000054|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/UART0.cpp:58
__vector_23         |00002918|   T  |              FUNC|00000032|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/UART0.cpp:45
__vector_21         |0000294a|   T  |              FUNC|0000005e|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/UART0.cpp:41
__vector_31         |000029a8|   T  |              FUNC|00000050|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:128
__vector_44         |000029f8|   T  |              FUNC|0000016a|     |.text	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:1151
__vector_30         |00002b62|   T  |              FUNC|00000220|     |.text	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:998
global constructors keyed to 65535_0_DriftAnimate_V2.ino.cpp.o.3535|00002d82|   t  |              FUNC|00000106|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:197
main                |00002e88|   T  |              FUNC|00001466|     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/main.cpp:49
__DATA_REGION_LENGTH__|00004000|   A  |            NOTYPE|        |     |*ABS*
head24              |00004202|   t  |            NOTYPE|        |     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\libraries\tinyNeoPixel_Static/tinyNeoPixel_Static.cpp:525
seconddelay24       |00004220|   t  |            NOTYPE|        |     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\libraries\tinyNeoPixel_Static/tinyNeoPixel_Static.cpp:525
smallerdelay24      |00004222|   t  |            NOTYPE|        |     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\libraries\tinyNeoPixel_Static/tinyNeoPixel_Static.cpp:525
nextbyte24          |00004224|   t  |            NOTYPE|        |     |.text	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\libraries\tinyNeoPixel_Static/tinyNeoPixel_Static.cpp:525
random_r            |000042ee|   T  |              FUNC|00000092|     |.text	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:429
random              |00004380|   T  |              FUNC|00000098|     |.text
srandom             |00004418|   T  |              FUNC|00000012|     |.text
__divmodsi4         |0000442a|   T  |            NOTYPE|00000028|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1686
__divmodsi4_neg2    |00004442|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1701
__divmodsi4_exit    |00004450|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1709
__negsi2            |00004452|   T  |            NOTYPE|00000010|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1718
__muluhisi3         |00004462|   T  |            NOTYPE|00000014|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:626
__mulshisi3         |00004476|   T  |            NOTYPE|00000004|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:603
__mulohisi3         |0000447a|   T  |            NOTYPE|00000008|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:613
__udivmodsi4        |00004482|   T  |            NOTYPE|00000044|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:617
__udivmodsi4_loop   |0000448e|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1646
__udivmodsi4_ep     |000044a8|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1660
__umulhisi3         |000044c6|   T  |            NOTYPE|0000001e|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:564
__subsf3            |000044e4|   T  |              FUNC|0000000a|     |.text
__addsf3            |000044e6|   T  |            NOTYPE|        |     |.text
__addsf3x           |00004508|   T  |              FUNC|000000cc|     |.text
__cmpsf2            |000045ae|   T  |              FUNC|00000008|     |.text
__eqsf2             |000045ae|   T  |            NOTYPE|        |     |.text
__lesf2             |000045ae|   T  |            NOTYPE|        |     |.text
__ltsf2             |000045ae|   T  |            NOTYPE|        |     |.text
__nesf2             |000045ae|   T  |            NOTYPE|        |     |.text
__divsf3            |000045b6|   T  |              FUNC|00000004|     |.text
__divsf3x           |000045d0|   T  |              FUNC|000000dc|     |.text
__divsf3_pse        |000045d4|   T  |            NOTYPE|        |     |.text
__fixunssfsi        |00004686|   T  |              FUNC|00000058|     |.text
__floatunsisf       |000046de|   T  |              FUNC|0000007a|     |.text
__floatsisf         |000046e2|   T  |            NOTYPE|        |     |.text
__fp_cmp            |00004758|   T  |              FUNC|00000048|     |.text
__fp_inf            |000047a0|   T  |              FUNC|0000000c|     |.text
__fp_nan            |000047ac|   T  |              FUNC|00000006|     |.text
__fp_pscA           |000047b2|   T  |              FUNC|0000000e|     |.text
__fp_pscB           |000047c0|   T  |              FUNC|0000000e|     |.text
__fp_round          |000047ce|   T  |              FUNC|00000022|     |.text
__fp_split3         |000047f0|   T  |              FUNC|00000044|     |.text
__fp_splitA         |00004800|   T  |            NOTYPE|        |     |.text
__fp_zero           |00004834|   T  |              FUNC|0000000e|     |.text
__fp_szero          |00004836|   T  |            NOTYPE|        |     |.text
__gesf2             |00004842|   T  |              FUNC|00000008|     |.text
__gtsf2             |00004842|   T  |            NOTYPE|        |     |.text
__mulsf3            |0000484a|   T  |              FUNC|00000004|     |.text
__mulsf3x           |00004862|   T  |              FUNC|000000d2|     |.text
__mulsf3_pse        |00004866|   T  |            NOTYPE|        |     |.text
__unordsf2          |00004910|   T  |              FUNC|00000008|     |.text
__mulsi3            |00004918|   T  |            NOTYPE|0000001e|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:648
__udivmodhi4        |00004936|   T  |            NOTYPE|00000028|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1408
__udivmodhi4_loop   |0000493e|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1413
__udivmodhi4_ep     |0000494c|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:1421
__tablejump2__      |0000495e|   T  |            NOTYPE|00000012|     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2296
abort               |00004970|   T  |              FUNC|00000008|     |.text
_exit               |00004978|   T  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2278
exit                |00004978|   W  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2278
__stop_program      |0000497a|   t  |            NOTYPE|        |     |.text	/home/admin/build/toolchain-avr-special/gcc-build/avr/avrxmega4/libgcc/../../../../gcc/libgcc/config/avr/lib1funcs.S:2280
__data_load_start   |0000497c|   A  |            NOTYPE|        |     |*ABS*
_etext              |0000497c|   T  |            NOTYPE|        |     |.text
__data_load_end     |00004ac8|   A  |            NOTYPE|        |     |*ABS*
__stack             |00007fff|   W  |            NOTYPE|        |     |*ABS*
__RODATA_PM_OFFSET__|00008000|   A  |            NOTYPE|        |     |*ABS*
__TEXT_REGION_LENGTH__|00020000|   A  |            NOTYPE|        |     |*ABS*
__DATA_REGION_ORIGIN__|00804000|   A  |            NOTYPE|        |     |*ABS*
__data_start        |00804000|   D  |            NOTYPE|        |     |.data
__vector_30::EncR_Prev|00804000|   d  |            OBJECT|00000001|     |.data
__vector_30::EncL_Prev|00804001|   d  |            OBJECT|00000001|     |.data
pktLength           |00804002|   d  |            OBJECT|00000001|     |.data	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:77
handleUI()::lastBtnState|00804003|   d  |            OBJECT|00000001|     |.data
handleUI()::lastBtnBounceState|00804004|   d  |            OBJECT|00000001|     |.data
handleLCD()::drift2_colors|00804005|   d  |            OBJECT|00000001|     |.data
UIChanged           |00804006|   d  |            OBJECT|00000001|     |.data	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:198
next                |00804007|   d  |            OBJECT|00000004|     |.data
digital_pin_to_timer|0080400b|   d  |            OBJECT|00000029|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\48pin-standard/pins_arduino.h:482
digital_pin_to_bit_position|00804034|   d  |            OBJECT|00000029|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\48pin-standard/pins_arduino.h:377
vtable for UartClass|0080405d|   d  |            OBJECT|0000001a|     |.data
digital_pin_to_bit_mask|00804077|   d  |            OBJECT|00000029|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\48pin-standard/pins_arduino.h:430
digital_pin_to_port |008040a0|   d  |            OBJECT|00000029|     |.data	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\variants\48pin-standard/pins_arduino.h:331
vtable for hd44780  |008040c9|   d  |            OBJECT|00000016|     |.data
vtable for hd44780_pinIO|008040df|   d  |            OBJECT|00000016|     |.data
__bss_start         |0080414c|   B  |            NOTYPE|        |     |.bss
__data_end          |0080414c|   D  |            NOTYPE|        |     |.data
_edata              |0080414c|   D  |            NOTYPE|        |     |.data
gotMessage          |0080414c|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:74
lastRFMsgAt         |0080414d|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:78
lastEncPins         |00804151|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:193
lastUserAction      |00804152|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:204
__vector_30::EncR_Val|00804156|   b  |            OBJECT|00000001|     |.bss
__vector_30::EncL_Val|00804157|   b  |            OBJECT|00000001|     |.bss
dataIn              |00804158|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:76
rxBuffer            |00804159|   b  |            OBJECT|00000020|     |.bss	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:79
bitnum              |00804179|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\AppData\Local\Temp\arduino_build_761867\sketch/LightCtrl_RevE.h:72
__vector_44::lasttime|0080417a|   b  |            OBJECT|00000004|     |.bss
timer_millis        |0080417e|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/wiring.c:58
handleUI()::lastPressAt|00804182|   b  |            OBJECT|00000004|     |.bss
handleUI()::lastBtnAt|00804186|   b  |            OBJECT|00000004|     |.bss
currentSettingRight |0080418a|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:195
currentSettingLeft  |0080418b|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:194
handleLCD()::attractmode|0080418c|   b  |            OBJECT|00000001|     |.bss
handleLCD()::lastInputAt|0080418d|   b  |            OBJECT|00000004|     |.bss
lastRFUpdateAt      |00804191|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:199
updatePatternFade()::bright|00804195|   b  |            OBJECT|00000001|     |.bss
updatePatternDots2()::b|00804196|   b  |            OBJECT|00000001|     |.bss
updatePatternDots2()::g|00804197|   b  |            OBJECT|00000001|     |.bss
updatePatternDots2()::r|00804198|   b  |            OBJECT|00000001|     |.bss
scratch             |00804199|   b  |            OBJECT|000005dc|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:211
frameNumber         |00804775|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:212
currentValueLeft    |00804779|   b  |            OBJECT|00000008|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:196
currentValueRight   |00804781|   b  |            OBJECT|00000008|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:197
currentMode         |00804789|   b  |            OBJECT|00000001|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:201
lastFrameAt         |0080478a|   b  |            OBJECT|00000004|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:209
loop::updated       |0080478e|   b  |            OBJECT|00000001|     |.bss
Serial0             |0080478f|   b  |            OBJECT|00000097|     |.bss	C:\Users\Spence\Documents\Arduino\hardware\DxCore\megaavr\cores\dxcore/UART0.cpp:62
pixels              |00804826|   b  |            OBJECT|000005dc|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:210
leds                |00804e02|   b  |            OBJECT|00000013|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:213
lcd                 |00804e15|   b  |            OBJECT|00000029|     |.bss	C:\Users\Spence\Documents\Electronics\DriftAnimate\DriftAnimate_V2/DriftAnimate_V2.ino:11
__bss_end           |00804e3e|   B  |            NOTYPE|        |     |.bss
_end                |00804e3e|   N  |            NOTYPE|        |     |.comment
__eeprom_end        |00810000|   N  |            NOTYPE|        |     |.comment

```
After:
```text
Program Space (flash):
Name                                                |  Address | Class |  Type  |   Size   |  Section |  Line | File
__vector_default                                    | 0x000200 |     W | NOTYPE |          |    .text |    61 | (gcc) gcrt1.S
__vectors                                           | 0x000200 |     T | NOTYPE |          |    .text |    61 | (gcc) gcrt1.S
mode10Name                                          | 0x0002f4 |     t | OBJECT | 0x000009 |    .text |       |
mode9Name                                           | 0x0002fd |     t | OBJECT | 0x000009 |    .text |       |
mode8Name                                           | 0x000306 |     t | OBJECT | 0x000009 |    .text |       |
mode7Name                                           | 0x00030f |     t | OBJECT | 0x000009 |    .text |       |
mode6Name                                           | 0x000318 |     t | OBJECT | 0x000009 |    .text |       |
mode5Name                                           | 0x000321 |     t | OBJECT | 0x000009 |    .text |       |
mode4Name                                           | 0x00032a |     t | OBJECT | 0x000009 |    .text |       |
mode3Name                                           | 0x000333 |     t | OBJECT | 0x000009 |    .text |       |
mode2Name                                           | 0x00033c |     t | OBJECT | 0x000009 |    .text |       |
mode1Name                                           | 0x000345 |     t | OBJECT | 0x000009 |    .text |       |
mode0Name                                           | 0x00034e |     t | OBJECT | 0x000009 |    .text |       |
mode7R2                                             | 0x000357 |     t | OBJECT | 0x000008 |    .text |       |
mode4R2                                             | 0x00035f |     t | OBJECT | 0x000008 |    .text |       |
mode5R1                                             | 0x000367 |     t | OBJECT | 0x000008 |    .text |       |
mode2R2                                             | 0x00036f |     t | OBJECT | 0x000008 |    .text |       |
mode1R1                                             | 0x000377 |     t | OBJECT | 0x000008 |    .text |       |
mode1R0                                             | 0x00037f |     t | OBJECT | 0x000008 |    .text |       |
pallete10                                           | 0x000387 |     t | OBJECT | 0x000008 |    .text |       |
pallete9                                            | 0x00038f |     t | OBJECT | 0x000008 |    .text |       |
pallete8                                            | 0x000397 |     t | OBJECT | 0x000008 |    .text |       |
pallete7                                            | 0x00039f |     t | OBJECT | 0x000008 |    .text |       |
pallete6                                            | 0x0003a7 |     t | OBJECT | 0x000008 |    .text |       |
pallete5                                            | 0x0003af |     t | OBJECT | 0x000008 |    .text |       |
pallete4                                            | 0x0003b7 |     t | OBJECT | 0x000008 |    .text |       |
pallete3                                            | 0x0003bf |     t | OBJECT | 0x000008 |    .text |       |
pallete2                                            | 0x0003c7 |     t | OBJECT | 0x000008 |    .text |       |
pallete1                                            | 0x0003cf |     t | OBJECT | 0x000008 |    .text |       |
pallete0                                            | 0x0003d7 |     t | OBJECT | 0x000008 |    .text |       |
mode0R0                                             | 0x0003df |     t | OBJECT | 0x000008 |    .text |       |
mode1L5                                             | 0x0003e7 |     t | OBJECT | 0x000008 |    .text |       |
mode1L4                                             | 0x0003ef |     t | OBJECT | 0x000008 |    .text |       |
mode1L3                                             | 0x0003f7 |     t | OBJECT | 0x000008 |    .text |       |
mode1L2                                             | 0x0003ff |     t | OBJECT | 0x000008 |    .text |       |
mode1L1                                             | 0x000407 |     t | OBJECT | 0x000008 |    .text |       |
mode1L0                                             | 0x00040f |     t | OBJECT | 0x000008 |    .text |       |
mode0L2                                             | 0x000417 |     t | OBJECT | 0x000008 |    .text |       |
mode0L1                                             | 0x00041f |     t | OBJECT | 0x000008 |    .text |       |
mode0L0                                             | 0x000427 |     t | OBJECT | 0x000008 |    .text |       |
defaultValueRight                                   | 0x00042f |     t | OBJECT | 0x000058 |    .text |       |
defaultValueLeft                                    | 0x000487 |     t | OBJECT | 0x000058 |    .text |       |
getModeRatio(uint16_t)::__c                         | 0x0004df |     t | OBJECT | 0x00001a |    .text |       |
leftValues                                          | 0x0004f9 |     t | OBJECT | 0x000020 |    .text |       |
getModeColors(uint8_t*, uint8_t*, uint8_t*, uint32  | 0x000519 |     t | OBJECT | 0x00001a |    .text |       |
colorPallete                                        | 0x000533 |     t | OBJECT | 0x000108 |    .text |       |
maxValueLeft                                        | 0x00063b |     t | OBJECT | 0x000058 |    .text |       |
__vector_30::enc_states                             | 0x000693 |     t | OBJECT | 0x000010 |    .text |       |
setup::__c                                          | 0x0006a3 |     t | OBJECT | 0x00000f |    .text |       |
setup::__c                                          | 0x0006b2 |     t | OBJECT | 0x000012 |    .text |       |
handleUI()::__c                                     | 0x0006c4 |     t | OBJECT | 0x00000b |    .text |       |
handleUI()::__c                                     | 0x0006cf |     t | OBJECT | 0x000008 |    .text |       |
handleUI()::__c                                     | 0x0006d7 |     t | OBJECT | 0x00000b |    .text |       |
doAttractLCD()::__c                                 | 0x0006e2 |     t | OBJECT | 0x000010 |    .text |       |
doAttractLCD()::__c                                 | 0x0006f2 |     t | OBJECT | 0x000011 |    .text |       |
doAttractLCD()::__c                                 | 0x000703 |     t | OBJECT | 0x000011 |    .text |       |
doAttractLCD()::__c                                 | 0x000714 |     t | OBJECT | 0x00000d |    .text |       |
doAttractLCD()::__c                                 | 0x000721 |     t | OBJECT | 0x00000b |    .text |       |
doAttractLCD()::__c                                 | 0x00072c |     t | OBJECT | 0x00000e |    .text |       |
doAttractLCD()::__c                                 | 0x00073a |     t | OBJECT | 0x00000b |    .text |       |
doAttractLCD()::__c                                 | 0x000745 |     t | OBJECT | 0x000010 |    .text |       |
handleLCD()::__c                                    | 0x000755 |     t | OBJECT | 0x000004 |    .text |       |
handleLCD()::__c                                    | 0x000759 |     t | OBJECT | 0x000004 |    .text |       |
modeNames                                           | 0x00075d |     t | OBJECT | 0x000016 |    .text |       |
handleLCD()::__c                                    | 0x000773 |     t | OBJECT | 0x000005 |    .text |       |
maxSetting                                          | 0x000778 |     t | OBJECT | 0x000016 |    .text |       |
handleLCD()::__c                                    | 0x00078e |     t | OBJECT | 0x000005 |    .text |       |
modesR                                              | 0x000793 |     t | OBJECT | 0x0000b0 |    .text |       |
palleteNames                                        | 0x000843 |     t | OBJECT | 0x000016 |    .text |       |
modesL                                              | 0x000859 |     t | OBJECT | 0x0000b0 |    .text |       |
pulseBrightnessTable                                | 0x000909 |     t | OBJECT | 0x000040 |    .text |       |
colorCount                                          | 0x000949 |     t | OBJECT | 0x00000b |    .text |       |
maxValueRight                                       | 0x000954 |     t | OBJECT | 0x000058 |    .text |       |
_usart0_pins                                        | 0x0009ac |     t | OBJECT | 0x000009 |    .text |       |
__ctors_start                                       | 0x0009b6 |     T | NOTYPE |          |    .text |       |
__ctors_end                                         | 0x0009b8 |     T | NOTYPE |          |    .text |   230 | (gcc) gcrt1.S
__init                                              | 0x0009b8 |     W | NOTYPE |          |    .text |   230 | (gcc) gcrt1.S
__do_copy_data                                      | 0x0009c4 |     T | NOTYPE | 0x00001a |    .text |  2373 | (gcc) lib1funcs.S
_initThreeStuff()                                   | 0x0009c4 |     T |   FUNC |          |    .text |  2373 | (gcc) lib1funcs.S
__do_clear_bss                                      | 0x0009de |     T | NOTYPE | 0x000010 |    .text |  2441 | (gcc) lib1funcs.S
.do_clear_bss_loop                                  | 0x0009e6 |     t | NOTYPE |          |    .text |  2446 | (gcc) lib1funcs.S
.do_clear_bss_start                                 | 0x0009e8 |     t | NOTYPE |          |    .text |  2448 | (gcc) lib1funcs.S
__do_global_ctors                                   | 0x0009ee |     T | NOTYPE | 0x000016 |    .text |  2466 | (gcc) lib1funcs.S
__bad_interrupt                                     | 0x000a0c |     T | NOTYPE |          |    .text |   209 | (gcc) gcrt1.S
Print::print(char)                                  | 0x000a0e |     t |   FUNC | 0x00000e |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::print(__FlashStringHelper const*)            | 0x000a1c |     t |   FUNC | 0x000048 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::write(uint8_t const*, uint16_t)              | 0x000a64 |     t |   FUNC | 0x00005a |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::availableForWrite()                      | 0x000abe |     t |   FUNC | 0x00001e |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::read()                                   | 0x000adc |     t |   FUNC | 0x000028 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::peek()                                   | 0x000b04 |     t |   FUNC | 0x00001c |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::available()                              | 0x000b20 |     t |   FUNC | 0x000018 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::end()                                    | 0x000b38 |     t |   FUNC | 0x00003a |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::begin(uint32_t, uint16_t)                | 0x000b72 |     t |   FUNC | 0x000252 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::_tx_data_empty_irq(UartClass&)           | 0x000dc4 |     t |   FUNC | 0x000052 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::_poll_tx_data_empty()                    | 0x000e16 |     t |   FUNC | 0x000038 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::write(uint8_t)                           | 0x000e4e |     t |   FUNC | 0x000098 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::flush()                                  | 0x000ee6 |     t |   FUNC | 0x000028 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::operator bool()                          | 0x000f0e |     t |   FUNC | 0x000004 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
micros                                              | 0x000f12 |     t |   FUNC | 0x00008a |    .text |   202 | DxCore/megaavr/cores/dxcore/wiring.c
delay                                               | 0x000f9c |     t |   FUNC | 0x000060 |    .text |   599 | DxCore/megaavr/cores/dxcore/wiring.c
millis                                              | 0x000ffc |     t |   FUNC | 0x000018 |    .text |   177 | DxCore/megaavr/cores/dxcore/wiring.c
hd44780::command(uint8_t)                           | 0x001014 |     t |   FUNC | 0x00006e |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::clear() [cnst.24]                          | 0x001082 |     t |   FUNC | 0x000008 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::setCursor(uint8_t, uint8_t)                | 0x00108a |     t |   FUNC | 0x00004c |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::write(uint8_t)                             | 0x0010d6 |     t |   FUNC | 0x000092 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::iosetContrast(uint8_t)                     | 0x001168 |     t |   FUNC | 0x000006 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::iosetBacklight(uint8_t)                    | 0x001168 |     t |   FUNC | 0x000006 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::ioread(hd44780::iotype)                    | 0x00116e |     t |   FUNC | 0x000006 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::availableForWrite()                          | 0x001174 |     t |   FUNC | 0x000006 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::ioinit()                                   | 0x001174 |     t |   FUNC | 0x000006 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getPalleteNumber()                                  | 0x00117a |     t |   FUNC | 0x000012 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getTransitionFrames()                               | 0x00118c |     t |   FUNC | 0x000030 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getDwellFrames()                                    | 0x0011bc |     t |   FUNC | 0x000022 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getDrift2Colors(uint8_t*, uint8_t*, uint8_t*, uint  | 0x0011de |     t |   FUNC | 0x00019a |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
pushPixel(uint8_t, uint8_t, uint8_t, uint8_t)       | 0x001378 |     t |   FUNC | 0x000042 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getLeftVal(uint8_t)                                 | 0x0013ba |     t |   FUNC | 0x000032 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
EERef::operator=(uint8_t)                           | 0x0013ec |     t |   FUNC | 0x00002e |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
UartClass::begin(uint32_t)                          | 0x00141a |     t |   FUNC | 0x000012 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::flush()                                      | 0x00142c |     t |   FUNC | 0x000002 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
digitalRead                                         | 0x00142e |     t |   FUNC | 0x000036 |    .text |   448 | DxCore/megaavr/cores/dxcore/wiring_digital.c
digitalWrite                                        | 0x001464 |     t |   FUNC | 0x000198 |    .text |   348 | DxCore/megaavr/cores/dxcore/wiring_digital.c
hd44780_pinIO::write4bits(uint8_t)                  | 0x0015fc |     t |   FUNC | 0x000040 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780_pinIO::iowrite(hd44780::iotype, uint8_t)    | 0x00163c |     t |   FUNC | 0x0000ba |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780::command4bit(uint8_t) [cnst.15]             | 0x0016f6 |     t |   FUNC | 0x000050 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780_pinIO::ioread(hd44780::iotype)              | 0x001746 |     t |   FUNC | 0x0002e6 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
hd44780_pinIO::ioinit()                             | 0x001a2c |     t |   FUNC | 0x0002a4 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
analogWrite                                         | 0x001cd0 |     t |   FUNC | 0x000208 |    .text |   400 | DxCore/megaavr/cores/dxcore/wiring_analog.c
hd44780_pinIO::iosetBacklight(uint8_t)              | 0x001ed8 |     t |   FUNC | 0x0000e2 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
random(long, long)                                  | 0x001fba |     t |   FUNC | 0x00005a |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
initColorsDrift2()                                  | 0x002014 |     t |   FUNC | 0x0000a8 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::write(char const*) [clone .part.2]           | 0x0020bc |     t |   FUNC | 0x00001e |    .text |    47 | DxCore/megaavr/cores/dxcore/api/Print.h
Print::printNumber(uint32_t, uint8_t)               | 0x0020da |     t |   FUNC | 0x00008a |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::println(char const*) [cnst.25]               | 0x002164 |     t |   FUNC | 0x000022 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
Print::printFloat(double, uint8_t) [cnst.8]         | 0x002186 |     t |   FUNC | 0x0001be |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
getModeColors(uint8_t*, uint8_t*, uint8_t*, uint32  | 0x002344 |     t |   FUNC | 0x000302 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
updatePatternWave()                                 | 0x002646 |     t |   FUNC | 0x000066 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
initLookupDrift2()                                  | 0x0026ac |     t |   FUNC | 0x0000c8 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
__cxa_pure_virtual                                  | 0x002774 |     t |   FUNC | 0x000004 |    .text |    24 | DxCore/megaavr/cores/dxcore/abi.cpp
setMode(uint8_t)                                    | 0x002778 |     t |   FUNC | 0x00014c |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
__vector_22                                         | 0x0028c4 |     T |   FUNC | 0x000054 |    .text |    58 | DxCore/megaavr/cores/dxcore/UART0.cpp
__vector_23                                         | 0x002918 |     T |   FUNC | 0x000032 |    .text |    45 | DxCore/megaavr/cores/dxcore/UART0.cpp
__vector_21                                         | 0x00294a |     T |   FUNC | 0x00005e |    .text |    41 | DxCore/megaavr/cores/dxcore/UART0.cpp
__vector_31                                         | 0x0029a8 |     T |   FUNC | 0x000050 |    .text |   128 | DxCore/megaavr/cores/dxcore/wiring.c
__vector_44                                         | 0x0029f8 |     T |   FUNC | 0x00016a |    .text |  1151 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
__vector_30                                         | 0x002b62 |     T |   FUNC | 0x000220 |    .text |   998 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
global constructors keyed to 65535_0_DriftAnimate_  | 0x002d82 |     t |   FUNC | 0x000106 |    .text |   197 | DxCore/megaavr/cores/dxcore/main.cpp
main                                                | 0x002e88 |     T |   FUNC | 0x001466 |    .text |    49 | DxCore/megaavr/cores/dxcore/main.cpp
head24                                              | 0x004202 |     t | NOTYPE |          |    .text |   525 | DxCore/megaavr/libraries/tinyNeoPixel_Static/tinyNeoPixel_Static.cpp
seconddelay24                                       | 0x004220 |     t | NOTYPE |          |    .text |   525 | DxCore/megaavr/libraries/tinyNeoPixel_Static/tinyNeoPixel_Static.cpp
smallerdelay24                                      | 0x004222 |     t | NOTYPE |          |    .text |   525 | DxCore/megaavr/libraries/tinyNeoPixel_Static/tinyNeoPixel_Static.cpp
nextbyte24                                          | 0x004224 |     t | NOTYPE |          |    .text |   525 | DxCore/megaavr/libraries/tinyNeoPixel_Static/tinyNeoPixel_Static.cpp
random_r                                            | 0x0042ee |     T |   FUNC | 0x000092 |    .text |   429 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
random                                              | 0x004380 |     T |   FUNC | 0x000098 |    .text |       |
srandom                                             | 0x004418 |     T |   FUNC | 0x000012 |    .text |       |
__divmodsi4                                         | 0x00442a |     T | NOTYPE | 0x000028 |    .text |  1686 | (gcc) lib1funcs.S
__divmodsi4_neg2                                    | 0x004442 |     t | NOTYPE |          |    .text |  1701 | (gcc) lib1funcs.S
__divmodsi4_exit                                    | 0x004450 |     t | NOTYPE |          |    .text |  1709 | (gcc) lib1funcs.S
__negsi2                                            | 0x004452 |     T | NOTYPE | 0x000010 |    .text |  1718 | (gcc) lib1funcs.S
__muluhisi3                                         | 0x004462 |     T | NOTYPE | 0x000014 |    .text |   626 | (gcc) lib1funcs.S
__mulshisi3                                         | 0x004476 |     T | NOTYPE | 0x000004 |    .text |   603 | (gcc) lib1funcs.S
__mulohisi3                                         | 0x00447a |     T | NOTYPE | 0x000008 |    .text |   613 | (gcc) lib1funcs.S
__udivmodsi4                                        | 0x004482 |     T | NOTYPE | 0x000044 |    .text |   617 | (gcc) lib1funcs.S
__udivmodsi4_loop                                   | 0x00448e |     t | NOTYPE |          |    .text |  1646 | (gcc) lib1funcs.S
__udivmodsi4_ep                                     | 0x0044a8 |     t | NOTYPE |          |    .text |  1660 | (gcc) lib1funcs.S
__umulhisi3                                         | 0x0044c6 |     T | NOTYPE | 0x00001e |    .text |   564 | (gcc) lib1funcs.S
__subsf3                                            | 0x0044e4 |     T |   FUNC | 0x00000a |    .text |       |
__addsf3                                            | 0x0044e6 |     T | NOTYPE |          |    .text |       |
__addsf3x                                           | 0x004508 |     T |   FUNC | 0x0000cc |    .text |       |
__cmpsf2                                            | 0x0045ae |     T |   FUNC | 0x000008 |    .text |       |
__eqsf2                                             | 0x0045ae |     T | NOTYPE |          |    .text |       |
__lesf2                                             | 0x0045ae |     T | NOTYPE |          |    .text |       |
__ltsf2                                             | 0x0045ae |     T | NOTYPE |          |    .text |       |
__nesf2                                             | 0x0045ae |     T | NOTYPE |          |    .text |       |
__divsf3                                            | 0x0045b6 |     T |   FUNC | 0x000004 |    .text |       |
__divsf3x                                           | 0x0045d0 |     T |   FUNC | 0x0000dc |    .text |       |
__divsf3_pse                                        | 0x0045d4 |     T | NOTYPE |          |    .text |       |
__fixunssfsi                                        | 0x004686 |     T |   FUNC | 0x000058 |    .text |       |
__floatunsisf                                       | 0x0046de |     T |   FUNC | 0x00007a |    .text |       |
__floatsisf                                         | 0x0046e2 |     T | NOTYPE |          |    .text |       |
__fp_cmp                                            | 0x004758 |     T |   FUNC | 0x000048 |    .text |       |
__fp_inf                                            | 0x0047a0 |     T |   FUNC | 0x00000c |    .text |       |
__fp_nan                                            | 0x0047ac |     T |   FUNC | 0x000006 |    .text |       |
__fp_pscA                                           | 0x0047b2 |     T |   FUNC | 0x00000e |    .text |       |
__fp_pscB                                           | 0x0047c0 |     T |   FUNC | 0x00000e |    .text |       |
__fp_round                                          | 0x0047ce |     T |   FUNC | 0x000022 |    .text |       |
__fp_split3                                         | 0x0047f0 |     T |   FUNC | 0x000044 |    .text |       |
__fp_splitA                                         | 0x004800 |     T | NOTYPE |          |    .text |       |
__fp_zero                                           | 0x004834 |     T |   FUNC | 0x00000e |    .text |       |
__fp_szero                                          | 0x004836 |     T | NOTYPE |          |    .text |       |
__gesf2                                             | 0x004842 |     T |   FUNC | 0x000008 |    .text |       |
__gtsf2                                             | 0x004842 |     T | NOTYPE |          |    .text |       |
__mulsf3                                            | 0x00484a |     T |   FUNC | 0x000004 |    .text |       |
__mulsf3x                                           | 0x004862 |     T |   FUNC | 0x0000d2 |    .text |       |
__mulsf3_pse                                        | 0x004866 |     T | NOTYPE |          |    .text |       |
__unordsf2                                          | 0x004910 |     T |   FUNC | 0x000008 |    .text |       |
__mulsi3                                            | 0x004918 |     T | NOTYPE | 0x00001e |    .text |   648 | (gcc) lib1funcs.S
__udivmodhi4                                        | 0x004936 |     T | NOTYPE | 0x000028 |    .text |  1408 | (gcc) lib1funcs.S
__udivmodhi4_loop                                   | 0x00493e |     t | NOTYPE |          |    .text |  1413 | (gcc) lib1funcs.S
__udivmodhi4_ep                                     | 0x00494c |     t | NOTYPE |          |    .text |  1421 | (gcc) lib1funcs.S
abort                                               | 0x004970 |     T |   FUNC | 0x000008 |    .text |       |
__stop_program                                      | 0x00497a |     t | NOTYPE |          |    .text |  2280 | (gcc) lib1funcs.S
__data_load_start                                   | 0x00497c |     A | NOTYPE |          |    *ABS* |       |
__data_load_end                                     | 0x004ac8 |     A | NOTYPE |          |    *ABS* |       |

Data Space (SRAM):
Name                           |  Address | Class |  Type  |   Size   |  Section |  Line | File
__vector_30::EncR_Prev         | 0x804000 |     d | OBJECT | 0x000001 |    .data |       |
__vector_30::EncL_Prev         | 0x804001 |     d | OBJECT | 0x000001 |    .data |       |
pktLength                      | 0x804002 |     d | OBJECT | 0x000001 |    .data |    77 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
handleUI()::lastBtnState       | 0x804003 |     d | OBJECT | 0x000001 |    .data |       |
handleUI()::lastBtnBounceState | 0x804004 |     d | OBJECT | 0x000001 |    .data |       |
handleLCD()::drift2_colors     | 0x804005 |     d | OBJECT | 0x000001 |    .data |       |
UIChanged                      | 0x804006 |     d | OBJECT | 0x000001 |    .data |   198 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
next                           | 0x804007 |     d | OBJECT | 0x000004 |    .data |       |
digital_pin_to_timer           | 0x80400b |     d | OBJECT | 0x000029 |    .data |   482 | DxCore/megaavr/variants/48pin-standard/pins_arduino.h
digital_pin_to_bit_position    | 0x804034 |     d | OBJECT | 0x000029 |    .data |   377 | DxCore/megaavr/variants/48pin-standard/pins_arduino.h
vtable for UartClass           | 0x80405d |     d | OBJECT | 0x00001a |    .data |       |
digital_pin_to_bit_mask        | 0x804077 |     d | OBJECT | 0x000029 |    .data |   430 | DxCore/megaavr/variants/48pin-standard/pins_arduino.h
digital_pin_to_port            | 0x8040a0 |     d | OBJECT | 0x000029 |    .data |   331 | DxCore/megaavr/variants/48pin-standard/pins_arduino.h
vtable for hd44780             | 0x8040c9 |     d | OBJECT | 0x000016 |    .data |       |
vtable for hd44780_pinIO       | 0x8040df |     d | OBJECT | 0x000016 |    .data |       |
__bss_start                    | 0x80414c |     B | NOTYPE |          |     .bss |       |
__data_end                     | 0x80414c |     D | NOTYPE |          |    .data |       |
gotMessage                     | 0x80414c |     b | OBJECT | 0x000001 |     .bss |    74 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
lastRFMsgAt                    | 0x80414d |     b | OBJECT | 0x000004 |     .bss |    78 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
lastEncPins                    | 0x804151 |     b | OBJECT | 0x000001 |     .bss |   193 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
lastUserAction                 | 0x804152 |     b | OBJECT | 0x000004 |     .bss |   204 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
__vector_30::EncR_Val          | 0x804156 |     b | OBJECT | 0x000001 |     .bss |       |
__vector_30::EncL_Val          | 0x804157 |     b | OBJECT | 0x000001 |     .bss |       |
dataIn                         | 0x804158 |     b | OBJECT | 0x000001 |     .bss |    76 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
rxBuffer                       | 0x804159 |     b | OBJECT | 0x000020 |     .bss |    79 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
bitnum                         | 0x804179 |     b | OBJECT | 0x000001 |     .bss |    72 | /Users/Spence/AppData/Local/Temp/arduino_build_761867/sketch/LightCtrl_RevE.h
__vector_44::lasttime          | 0x80417a |     b | OBJECT | 0x000004 |     .bss |       |
timer_millis                   | 0x80417e |     b | OBJECT | 0x000004 |     .bss |    58 | DxCore/megaavr/cores/dxcore/wiring.c
handleUI()::lastPressAt        | 0x804182 |     b | OBJECT | 0x000004 |     .bss |       |
handleUI()::lastBtnAt          | 0x804186 |     b | OBJECT | 0x000004 |     .bss |       |
currentSettingRight            | 0x80418a |     b | OBJECT | 0x000001 |     .bss |   195 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
currentSettingLeft             | 0x80418b |     b | OBJECT | 0x000001 |     .bss |   194 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
handleLCD()::attractmode       | 0x80418c |     b | OBJECT | 0x000001 |     .bss |       |
handleLCD()::lastInputAt       | 0x80418d |     b | OBJECT | 0x000004 |     .bss |       |
lastRFUpdateAt                 | 0x804191 |     b | OBJECT | 0x000004 |     .bss |   199 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
updatePatternFade()::bright    | 0x804195 |     b | OBJECT | 0x000001 |     .bss |       |
updatePatternDots2()::b        | 0x804196 |     b | OBJECT | 0x000001 |     .bss |       |
updatePatternDots2()::g        | 0x804197 |     b | OBJECT | 0x000001 |     .bss |       |
updatePatternDots2()::r        | 0x804198 |     b | OBJECT | 0x000001 |     .bss |       |
scratch                        | 0x804199 |     b | OBJECT | 0x0005dc |     .bss |   211 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
frameNumber                    | 0x804775 |     b | OBJECT | 0x000004 |     .bss |   212 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
currentValueLeft               | 0x804779 |     b | OBJECT | 0x000008 |     .bss |   196 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
currentValueRight              | 0x804781 |     b | OBJECT | 0x000008 |     .bss |   197 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
currentMode                    | 0x804789 |     b | OBJECT | 0x000001 |     .bss |   201 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
lastFrameAt                    | 0x80478a |     b | OBJECT | 0x000004 |     .bss |   209 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
loop::updated                  | 0x80478e |     b | OBJECT | 0x000001 |     .bss |       |
Serial0                        | 0x80478f |     b | OBJECT | 0x000097 |     .bss |    62 | DxCore/megaavr/cores/dxcore/UART0.cpp
pixels                         | 0x804826 |     b | OBJECT | 0x0005dc |     .bss |   210 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
leds                           | 0x804e02 |     b | OBJECT | 0x000013 |     .bss |   213 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
lcd                            | 0x804e15 |     b | OBJECT | 0x000029 |     .bss |    11 | /Users/Spence/Documents/Electronics/DriftAnimate/DriftAnimate_V2/DriftAnimate_V2.ino
__bss_end                      | 0x804e3e |     B | NOTYPE |          |     .bss |       |
_end                           | 0x804e3e |     N | NOTYPE |          | .comment |       |

```

Much better, no?

## Assembly listings
The assembly listings are a lot more usable (unless using Optiboot board def with DxCore, but that's a separate issue)
There is are only two problems here, first, it sometimes expresses offsets and addresses very unhelpfully, finding the least-useful sympbol to express addresses relative to, for example,this direct store to address 0x800A01:
```text
"40a:	90 93 01 0a 	sts	0x0A01, r25	; 0x800a01 <__TEXT_REGION_LENGTH__+0x7e0a01>
```
Now, that's a peripheral control register (being betweeen 0x003F and 0x103F - while it'd be sweet to know that it relates to TCA - just showing something like <Peripheral register 0x0A0> would be a lot better than that. And really, it wouldn't even be that hard to make it do like <TCA0 + 0x0001> (the trick is that they aren't changing where they put the peripherals on modern AVRs - on any post-2016 AVR, 0x0A00 to 0x0A40 is TCA0). Sometimes the values are nonsensical. "`__LOCK_REGION_LENGTH__` which is 0x400 apparently, so it little sense to express the destination of that relative jump that lands at 0x520 as `__LOCK_REGION_LENGTH__ + 0x120` There ain't no section of memory on those things that has any clearly deliniated area 1024 bytes in size! Where did they get 0x400 from. Unless the lock region is everything from the NVMCTRL registers starting at 0x1000 to the EEPROM at 0x3400? *shrug* Whatever the case may be, it's not of practical use. These should ideally give the offset from the peripheral if they're under 0x1040, and if they're in RAM and got a useless offset, it should be replaced with a useful one if possible. Addresses in flash are the hardest, since ideally you'd want to have it find the destination, then iterate upwards until it found a line with no spaces ending in `()`, then move down until you found the first instruction, and subtract that from the destination yielding the output that avr-objdump is supposed to.

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

In fact, I'd argue that for any .S file, you might as well cut out the filename altogether (if you're using this tool, you probably don't even need to see the listings for those functions by now for general processing since you typically aren't going to be able to see it without a major archeological excavation, and all you would find is the same assembly you see here.

tameListings.py is a crude attempt at doing some of this. It's not ready for prime time, but it's a start.

## tallycount.py - Count the number of times an instruction is used
tallycount.py runs processes every .lst in the directory, creates a subdirectory called stats, containing a file for each listing processed, which counts up how often each instruction is called. and a file called totals.csv with the totals for all files.

This was used to create a few of [these exceptional and unremarkable examples](isncount.md), based on normal and whackjob test code I had lying around.

It now also creates a totals.md file pre-formatted appropriately for a github markdown documeny
