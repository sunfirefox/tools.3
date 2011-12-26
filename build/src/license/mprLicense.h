/*
 *  @file   mprLicense.h
 *  @brief  License header
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

#ifndef _h_LICENSE
#define _h_LICENSE 1

/********************************** Includes **********************************/

#include    <assert.h>
#include    <ctype.h>
#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>

/***************************** Forward Declarations ***************************/

#ifdef __cplusplus
extern "C" {
#else
typedef int bool;
#endif

/********************************** Defines ***********************************/

typedef unsigned int uint;
typedef unsigned char uchar;

#if WIN
    typedef unsigned __int64 uint64;
    #define INT64(x) (x##i64)
#else
    __extension__ typedef long long int int64;
    __extension__ typedef unsigned long long int uint64;
    #define INT64(x) (x##LL)
#endif

/*
 *  Supported products
 */
#define MPR_PRODUCT_EVAL            1
#define MPR_PRODUCT_APPWEB          2
#define MPR_PRODUCT_EJS             3
#define MPR_PRODUCT_MAX             4


/*
 *  Internal constants
 */
#define MPR_LIC_SEED                0x1             /* 8 bits */
#define MPR_LIC_KEY                 INT64(0x371aabcd7abcfe2b)
#define MPR_LIC_MAX_SERIAL          0xFFFF
#define MPR_LIC_MAX_KEY             8
#define MPR_CRYPT_BLEND_COUNT       8
#define MPR_CRYPT_ROUNDS            2

/********************************* Prototypes *********************************/

extern int mprGenerateLicense(uint64 *key, char *product, int serial, int version, int productBits);
extern int mprChecksumLicense(int serial);
extern int mprCrypt(uchar *output, int outputSize, uchar *input, int inputSize, uint64 *key, int keySize);
extern int mprDecrypt(uchar *output, int outputSize, uchar *input, int inputSize, uint64 *key, int keySize);
extern int mprValidateLicense(uint64 licenseKey, char **product, int *version, int *serial, int *productBits);

#if __cplusplus
} // extern "C"
#endif

#endif /* _h_LICENSE */
