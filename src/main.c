#include <snes.h>

#include "data.h"

void main()
{
    // Initialize SNES
    consoleInit();

    consoleInitText(1, 1, &gfx_font_pic);

    // Copy tiles to VRAM
    bgInitTileSet(0, &gfx_test_pic, &gfx_test_pal, 0, gfx_test_pic_size, gfx_test_pal_size,
                  BG_16COLORS, 0x4000);

    // Copy map to VRAM
    bgInitMapSet(0, &gfx_test_map, gfx_test_map_size, SC_32x32, 0x1000);

    setMode(BG_MODE1, 0);
    // bgSetDisable(1);
    bgSetDisable(2);
    setScreenOn();

    while (1)
    {
        WaitForVBlank();
    }
}