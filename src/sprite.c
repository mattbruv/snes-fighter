#include <snes.h>
#include "sprite.h"
#include "spriteData.h"

#define SPRITE_ADDR 0x6000

void initSprites()
{
    initSpriteData();
}

void tickSprite()
{
}

void moveSprites()
{
}

void updateSprites()
{
}

/*
    sprite height/widths need to be aligned by 16 I think...

    using larger sprites would mean less for loop iterations
    consider this if speed becomes an issue

    For each 16x16 sprite, you have to calculate the graphics
    address correctly. Multiplying the index by two isn't enough,
    you also have to skip rows that are already included in the previous sprites
    For example, assume the line

    aaaaaaaaaa 
    bbbbbbbbbb
    cccccccccc
    dddddddddd

    you can render:   aa aa aa aa aa    as one row of sprites
                      bb bb bb bb bb
    but the next     
    line would be:    bb bb bb bb bb    which is incorrect, because we already showed
                      cc cc cc cc cc    bb
    
    in reality you    cc cc cc cc cc
    want to draw:     dd dd dd dd dd

*/
