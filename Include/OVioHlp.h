/*
 OCL - OS/2 Class Library
 (c) Cubus 1995
 All Rights Reserved
 OVioHlp.h
*/

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


/* $Header: W:/Projects/OCL/Include/rcs/OVioHlp.h 1.50 1996/08/11 23:47:35 B.STEIN Release $ */

#ifndef OVIOHLP_INCLUDED
  #define OVIOHLP_INCLUDED

#define UP                   1
#define LEFT                 2
#define DOWN                 3
#define RIGHT                4
#define GOBBLE               5
#define ZIG_UP               6
#define BOX                  7
#define ZIG_DOWN             8

#define WM_BLACK             0x00
#define WM_BLUE              0x01
#define WM_GREEN             0x02
#define WM_CYAN              0x03
#define WM_RED               0x04
#define WM_MAGENTA           0x05
#define WM_BROWN             0x06
#define WM_PALEGREY          0x07
#define WM_DKGREY            0x08
#define WM_LBLUE             0x09
#define WM_LGREEN            0x0A
#define WM_LCYAN             0x0B
#define WM_LRED              0x0C
#define WM_LMAGENTA          0x0D
#define WM_YELLOW            0x0E
#define WM_WHITE             0x0F
#define WM_MAX_COLOR         0X0F

#define MKATRB(a,b )     ((BYTE) (a << 4 ) + b )


/* ANSI */

#define ESC "\x01B"

#define ANSI_NORMAL            "\x01B[0m"
#define ANSI_HIGHINTENS        "\x01B[1m"
#define ANSI_NORMINTENS        "\x01B[2m"
#define ANSI_UNDERLINE         "\x01B[4m"
#define ANSI_BLINKING          "\x01B[5m"
#define ANSI_REVERSE           "\x01B[7m"
#define ANSI_INVISIBLE         "\x01B[8m"


/* Foreground */

#define ANSI_FORE_BLACK        "\x01B[30m"
#define ANSI_FORE_RED          "\x01B[31m"
#define ANSI_FORE_GREEN        "\x01B[32m"
#define ANSI_FORE_YELLOW       "\x01B[33m"
#define ANSI_FORE_BLUE         "\x01B[34m"
#define ANSI_FORE_MAGENTA      "\x01B[35m"
#define ANSI_FORE_CYAN         "\x01B[36m"
#define ANSI_FORE_WHITE        "\x01B[37m"

/* highintens */

#define ANSI_FORE_LRED        "\x01B[1m\x01B[31m"
#define ANSI_FORE_LGREEN      "\x01B[1m\x01B[32m"
#define ANSI_FORE_LYELLOW     "\x01B[1m\x01B[33m"
#define ANSI_FORE_LBLUE       "\x01B[1m\x01B[34m"
#define ANSI_FORE_LMAGENTA    "\x01B[1m\x01B[35m"
#define ANSI_FORE_LCYAN       "\x01B[1m\x01B[36m"
#define ANSI_FORE_LWHITE      "\x01B[1m\x01B[37m"

/* Background */

#define ANSI_BACK_BLACK        "\x01B[40m"
#define ANSI_BACK_RED          "\x01B[41m"
#define ANSI_BACK_GREEN        "\x01B[42m"
#define ANSI_BACK_YELLOW       "\x01B[43m"
#define ANSI_BACK_BLUE         "\x01B[44m"
#define ANSI_BACK_MAGENTA      "\x01B[45m"
#define ANSI_BACK_CYAN         "\x01B[46m"
#define ANSI_BACK_WHITE        "\x01B[47m"

/* highintens */

#define ANSI_BACK_LRED        "\x01B[1m\x01B[41m"
#define ANSI_BACK_LGREEN      "\x01B[1m\x01B[42m"
#define ANSI_BACK_LYELLOW     "\x01B[1m\x01B[43m"
#define ANSI_BACK_LBLUE       "\x01B[1m\x01B[44m"
#define ANSI_BACK_LMAGENTA    "\x01B[1m\x01B[45m"
#define ANSI_BACK_LCYAN       "\x01B[1m\x01B[46m"
#define ANSI_BACK_LWHITE      "\x01B[1m\x01B[47m"


/* end of source */

#endif /* OVIOHLP_INCLUDED */
