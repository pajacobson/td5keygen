/*

File:  keygen.c
Keygen for Td5 ECU security access

Copyright (c) 2017, paul@discotd5.com

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.
*/

/*
 Timed processor cycle count = 328 with seed = 0x8091 running on PIC32MX795F512
*/

#include "keygen.h"

void keyGenerate(keyBytes_t * key) {

    uint16_t seed = key->keyword;
    uint16_t tmp = 0;
    uint8_t count = 0;
    uint8_t idx;
    uint8_t tap = 0;

    count = ((seed >> 0xC & 0x8) | (seed >> 0x5 & 0x4) | (seed >> 0x3 & 0x2) | (seed & 0x1)) + 1;
    
    for (idx = 0; idx < count; idx++) {
        
        tap = ((seed >> 1 ) ^ (seed >> 2 ) ^ (seed >> 8 ) ^ (seed >> 9 )) & 1;
        
        tmp = ((seed >> 1) | (tap << 0xF));
        
        if ((seed >> 0x3 & 1) && (seed >> 0xD & 1)) {
            seed = tmp & ~1; 
        } else {
            seed = tmp | 1;
        }
    }
    key->keyword = seed;    
}