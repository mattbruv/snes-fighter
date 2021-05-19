#include <snes.h>

#include "background.h"
#include "vblank.h"
#include "data.h"
#include "sprite.h"

// IMPORTANT:
// Changing which pallette the BGs use is done via GFX compilation process
// * BGs always(?) use palette color #0 as the transparent color

void main()
{
    // Initialize SNES
    consoleInit();
    initBackground();

    consoleInitText(0, 0, &gfx_font_pic);
    consoleDrawText(1, 1, "testing");

    u16 x = 0;
    u16 y = 0;
    u16 pad;

    u8 SPEED = 3;

    while (1)
    {
        pad = padsCurrent(0);
        if (pad && (pad & KEY_L))
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

        bgSetScroll(1, x, y);
        WaitForVBlank();
    }
}