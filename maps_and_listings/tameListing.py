# Written by Spence Konde (C) 2022
# This code is clumsy and amateurish.
# Of course it is, I don't even know python!
# This is released as open source software under the GPL v2.1
# though you might be better off starting from scratch
# if you want to do anything other than read AVR memory maps
# in sysv format and not have to write a script ro make them
# readable.

import sys
import re

isnbuckets = {
    "add":0,
    "adc":0,
    "adiw":0,
    "sub":0,
    "subi":0,
    "sbc":0,
    "sbci":0,
    "sbiw":0,
    "and":0,
    "andi":0,
    "or":0,
    "ori":0,
    "eor":0,
    "com":0,
    "neg":0,
    "sbr":0,
    "cbr":0,
    "inc":0,
    "dec":0,
    "tst":0,
    "clr":0,
    "ser":0,
    "mul":0,
    "muls":0,
    "mulsu":0,
    "fmul":0,
    "fmuls":0,
    "fmulsu":0,
    "des":0,
    "rjmp":0,
    "ijmp":0,
    "eijmp":0,
    "jmp":0,
    "rcall":0,
    "icall":0,
    "eicall":0,
    "call":0,
    "ret":0,
    "reti":0,
    "cpse":0,
    "cp":0,
    "cpc":0,
    "cpi":0,
    "sbrc":0,
    "sbrs":0,
    "sbic":0,
    "sbis":0,
    "brbs":0,
    "brbc":0,
    "breq":0,
    "brne":0,
    "brcs":0,
    "brcc":0,
    "brsh":0,
    "brlo":0,
    "brmi":0,
    "brpl":0,
    "brge":0,
    "brlt":0,
    "brhs":0,
    "brhc":0,
    "brts":0,
    "brtc":0,
    "brvs":0,
    "brvc":0,
    "brie":0,
    "brid":0,
    "mov":0,
    "movw":0,
    "ldi":0,
    "lds":0,
    "ld_X":0,
    "ld_X+":0,
    "ld_-X":0,
    "ld_Y":0,
    "ld_Y+":0,
    "ld_-Y":0,
    "ldd_Y+q":0,
    "ld_Z":0,
    "ld_Z+":0,
    "ld_-Z":0,
    "ldd_Z+q":0,
    "sts":0,
    "st_X":0,
    "st_X+":0,
    "st_-X":0,
    "st_Y":0,
    "st_Y+":0,
    "st_-Y":0,
    "std_Y+q":0,
    "st_Z":0,
    "st_Z+":0,
    "st_-Z":0,
    "std_Z+q":0,
    "lpm":0,
    "lpm_Z":0,
    "lpm_Z+":0,
    "elpm":0,
    "elpm_Z":0,
    "elpm_Z+":0,
    "spm":0,
    "spm_Z+":0,
    "in":0,
    "out":0,
    "push":0,
    "pop":0,
    "xch_Z":0,
    "las_Z":0,
    "lac_Z":0,
    "lat_Z":0,
    "lsl":0,
    "lsr":0,
    "rol":0,
    "ror":0,
    "asr":0,
    "swap":0,
    "sbi":0,
    "cbi":0,
    "bst":0,
    "bld":0,
    "bset":0,
    "bclr":0,
    "sec":0,
    "clc":0,
    "sen":0,
    "cln":0,
    "sez":0,
    "clz":0,
    "sei":0,
    "cli":0,
    "ses":0,
    "cls":0,
    "sev":0,
    "clv":0,
    "set":0,
    "clt":0,
    "seh":0,
    "clh":0,
    "break":0,
    "nop":0,
    "sleep":0,
    "wdr":0
}

file_name = sys.argv[1]
outfile_name = file_name[:-3]+"tidied.lst"
asmfile_name = file_name[:-3]+"asm.lst"
f = open(file_name,"r")
avr_lst_raw = f.readlines()
f.close()
f2 = open(outfile_name,"w")
f3 = open(asmfile_name,"w")
pass1=[]
p = re.compile(r"../../../../crt1/gcrt1.S:.*")
q = re.compile("/home/.*/lib1funcs.S:.*")
t = re.compile("^ +[a-z0-9]+:.*")
s = re.compile("^ +[a-z0-9]+: +[a-f0-9]{2} [a-f0-9]{2} ?[a-f0-9]{2}? ?[a-f0-9]{2}? +([a-z0-9]+).*")
nocomments = re.compile(" +;.*")
hasisn=re.compile("^.{25} [a-f0-9]{2}")
commaone=re.compile("  ")
nospace=re.compile(" ")
notabs = re.compile(r"\t")
notdata = re.compile("^[a-z]")
for x in avr_lst_raw:
  if p.match(x) == None:
    if q.match(x) == None:
        x=notabs.sub("  ",x)
        print(x[:-1], file=f2)
        if t.match(x) != None:
            x=nocomments.sub("",x)
            y = x[25:]
            if hasisn.search(y) == None:
                y=commaone.sub(",",y,count=1)
                y=nospace.sub("",y)
                if notdata.match(y):
                    if(len(y) < 20):
                        print(y[:-1], file=f3)
asm = []
print(len(pass1))

f2.close()
f3.close()
f4=open(asmfile_name,"r")
asmlist=f4.readlines()
for x in asmlist:
    x=x[:-1]
    splits=x.split(",")
    #print(splits[0])
    #if len(splits) > 1:
        #print(splits[1])
    if splits[0]=="ld":
        splits[0]=splits[0]+"_"+splits[2]
    if splits[0]=="ldd":
        splits[0]=splits[0]+"_"+splits[2][0]+"+q"
    if splits[0]=="st":
        splits[0]=splits[0]+"_"+splits[1]
    if splits[0]=="std":
        splits[0]=splits[0]+"_"+splits[1][0]+"+q"
    isnbuckets[splits[0]] += 1
f4.close()
countfile ="stats/"+file_name[:-3]+"cnt"
f5=open(countfile,"w")
for x in isnbuckets:
    print(x+","+str(isnbuckets[x]),file=f5)
