# Td5 keygen
Keygen for Td5 ECU diagnostics protocol.

- Consumes the 2 byte security code seed sent by the Land Rover Td5 ECU. 
- Produces the matching access key using an algorithm derived from disassembly of ECU code.

The keygen.c and keygen.h C code should be portable with minimal modifications. 
The seed value is assumed to have big endian byte ordering:
[high_byte][low_byte]

keygen_bitfield.c is a version of the keygen that uses C bitfields and union structure to elminate the bit-twiddling.
This version is faster than keygen.c but likely to be less portable. It's probably worth a look even if you plan not to use this version as the bits the algorithm manipulates are not obscured by masks and shifts.

** Td5 Security Access - seed request 

The ISO14230 securityAccess request has the following format:

securityAccess Request#1 Service ID = 0x27
requestSeed = 0x01

So the Td5 security access request sent from the test to the ECU is formatted as:
02 27 01 2A
   ^^ ^^

The ECU responds with the seed values:
04 67 01 34 A5 45
         ^^ ^^
This message is decoded as:

   securityAccess Positive Response Service ID = 0x67
   requestSeed = 0x01
   seed#1 = high byte (e.g. 0x34)
   seed#2 = low byte (e.g. 0xA5)


The typedef union given in keygen.h is a C construct that allows the seed to be accessed as individual bytes or the complete seed.  This avoids the need to bitshift manually.

If prefered, simple bitshifting of the seeds can be done to combine the individual bytes.

   seed = seed_1 << 8 | seed_2

- - -
**** Long winded explanation

Looking at the binary representation shows how this works.

    b0011 0100  (0x34)
    b1010 0101  (0xA5)

shifting left by 8 bits (or * 2^8)

    b0011 0100 0000 0000 (0x3400)

then OR the two numbers to combine the bits that are set the first OR second number.

    b0011 0100 0000 0000  (0x3400)
    b0000 0000 1010 0101  (0x00A5)
    --------------------
    b0011 0100 1010 0101  (0x34A5)

- - -

It really doesn't matter which method you use to combine the two seed bytes providing the input to the core algorithm is a correctly ordered 16 bit seed.


## Td5 Security Access - seed response
The response sent from the tester to the ECU contains the two bytes calcuated from the seed bytes using the keygen.

    04 27 02 54 D3 54
             ^^ ^^
	securityAccess Request Service ID = 0x27
	keySend = 0x02
   	key#1 = high byte (e.g. 0x54)
   	key#2 = low byte (e.g. 0xD3)

 The single value returned by the keygen can be broken into bytes for transmission to the ECU using bit shifts and masks.
    
    high_byte = returned_key >> 8;
    low_byte = returned_key & 0xFF;  	

Assuming you've done everything correctly the ECU should send a positive response message indicating that the tester has securityAccess to the ECU.

    02 67 02 6B

 And you can now do stuff...

## Demo code
There is a demonstration of how the C code is used in the file "demo.c"
This can be compiled using  "gcc demo.c keygen.c -o demo.o", and run by typing ".\demo.o" from the same directory.

    Td5 security key example usage.

    Enter first byte of security key: 34
    Enter second byte of security key: A5
    
    seed: 34A5
    key: 54D3
    high byte: 54	low byte: D3  


## Change Log

2017-01-16:
- Merge pull request from EA2EGA
- Minor changes to python code
	- alter loop structure to "for".