#include <snes.h>

#include "background.h"
#include "vblank.h"
#include "data.h"

// IMPORTANT:
// Changing which pallette the BGs use is done via GFX compilation process
// * BGs always(?) use palette color #0 as the transparent color

void main()
{
    // Initialize SNES
    consoleInit();

    initBackground();
    bgSetEnable(2);
    consoleInitText(2, 0, &gfx_font_pic);
    consoleSetTextCol(RGB15(0, 0, 31), RGB15(0, 31, 0));

    u8 x, y;
    u16 pad;

    u8 SPEED = 1;
    char coord_msg[50];

    consoleDrawText(0, 0, "testing");

    while (1)
    {
        pad = padsCurrent(0);
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
        }

        bgSetScroll(0, x, y);
        sprintf(coord_msg, "x: %u, y: %u\n", (u32)x, (u32)y);
        consoleNocashMessage(coord_msg);
        WaitForVBlank();
    }
}