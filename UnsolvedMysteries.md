# Unsolved Mysteries in AVRs
Solve these - and let me know if you do. You'll get credit and a link to your report, and (depending on the scale of the mystery) maybe even free hardware. 

## Modern AVRs

### TCA frequency mode
The frequency mode of a type A timer is inconsistent with the description of the timer. 
In frequency mode, the period is determined by the compare match value. It's specified generically, implying that all three WO channels should be avbailable, so what happens if you try to get different frequencies out of them? It seems like it's inevitably going to come out broken on one pin or the other, it's not clear how this would behave - either that, or the timer would need to keep three counts. If so, 1: that's ingenious however they did it, and 2: Well then, what do the other registers do when it's working this magic? TCA0.CNT does what? What about PER and PERBUF, which are theoretically not used here (it's conceivable that, if it does work, it's keeping three counts. That strikes me as extremely improbable, however. 

### TCA "restart" errata
Wait, why is this in the errata? It says that the problem is that it resets the direction? The datasheet says it is supposed to! Did they not read their own datasheet? Were major customers gathering outside Microchip HQ with pitchforks demanding this not be how it works? 

### USART RS485 = 0b10 mode
The tinyAVR 0/1-series parts have two RS485 bits, 0b01 gives the behavior we know, where it drives XDIR to control an external line driver. Early versions of the DA-series headers had it, (the same version with the 4x PLL option (which is in the released silicon) and the 4th power profile for the analog comparators). Since none of the bugs in the USART were fixed on the Dx-series, it stands to reason that this feature was also removed only on paper. 

I can't make sense of what the second mode is supposed to do... the documentation on the parts that admit to having this feature is a bit terse:
```
Either an external line driver is supported as shown in the figure below (RS485=0x1 in USART.CTRLA), or control of
the transmitter driving the TxD pin is provided (RS485=0x2)
```
What does that mode do? Is whatever it does something that is plausibly what was intended, or did it not really work right and get dropped for that reason? Is it secretly present on Dx-series parts? Does it have any practical use?

### Why was the 4th power profile for the analog comparators dropped from the DA datasheet and headers at the last minute? 
The functionality is almost certainly still in the silicon. One imagines that it must have been broken, and they decided to drop it entirely, instead of of adding to the pile of errata on these parts. This would have had the slowest response time and the lowest power consumption. 

### tinyAVR 0/1 CCL inputs: SPI MISO, MOSI, and SCK?
On everything else, the CCL can only get SPI SCK and MOSI, and supposedly only in Master mode. I'm not really sure what the point of this functionality is. The Master mode only caveat is not present in the 0/1-series datasheets - AND all three lines are available! Do they all work? Can you use them in slave mode? For that matter, are they really disabled in SPI slave mode on anything that's not a tinyAVR 0/1?

## classic AVRs

### The 828 and the mystery of the ADC
The 828 is a sorry, sorry piece of hardware. It is clear reading the datasheet that it was supposed to have a differential ADC, and at the last minute, someone scrubbed out mention of it (they refer to single ended channels, normally they only call them that when they might be a differential channel. The register layout looks like that of the killer ADC on the 841 (one of the best on any classic AVR) - except that almost every bit is marked reserved instead. Rather, it has the lamest ADC possible, and is notable only in that it can use all 28 I/O pins. It has the one basic reference option (REFS0 is all alone), and the high MUX bit (normaly what selects differential or single ended channels on classic AVRs) is always supposed to be set to 0. 

If we accept the hypothesis that the differential ADC was planned, but got scrubbed at the last minute, without them being able to swap back to a normal register layout, what does that imply? 
The fact that the register layout looks like it does, and that the changes to the datasheet look to have been made in such a hurried and slapdash manner strongly suggests that it must have happened *very* late in the process. I would venture a guess that there were no changes to the die between after QA found that the differential ADC had a major defect. Most likely, management refused to let them respin to fix it, and they didn't want to deal with it via Errata because 1) they knew very well that the chip would never get a fix, and 2) it was so severely broken that it would be embarassing to publically disclose what went wrong and expect customers to navigate the complicated workaround that might be needed to use it, if there was one. 
So they were left with a ATtiny88-like chip, with it's only advantage being 1 hardware serial port. Everything else about it is worse than the much older, much cheaper 88: The USI clock pin is pulled low if the WDT isn't in use (per errata, same bug as the 1634 has) The TWI is slave only. You get remappable PWM pins within 1 port, but you still only have 2 timers to generate the PWM with.... Was there really a market for that? Who's gonna buy that? If that's what they had, I'd have expected them to take the design (and possibly some design team members) behind the woodshed. But they didn't they're still selling them 8 years later. Someone must be buying enough of them to keep it profitable to make these. Why? Someone picked it because yhey wanted lots of ADC mux options? Because they couldn't make a software USART work? 
As I pointed out, it looks like they still have the register layout for the fancy ADC that it didn't get, which is highly suggestive of the possibility that no changes were made to the design, and they do have a differential ADC under the hood. This would also explain why they are still in production: A few key customers, say ones that Atmel worked closely with, know what happened, and were told how to work around to use the ADC for differential measurements. 

The first test, would be to make some crude resistor ladder contraption, put one on a breakout board, and feed a bunch of the pins each with a different voltage.Say you do the first 16. Then you can increment through the mux values and see that you're getting a different value every time. 
Then do the same, only with the high bit of the mux set. If you get the same values, that suggests that this theory is wrong.
Treat the value you read as a signed 16-bit integer. 0's or 1023's could mean anything, so you'd need to dig deeper to see if there's anything to this... seemingly random numbers are a good sign, and numbers constrained between 0 and 512, or that are negative demonstrate that there's a differential ADC there. 

Then you just have to piece together how it was supposed to work (841's ADC is the reference to uee), and then figure out what's wrong with it and how to work around the bug.... 

I would consider the possibility that the broken pin could be related somehow. You might need the WDT on to make it not-pull-low for things to work. Or the opposite. Or for it to be pulled high externally. The observed behavior of it though looks almost like a prtotection diode is pulling it low, suggesting that they connected it to the nearest power rail, but that was for some reason not actually powered when the WDT/ULP isn't running. We do know that a hidden ADC is not required for this though, so it may be unrelated, as the 1634 has no indications of a fancier ADC, but still has a bugged pin. On the other hand, the 1634 may have been slated to get the same fancy ADC, had the same problem, and had only slightly more time to deal with it by switching back to a normal register layout.


If you manage that, it still wouldn't be better than the modern AVRs, but it would be a demonstration of persistence and clever low-level work that would win you the admiration of your peers (who you just demonstrated were actually not peers: you're better than they are, because you solved this and they didn't)

