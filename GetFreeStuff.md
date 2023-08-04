# Hey, you!
Yea, you, the AVR user who'd be reading a repo dedicated to obscure minutae of the AVR processor lines

## Want some free stuff?
As you may know I have a Tindie store: https://tindie.com/stores/drazzy

There's an "easy" way - find undocumented, wacky behavior in modern AVRs and inform me of it. Even if all you can do is exclude wide ranges of register addresses from potential magic functionality, that's important information to prevent duplicated effort.

And there a "slower" way but without the uncertaity. See [the Die Photos](DiePhotos/README.md)

## The very simple rules
* It must be novel (unless there is an unsolved mystery related to it on that page)
  * Elaborations on existing errata don't count unless they're really juicy.
* It must not already be publically known (ie, it must be your own research, and you must not have already told the world)
* Email info to spencekonde@gmail.com
* Once I respond and confirm, you are free to disclose it to whomever you want, except as noted below.
  * You may always disclose it to Microchip at your discretion (I suggest doing so for things that cause functioning which would not plausibly be desirable, or security vulnerabilities). You may do this even before notifying me, as long as you notify me before it gets into the errata.
* I will then attempt to reprodce the behavior you report.

### Once a confirmed novel peice of unducumented behavior is in my hands
Some due dilligence is performed prior to proceedng...
* Assuming it does not fall under the exceptions below which would make it irresponsible to dsclose I will add what has been determined about it to this repo, crediting you, your chosen pseudonym (no impersonation please, obviously), or an "anonymous user" or "an anonymous user from (your nation)".
* If the behavior is looks to be a bug, albeit 
* If the behavior is not obviously a bug or contrary to the datasheet and has obvious, non-malicious applications, It will be added to the errata page, but I see no reason to tip off Microchip more aggressively than that.

## Reward determinsion
Now, the exciting part. At my sole determiination rewards may be given for reporting to me some types of undocumented behavior. These will largely depend on the scale, applicability, and usefulness of the novel undocumented behavior. 
* Useful behavior (even if buggy or flaky) is more valuable than beavior that can only break functionaliy.
  * We do not pay for straight up silicon bugs without redeeming value. Microchip should, but I suspect for some reason the last thing they want is another 50 errata to fix. 
* Null results (that is, exclusion of large ranges of registers from any strange beavior) are of value, but omly if wide swathe of the special function registers can be excluded from having any interesting functionaliy.
* The simpler the trick, the greater the value (the 4x PLL multiplier would be a good one, except I alread know because Microchip accidentally disclosed it).
* The more powerful the result, the greater the value
* Exploits should not be disclosed publically. You can send them to me to get my agreement that this is an a bad exploit (really I'm thinking of only one kind of exploit.
  * An exploit to exfiltrate information from a locked chip is a critical bug - this should be sent to Microchip promptly. Really, this is so severe that don't really have any business knowing the trick while Microchip. I would hope that you could at least shake them down for a development board of theirs as a thanks. That said, if you do find one, do ping me just to say that you did. If a bunch of die revs that also fix other bugs rapidly start coming out, we'll know who to thank :P
  * If you find a way of writing read-only sigrow value (I would be fascinated if this were possible, I am almost certainy it is not), that's definitely an exploit. But it's also one that I would want to use to crack open the remaining secrets of the sigrow... so it's eligible for a reward from me.
  * I wlll never publically disclose anything that could be called an exploit until:
    * My contacts on the inside indicate that they don't consider it any worse than any other silicon errata.
    * I will then directly ask "Okay, so you don't consider this an exploit? So it won't bother you if I disclose it puiblically? If I do not hear back within 7 days I will interpret that as "no objection"."
