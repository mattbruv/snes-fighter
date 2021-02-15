#include <snes.h>

#include "data.h"
#include "vblank.h"

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

    // Set custom VBlank function
    nmiSet(customVBlank);
    u8 i = 0;
    char msg[16];

    while (1)
    {
        i++;
        sprintf(msg, "%u\n", (u32)i);
        consoleNocashMessage(msg);
        WaitForVBlank();
    }
}