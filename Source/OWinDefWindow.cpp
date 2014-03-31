// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OWinDefWindow.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OWinDefWindow.cpp 1.50 1996/08/11 23:49:36 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OApp.hpp>
#include <OCommand.hpp>


// standard window procedure

MRESULT __CPP_EXPORT__ EXPENTRY OWinDefWindowProc(HWND   hwnd,
                                                  ULONG  msg,
                                                  MPARAM mp1,
                                                  MPARAM mp2)
{
 switch(msg)
  {
   case WM_CREATE:
     if (!mp1) return(MRESULT(TRUE));
     WinSetWindowULong(hwnd, QWL_USER, (ULONG)mp1);
     if (!OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));
     break;

   case DM_DRAGOVER:
     if (OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(MPFROM2SHORT(DOR_DROP, DO_UNKNOWN));
     else
       return(MPFROM2SHORT(DOR_NODROP, DO_UNKNOWN));

   case WM_CONTROL:
     if(SHORT2FROMMP(mp1) == CN_DRAGOVER)
      {
       if (OApp::OCMDTrace(hwnd, msg, mp1, mp2))
         return(MPFROM2SHORT(DOR_DROP, DO_UNKNOWN));
       else
         return(MPFROM2SHORT(DOR_NODROP, DO_UNKNOWN));
      }
     else if (!OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));
     break;

   case WM_HITTEST:
     if (!OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));
     else
       return(MPFROMSHORT(HT_NORMAL));

   case WM_ERASEBACKGROUND:
     if (!OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(MRESULT(TRUE));
     else
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));

   case WM_DRAWITEM:
     return(MRESULT(OApp::OCMDTrace(hwnd, msg, mp1, mp2)));

   case WM_CLOSE:
   case WM_DESTROY: {
     BOOL dispatched = OApp::OCMDTrace(hwnd, msg, mp1, mp2);
     WinSetWindowULong(hwnd, QWL_USER, (ULONG)OApp::currentOApp->NullHandler());
     if (!dispatched)
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));
     break; }

   default:
     if (!OApp::OCMDTrace(hwnd, msg, mp1, mp2))
       return(WinDefWindowProc(hwnd, msg, mp1, mp2));
     break;
  }
 return(MRESULT(FALSE));
}

// end of source
