
"""

.map files are 32x30 arrays of 2 bytes
1920 bytes

.pic files are 
32*30 arrays of 8 * 4 bytes

30720 bytes
chunk into 32x32 of 8 * 4 bytes

"""

import chunk


def partition(data, size):
    chunks = []
    for i in range(0, len(data), size):
        chunk = data[i:i+size]
        chunks.append(chunk)
    return chunks

def rotate(data):
    return data

f = open("../data/lake_01.map", "rb")
data = list(f.read())
chunks = partition(data, 2)
print(chunks)
print(len(chunks))
