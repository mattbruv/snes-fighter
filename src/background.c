#include <snes.h>

#include "data.h"

void initBackground()
{
    consoleNocashMessage("Initializing Background..");

    // bgInitTileSet(0, &gfx_demo_pic, &gfx_demo_pal, 1, gfx_demo_pic_size, gfx_demo_pal_size,
    //            BG_16COLORS, 0x3000);
    // bgInitMapSet(0, &gfx_demo_map, gfx_demo_map_size, SC_64x32, 0x1000);
    // bgSetMapPtr(0, 0x0000, SC_64x32);
    //bgInitTileSet(0, &gfx_test1_pic, &gfx_test1_pal, 0, gfx_test1_pic_size, gfx_test1_pal_size,
    //             BG_16COLORS, 0x0000);
    // bgInitMapSet(0, &gfx_test1_map, gfx_test1_map_size, SC_64x32, 0x2000);

    setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH);

    bgSetEnable(0);
    bgSetDisable(1);
    bgSetDisable(2);
    bgSetDisable(3);

    setScreenOn();
}