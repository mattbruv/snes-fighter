#include <snes.h>

void main()
{
    // Initialize SNES
    consoleInit();
    setMode(BG_MODE1, 0);
    setBrightness(0xF);

    char msg[16];

    u8 i = 0;
    while (1)
    {
        sprintf(msg, "%u\n", (u32)i);
        i += 1;
        consoleNocashMessage(msg);

        WaitForVBlank();
    }
}