from pathlib import Path

C_SOURCE = """#include <snes.h>
#include "spriteData.h"
#include "data.h"

void initSpriteData()
{{
    {initCode}
}}
"""

C_HEADER = """#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <snes.h>
#include "sprite.h"

{defAnims}
{defAnimFrames}

void initSpriteData();

#endif
"""

def getSprites():
    anims = {}

    files = Path.cwd().rglob(pattern="gfx/sprites/fighters/*/*/*.bmp")
    for f in files:
        p = f.parts
        person = p[6]
        anim = p[7]
        file = p[-1].split('.')[0]
        if person not in anims:
            anims[person] = {}
        if anim not in anims[person]:
            anims[person][anim] = []
        anims[person][anim].append(file)
        print(person, anim, p, file)
    return anims

def writeHeader():
    anims = getSprites()
    print(anims)
    header = C_HEADER
    defAnims = []
    defAnimFrames = []

    for person in anims:
        defAnims.append("// " + person + " animations")
        defAnimFrames.append("// " + person + " frames")
        for anim in anims[person]:
            defAnims.append("Animation " + "anim_" + person + "_" + anim + ";")
            for frame in anims[person][anim]:
                defAnimFrames.append("AnimFrame animframe_" + frame + ";")
                print(frame)
            print(person, anim)
        defAnims.append("")
        defAnimFrames.append("")
    
    header = header.format(
        defAnims='\n'.join(defAnims),
        defAnimFrames='\n'.join(defAnimFrames)
    )

    return header

def writeSource():
    source = C_SOURCE
    initCode = ["// queriendo quedarse en Monaco"]

    anims = getSprites()

    for person in anims:
        for anim in anims[person]:
            for frame in anims[person][anim]:
                label = "animframe_" + frame
                initCode.append("    " + label + ".centerX = 0;")
                initCode.append("    " + label + ".centerY = 0;")

                initCode.append("    " + label + ".picAddr = &gfx_" + frame + "_pic;" )
                initCode.append("    " + label + ".palAddr = &gfx_" + frame + "_pal;" )
                initCode.append("    " + label + ".picSize = gfx_" + frame + "_pic_size;" )
                initCode.append("    " + label + ".palSize = gfx_" + frame + "_pal_size;" )

                initCode.append("")
                print(frame)
            initCode.append("")
            print(person, anim)

    source = source.format(initCode="\n".join(initCode))
    return source

header = writeHeader()
open("src/spriteData.h", "w").write(header)
source = writeSource()
open("src/spriteData.c", "w").write(source)