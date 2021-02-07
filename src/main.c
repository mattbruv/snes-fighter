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

    char keys[16] = "0000000000000000";

    u8 i;
    u16 pad0;
    consoleDrawText(1, 1, "Controller keys:");
    u8 x = 0;
    u8 y = 0;

    char frame_str[16];
    u32 frame = 0;

#define SPEED 3

    while (1)
    {
        pad0 = padsCurrent(0);
        for (i = 0; i < 16; i++)
        {
            keys[i] = '0';
            if ((pad0 & (1 << i)))
            {
                keys[i] = '1';
            }
        }
        consoleDrawText(1, 3, keys);
        if (pad0 & KEY_LEFT)
            x -= SPEED;
        if (pad0 & KEY_RIGHT)
            x += SPEED;
        if (pad0 & KEY_UP)
            y -= SPEED;
        if (pad0 & KEY_DOWN)
            y += SPEED;

        sprintf(frame_str, "%u", ++frame);
        consoleDrawText(1, 18, "frame:");
        consoleDrawText(1, 20, frame_str);

        WaitForVBlank();
        bgSetScroll(0, x, y);
    }
}