/*
 *  @file       genLicense.cpp 
 *  @brief      Generate a license key and serial number for a product.
 *  @overview   The genLicense command generates a serial number and activation key for the required product. 
 *
 *  Usage:
 *      genLicense -p product -v version -s serial -b productBits
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

/***************************** Forward Declarations ***************************/

static int genKey(uint64 *licenseKey, int product, int version, int serial, int productBits);
static int mprAtoi(const char *str, int radix);
static char *mprStrTrim(char *str, const char *set);

static uint64 mprKey[1] = {
    MPR_LIC_KEY,
};


static char *licensedProducts[] = {
    "",                                             /* Eval */
    "eval",
    "appweb",
    "ejs",
    0,
};

/*********************************** Code *************************************/

int main(int argc, char *argv[])
{
    uint64      licenseKey, key;
    char        *program, *product, *tok, *cp, *versionStr, *argp;
    int         errors, major, minor, patch, productBits, serial, version;
    int         nextArg, radix, decode, quiet, validMsg, i;

    decode = 0;
    errors = 0;
    program = "genLicense";
    productBits = 0;
    product = 0;
    serial = 0;
    version = 0;
    quiet = 0;
    validMsg = 0;
    major = minor = patch = 0;

    for (nextArg = 1; nextArg < argc; nextArg++) {
        argp = argv[nextArg];
        if (*argp != '-') {
            break;
        }

        if (strcmp(argp, "--bits") == 0) {
            if (nextArg >= argc) {
                errors++;
            } else {
                argp = argv[++nextArg];
                radix = 10;
                if (argp[0] == '0' && (argp[1] == 'x' || argp[1] == 'X')) {
                    radix = 16;
                }
                productBits = mprAtoi(argp, radix);
            }

        } else if (strcmp(argp, "--decode") == 0) {
            decode++;

        } else if (strcmp(argp, "--validate") == 0) {
            validMsg++;

        } else if (strcmp(argp, "--quiet") == 0) {
            quiet++;

        } else if (strcmp(argp, "--product") == 0) {
            if (nextArg >= argc) {
                errors++;
            } else {
                product = argv[++nextArg];
            }

        } else if (strcmp(argp, "--serial") == 0) {
            if (nextArg >= argc) {
                errors++;
            } else {
                serial = mprAtoi(argv[++nextArg], 10);
            }

        } else if (strcmp(argp, "--version") == 0) {
            if (nextArg >= argc) {
                errors++;
            } else {
                argp = argv[++nextArg];
                tok = versionStr = strdup(argp);
                if ((cp = strchr(tok, '.')) != 0) {
                    *cp++ = '\0';
                }
                major = mprAtoi(tok, 10);

                if (cp) {
                    tok = cp;
                    if ((cp = strchr(tok, '.')) != 0) {
                        *cp++ = '\0';
                    }
                    minor = mprAtoi(tok, 10);
                }
                if (cp) {
                    tok = cp;
                    if ((cp = strchr(tok, '.')) != 0) {
                        *cp++ = '\0';
                    }
                    patch = mprAtoi(tok, 10);
                }
                version = major << 16 | minor << 8 | patch;
            }

        } else {
            errors++;
        }
    }

    if (decode) {
        if (argc != 3) {
            errors++;
        }

    } else if (product == 0) {
        errors++;
    }

    if (errors) {
        fprintf(stderr, "Bad arguments\n"
            "%s: -p product -v version -s serial -b productBits\n"
            "%s: -d serial key\n", program, program);
        exit(2);
    }

    if (decode) {
        int     major, minor, patch;

        licenseKey = 0;
        tok = argv[2];
        mprStrTrim(tok, "\"");

        for (i = 0; tok && *tok && i < 4; i++) {
            licenseKey |= mprAtoi(tok, 16);
            tok = strchr(tok, '-');
            if (tok) {
                tok++;
            }
            if (i < 3) {
                licenseKey <<= 16;
            }
        }
#if TESTING
        printf("%010LX\n", licenseKey);
#endif

        if (mprValidateLicense(licenseKey, &product, &version, &serial, &productBits) < 0) {
            if (validMsg) {
                printf("invalid\n");
                return 0;
            } else {
                if (! quiet) {
                    printf("genLicense: Key does not validate: %010LX\n", licenseKey);
                }
                return -1;
            }

        }
        major = (version >> 16) & 0x7;
        minor = (version >> 8) & 0x7;
        patch = (version) & 0x7;

        if (validMsg) {
            printf("valid\n");

        } else if (! quiet) {
            printf("Product %s, version %d.%d.%d, serial %d, productBits %x\n",
                product, major, minor, patch, serial, productBits);
        }

    } else {

        if (mprGenerateLicense(&licenseKey, product, serial, version, 
                productBits) < 0) {
            fprintf(stderr, "Can't generate license");
            return 1;
        }

        key = licenseKey;
        for (i = 3; i >= 0; i--) {
            if (i > 0) {
                printf("%04LX-", (key >> (i * 16)) & 0xFFFF);
            } else {
                printf("%04LX",  (key >> (i * 16)) & 0xFFFF);
            }
        }
        printf("\n");

#if TESTING
        printf("%010LX\n", licenseKey);
#endif
    }
    
    return 0;
}



