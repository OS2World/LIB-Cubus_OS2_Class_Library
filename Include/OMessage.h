// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMessage.hpp


/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Neither the name Cubus nor the name Team OCL may be used to
 *    endorse or promote products derived from this software
 *    without specific prior written permission.
 * 3. See OCL.INF for a detailed copyright notice.
 *
 *              THIS SOFTWARE IS PROVIDED ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


// $Header: W:/Projects/OCL/Include/rcs/OMessage.h 1.50 1996/08/11 23:47:22 B.STEIN Release $

#ifndef OMESSAGE_H_INCLUDED
  #define OMESSAGE_H_INCLUDED

// OCL

#define             OCL_VER_MSG                   1         // %MSG%, Compiler, Copyright 
#define             OCL_BORLAND                   2
#define             OCL_WATCOM                    3
#define             OCL_VA                        4
#define             OCL_CSET                      5
#define             OCL_METAWARE                  6
#define             OCL_EMX                       7
#define             OCL_COPYRIGHT                 8
#define             OCL_UNKNOWN_EXCEPTION         9
#define             OCL_ERROR_PAGESELECT          10
#define             OCL_INVALID_PAGE              11
#define             OCL_ERROR_APPLICATION         12

#define             OCL_LARGE_TILE                20
#define             OCL_LEAST_SIZE                21
#define             OCL_ERROR_ALLOC               22        // %MSG%, %APIMSG%

#define             OCL_ERROR_LOADBMP             30
#define             OCL_NULLHANDLE_BMP            31
#define             OCL_BMP_FROM_FILE             32

#define             OCL_VIEW_STR                  38

#define             OCL_OCRIT_ENTER               40
#define             OCL_OCRIT_EXIT                41

#define             OCL_ODRG_REG                  45
#define             OCL_ODRG_CREAT                46
#define             OCL_CTRL_NOT_EXISTS           47

#define             OCL_FN_BY_ORD                 50
#define             OCL_FN_BY_NAME                51
#define             OCL_FNTYPE_BY_ORD             52
#define             OCL_FNTYPE_BY_NAME            53
#define             OCL_MOD_NAME                  54
#define             OCL_APP_TYPE                  55
#define             OCL_GET_RES                   56
#define             OCL_RES_SIZE                  57

#define             OCL_OGRBTN_REG                60
#define             OCL_OGRBTN_CREAT              61

#define             OCL_OHLPPOP_CREAT             65



#define             OCL_ODATE_MON                 225
#define             OCL_ODATE_TUE                 226
#define             OCL_ODATE_WED                 227
#define             OCL_ODATE_THU                 228
#define             OCL_ODATE_FRI                 229
#define             OCL_ODATE_SAT                 230
#define             OCL_ODATE_SUN                 231
#define             OCL_ODATE_JAN                 232
#define             OCL_ODATE_FEB                 233
#define             OCL_ODATE_MAR                 234
#define             OCL_ODATE_APR                 235
#define             OCL_ODATE_MAY                 236
#define             OCL_ODATE_JUN                 237
#define             OCL_ODATE_JUL                 238
#define             OCL_ODATE_AUG                 239
#define             OCL_ODATE_SEP                 240
#define             OCL_ODATE_OCT                 241
#define             OCL_ODATE_NOV                 242
#define             OCL_ODATE_DEC                 243


// OIP

#define             OIP_VER_MSG                   1         // %MSG%, Compiler, Copyright 
#define             OIP_BORLAND                   2
#define             OIP_WATCOM                    3
#define             OIP_VA                        4
#define             OIP_CSET                      5
#define             OIP_METAWARE                  6
#define             OIP_EMX                       7
#define             OIP_COPYRIGHT                 8
#define             OIP_UNKNOWN_EXCEPTION         9

# endif // OMESSAGE_H_INCLUDED

// end of source
