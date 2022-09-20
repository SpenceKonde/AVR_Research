# Bounties, or how to get free loot

There are a number of known things, and an unknown number of unknown things, which knowledge of could be used to expose new functionality (things like the fact that you can set DA/DB internal oscillator to 32, and the PLL multiplier up to 4x, not just 3x as the docs say). Transferring such valuable otherwise unknown information to me qualifies you for rewards.

## Conditions:
* The reward goes to someone who discovers undocumented functionalities and behavior in any modern AVR (or solves the mystery of the ATTiny828 ADC - that's the only classic AVR undocumented feature with a bounty on it)
* Unless stated otherwise where the specific bounty is discused (as is the case with the t828), the basic reward is an item in my tindie store featuring an impacted part, OR the equivalent price in bare boards (quantity discounts do apply, too). 
* In order to qualify for this, your discovery must be
  * Previously unknown to me and undocumented
  * Behavior intrinsic to the hardware, not an artifact of code (yours or the core's)
  * Useful
  * Working on the latest commercially available version of the silicon. 

## Things that do not qualify
* Finding behavior that directly contradicts the documentation and makes the device less useful, and which isn't listed on the errata sheet. These are silicon bugs, and while finding out about them is lovely (in order to know to warn others), they fail the usefulness criteria. You should let Microchop know post-haste. (for better results from them, try to gove code that overrides main to get rid of setup and loop, so they can'd blame Arduino or the core; If you've found a bug which they deny to be a bug, I have someone I can complain to on the inside).
* An undocumented feature must be useful. The BIST-facility on the 2-series (unclear if it made it into released silicon), is not useful unless you happen to be a test engineer at Microchip (plus, anyone who read the first ATpack's IO headers knows about it, same with the EA-series' NVM-related settings, which as far as I can tell are likely to be wedged into combination that produces the best write endurance and lowest power consuptionn, also seem unlikely to be useful.
* Finding an issue that reduces the security of the chip lock feature or otherwise allows exfiltration of code from a locked chip. This is a critical issue - but it needs to be handled mby the manufacturer. Contact Microchip at once.
* Finding an issue that allows you to make one chip think it is a different one (for example, if you discovered you could trick an  AVR32D48 into thinking it was actually an AVR128DA48. That would be useful, yes, but also poses a supply chain security problem, as counterfeit chips flooded the market with fake signatures. Any way to write to the signature row at all qualifies here. While they could very well be useful, that usefullness would be concentrated in deceptive and nefarious purposes.
* Contributing clever code adds a feature to the core is always appreciated, and accords prestige and esteem within the community, but doesn not qualify for freebies if based on documented features, even if said documentation is umclear and poorly written. 

## Things that would quality
  * Finding an extra group code (value of a multi-bit bitfield, like how PORT.PINnCTRL has 3 bits marked ISC (Input Sense Control), but only 6 are used) that is marked as "reseverd" but in fact does do something that is plausibly useful. 
  * nding that certain registers within a peripheral's address range but listed as reserved, and which change the behavior of the peripheral in a way that doesn't renderit non-functional (for example the aforementioned CLKCTRL registers that allow overclocking the internal oscillator and increasing the PLL multiplier)
  * Finding that a reseved bit actually has an effect, and that the effect has plausible uses. Sometimes they start out planning to include a feature, and then late in the design program, become unhappy with it, and drop it.... even though the implementation has already been completed. These are often not removed from the hardware before release, and just scrubbed from the documentation. Wouldn't you rather know that there's somewhat fiddly and awkward feature that isnt're really of release quality in case you ever need it? 
  * Using "fuzzing" (using automated means to enter every invalid combination of values into a set of registers, and seeing if any do anything detectable) to generate leads is entirely within the spirit of this offer. You still have to be able to describe what useful thing it does. 

## Concrete, imaginary examples that would qualify:
* Reading the page buffer on parts that have one. 
* Reversing the bit order on serial (this strains the useful requirement)
* A new mode or option on a peripheralthat is not documented, and does something potentially useful.
* Any hidden event generator, event user, or CCL input source that does something 
* Any non-destructive method short of contacting Microchip Support to determine whther a specimen of AVR Dx-series part is Industrial or Extended temperature range. (the part numbers are AVRfffDxpp-t/package, where fff is the flash size, X is a A, B, or D, pp is the number of pins, T is either I (max temp 105C) or E (max temp 125C), and package is a 2-3 character code consisting of letters and sometimes numbers that identifies the package that the part is in. 

## Also, at times I may explicitly mention rewards for something
This is the case for:
* The ATTiny828 ADC mystery (I swear, if you did the right things you could get a differential reading out of that thing....)
* The meaning of the three non constant bytes in the signature block of modern tinyAVRs. They must mean something!
* Fixing the ATTinyCore Virtual Boot erase bug in Optinooy (this isn't a case of information, but rather of actual code changes, making it distinctly different from the other bounties discussed here. But it will get you free stuff, and more than the usual reward. Currently, the bootloader erases pages as it rewrites them, and and stores the rjmp/jmp to the app where the EERDY vector is. That means that if the erase process is interrupted, neither the app nor the bootloader can be accessed. The required erase behavior is this: When the bootloader currently erases the first page, it must instea erase all pages, in decending order, starting from the page immediately before the the bootloader. The rjmp/jmp that jumps to the start of the application must be moved to the very end of the last page before the bootloader (like micronucleus does). See the issues listed for ATTinyCore for more information. If you have this working on either 4-byte vector (16k flash) or 2-byte vector (8 or less), that is sufficient, I can generalize it from there. 

## Restrictions
* I (Spence Konde) have final say over whether something is useful and novel (I am open about what I know about the AVRs. There is no beahvior I'm aware of that's undocumented that i'm keeping secret, and if there was, it would be because it was a security issue, and I'd have related it to Microchip).
* You must provide information sufficient for me to demonstrate the undocumented feature. 
* If you have code that demonstrates it, you must have released it as open source and consent to any code I write to make use of it being released, with credit given to you for discovering the trick. 
* I may ask you for to justify how a proposed undocumented feature is useful if it looks like a bug.
* Free shipping applies to the USA only, unless the feature you found was particularly outstanding. International shipping rates have gone up 5:1 for outbound packages since I started this business, most of it between 2016 and 2020.
* I may increase the reward at my sole discretion. 
* I cannot send as a reward an item which I am out of stock of.
* No matter how good the undocumented feature is, due to current world events and in accordance with US law, I am not shipping rewards (or anything else) to Russia, Belarus, or Ukraine. Due to decade long world events, I cannot ship rewads (or anything else) to North Korea or Iran, or any other nation covered by sanctions t that prohibit doing so. I apologize to my fellow humans in Ukraine (except for the Russian troops), Belarus, and North Korea, as well as those in Russia who aren't actively abbetting that shameful war. 
* Offer void were prohibited or restricted by law.
