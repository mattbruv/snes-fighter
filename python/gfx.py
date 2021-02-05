import subprocess
from pathlib import Path
from tools import GFX_TOOL, makeDirs, moveFilesToData

# $(GFXCONV) -pr -pc16 -n -gs8 -pe0 -fbmp -m $<

params = ["-pr", "-pc16", "-n", "-gs8", "-pe0", "-fbmp", "-m"]

gfxPath = Path("gfx/")


def addGFXData(string, name):
    splitName = name.split(".")[0]
    files = [".pic", ".map", ".pal"]
    for f in files:
        name = splitName + "_" + f.replace(".", "")
        string += name + ":" + "\n"
        string += '.incbin "data/' + splitName + f + '"\n'
        string += name + "_end:\n\n"
    return string


def run():
    makeDirs()

    images = gfxPath.rglob("*.bmp")
    asmText = ""

    for img in images:
        asmText += addGFXData(asmText, img.name)
        subprocess.run([GFX_TOOL] + params + [str(img)])

    moveFilesToData(gfxPath, [".map", ".pal", ".pic"])

    text = open("python/data_template.asm", "r").read()
    text = text.replace("{GFX}", asmText)
    open("data.asm", "w").write(text)


run()