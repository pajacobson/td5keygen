# 
# File:   keytool.py

# Based on the work of:
# Copyright (c) 2017, paul@discotd5.com

# Modified by:
# Copyright (c) 2017, xabiergarmendia@gmail.com

# All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this
   # list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
   # this list of conditions and the following disclaimer in the documentation
   # and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# The views and conclusions contained in the software and documentation are those
# of the authors and should not be interpreted as representing official policies,
# either expressed or implied, of the FreeBSD Project.
#

#!/usr/bin/python

import sys

def printhelp():
    print "\nLand Rover Td5 Storm Engine ECU auth keygen"
    print "Usage:"
    print "\tGet key with seed (0-65535), example:"
    print "\t\tkeytool.py 1082"
    print "\t\tWill return key"
    exit()

if len(sys.argv)==2:
    if 0<=int(sys.argv[1])<=0xFFFF:

        seedin=int(sys.argv[1])
        seed=seedin
        
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

        #Calculate high and low bytes, for auth response      
        if (seed<256):
            high=0x00
            low=seed
        else:
            high=seed/256
            low=seed%256
            
        print "Seed: ",seedin," (",hex(seedin),") - Key: ",seed," (",hex(seed),") "
    else:
        printhelp()
else:
    printhelp()