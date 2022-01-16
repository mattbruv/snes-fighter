#include <snes.h>
#include "data.h"

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

void initSprites()
{
    oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
                  gfx_matt_idle_01_pal_size, 0, 0x2000, OBJ_SIZE8_L16);

    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;
    u16 gfxOffset = 0;
    u8 message[200];
    u16 rows = 0;
    u16 offset = 0;

    for (y; y < 8; y++)
    {
        for (x; x < 3; x++)
        {
            rows = (spriteCount * 2) / 16;
            id = spriteCount * 4;

            offset = ((spriteCount * 2)) + rows * 16;
            oamSet(id, x * 16, y * 16, 3, 0, 0, offset, 0);
            sprintf(message, "id: %hu (%hu) gfxOffset: %hu rows: %hu offset: %hu \n", id, (id / 4),
                    gfxOffset, rows, offset);
            consoleNocashMessage(message);
            oamSetEx(id, OBJ_LARGE, OBJ_SHOW);
            spriteCount++;
        }
        //WaitForVBlank();
        if (spriteCount % 6 == 0)
        {
            gfxOffset += 16;
        }
        sprintf(message, "spriteCount: %hu gfxOffset: %hu\n", spriteCount, gfxOffset);
        consoleNocashMessage(message);
        x = 0;
    }
}

void updateSprites()
{
    return;
    /*
    u16 col = 0;
    u16 row = 0;
    for (row = 0; row < 11; row++)
    {
        for (col = 0; col < 4; col++)
        {
            u16 id = (row * 4) + col;
            oamSet(id, 256, 50, 0, 0, 0, id, 0);
            oamSetEx(id, OBJ_SIZE16, OBJ_SHOW);
        }
    }
    */
}