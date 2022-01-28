from pathlib import Path


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
                defAnimFrames.append("AnimFrame " + frame + ";")
                print(frame)
            print(person, anim)
        defAnims.append("")
        defAnimFrames.append("")
    
    header = header.format(
        defAnims='\n'.join(defAnims),
        defAnimFrames='\n'.join(defAnimFrames)
    )

    return header

header = writeHeader()
open("src/spriteData.h", "w").write(header)