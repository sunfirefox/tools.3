/**
 *  @file   bldout.c
 *  @brief  Format build output
 *  @copy   default
 *  
 *  Copyright (c) Embedthis Software LLC, 2003-2012. All Rights Reserved.
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
 *  details at: http: *www.embedthis.com/downloads/gplLicense.html
 *  
 *  This program is distributed WITHOUT ANY WARRANTY; without even the 
 *  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *  
 *  This GPL license does NOT permit incorporating this software into 
 *  proprietary programs. If you are unable to comply with the GPL, you must
 *  acquire a commercial license to use this software. Commercial licenses 
 *  for this software and support services are available from Embedthis 
 *  Software at http: *www.embedthis.com 
 *  
 *  Local variables:
    tab-width: 4
    c-basic-offset: 4
    End:
    vim: sw=4 ts=4 expandtab

    @end
 */
/******************************* Documentation ********************************/
/*
 *  usage:  bldout [-c contIndent] [-i indent] [-w width] file ...
 */
/********************************* Includes ***********************************/

#include    <ctype.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#if !_WIN32
    #include    <unistd.h>
#endif

/********************************* Defines ************************************/

#define MAX_BUF             (4 * 4096)
#define DEFAULT_WIDTH       100                 /* Maximum column width */
#define DEFAULT_INDENT      2                   /* Indent continuation lines */
#define DEFAULT_CONT_INDENT 4                   /* Indent continuation lines */

/********************************* Defines ************************************/

static int contIndent;
static int indent;
static int width;

/***************************** Forward Declarations ***************************/

static int format(FILE *fp);

/************************************ Code ************************************/

int main(int argc, char *argv[])
{
    FILE    *fp;
    char    *argp;
    int     n, c, errflag, status, nextArg;

    errflag = 0;
    contIndent = DEFAULT_CONT_INDENT;
    indent = DEFAULT_INDENT;
    width = DEFAULT_WIDTH;

    for (nextArg = 1; nextArg < argc; nextArg++) {
        argp = argv[nextArg];
        if (*argp != '-') {
            break;
        }
        if (strcmp(argp, "-c") == 0) {
            if (nextArg >= argc) {
                errflag++;
            } else {
                contIndent = atoi(argv[++nextArg]);
            }

        } else if (strcmp(argp, "-i") == 0) {
            if (nextArg >= argc) {
                errflag++;
            } else {
                indent = atoi(argv[++nextArg]);
            }

        } else if (strcmp(argp, "-w") == 0) {
            if (nextArg >= argc) {
                errflag++;
            } else {
                width = atoi(argv[++nextArg]);
            }
        }
    }
    if (errflag) {
        fprintf(stderr, "%s: usage: [-c contIndent] [-i indent] [-w width] files....\n", argv[0]);
        exit(2);
    }

    status = 0;
    if (nextArg >= argc) {
        status = format(stdin);

    } else for (n = nextArg; n < argc; n++) {
        fp = fopen(argv[n], "r");
        if (fp == NULL) {
            fprintf(stderr, "Can't open %s\n", argv[n]);
            exit(3);
        }
        status = format(fp);
        fclose(fp);
    }
    return status;
}

/******************************************************************************/

static int format(FILE *fp)
{
    char    inBuf[MAX_BUF], outBuf[MAX_BUF];
    char    *start, *end, *cp;
    int     i, nbytes, col, len, gotError;

    len = 0;
    col = 0;
    gotError = 0;

    memset(outBuf, ' ', sizeof(outBuf));
    outBuf[col] = '\0';

    while (! feof(fp)) {
        inBuf[MAX_BUF - 1] = '\0';
        if (fgets(inBuf, sizeof(inBuf) - 1, fp) == 0) {
            break;
        }
        len = strlen(inBuf);
        if (inBuf[len - 1] == '\n') {
            len--;
            inBuf[len] = '\0';
        }
        start = inBuf;
        end = &inBuf[len];

        if (len == 0) {
            if (col > 0) {
                printf("  %s\n", outBuf);
                outBuf[0] = 0;
                col = 0;
            } 
            printf("\n");
        }
        while (start < end) {
            /*
             *  Skip over input spaces
             */
            while (*start && isspace(*start)) {
                start++;
            }

            if (*start == '-' && strcmp(start, "--ERROR--") == 0) {
                gotError++;
            }

            /*
             *  Find length of next word
             */
            cp = start;
            while (*cp && !isspace(*cp)) {
                cp++;
            }
            nbytes = (cp - start);

            /*
             *  Flush the line if it is blank or our buffer will exceed our
             *  max width.
             */
            if ((col + nbytes) > width) {
                printf("  %s \\\n", outBuf);
                col = 0;
                for (i = 0; i < contIndent; i++) {
                    outBuf[col++] = ' ';
                }

            } else {
                if (col > 0) {
                    outBuf[col++] = ' ';
                }
            }
            memcpy(&outBuf[col], start, nbytes);
            col += nbytes;
            outBuf[col] = '\0';
            start += nbytes;
        }
        if (col > 0) {
            printf("  %s\n", outBuf);
            outBuf[0] = 0;
            col = 0;
        } 
    }
    if (col > 0) {
        printf("  %s\n", outBuf);
    }
    return (gotError) ? -1 : 0;
}

