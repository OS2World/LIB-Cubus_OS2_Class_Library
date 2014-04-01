// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OCL.HPP

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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OCL.hpp 1.1 1996/08/12 00:01:11 B.STEIN Release $

#ifndef OCL_HPP_INCLUDED
  #define OCL_HPP_INCLUDED

#define __OCL__
#define OCLVER      150


#define INCL_DOS
#define INCL_PM
#define INCL_WIN
#define INCL_GPI

#if ( defined (__HIGHC__))
  #pragma Off(Optimize_ptr_mem_func)
  #pragma Off(Behaved)
  #define __MULTI__
#endif

#ifndef __EMX__
 #include <os2.h>
 #include <stddef.h>
 #include <bsedos.h>
 #include <bsedev.h>
 #include <bseerr.h>
#else
 #define INCL_DOSDEVIOCTL	
 #define INCL_DOSERRORS
 #define INCL_DOSPROCESS
 #define APIENTRY16
 typedef unsigned short APIRET16;
 #define __OCL_RESOLVE_TEMPLATES__
 #define strcmpi( String1, String2) stricmp( String1, String2)
 #include <os2.h>
#endif

#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <iostream.h>
#include <fstream.h>

#include <OMessage.h>

#if ( defined (__BCPLUSPLUS__) || defined (__HIGHC__) )
  typedef const char *PCSZ;
#endif

#ifdef __BUILD_OCL_DLL__
# ifdef __IBMCPP__
#   define __CPP_EXPORT__ _Export
# endif
# if (defined (__WATCOM_CPLUSPLUS__) || defined (__BCPLUSPLUS__))
#   define __CPP_EXPORT__ __export
# endif
# ifdef __HIGHC__
#   define __CPP_EXPORT__
#   pragma On(dllexport)
# endif
#else
# define __CPP_EXPORT__
#endif

#ifdef __IBMCPP__
# define __OCL16 
#elif __WATCOM_CPLUSPLUS__
# define __OCL16 __far16
#elif __BCPLUSPLUS__
# define __OCL16
#elif __HIGHC__
# define __OCL16 _Seg16
#endif


#include <OCLObject.hpp>
#include <OString.hpp>

#ifdef OINCL_BASE
 #include <OList.hpp>
 #include <OSortedList.hpp>
#endif


#ifdef __DEBUG_ALLOC__

class __CPP_EXPORT__ MemoryChecker
{
 public:
    MemoryChecker() {}
    ~MemoryChecker() {
       _dump_allocated(-1); }
};

extern MemoryChecker memCheck;

#endif // __DEBUG_ALLOC__


class __CPP_EXPORT__ OCL
{
 protected:

    static
        OString           transport;

    OCL                   () {}

    virtual
        ~OCL              () {}

 public:

    static
        OString            MSGFILE;

    static OString
        &Version           (),
        &Version           (OString& str),
        &error             (ULONG x),
        &apierror          (ULONG x, ULONG rc);
 
    static BOOL
        saveID            (PCH Desk);

    static void
        showDialogItem    (HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount),
        hideDialogItem    (HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount),
        disableDialogItem (HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount, ULONG ulStyle),
        disableControls   (HWND hwnd, ULONG usDialogIDs[], ULONG count),
        enableControls    (HWND hwnd, ULONG usDialogIDs[], ULONG count),
        hideControls      (HWND hwnd, ULONG usDialogIDs[], ULONG count),
        showControls      (HWND hwnd, ULONG usDialogIDs[], ULONG count);

    static APIRET
        startSession      (STARTDATA *SessionData);
};


#ifndef DB_DEPRESSED
  #define DB_DEPRESSED 0x800
#endif

#ifndef DB_RAISED
  #define DB_RAISED 0x400
#endif


#if (defined (__OCL_SOURCE__) && defined (__IBMCPP__) && (__IBMCPP__ == 300))
  #pragma hdrstop
#endif


#endif // OCL_HPP_INCLUDED


// end of source  
