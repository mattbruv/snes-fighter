#include <snes.h>

#include "background.h"
#include "vblank.h"
#include "data.h"
// #include "sprite.h"

// IMPORTANT:
// Changing which pallette the BGs use is done via GFX compilation process
// * BGs always(?) use palette color #0 as the transparent color

void main()
{
    // Initialize SNES
    consoleInit();
    initBackground();

    consoleInitText(0, 0, &gfx_font_pic);
    void (*bg_funcs[2])() = { bgDemo, bgMichael };
    char* bg_names[2] = { "DEMO.BMP", "PEE.BMP" };
    char bg_name_curr[32];

    u8 bg_index = 0;

    u16 x = 0;
    u16 y = 0;
    u16 pad;
    u16 prev;

    u8 SPEED = 3;

    char pad_str[17] = "0000000000000000\0";
    u8 i = 0;

    while (1)
    {
        pad = padsCurrent(0);

        if (pad != prev)
        {
            for (i = 0; i < 16; i++)
            {
                if (pad & (1 << i))
                {
                    pad_str[i] = '1';
                }
                else
                {
                    pad_str[i] = '0';
                }
            }
            consoleDrawText(1, 23, "%s", pad_str);
        }

        if (pad)
        {
            if (pad & KEY_UP)
                y -= SPEED;
            if (pad & KEY_DOWN)
                y += SPEED;
            if (pad & KEY_LEFT)
                x -= SPEED;
            if (pad & KEY_RIGHT)
                x += SPEED;

            if ((pad & KEY_X) && ((prev & KEY_X) == 0))
                SPEED = (SPEED + 1 <= 50) ? SPEED + 1 : 50;
            if ((pad & KEY_Y) && ((prev & KEY_Y) == 0))
                SPEED = ((s8)(SPEED - 1) >= 0) ? SPEED - 1 : 0;

            if ((pad & KEY_A) && ((prev & KEY_A) == 0))
            {
                bg_index++;
                if (bg_index >= 2)
                {
                    bg_index = 0;
                }
                sprintf(bg_name_curr, "bg%u: %s", (u32)bg_index, bg_names[bg_index]);
                consoleDrawText(1, 1, "                               ");
                consoleDrawText(1, 1, "%s", bg_name_curr);
                (*bg_funcs[bg_index])();
                setScreenOn();
            }

            bgSetScroll(1, x, y);
            consoleDrawText(1, 26, "x: %u y: %u     ", (u32)x % (256 * 2), (u32)y % 256);
            consoleDrawText(1, 25, "speed: %u   ", (u32)SPEED);
        }
        prev = pad;

        WaitForVBlank();
    }
}