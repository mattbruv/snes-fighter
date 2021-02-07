import subprocess
from pathlib import Path

from tools import GFX_TOOL, moveFilesToData

defaultArgs = ["-pr", "-pc16", "-n", "-gs8", "-pe0", "-fbmp", "-m"]
fontArgs = "-n -gs8 -po2 -pc16 -pe1 -mR! -m! -p!".split()

graphics = [  #
    {
        "glob": "backgrounds/*.bmp",
        "args": defaultArgs
    },  #
    {
        "glob": "fonts/*.bmp",
        "args": fontArgs
    }
]

filetypes = [".map", ".pal", ".pic"]

gfxPath = "gfx/"


def processOutput(data):
    for filetype in filetypes:
        files = Path(gfxPath).rglob("*" + filetype)
        for f in files:
            name = f.name
            entry = {"file": name, "prefix": "gfx"}
            data.append(entry)
            f.replace("data/" + name)


def processGraphics(data):
    print("Processing graphics...")

    for group in graphics:
        files = Path("gfx/").rglob(group["glob"])
        for f in files:
            command = [GFX_TOOL] + group["args"] + [str(f)]
            subprocess.run(command)

    processOutput(data)
