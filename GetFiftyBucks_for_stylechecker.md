# We hate AStyle
Checking of code formatting is of great importance when maintaining a shared library such as my cores. To that end we used the Check Code Formatting github action (see actions in any of my cores) which relies on astyle. Unfortunately, astyle has one particular piece of behavior that doesn't seem to be tunable. And this turns out to be a big problem. It's why we don't run the style check on the core itself *at all* (every single file would have to disable astyle). So what is this problem that we hate it so much for? 

It's only one thing: The handling of preprocessor directives. I can imagine that maybe for people working at high levels of abstraction with desktop PCs running their program, that's fine, because they probably don't have a huge number of conditionally compiled blocks, and almost certainly not ones nested more than a layer or two. It's routine for desktop programs to test for things that they could have known at compiletime would be one way or another way, but their program can end upo being 200mb in size and people would hardly raise an eyebrow. But on embedded systems, we program at a much lower level, we have nonvolatile memory at most 1/8000000 that of a desktop PC (with 1TB HDD), and 1/1000000th as much ram (16GB vs 16KB), often less. Thus, **EVERYTHING** that can be snipped out of the binary using preprocessor directives, must be, otherwise your binary will be bloated and you'll need a larger chip, if it will fit at all. And the ecosystem is far less homogenous than a desktop PC, because each chip has different peripherals and features, and the same code must support all of them. The result is, inevitably, 5+ levels of nested preprocessor tests. The enclosing #if might run for 2, 3, or even more or more screenfuls of incredibly dense code full of preprocessor tests and conditionally compiles mini-chunks.

The **CORRECT** way to format an #if block, just like any other conditional block, would be to add an indentation for each level of preprocessor block, like we do for if statements. This method is both reasonable and readable.
```c
#if something
  #if somethingelse
    doThis();
    #if defined(SOMEPERIPHERAL)
      SOMEPERIPHERAL.SFR = foo;
    #elif defined(SOMEOTHERPERIPHERAL)
      if (SYSCFG.REVID > 0x08) {
        SOMEOTHERPERIPHERAL.SFR=getValueForOther(foo);
      }
    #else
      return -1;
    #endif
  #endif
  return DoThatThing();
#endif
```
AStyle would issue a failure unless that was formatted like this:
```c
#if something
#if somethingelse
doThis();
#if defined(SOMEPERIPHERAL)
SOMEPERIPHERAL.SFR = foo;
#elif defined(SOMEOTHERPERIPHERAL)
if (SYSCFG.REVID > 0x08) {
  SOMEOTHERPERIPHERAL.SFR=getValueForOther(foo);
}
#else
return -1;
#endif
#endif
return DoThatThing();
#endif
```

As you can see, even in this greatly simplified case, astyle is telling us to reduce the readability instead of increase it. This sucks. And it can't be turned off without losing the rest of the stylechecking, which I would love to apply to the core. I can turn on and off other features, but there's no option for this one. I like all the other options that I have on

So, I am willing to give **$50 in merchandise** to anyone who is able to deliver either - a fork of astyle that does it, or some other tool that provides the same sort of format checking, but doesn't insist on a moronic layout. 

## Email your submission to spencekonde@gmail.com, with subject "$50 AStyle replacement submission"


## Fine print
Void where prohibited. in the case that multiple tools are suggested, the first one that works will be the winner. I must be able to make the tool work as a github action to qualify (by modifying check code formatting). A tool that runs on the desktop is useless - it needs to run in github actions. 
