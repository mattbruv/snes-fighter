#include <snes.h>

#include "background.h"
#include "data.h"

void initBackground()
{
    consoleNocashMessage("Initializing Background..");

    bgDemo();
    setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH);

    bgSetEnable(0);
    bgSetEnable(1);
    bgSetDisable(2);
    bgSetDisable(3);

    setScreenOn();
}

void bgDemo()
{
    bgInitTileSet(1, &gfx_demo_pic, &gfx_demo_pal, 1, gfx_demo_pic_size, gfx_demo_pal_size,
                  BG_16COLORS, 0x4000);
    bgInitMapSet(1, &gfx_demo_map, gfx_demo_map_size, SC_64x32, 0x2000);
}

void bgMichael()
{
    bgInitTileSet(1, &gfx_pee_pic, &gfx_pee_pal, 1, gfx_pee_pic_size, gfx_pee_pal_size, BG_16COLORS,
                  0x4000);
    bgInitMapSet(1, &gfx_pee_map, gfx_pee_map_size, SC_64x32, 0x2000);
}