#include <snes.h>
#include "data.h"

typedef struct
{
    u8* picAddr;
    u8* palAddr;
    u16 picSize;
    u16 palSize;
} AnimFrame;

#define MAX_FRAMES 4

AnimFrame frames[MAX_FRAMES];

u8 reverse = 0;
u16 frameDelay = 3;
u16 frameCount = 0;
u8 currentFrame = 0;

//    oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
//                 gfx_matt_idle_01_pal_size, 0, 0x2000, OBJ_SIZE8_L16);

/*
    sprite height/widths need to be aligned by 16 I think...

    using larger sprites would mean less for loop iterations
    consider this if speed becomes an issue

    For each 16x16 sprite, you have to calculate the graphics
    address correctly. Multiplying the index by two isn't enough,
    you also have to skip rows that are already included in the previous sprites
    For example, assume the line

    aaaaaaaaaa 
    bbbbbbbbbb
    cccccccccc
    dddddddddd

    you can render:   aa aa aa aa aa    as one row of sprites
                      bb bb bb bb bb
    but the next     
    line would be:    bb bb bb bb bb    which is incorrect, because we already showed
                      cc cc cc cc cc    bb
    
    in reality you    cc cc cc cc cc
    want to draw:     dd dd dd dd dd

*/

#define SPRITE_ADDR 0x6000

void loadSprite(AnimFrame* frame)
{
    oamInitGfxSet(frame->picAddr, frame->picSize, frame->palAddr, frame->palSize, 0, SPRITE_ADDR,
                  OBJ_SIZE8_L16);
}

char message[200];

void tickSprite()
{
    if (++frameCount > frameDelay)
    {
        if (reverse)
            currentFrame--;
        else
            currentFrame++;

        if (currentFrame >= MAX_FRAMES) // 0 - 1 should wrap around.. || currentFrame < 0)
        {
            if (reverse == 1)
            {
                reverse = 0;
                currentFrame = 1;
                //sprintf(message, "reverse: %u frame: %u\n", (u32)reverse, (u32)currentFrame);
            }
            else
            {
                reverse = 1;
                currentFrame -= 2;
                //sprintf(message, "reverse: %u frame: %u\n", (u32)reverse, (u32)currentFrame);
            }
        }

        //consoleNocashMessage(message);

        loadSprite(&frames[currentFrame]);
        frameCount = 0;
    }
}

void seedFrames()
{
    frames[0].picAddr = &gfx_matt_idle_01_pic;
    frames[0].palAddr = &gfx_matt_idle_01_pal;
    frames[0].picSize = gfx_matt_idle_01_pic_size;
    frames[0].palSize = gfx_matt_idle_01_pal_size;

    frames[1].picAddr = &gfx_matt_idle_02_pic;
    frames[1].palAddr = &gfx_matt_idle_02_pal;
    frames[1].picSize = gfx_matt_idle_02_pic_size;
    frames[1].palSize = gfx_matt_idle_02_pal_size;

    frames[2].picAddr = &gfx_matt_idle_03_pic;
    frames[2].palAddr = &gfx_matt_idle_03_pal;
    frames[2].picSize = gfx_matt_idle_03_pic_size;
    frames[2].palSize = gfx_matt_idle_03_pal_size;

    frames[3].picAddr = &gfx_matt_idle_04_pic;
    frames[3].palAddr = &gfx_matt_idle_04_pal;
    frames[3].picSize = gfx_matt_idle_04_pic_size;
    frames[3].palSize = gfx_matt_idle_04_pal_size;
}

void initSprites()
{
    seedFrames();
    oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
                  gfx_matt_idle_01_pal_size, 0, SPRITE_ADDR, OBJ_SIZE8_L16);

    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;
    //u8 message[200];
    u16 rows = 0;
    u16 offset = 0;

    for (y; y < 8; y++)
    {
        for (x; x < 3; x++)
        {
            rows = (spriteCount * 2) / 16;
            id = spriteCount * 4;

            offset = ((spriteCount * 2)) + rows * 16;
            oamSet(id, x * 16 + 50, y * 16 + 75, 3, 0, 0, offset, 0);
            //sprintf(message, "id: %hu (%hu) gfxOffset: %hu rows: %hu offset: %hu \n", id, (id / 4),
            //  gfxOffset, rows, offset);
            //consoleNocashMessage(message);
            oamSetEx(id, OBJ_LARGE, OBJ_SHOW);
            spriteCount++;
        }
        //sprintf(message, "spriteCount: %hu gfxOffset: %hu\n", spriteCount, gfxOffset);
        //consoleNocashMessage(message);
        x = 0;
    }
}

void updateSprites()
{
    return;
}