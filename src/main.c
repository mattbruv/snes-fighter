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
    dmaClearVram();

    WaitForVBlank();

    initBackground();

    setScreenOn();

    //initSprites();

    while (1)
    {
        //   tickSprite();
        WaitForVBlank();
    }
}