/*
 *  Generate an activation key given the product, serial number and version.
 */
int mprGenerateLicense(uint64 *licenseKey, char *product, int serial, int version, int productBits)
{
    int     i, productId;

    assert(licenseKey);
    assert(product && *product);
    assert(serial >= 0);
    assert(version >= 0);

    productId = -1;
    for (i = 0; licensedProducts[i]; i++) {
        if (strcmp(licensedProducts[i], product) == 0) {
            productId = i;
            break;
        }
    }
    if (productId < 0) {
        fprintf(stderr, "Unknown product: %s", product);
        return -1;
    }

    if (serial < 0 || version < 0) {
        fprintf(stderr, "Bad serial or version");
        return -1;
    }

    /*
     *  Generate a key and then check it.
     */
    if (genKey(licenseKey, productId, version, serial, productBits) != 0) {
        fprintf(stderr, "Can't make activation key");
        return -1;
    }

#if FUTURE
    if (mprValidateLicense(*licenseKey, 0, 0, 0, 0) < 0) {
        fprintf(stderr, "Can't validate activation key");
        return -1;
    }
#endif
    return 0;
}



/*
 *  This routine generates an activation key, given a product ID and a serial number. 
 */
static int genKey(uint64 *licenseKey, int product, int version, int serial, int productBits)
{
    uint64      bits;
    int         checkBits, i, major, minor, patch;

    assert(licenseKey);

    /*
     *  62 bits (31 bits x 2 -- 2,147,438,648)
     *
     *  Bits format:        Bits
     *  ------------------------
     *
     *  High 31 bits
     *      Seed:           7
     *      Serial Number:  16
     *      Product bits:   8
     *
     *  Low 31 bits
     *      Product ID:     5
     *      Major Version:  4
     *      Minor Version:  3
     *      Patch Version:  3
     *      Checksum bits:  16
     */

    major = (version >> 16) & 0x7;
    minor = (version >> 8) & 0x7;
    patch = (version) & 0x7;

    /*  TODO -- ENDIAN */
    bits =  (((int64) (MPR_LIC_SEED & 0x7F)) << 55) |
            (((int64) (serial & 0xFFFF)) << 39) |
            (((int64)(productBits & 0xFF)) << 31) |
            ((product & 0x1F) << 26) |
            ((major & 0xF) << 22) |
            ((minor & 0x7) << 19) |
            ((patch & 0x7) << 16);
    
    /*
     *  Calculate a checksum
     */
    checkBits = 0;
    for (i = 1; i < 4; i++) {
        checkBits ^= ((bits >> (i * 16)) & 0xFFFF);
    }
    bits |= (checkBits & 0xFFFF);

    /*
     *  Crypt 
     */
    mprCrypt((uchar*) licenseKey, sizeof(uint64), (uchar*) &bits, sizeof(uint64), (uint64*) mprKey, sizeof(mprKey));
    
    return 0;
}



/*
 *  Parse an ascii number. Supports radix 10 or 16.
 */
static int mprAtoi(const char *str, int radix)
{
    int     c, val, negative;

    assert(radix == 10 || radix == 16);

    if (str == 0) {
        return 0;
    }

    val = 0;
    if (radix == 10 && *str == '-') {
        negative = 1;
        str++;
    } else {
        negative = 0;
    }

    if (radix == 10) {
        while (*str && isdigit(*str)) {
            val = (val * radix) + *str - '0';
            str++;
        }
    } else if (radix == 16) {
        if (*str == '0' && tolower(str[1]) == 'x') {
            str += 2;
        }
        while (*str) {
            c = tolower(*str);
            if (isdigit(c)) {
                val = (val * radix) + c - '0';
            } else if (c >= 'a' && c <= 'f') {
                val = (val * radix) + c - 'a' + 10;
            } else {
                break;
            }
            str++;
        }
    }

    return (negative) ? -val: val;
}



static char *mprStrTrim(char *str, const char *set)
{
    int     len, i;

    if (str == 0 || set == 0) {
        return str;
    }

    i = strspn(str, set);
    str += i;

    len = strlen(str);
    while (strspn(&str[len - 1], set) > 0) {
        str[len - 1] = '\0';
        len--;
    }
    return str;
}
