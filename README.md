# snes-fighter
A homebrew two player fighting game for the SNES themed around my family

The vision for this game is to be like a knock-off Street Fighter with my family
members as the selectable characters.
The hope is that it will be a fun game to play during family get togethers
when the SNES classic is brought out.

This entire idea and game itself is very *very* crude and in the early stages.
I'm not sure about the practicality of it, but I think it can be done in C
without a large loss of speed.

This game uses the [pvsneslib](https://github.com/alekmaul/pvsneslib)
suite which is a C compiler and toolchain for developing games on the SNES in a higher level than assembly.
The library is quite finnicky to get set up.

# Game Design
I have no experience with fighting games, so this part is going to come once:
* Fundamental parts of the rendering engine are working.
* I understand the limitations of the SNES better
* I gain experience with other fighting games to know what base features to add.

# Engine Specifications

## Sprites

For designing sprites and animation for general gameplay, I'm thinking small sprites of 16x16 and large sprites of 32x32.
Fighters will be represented in sprite form in 32x32 pixel chunks.

There are 128 total available sprite slots in RAM.

Let's suppose the average sprite will be 64x120.
Now we are going to turn this into a grid of `n x n` sprites:

* at 8x8, it would be 8 columns and 15 rows, for 120 total sprites.
* at 16x16, it would be 4 columns and 8 rows, for 32 total sprites.
* at 32x32, it would be 2 columns and 4 rows, for 8 total sprites.

8x8 making 120 sprites is almost the entire capacity of the sprite system, so obviously this isn't going to work.
16x16 is much better, making only 32 sprites on average per character. 
But at 32x32 being 8 total sprites, saves the most amount of space with only 16 sprites per two characters on average.

This means that you iterate over the sprites a lot less, saving CPU time.
Whether or not this is significant is hard to measure, but in theory it is a lot less.

What are the downsides of using 32x32 sprite sizes?
The only downside I can think of right now is that when the sprites go off screen towards the left, they get clipped if their X value is less than zero.
So in the worst case, the boundaries of the screen for fighters will be +/- 32 pixels of blank space on both sides of the screen to prevent sprite graphical glitches.
This leaves `256 - 32 * 2` = `192` pixels, or 75% of screen space for the fighters (again, worst case).
in 16x16 mode, the worst case would be 87.5% screen space.

## ROM Size
It doesn't seem like ROM size is going to be an issue, and it looks like
I will be able to at least use up to 4MB if needed, so I'm not too worried
about this for now.

## VRAM Partitioning

At the moment, it looks like the standard library functions for loading data into VRAM must have addresses that are aligned with `0x1000` or `4096`.
Apparently this is a limitation with the SNES hardware.

It may be possible to use creative methods to really wedge the VRAM data together and eliminate blank space.
One example could be creating a huge buffer in WRAM and loading in the required data into the buffer, and transferring that via DMA, assuming that's possible.

I'm not going to explore this unless it is absolutely necessary and simple partitioning while using the standard library turns out to waste too much VRAM.
For the sake of [KISS](https://en.wikipedia.org/wiki/KISS_principle) I'm going to just work with `0x1000` chunks.


The entire SNES VRAM Space is `0x8000` **shorts** (or `0x10000` bytes), which gives 8 total chunks of storage space to play with.



# Useful Links:
[SNES Specs and documentation](https://problemkaputt.de/fullsnes.htm)

[pvsneslib](https://github.com/alekmaul/pvsneslib) C SNES library

[Yo-Yo Shuriken](https://drludos.itch.io/yo-yo-shuriken/devlog/147478/making-a-snes-game-in-2020), a devlog about making a SNES game with PVSNESLib

[SNES Background Graphics](https://en.wikibooks.org/wiki/Super_NES_Programming/Graphics_tutorial)