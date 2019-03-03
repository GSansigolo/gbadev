===============================================================================
Zero's Demos/PSEUDO Tutorial

Really they are just underdocumented source code (that is where the PSEUDO comes
in).  This is what I was looking for when I started and didn't find... I read 
through Dovoto's (pern project) and gbajunkies to get to here, so I am 
releasing my test demos (not incredible in any way (well hopefully they will 
be incredibly easy to understand)). I suggest you read the Cowbite Specs with 
these to purely understand it all. Here is the order to read them in. I have
a ton of experience with dos mod 13h and linux svgalib so if I do some things
strangely that could be why.

Also I use symbolic links to put crt0.o and lnkscript in all of the sub
directories without actually putting them there. If you need to understand
more about symbolic links I suggest reading the ln manpage (type: "man ln")

Also Also my vsync code is crap, don't use it.

00. Dot
01. Blit
02. Sprite
03. Keypad
04. Background
05. Moving
06. Chaos
07. DMA-Simple
08. DMA-Complex
09. Timer-IRQ
10. Sound-DMA

Maybe I will add some more in the future. I still haven't played with
rotation or transparency.... (I wanted to get to serial so I could
write a graphics editor that displayed on the gba screen and the pc
at the same time)
===============================================================================