# Really, really ghetto die photos, and die dimensions!

These are not gonna look likethe ones your used to. Those are taken after cleaning the packaging off the die until it is pristine, and undamaged, with white fuming nitric acid (hot, white fuming nitric acid, actually - but that's done by heating the chip, not the fuming acid), the step of applying acid and then rising it off with acetone is repeated many times, before the chips are placed into your electron microscope to get a nice photo (you do have an electron microscope at home right?)

Me neither.

Nor do I happen to have any white fuming nitric acid. That stuff's a little hard to get, as a couple of federal agencies dislike it for very good reasons: DHS first off knows the main application better than almost anyone else - it's a key reagent in making all the military grade high explosives. Though wouldbe terrorists making high explosives at home usually blow themselves up before their targets, DHS still would prefer that the general public not have this stuff easily available. The DoT, being concerned with the hazards to road transport requires onerous regulations to be met to ship the stuff. Since it is toxic, corrosive, and can convert organic material it comes into contact with into explosive or near-explosive materials, this is not an unjustified or over cautious position.

Its the sort of thing that really needs a properly equipped chem lab to work with safely and I dunno what you're supposed to do with that acetone rinse the mixture of oxidizing acids and flamable solvents presents an explosion risk.

But you don't need that to learn a few things. What this study is directed towards is identifying which parts share dice, how many process nodes Microchip is using for different flash sizes (we know the 2-series must have a smaller one for the 3226 in the QFN)

## Taking die photos for fun and profit
Okay, maybe not *profit* but breakeven, assuming you consider the products in my store to be fairly priced.

### Step 1: Mount the chip on a PCB or breakout board
Be sure theat there are no taller components nearby.

### Step 2: Start filing
Use a small file with finely spaced teeth have a file cleaner on hand as these can clog files easily. This is going to take forever on a wide SOIC package, so that's not recommended. Try tomake sure you are filing it downevenly. routinely wipe the dust away. Eventhally you will see a color other than black poking through the corner. Immediately shift your filing away from that area. Try not to do any filing of the die once it's exposed.You may see some bits of encapsulation plastic still there Don't worry.

### Step 3: Put it under your digital microscope ($30 on aliexpress, or 80 for a nice one)
Adjust the focus - the you'll likely much more clearly see the places where encapsulation is still there.
use the end of the file to scrape those off, applying the minimum amount of force.

### Step 4: remove from digital microscope, measure with your best dial calipers, and note the size of the die.

### Step 5: Take a die photo with your digital microscope
Get it focused as well as you can and as close to straight down as you can.

Take a few pictures
This may or may not be possible with an unmodified microscope (at least, taking decent photos).

Many of them have the button to take a photolocated on on the same armature as the camera, so the force of you pushing the button shakes the camera and blurs every photo you take. There is an easy fix: You will need 1 normally open push button swtich, a several feet of two conductor wire, and a means to make a large enopugh hole to get the wire through the housing somehow (I used a "nibbler" to remove a bit of plastic from the enclosure edge. Diagonal cuttters work, they just look a lot worse). Solder the wire to the switch, and protect with shrink tube. Strip and tin a very short length from the other end of both conductors. Set aside.

Remove the screws that hold the on the enclosure that the buttons live in. You will likely find a bog standard screen and a small PCB, likely with a flat flex cable going to it and containing only buttons. Study the connector, and see if you can figure out how to disconnect it (this was the slowest part of the process for me). Once that is disconnected, remove the screws securing that pcb, and you will be looking at a circuit board with, most likely, half a dozen or so tact pushbuttons on it. Identify the swich that you press to take a pictire. Usually these have 4 pins, and with 2 pins connected together internally on each side, use your multimeter to locate two pins that are connected only when the button is pressed. Solder the ends of wires leading to your button on. Using hot-melt glue, secure the wires to the board, otherwise they will break off very rapidly. Remount the pcb with the buttons. Make a hole (easiest if you do it where the two halves of the housing come together) large enough for the two wires to fit through. run them through there, reinstall the screws that hold the enclosure together and test that it still works. You may have to go back and adjust how the focus knob is oriented relative to where in the range of focus you have, but this should be straigthforward - you want the stop on the knob coincide with the point at which the focus mechanism can move no further). Once you confirm that it works and can take pictures,secure the wires going through the hole in the enclosure with hot-melt glue (you'll need to do this to take useful pics anyway)

### Step 6: So what about that profit part? Email me the die photo and what it was from
I need the die photo, the measured size, and the part number of the chip it was from (ideally including the temeprature grade), and the name which you want to be identified as (note: this should be either a pseudonym, your name, or anonymous. Not someone else's name who was uninvolved in the works
The following dice still qualify for a small freebie (equal to the value of the chip (microchip direct qty 1 price) plus the value of our cheapest breakout board for the package). Multiple novel die photos can be added to get a larger amount of credit - any item in my Tindie store is fair game.

### Store credit eligible chips

| Series    | Large flash | med. flash   | small flash | v.small flash |
|-----------|-------------|--------------|-------------|---------------|
| tiny0     |    N/A      | 1607 or 1606 | 807 or 806  | 406, 402, 202 |
| tiny1     | 3216/3217   | 1616 qfn     | 817 or 816  | 412, 212, 417 |
| tiny2     | 3226 qfn    | Got em.      | 826 or 827  | 426 or 427    |
| AVR DA S  | 128DA32     | 64DA32       | 32DA32      | N/A           |
| AVR DA L  | 128DA48     | 64DA48       | 32DA48      | N/A           |
| AVR DB S  | Done        | 64DB32       | 32DB32      | N/A           |
| AVR DB L  | 128DB48     | 64DB48       | 32DB48      | N/A           |
| AVR DD S  | 64DD14      | Done         | 16DD20 QFN  | N/A           |
| AVR DD L  | 64DD28 QFN  | 32DD28 QFN   | 16DD28 QFN  | N/A           |
| AVR EA S *| 64EA28      | 32EA28       | 16EA28      | 8EA28         |
| AVR EA L *| 64EA48      | 32EA48       | 16EA48      | 8EA48         |

`*` - once one "S" the same size flash "L" are checked, if the die is the same (I think it is) all we will need is one of each flash size.

Where I marked QFN, that was not because I think the die is different. Rather, it's because that is the cheapest package and by far the easiest to file through

64 pin parts could be filed down instead, but cost more and willbe more work to file away than a 48-pin one. All indications are that the die is the same.

What will be really interesting is to see if the dies for the 28/32 and 48/64 DA/DB are the same. If they are, then the next question is how they tell the die which it is.

A few other interesting predictions: The 417 die will be the same die as the 817/816, not the other 4k 1-series parts.
The dinmensions of the 3226 die will be smaller than expected based on 1626 - there's no way they could fit it otherwise I don't think - they must be using a smaller process node.

The die from a SOIC-14 part is still just as valid - but is a lot more filing. An SOIC20 is a whole other level of filing, I wouldn't wish that on anyone.

We know that the two small and two large DD's of each flash size are not the same, as they are on different die revs.

## Results
Tiny2, 16k: [1627](ATtiny1627.png), [1626](ATtiny1626.png) Will add measurements once I relocate these and measure them. (Spence Konde)
AVR DB: [AVR128DB32 2.8mm x 2.8mm](AVR128DB32.png) (Spence Konde)
AVR DD: AVR32DD20 - as soon as I find it (I decapped one) and can measure and photograph it (Spence Konde)


## Classic AVRs
We'll post your photos, but we do not offer store credit as a reward - modern AVRs only.
