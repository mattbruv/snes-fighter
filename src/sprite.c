#include <snes.h>
#include "data.h"
#include "sprite.h"
#include "spriteData.h"

#define SPRITE_ADDR 0x6000
#define PAL_INDEX 0

typedef struct SpriteFighter
{
    u8 xPos;
    u8 yPos;
    Animation* currentAnim;
} SpriteFighter;

SpriteFighter spritePlayer1;

void loadSprite(SpriteFighter* sprite)
{
    Animation* anim = sprite->currentAnim;
    AnimFrame* frame = &anim->frames[anim->frameCounter];

    //consoleNocashMessage("pic addr: %hu, pal addr: %hu\n",
    //                    (u16)anim->frames[anim->frameCounter].picAddr, (u16)&frame->palAddr);

    oamInitGfxSet(frame->picAddr, frame->picSize, frame->palAddr, frame->palSize, PAL_INDEX,
                  SPRITE_ADDR, OBJ_SIZE8_L16);

    u16 x = 0;
    u16 y = 0;
    u16 spriteCount = 0;
    u16 id = 0;
    u16 rows = 0;
    u16 offset = 0;

    for (y = 0; y < frame->rowCount; y++)
    {
        for (x = 0; x < frame->colCount; x++)
        {
            rows = (spriteCount * 2) / 16;
            id = spriteCount * 4;
            offset = ((spriteCount * 2)) + rows * 16;
            oamSet(id, x * 16 + sprite->xPos, y * 16 + sprite->yPos, 3, 0, 0, offset, PAL_INDEX);
            oamSetEx(id, OBJ_LARGE, OBJ_SHOW);
            spriteCount++;
        }
    }
}

void initSprites()
{
    initSpriteData();

    anim_evan_idle.frames = frames_evan_idle;
    anim_evan_idle.totalFrames = 10;
    anim_evan_idle.waitThreshold = 3;
    anim_evan_idle.frameCounter = 0;
    anim_evan_idle.waitCounter = 0;
    anim_evan_idle.reversable = 1;
    anim_evan_idle.frameDirection = 1;

    anim_matt_idle.frames = frames_matt_idle;
    anim_matt_idle.totalFrames = 4;
    anim_matt_idle.waitThreshold = 4;
    anim_matt_idle.frameCounter = 0;
    anim_matt_idle.waitCounter = 0;
    anim_matt_idle.reversable = 1;
    anim_matt_idle.frameDirection = 1;

    spritePlayer1.xPos = 55;
    spritePlayer1.yPos = 85;
    spritePlayer1.currentAnim = &anim_matt_idle;

    loadSprite(&spritePlayer1);
}

void tickSprite()
{
    Animation* anim = spritePlayer1.currentAnim;

    if (++anim->waitCounter >= anim->waitThreshold)
    {
        anim->waitCounter = 0;

        anim->frameCounter += anim->frameDirection;

        if (anim->reversable == 1)
        {
            if (anim->frameCounter >= anim->totalFrames)
            {
                anim->frameCounter -= 2;
                anim->frameDirection = -1;
            }
            else if (anim->frameCounter == 0)
            {
                anim->frameDirection = 1;
            }
        }
        else
        {
            if (anim->frameCounter >= anim->totalFrames)
            {
                anim->frameCounter = 0;
            }
        }

        loadSprite(&spritePlayer1);
        //consoleNocashMessage("frame: %hu\n", (u16)anim->frameCounter);
        //consoleNocashMessage("addr evan: %hu\n", (u16)&frames_evan_idle);
        //consoleNocashMessage("addr sprite: %hu\n", (u16)&anim->frames);
    }
}

void moveSprites()
{
}

void updateSprites()
{
}

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
