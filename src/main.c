#include <snes.h>

#include "background.h"
#include "vblank.h"

void main()
{
    // Initialize SNES
    consoleInit();

    initBackground();

    while (1)
    {
        WaitForVBlank();
    }
}