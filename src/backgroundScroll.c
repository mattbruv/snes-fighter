#include <snes.h>
#include "data.h"
#include "backgroundScroll.h"

// Hardcoded Background engine constants
#define BG_NUMBER 1
#define BG_PAL_NUMBER 0
#define BG_SIZE_MODE SC_64x32
#define COLOR_MODE BG_16COLORS

// Background tiles take up 0x8000 (32x32) + 0x1000 (32x4)
// Tile space calculation = 8 * 4 * total_tiles
// 8 * 4 * (32 * 32) = 0x8000
// 8 * 4 * (32 * 4) = 0x1000
// Total VRAM = 0x10000 - 0x9000 = 0x7000 BYTES, not SHORTS

// WARNING!
// The Tile Address MUST BE ALONG A 0x1000 BOUNDARY. You can't do 0x1000 / 2,
// or else the SNES will not render the graphics correctly, even though
// they will end up at (0x1000 / 2) in memory...
#define TILE_ADDRESS 0x1000 // 0x7000 / 2
#define MAP_ADDRESS TILE_ADDRESS - (0x1000 / 2)

typedef struct
{
    u8* tileAddress;
    u8* paletteAddress;
    u16 tileSize;
    u16 paletteSize;

    u8* mapAddress;
    u16 mapSize;

} BGInfo;

typedef struct
{
    u8 bgCount;
    BGInfo bg[5];

} ScrollBG;

ScrollBG lake;
ScrollBG* currentScrollBG;

void setScrollBackground()
{
    setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH);

    currentScrollBG = &lake;
    BGInfo* bg = &currentScrollBG->bg[0];
    bgInitTileSet(BG_NUMBER, bg->tileAddress, bg->paletteAddress, BG_PAL_NUMBER, bg->tileSize,
                  bg->paletteSize, COLOR_MODE, TILE_ADDRESS);
    bgInitMapSet(BG_NUMBER, bg->mapAddress, bg->mapSize, BG_SIZE_MODE, MAP_ADDRESS);

    // Disable all backgrounds except the relevant one in this file
    u8 i = 0;
    for (; i < 4; i++)
    {
        if (i == BG_NUMBER)
            bgSetEnable(i);
        else
            bgSetDisable(i);
    }

    setScreenOn(); // needed after enabling/disabling the backgrounds
    WaitForVBlank();

    // center this map in the 64x32 grid
    WaitForVBlank();
    //dmaCopyVram(bg->mapAddress, 0x1400 / 2, bg->mapSize);
    bgSetScroll(BG_NUMBER, 128, 8 * 2);

    // !!!!!!!!
    // I'm actually not sure if my idea makes sense, or can be done....
    // !!!!!!!!

    WaitForVBlank();
}

u8 i = 0;

void scrollBGUpdate()
{
    //dmaCopyVram(currentScrollBG->bg[1].tileAddress + (8 * 4 * i++), 0x5000, 8 * 4 * 32 * 2);
}

void initScrollBackgrounds()
{
    lake.bgCount = 2;

    lake.bg[0].tileAddress = &gfx_lake_01_pic;
    lake.bg[0].paletteAddress = &gfx_lake_01_pal;
    lake.bg[0].mapAddress = &gfx_lake_01_map;
    lake.bg[0].tileSize = gfx_lake_01_pic_size;
    lake.bg[0].paletteSize = gfx_lake_01_pal_size;
    lake.bg[0].mapSize = gfx_lake_01_map_size;

    lake.bg[1].tileAddress = &gfx_lake_02_pic;
    lake.bg[1].paletteAddress = &gfx_lake_02_pal;
    lake.bg[1].mapAddress = &gfx_lake_02_map;
    lake.bg[1].tileSize = gfx_lake_02_pic_size;
    lake.bg[1].paletteSize = gfx_lake_02_pal_size;
    lake.bg[1].mapSize = gfx_lake_02_map_size;
}