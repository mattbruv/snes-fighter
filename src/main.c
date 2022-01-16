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
    // consoleInit();
    // consoleInitText(0, 0, &gfx_font_pic);

    initBackground();

    while (1)
    {
        WaitForVBlank();
    }
}