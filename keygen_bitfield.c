
/*

File:  keygen_bitfield.c
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
 Timed processor cycle count = 295 with seed = 0x8091 running on PIC32MX795F512
*/

#include "headers/keygen.h"

void keyGenerate(keyBytes_t * key) {

    typedef union {
        uint16_t  all;
        struct {
           uint16_t bit00 : 1,
                    bit01 : 1,
                    bit02 : 1,
                    bit03 : 1,
                    bit04 : 1,
                    bit05 : 1,
                    bit06 : 1,
                    bit07 : 1,
                    bit08 : 1,
                    bit09 : 1,
                    bit10 : 1,
                    bit11 : 1,
                    bit12 : 1,
                    bit13 : 1,
                    bit14 : 1,
                    bit15 : 1; 
        };
    
    } seedbits_t;

    seedbits_t seed, tmp;
    uint8_t count, tap, idx = 0;
    
    seed.all = key->keyword;
    
    count = ((seed.bit15 * 8) + (seed.bit07 * 4) + (seed.bit04 * 2 ) + (seed.bit00)) + 1;

    while (idx < count) {
        
        tap = (seed.bit01 ) ^ (seed.bit02) ^ (seed.bit08 ) ^ (seed.bit09);
        
        tmp.all = (seed.all >> 1);
        tmp.bit15 = tap;
        tmp.bit00 = ((seed.bit03) && (seed.bit13)) ? 0 : 1;
        
        seed.all = tmp.all;
        
        idx++;
    }         
    key->keyword = seed.all;
}
