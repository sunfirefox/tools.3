/**
 *  @file       mprLiense.c 
 *  @brief      Mpr commerical license validation
 *  @overview 
 *  @remarks 
 */

/*
 *  @copy   default
 *  
 *  Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
 *  Copyright (c) Michael O'Brien, 1994-2012. All Rights Reserved.
 *  
 *  This software is distributed under commercial and open source licenses.
 *  You may use the GPL open source license described below or you may acquire 
 *  a commercial license from Embedthis Software. You agree to be fully bound 
 *  by the terms of either license. Consult the LICENSE.TXT distributed with 
 *  this software for full details.
 *  
 *  This software is open source; you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as published by the 
 *  Free Software Foundation; either version 2 of the License, or (at your 
 *  option) any later version. See the GNU General Public License for more 
 *  details at: http://www.embedthis.com/downloads/gplLicense.html
 *  
 *  This program is distributed WITHOUT ANY WARRANTY; without even the 
 *  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *  
 *  This GPL license does NOT permit incorporating this software into 
 *  proprietary programs. If you are unable to comply with the GPL, you must
 *  acquire a commercial license to use this software. Commercial licenses 
 *  for this software and support services are available from Embedthis 
 *  Software at http://www.embedthis.com 
 *  
 *  Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */

/********************************** Includes **********************************/

#include    "mprLicense.h"

/**************************** Forward Declarations ****************************/

#if BLD_FEATURE_LICENSE || 1

static uint64 mprKey[1] = {
    MPR_LIC_KEY,
};

static void mprSleep(int milliseconds);

/************************************* Code ***********************************/

uint mprRotate(uint x, int count) 
{
    uint    y;

    if (count > 0) {
        y = ((x << count) | (x >> ((sizeof(x) * 8) - count)));
    } else {
        y = ((x >> -count) | (x << ((sizeof(x) * 8) + count)));
    }
    return y;
}



/*
 *  Validate a license
 */
int mprValidateLicense(uint64 licenseKey, char **product, int *version, int *serial, int *productBits)
{
    static      int times = 0;
    uint64      bits;
    int         i, seed, major, minor, patch, checkBits, sum;
    int         productId, serialNum;

    assert(licenseKey != 0);

    if (times++ > 6) {
        mprSleep((times / 2) * 1000);
    }

    mprDecrypt((uchar*) &bits, sizeof(bits), (uchar*) &licenseKey, sizeof(licenseKey), mprKey, 1);

    seed = (int) ((bits >> 55) & 0x7F);
    serialNum = (int) ((bits >> 39) & 0xFFFF);

    if (productBits) {
        *productBits = (int) ((bits >> 31) & 0xFF);
    }

    productId = (int) ((bits >> 26) & 0x1F);

    if (product) {
        switch (productId) {
        case MPR_PRODUCT_EVAL:
            *product = "eval";
            break;
        case MPR_PRODUCT_APPWEB:
            *product = "appweb";
            break;
        case MPR_PRODUCT_EJS:
            *product = "ejs";
            break;
        default:
            *product = "unknown product";
            break;
        }
    }

    major = (int) ((bits >> 22) & 0xF);
    minor = (int) ((bits >> 19) & 0x7);
    patch = (int) ((bits >> 16) & 0x7);
    checkBits = (int) (bits & 0xFFFF);

    sum = 0;
    for (i = 1; i < 4; i++) {
        sum ^= (int) ((bits >> (i * 16)) & 0xFFFF);
    }
    if (checkBits != sum) {
        return -1;
    }

    if (seed != MPR_LIC_SEED) {
        return -1;
    }
    if (serialNum > MPR_LIC_MAX_SERIAL) {
    }
    if (major > 16) {
        return -1;
    }
    if (minor > 7) {
        return -1;
    }
    if (patch > 7) {
        return -1;
    }

    if (version) {
        *version = ((major & 0xFF) << 16) | ((minor & 0xFF) << 8) | (patch & 0xFF);
    }

    if (productId < 0 || productId > MPR_PRODUCT_MAX) {
        return -1;
    }

    return 0;
}


/*
 *  Basic crypto routine. Modified Feistel cipher suitable for encrypting small blocks of input.
 */
static int mprCrypto(uchar *output, int outputSize, uchar *input, int inputSize, uint64 *key, int keySize, int cryptDir)
{
    uint    left, right;
    uint    subKey;
    uchar   *op;
    int     j, i, n, size;

    keySize /= sizeof(uchar);

    if (inputSize <= 0) {
        if (input) {
            inputSize = strlen((char*) input) + 1;
        }
    }

    if (inputSize >= 8) {
        if (outputSize < inputSize) {
            return -1;
            return -1;
        }
        if ((outputSize % 8) != 0) {
            if ((outputSize / 8) <= (inputSize / 8)) {
                return -1;
            }
        }
    }

    if (input != 0) { 
        if (output != input) {
            for (i = 0; i < inputSize; i++) {
                output[i] = input[i];
            }
            for (; i < outputSize; i++) {
                output[i] = 0;
            }
        }
        outputSize = inputSize;
    }

    /*  FUTURE -- ENDIAN, 64 BIT */
    size = (outputSize + 7) & ~0x7;

    for (j = 0; j < size; j += sizeof(uint64)) {
        op = &output[j];
        left = ((uint*) op)[0];
        right = ((uint*) op)[1];

        /*
         *  Compute n rounds over each pair.
         */
        for (n = 0; n < MPR_CRYPT_ROUNDS; n++) {

            uint shifted;

            if (cryptDir > 0) {
                /*
                 *  R = (L ^ Fn(R, key)) <<< L);
                 */
                subKey = (uint) (key[(n / 2) % keySize] >> ((n % 2) * 32));

                shifted = left ^ right;
                right = mprRotate(shifted, left & 0x1F);
                right += subKey;

                shifted = left ^ right;
                left = mprRotate(shifted, right & 0x1F);
                left += subKey;

            } else {
                /*
                 *  R = Fn((R >>> L) ^ L);
                 */
                int index = MPR_CRYPT_ROUNDS - n - 1;
                subKey = (uint) (key[(index / 2) % keySize] >> ((index % 2) * 32));

                left = left - subKey;
                left = mprRotate(left, - (int) (right & 0x1F));
                left ^= right;

                right = right - subKey;
                right = mprRotate(right, - (int) (left & 0x1F));
                right ^= left;

            }
        }
        ((uint*) op)[0] = left;
        ((uint*) op)[1] = right;
    }
    return size;
}



/*
 *  Crypt block.
 */
int mprCrypt(uchar *output, int outputSize, uchar *input, int inputSize, uint64 *key, int keySize)
{
    return mprCrypto(output, outputSize, input, inputSize, key, keySize, 1);
}


/*
 *  Decrypt block. 
 */
int mprDecrypt(uchar *output, int outputSize, uchar *input, int inputSize, uint64 *key, int keySize)
{
    return mprCrypto(output, outputSize, input, inputSize, key, keySize, -1);
}


static void mprSleep(int milliseconds)
{
#if WIN
    Sleep(milliseconds);
#elif LINUX || CYGWIN || SOLARIS
    struct timespec timeout;
    int             rc;

    mprAssert(milliseconds >= 0);
    timeout.tv_sec = milliseconds / 1000;
    timeout.tv_nsec = (milliseconds % 1000) * 1000000;
    do {
        rc = nanosleep(&timeout, &timeout);
    } while (rc < 0 && errno == EINTR);

#endif
}


#endif /* BLD_FEATURE_LICENSE */
