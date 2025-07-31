# Examples of exceptional and unexceptional instruction distributions

These are the following sketches - can you guess which is which?


## Contestant 1: 

| Isn.  |count| Note
|-------|-----|------
| total |3118 |
|   eor | 326 |
|   sts | 285 |
|   ldi | 275 |
|   add | 271 |
|  movw | 222 |
|   adc | 215 |
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


## Contestant 2

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


## Analysis

Contestant #1 is clearly exceptional. The top instructions are, in order:
1. eor (exclusive OR)
2. sts (store a value in a working register to either main memory (to update a variable) or to write a register in the extended I/O space)
3. ldi (load immediate - this instruction is commonly found as a "top used instruction") 
4. add (addition - or logical shift left)
5. movw (copies the contents of working register X and X+1 to Y and Y+1. X and Y both even)
6. adc (addition with carry)


WTF is going on there? 

That program consists of every 16-bit full-period XORSHIFT prng in hand optimized asm, and a procedure to initialize them and then call them 2^16 times, checking that the result is never 0 or the first result. By printing a small bit of text after finishing every generator, the serial console's timestamps also served to confirm expected performance. These are of the form:
```c
  /* a, b, and c are compile-time known constants. */
  /* y is a static uint16_t, and is both the seed for the next round and the value returned. 
  y ^= y << a; 
  y ^= y >> b;
  y ^= y << c;
  /* the above code, generated for each set of triples confirmed to be full length, used for initial testing was then optimized. The lines of the above form were replaced (find/replace) with hand-optimized asm, as this code sucks with -Os if you care about performance too */

  return y;
```
The totals look more normal (and the binary is snaller but slower) if you let the compiler do it. The compiler is uninspiring on this sort of math (Secret: The architectures algos get written for have an operation that bitshifts or rotates a register n bits - same cost regardless of shift, We need 1 clock per cycle per byte to do it the naive way.)