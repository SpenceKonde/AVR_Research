# Examples of exceptional an unexceptional instruction distributions

These are the following sketches - can you guess which is which?


## Exceptional #1
A highly abnormal distribution of instructions

What immediately jumps out are:
1. An absolutely huge number of eor instructions.
2. note that a synonym for add rd, rd is lsl rd, likewise adc and rol. There's a whole lot of shifting and xoring going on, the total numbers of certain instructions seem to be


| Isn.  |count| Note
|-------|-----|------
| total |3118 |
|   eor | 326 | Lotta xoring going on!
|   sts | 285 | unusually large number of STSs
|   ldi | 275 |
|   add | 271 | add rd, rd = lsl rd
|  movw | 222 |
|   adc | 215 | adc rd, rd = rol rd
|   lds | 149 |
|   lsr | 129 |
|   mov | 106 |
| rcall |  96 |
|   ror |  94 |
|  rjmp |  80 |
|  breq |  69 |
|  sbiw |  67 |
|  push |  61 |
|   pop |  61 |
|  call |  48 |
| std_Z |  41 |
|   nop |  38 |
|  andi |  36 |
| ldd_Z |  35 |
|   sbc |  26 |
| ldd_Y |  26 |
|  swap |  23 |
|  subi |  21 |
|   out |  20 |
|   bst |  20 |
|   bld |  20 |
|  sbci |  18 |
|   ret |  18 |
|   neg |  14 |
|   cpc |  14 |
|   sub |  13 |
|   ori |  11 |
|   mul |  11 |
|   cpi |  11 |
|   jmp |  10 |
|    in |  10 |
|    cp |   9 |
|  brne |   9 |
| std_Y |   9 |
|  adiw |   8 |
|  sbrs |   8 |
|  ld_Z |   7 |
|  sbrc |   6 |
|   com |   5 |
|  cpse |   5 |
|  brcs |   5 |
|  ld_X |   5 |
|  st_Z |   5 |
|   and |   4 |
|    or |   4 |
|  reti |   4 |
|   cli |   4 |
|  brcc |   3 |
|  ld_Y |   3 |
|   lpm |   3 |
|  elpm |   3 |
| ld_Z+ |   2 |
|  st_X |   2 |
| st_X+ |   2 |
|   cbi |   2 |
|   dec |   1 |
|  ijmp |   1 |
| icall |   1 |
|  brlt |   1 |
|  brts |   1 |
| ld_X+ |   1 |
| ld_Y+ |   1 |
| st_-Z |   1 |
|   sei |   1 |
|   set |   1 |
|   clt |   1 |


## Unexceptional

### Unexceptional #1
But is this really unexceptional?


| Isn.  |count |
|-------|------|
| total | 7484 |
|   ldi | 1110 |
|  movw |  606 |
|  rjmp |  375 |
|   pop |  312 |
|  push |  298 |
|  subi |  269 |
|   lds |  264 |
|   mov |  259 |
|  sbci |  222 |
|   cpi |  217 |
|  call |  211 |
|   sts |  187 |
|   adc |  174 |
|   add |  165 |
| ldd_Y |  147 |
| rcall |  135 |
|   cpc |  135 |
|  breq |  132 |
|   sbc |  125 |
| std_Y |  125 |
|  brne |  119 |
|   eor |  116 |
|  ld_Z |   99 |
|   mul |   98 |
| std_Z |   92 |
|    cp |   88 |
|   ret |   87 |
|  brcc |   80 |
|  brcs |   75 |
| ldd_Z |   73 |
|  andi |   67 |
|   sub |   61 |
|  adiw |   59 |
|   lpm |   58 |
|   out |   55 |
|   nop |   54 |
|   ror |   51 |
|   and |   48 |
|  st_Z |   48 |
|    in |   45 |
|  ld_X |   43 |
|    or |   41 |
|   ori |   39 |
|   lsr |   38 |
|  sbrs |   34 |
|   com |   33 |
|  cpse |   31 |
|   dec |   27 |
|   cli |   27 |
|  st_X |   20 |
|  sbiw |   19 |
|  sbrc |   19 |
|  brge |   13 |
|  ld_Y |   11 |
|  brlt |   10 |
|   inc |    9 |
|   jmp |    9 |
|  brtc |    9 |
|  brmi |    8 |
| ld_X+ |    8 |
|   asr |    8 |
|   bld |    8 |
|  st_Y |    7 |
| icall |    6 |
|  reti |    6 |
| ld_Z+ |    5 |
| st_X+ |    5 |
|   bst |    5 |
|   clt |    5 |
|   neg |    4 |
|  ijmp |    4 |
|  brpl |    4 |
|   sbi |    4 |
|   cbi |    4 |
| st_Z+ |    3 |
|  elpm |    3 |
|  swap |    3 |
|   sei |    3 |
|  sbis |    2 |
|  brts |    1 |
| ld_Y+ |    1 |
| ld_-Z |    1 |
| st_-X |    1 |
|   sec |    1 |
|   set |    1 |
