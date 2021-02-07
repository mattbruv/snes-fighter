#include <snes.h>

#include "data.h"

void main()
{
    // Initialize SNES
    consoleInit();

    // Copy tiles to VRAM
    bgInitTileSet(0, &gfx_test_pic, &gfx_test_pal, 0, gfx_test_pic_size, gfx_test_pal_size,
                  BG_16COLORS, 0x4000);

    // Copy map to VRAM
    bgInitMapSet(0, &gfx_test_map, gfx_test_map_size, SC_32x32, 0x0000);

    setMode(BG_MODE1, 0);
    bgSetDisable(1);
    bgSetDisable(2);
    setScreenOn();

    char msg[16];

    u8 i = 0;
    while (1)
    {
        bgSetScroll(0, i, i);
        sprintf(msg, "%u\n", (u32)i);
        i += 1;
        consoleNocashMessage(msg);

        WaitForVBlank();
    }
}