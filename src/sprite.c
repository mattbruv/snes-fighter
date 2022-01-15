#include <snes.h>
#include "data.h"

void initSprites()
{
    return;
    //oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
    //             gfx_matt_idle_01_pal_size, 0, (0x4000 * 1), OBJ_SIZE16);
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