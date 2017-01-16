/*

File:  main.c
example usage of keygen.c for Td5 ECU security access

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
#include <stdint.h>
#include <stdio.h>
#include "keygen.h"

int main()
{
	keyBytes_t myKey;
	int keyLow, keyHigh;
	uint16_t seed;

    printf("Td5 security key example usage.\n\n" );
    printf("Enter first byte of security key: ");
    scanf("%2X", &keyHigh);
    printf("Enter second byte of security key: ");
    scanf("%2X", &keyLow);

    myKey.low_byte = (uint8_t)keyLow;
    myKey.high_byte = (uint8_t)keyHigh;
    seed = myKey.keyword;

    keyGenerate(&myKey);
    printf("seed: %X\n", seed);
    printf("key: %X\n", myKey.keyword );
    printf("high byte: %X\tlow byte: %X\n", myKey.high_byte, myKey.low_byte );
  
	return 0;
}
