#include <snes.h>
#include "data.h"
#include "backgroundScroll.h"

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

ScrollBG* bgCurrent;

void setScrollBackground()
{
    bgCurrent = &lake;
}

/*
void bgInitMapSet(u8 bgNumber, u8 *mapSource, u16 mapSize, u8 sizeMode, u16 address)

void bgInitTileSet(
    u8 bgNumber,
    u8 *tileSource,
    u8 *tilePalette,
    u8 paletteEntry,
    u16 tileSize,
    u16 paletteSize,
    u16 colorMode,
    u16 address)

    bgInitTileSet(1, &gfx_pee_pic, &gfx_pee_pal, 1, gfx_pee_pic_size, gfx_pee_pal_size, BG_16COLORS,
                  0x1000);

    bgInitMapSet(1, &gfx_pee_map, gfx_pee_map_size, SC_64x32, 0x0000);
*/

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