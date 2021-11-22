# Written by Spence Konde (C) 2021
# This code is clumsy and amateurish. 
# Of course it is, I don't even know python!
# This is released as open source software under the GPL v2.1
# though you might be better off starting from scratch
# if you want to do anything other than read AVR memory maps
# in sysv format and not have to write a script ro make them
# readable. 

import sys
import re

file_name = sys.argv[1]
outfile_name = file_name[:-3]+"clean.map"
f = open(file_name,"r")
avr_memory_map_raw = f.readlines()
pass1 = []
badint_address=""
ctors_start=""
ctors_end=""
dtors_start=""
dtors_end=""
trampolines_start=""
trampolines_end=""
init=""
name_length_overall=0
cols=['Name','Value','Class','Type','Size','Section','Line','File']
for x in avr_memory_map_raw[6:]:
    x = re.sub('\t','|',x)
    y = x.split("|")
    y[0]= re.sub("unsigned char", "uint8_t", y[0])
    y[0]=re.sub("unsigned int", "uint16_t", y[0])
    y[0]=re.sub("unsigned long", "uint32_t", y[0])
    y[0]=re.sub("clone \.constprop", "cnst", y[0])
    y[0]=re.sub("constarg", "cnst", y[0])
    y[0]=y[0].strip()
    if y[0].startswith("__trampolines_start"):
        trampolines_start=y[1]
    if y[0].startswith("__trampolines_end"):
        trampolines_end=y[1]
    if y[0].startswith("__dtors_start"):
        dtors_start=y[1]
    if y[0].startswith("__dtors_end"):
        dtors_end=y[1]
    if y[0].startswith("__ctors_start"):
        ctors_start=y[1]
    if y[0].startswith("__ctors_end"):
        ctors_end=y[1]
    if y[0].startswith("__init"):
        init=y[1]
    if len(y[0]) > name_length_overall:
        name_length_overall = len(y[0])
    if len(y[0]) > 50:
        y[0]=y[0][:50]
    temp1="0x"
    temp1 += y[1][2:]
    y[1]=temp1
    if y[0].startswith("__bad_interrupt"):
        badint_address = y[1]
    y[2]=y[2].strip()
    y[3]=y[3].strip()
    if (not y[4].isspace()):
        temp4="0x"
        temp4+=y[4][2:]
        y[4]=temp4
    y[5]=y[6].strip()
    y[6]=' '
    if len(y) == 8:
        if ":" in y[7]:
            lineinfo = y[7].split(":")
            if len(lineinfo) > 2:
                lineinfo=lineinfo[1:]
            lineinfo[0] = re.sub(re.escape("\\"),"/",lineinfo[0])
            #temp=lineinfo[0].split("/")
            #print(temp)
            #print(temp)
            #temp2=temp[-2]+'/'+temp[-1]
            #if temp[-2] != "crt1" and temp[-2] != "gcc":
            #    temp2=temp[-3]+'/'+temp2
            #print(temp2)
            y[6]=lineinfo[-1].strip()
            y[7]=lineinfo[0].strip()
            y[7]=re.sub(".*hardware/","",y[7])
            y[7]=re.sub(".*"+re.escape("../../"),"(gcc) ",y[7])
            y[7]=re.sub(re.escape("(gcc)")+" crt1/", "(gcc) ",y[7])
            y[7]=re.sub(re.escape("(gcc)")+".*avr/", "(gcc) ",y[7])
            #print(lineinfo)
            #y[5] = lineinfo[-1]
            #print(y)
    for num in range(len(y)):
        y[num] = y[num].strip()
    pass1.append(y)
f.close()

cols=['Name',' Address','Class',' Type ','  Size  ',' Section',' Line','File']
cols2=list(cols)
# Widths: 50, 8, 5, 6, 8, 8, 5, w/e
outdata=[]

name_length_flash=0
name_length_data=0
done_flash=0
for x in pass1:
    if x[0].startswith("_exit") or x[0].startswith("_etext") or x[0].startswith("_edata") or x[0].startswith("exit") or x[0].startswith("__data_start") or x[0].startswith("__eeprom_end") or  x[0].startswith("__heap_end"):
        continue
    if x[0].startswith("__") and x[0].endswith("__"):
        continue
    if x[0].startswith("__vector") and x[1]==badint_address:
        continue
    if (trampolines_end == trampolines_start and x[0].startswith("__trampoline")):
        continue
    if (ctors_end == ctors_start and x[0].startswith("__ctors_")):
        continue
    if (dtors_end == dtors_start and x[0].startswith("__dtors_")):
        continue
    if not done_flash:
        if (x[0].startswith("__stack")):
              done_flash = 1
        else:
            if (len(x[0].strip()) > name_length_flash):
                name_length_flash = len(x[0].strip())
    else:
        if (len(x[0].strip()) > name_length_data):
            name_length_data = len(x[0].strip())
outdata.append("Program Space (flash):")
cols[0]=cols[0].ljust(name_length_flash+1)
outdata.append(cols)
name_length = name_length_flash+1
for x in pass1:
    if x[0].startswith("_exit") or x[0].startswith("_etext") or x[0].startswith("_edata") or x[0].startswith("exit") or x[0].startswith("__data_start") or x[0].startswith("__eeprom_end") or  x[0].startswith("__heap_end"):
        continue
    if x[0].startswith("__") and x[0].endswith("__"):
        continue
    if x[0].startswith("__vector") and x[1]==badint_address:
        continue
    if (trampolines_end == trampolines_start and x[0].startswith("__trampoline")):
        continue
    if (ctors_end == ctors_start and x[0].startswith("__ctors_")):
        continue
    if (dtors_end == dtors_start and x[0].startswith("__dtors_")):
        continue
    x[0]=x[0].ljust(name_length)
    x[2]=x[2].rjust(5)
    x[3]=x[3].rjust(6)
    x[4]=x[4].rjust(8)
    x[5]=x[5].rjust(8)
    x[6]=x[6].rjust(5)
    if len(x) == 7:
        x.append(" ")
    if x[0].strip()==("__stack"):
        name_length = name_length_data
        cols2[0]=cols2[0].strip().ljust(name_length_data)
        outdata.append("")
        outdata.append("Data Space (SRAM):")
        outdata.append(cols2)
    else:
        outdata.append(x)
f2 = open(outfile_name,"w")

for y in outdata:
    if len(y)==8:
        print(y[0],y[1],y[2],y[3],y[4],y[5],y[6],y[7], sep = " | ", file=f2)
    else:
        print(y, file=f2)
f2.close()
