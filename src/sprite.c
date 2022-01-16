#include <snes.h>
#include "data.h"

/*
    sprite height/widths need to be aligned by 16 I think...


*/

void initSprites()
{
    oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
                  gfx_matt_idle_01_pal_size, 0, 0x2000, OBJ_SIZE8_L16);

    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;

    for (y; y < 7; y++)
    {
        for (x; x < 3; x++)
        {
            id = spriteCount * 4;
            oamSet(id, x * 16, y * 16, 3, 0, 0, id * 0x40, 0);
            oamSetEx(id, OBJ_LARGE, OBJ_SHOW);
            spriteCount++;
        }
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