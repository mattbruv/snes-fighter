#include <snes.h>
#include "data.h"

typedef struct
{
    u8* picAddr;
    u8* palAddr;
    u16 picSize;
    u16 palSize;
} AnimFrame;

#define MAX_FRAMES 10

AnimFrame frames[MAX_FRAMES];

u8 reverse = 0;
u16 frameDelay = 2;
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

void moveSprites();

void tickSprite()
{
    //    moveSprites();

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
    frames[0].picAddr = &gfx_evan_idle_01_pic;
    frames[0].palAddr = &gfx_evan_idle_01_pal;
    frames[0].picSize = gfx_evan_idle_01_pic_size;
    frames[0].palSize = gfx_evan_idle_01_pal_size;

    frames[1].picAddr = &gfx_evan_idle_02_pic;
    frames[1].palAddr = &gfx_evan_idle_02_pal;
    frames[1].picSize = gfx_evan_idle_02_pic_size;
    frames[1].palSize = gfx_evan_idle_02_pal_size;

    frames[2].picAddr = &gfx_evan_idle_03_pic;
    frames[2].palAddr = &gfx_evan_idle_03_pal;
    frames[2].picSize = gfx_evan_idle_03_pic_size;
    frames[2].palSize = gfx_evan_idle_03_pal_size;

    frames[3].picAddr = &gfx_evan_idle_04_pic;
    frames[3].palAddr = &gfx_evan_idle_04_pal;
    frames[3].picSize = gfx_evan_idle_04_pic_size;
    frames[3].palSize = gfx_evan_idle_04_pal_size;

    frames[4].picAddr = &gfx_evan_idle_05_pic;
    frames[4].palAddr = &gfx_evan_idle_05_pal;
    frames[4].picSize = gfx_evan_idle_05_pic_size;
    frames[4].palSize = gfx_evan_idle_05_pal_size;

    frames[5].picAddr = &gfx_evan_idle_06_pic;
    frames[5].palAddr = &gfx_evan_idle_06_pal;
    frames[5].picSize = gfx_evan_idle_06_pic_size;
    frames[5].palSize = gfx_evan_idle_06_pal_size;

    frames[6].picAddr = &gfx_evan_idle_07_pic;
    frames[6].palAddr = &gfx_evan_idle_07_pal;
    frames[6].picSize = gfx_evan_idle_07_pic_size;
    frames[6].palSize = gfx_evan_idle_07_pal_size;

    frames[7].picAddr = &gfx_evan_idle_08_pic;
    frames[7].palAddr = &gfx_evan_idle_08_pal;
    frames[7].picSize = gfx_evan_idle_08_pic_size;
    frames[7].palSize = gfx_evan_idle_08_pal_size;

    frames[8].picAddr = &gfx_evan_idle_09_pic;
    frames[8].palAddr = &gfx_evan_idle_09_pal;
    frames[8].picSize = gfx_evan_idle_09_pic_size;
    frames[8].palSize = gfx_evan_idle_09_pal_size;

    frames[9].picAddr = &gfx_evan_idle_10_pic;
    frames[9].palAddr = &gfx_evan_idle_10_pal;
    frames[9].picSize = gfx_evan_idle_10_pic_size;
    frames[9].palSize = gfx_evan_idle_10_pal_size;
}

u8 xOff = 0;
u8 yOff = 0;

void moveSprites()
{
    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;

    for (y; y < 8; y++)
    {
        for (x; x < 4; x++)
        {
            id = spriteCount * 4;
            oamMemory[id] = x * 16 + xOff; // xPos
            oamMemory[id + 1] = y * 16 + yOff; // yPos

            //offset = ((spriteCount * 2)) + rows * 16;
            //oamSet(id, x * 16 + 50, y * 16 + 75, 3, 0, 0, offset, 0);
            spriteCount++;
        }
        x = 0;
    }

    // increase offsets
    //    if (rand() > 65535 / 2)
    {
        xOff += 2;
        yOff += 2;
    }
}

void initSprites()
{
    seedFrames();
    //oamInitGfxSet(&gfx_matt_idle_01_pic, gfx_matt_idle_01_pic_size, &gfx_matt_idle_01_pal,
    //             gfx_matt_idle_01_pal_size, 0, SPRITE_ADDR, OBJ_SIZE8_L16);

    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;
    //u8 message[200];
    u16 rows = 0;
    u16 offset = 0;

    for (y; y < 8; y++)
    {
        for (x; x < 4; x++)
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