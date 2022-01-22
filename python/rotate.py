
"""

.map files are 32x30 arrays of 2 bytes
1920 bytes

.pic files are 
32*30 arrays of 8 * 4 bytes

30720 bytes
chunk into 32x32 of 8 * 4 bytes

"""

def flatten(t):
    return [item for sublist in t for item in sublist]

def rotatePic(data):
    if len(data) != 30720:
        exit("ERROR: PICTURE NOT 32x30!!")

    rotated = []
    width = 32*8*4

    for x in range(0, 32):
        for y in range(0, 30):
            offset = y * width + (x * 8 * 4)
            ns = data[offset:offset+8*4]
            rotated.append(ns)
            print(x, y, offset, ns)
            pass

    return flatten(rotated)

def rotateMap(data):
    if len(data) != 32*30*2:
        exit("ERROR: MAP NOT 32x30!!")

    rotated = []
    width = 32*2

    for x in range(0, 32):
        for y in range(0, 30):
            offset = y * width + (x * 2)
            ns = data[offset:offset+2]
            rotated.append(ns)
            print(x, y, offset, ns)
            pass

    return flatten(rotated)



f = open("../data/lake_01 copy.pic", "rb")
data = list(f.read())
data = rotatePic(data)
open("../data/lake_01.pic", "wb").write(bytes(data))

f = open("../data/lake_01 copy.map", "rb")
data = list(f.read())
data = rotateMap(data)
open("../data/lake_01.map", "wb").write(bytes(data))
