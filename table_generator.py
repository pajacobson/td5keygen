#!/usr/bin/python

seed=0x00FA #Seed Input

count = ((seed >> 0xC & 0x8) + (seed >> 0x5 & 0x4) + (seed >> 0x3 & 0x2) + (seed & 0x1)) + 1

idx = 0
while (idx < count):
        tap = ((seed >> 1) ^ (seed >> 2 ) ^ (seed >> 8 ) ^ (seed >> 9)) & 1
        tmp = (seed >> 1) | ( tap << 0xF)
        if (seed >> 0x3 & 1) and (seed >> 0xD & 1):
                seed = tmp & ~1
        else:
                seed = tmp | 1

        idx = idx + 1

if (seed<256):
    high=0x00
    low=seed
else:
    high=seed/256
    low=seed%256

#Return Bytes
    
print hex(seed), hex(high), hex(low)