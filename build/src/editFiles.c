/** 
 *  editFiles.c - Edit configuration files
 * 
 *  Copyright (c) All Rights Reserved. See details at the end of the file.
 */

/********************************* Includes ***********************************/

#include    "buildConfig.h"

#if WIN && 0
#include    <stdio.h>
#include    <direct.h>
#include    <windows.h>

/*********************************** Locals ***********************************/

#define PROGRAM         BLD_NAME " Configuration Editor"
#define MPR_MAX_FNAME   1024
#define MPR_MAX_ARG     16

/***************************** Forward Declarations ***************************/

static int      initWindow();
static void     change(char *file, int argc, char *argv[]);
static char     *mprGetDirName(char *buf, int bufsize, const char *path);
static int      mprStrcpy(char *dest, int destMax, const char *src);

/*********************************** Code *************************************/

int APIENTRY WinMain(HINSTANCE inst, HINSTANCE junk, char *args, int junk2)
{
    char    dir[MPR_MAX_FNAME], moduleBuf[MPR_MAX_FNAME], *argv[MPR_MAX_ARG];
    char    *cp;
    int     errflg, nextArg, argc;

    errflg = 0;
    sleepMsecs = 0;
    removeOk = 0;

    GetModuleFileName(0, moduleBuf, sizeof(moduleBuf) - 1);
    mprGetDirName(dir, sizeof(dir), moduleBuf);
    _chdir(dir);

    if (args == 0 || *args == '\0') {
        errflg++;

    } else{
        args = strdup(args);
        for (argc = 0, cp = args; *cp; cp++) {
            if (*cp == '-') {
                ;
            } else if (isspace(*cp)) {
                *cp = '\0';
                continue;
            } else {
                if (argc >= MPR_MAX_ARG) {
                    errflg++;
                    break;
                }
                argv[argc++] = cp;
            }
        }
    }

    if (argc != 5) {
        errflg++;
    }

    /*
     *  We use removeOk to ensure that someone just running the program won't 
     *  do anything bad.
     */
    if (errflg) {
        MessageBoxEx(NULL, "Bad Usage", PROGRAM, MB_OK, 0);
        return FALSE;
    }   

    change(argv[0], atoi(argv[1], argv[2], atoi(argv[3]), argv[4]);

    return 0;
}



/*
 *  Edit "file" and search for the Nth "occurrence" of "pattern" and then change
 *  the nth "fieldNumber" to "newString"
 */
static void change(char *file, int occurrence, char *pattern, int fieldNumber, char *newString)
{
    int     i, fd;

    fd = fopen(file, ");
    for (i = 0; i < argc; i++) {
        read(fd, buf, 
    }
    close(fd);
}



/*
 *  Simple wild-card matching
 */
static int match(char *file, char *pat)
{
    char    fileBuf[MPR_MAX_FNAME], patBuf[MPR_MAX_FNAME];
    char    *patExt;
    char    *fileExt;

    mprStrcpy(fileBuf, sizeof(fileBuf), file);
    file = fileBuf;
    mprStrcpy(patBuf, sizeof(patBuf), pat);
    pat = patBuf;

    if (strcmp(file, pat) == 0) {
        return 1;
    }
    if ((fileExt = strrchr(file, '.')) != 0) {
        *fileExt++ = '\0';
    }
    if ((patExt = strrchr(pat, '.')) != 0) {
        *patExt++ = '\0';
    }
    if (*pat == '*' || strcmp(pat, file) == 0) {
        if (patExt && *patExt == '*') {
            return 1;
        } else {
            if (fileExt && strcmp(fileExt, patExt) == 0) {
                return 1;
            }
        }
    }
    return 0;
}



#endif /* WIN */

/*
 *  @copy   default
 *  
 *  Copyright (c) Embedthis Software LLC, 2003-2011. All Rights Reserved.
 *  Copyright (c) Michael O'Brien, 1993-2011. All Rights Reserved.
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
