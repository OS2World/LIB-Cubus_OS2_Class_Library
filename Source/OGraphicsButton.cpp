// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OGraphicsButton.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/OGraphicsButton.cpp 1.50 1996/08/11 23:49:16 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OGraphicsButton.hpp>
#include <OMessage.hpp>

OGraphicsButton::OGraphicsButton (ULONG    id,
                                  HWND     Parent,
                                  pOIcon   ico,  
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pIco(ico),
    imageType(OGraphicsButton::useIcon),
    isEnabled(TRUE) 
  {}

OGraphicsButton::OGraphicsButton (ULONG    id,
                                  HWND     Parent,
                                  pOBitmap bmp,    
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pBmp(bmp),
    imageType(OGraphicsButton::useBitmap),
    isEnabled(TRUE) 
  {}

OGraphicsButton::OGraphicsButton (ULONG    id,
                                  OFrame&  Parent,
                                  pOIcon   ico,    
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pIco(ico),
    imageType(OGraphicsButton::useIcon),
    isEnabled(TRUE) 
  {}

OGraphicsButton::OGraphicsButton (ULONG    id,
                                  OFrame&  Parent,
                                  pOBitmap bmp,    
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pBmp(bmp),
    imageType(OGraphicsButton::useBitmap), 
    isEnabled(TRUE) 
  {}


OGraphicsButton::OGraphicsButton (ULONG    id,
                                  pOFrame  Parent,
                                  pOIcon   ico,    
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pIco(ico),
    imageType(OGraphicsButton::useIcon),
    isEnabled(TRUE) 
  {}

OGraphicsButton::OGraphicsButton (ULONG    id,
                                  pOFrame  Parent,
                                  pOBitmap bmp,    
                                  PSZ      help,  
                                  ULONG    x,
                                  ULONG    y,
                                  ULONG    cx,
                                  ULONG    cy)
  : OUserButton(id, Parent, x, y, cx, cy),
    helpText(help),
    pBmp(bmp),
    imageType(OGraphicsButton::useBitmap),
    isEnabled(TRUE) 
  {}


OGraphicsButton::~OGraphicsButton()
  {}


PSZ OGraphicsButton::isOfType() const
{
 return("OGraphicsButton");
}


MRESULT OGraphicsButton::UBDefaultCall(ULONG  msg,  
                                       MPARAM mp1,
                                       MPARAM mp2)
{
 return((MRESULT)PM_ButtonProc(hwnd, msg, mp1, mp2));
}


OButton& OGraphicsButton::createButton()
{
 CLASSINFO clsi ;
   
 WinQueryClassInfo(OApp::current().anchor(),
                   WC_BUTTON, &clsi);

 PM_ButtonProc = clsi.pfnWindowProc;

 if (!WinRegisterClass(OApp::current().anchor(),
                       "OGraphicsButton",
                       (PFNWP) OGraphicsButtonProc,
                       0,
                       clsi.cbWindowData + sizeof (PVOID)))
   throw OPMException(OCL::error(60), 0, OException::fatal);

 hwnd = WinCreateWindow(parent, "OGraphicsButton",
                        "", BS_PUSHBUTTON | BS_USERBUTTON | BS_NOPOINTERFOCUS | WS_VISIBLE,
                        sizepos.x, sizepos.y, sizepos.cx, sizepos.cy,
                        owner, HWND_TOP, res, this, NULL);

 if (!hwnd)
   throw OPMException(OCL::error(61), 0, OException::fatal);
 
 return(*this);
}


OGraphicsButton& OGraphicsButton::drawButton(HPS hPS)
{
 POINTL ptl;

 WinQueryWindowRect(hwnd, &rcl);
 GpiCreateLogColorTable(hPS, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL);
 WinFillRect(hPS, &rcl, SYSCLR_BUTTONMIDDLE);
 if (pushState)
   WinDrawBorder(hPS, &rcl, 2, 2, 0, 0, DB_PATCOPY | DB_DEPRESSED);
 else
   WinDrawBorder(hPS, &rcl, 2, 2, 0, 0, DB_PATCOPY | DB_RAISED);

 WinQueryWindowRect(hwnd, &rcl);
 if (imageType == OGraphicsButton::useIcon)
  {
   ptl.x = (rcl.xRight - rcl.xLeft - pIco->width  + pushState * 3)  / 2;
   ptl.y = (rcl.yTop - rcl.yBottom - pIco->height - pushState * 3) / 2;
   WinDrawPointer(hPS, ptl.x, ptl.y, pIco->hptr, isEnabled ? DP_NORMAL : DP_HALFTONED);
  }
 else
  {
   ptl.x = (rcl.xRight - rcl.xLeft - pBmp->width  + pushState * 3)  / 2;
   ptl.y = (rcl.yTop - rcl.yBottom - pBmp->height - pushState * 3) / 2;
   WinDrawBitmap(hPS, pBmp->hbm, NULL, &ptl, 0, 0, isEnabled ? DBM_NORMAL : DBM_HALFTONE);
  }
 return(*this);
}


BOOL OGraphicsButton::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_CREATE:
     pushState = FALSE;
     break;
 
   case BM_SETHILITE:
     WinSendMsg(parent, WM_CONTROL,
                MPFROM2SHORT(OGRBTN_SETHILITE, res), NULL);
     pushState = ((BOOL)SHORT1FROMMP(mp1));
     hps = WinGetPS(hwnd);
     drawButton(hps);
     WinReleasePS(hps);
     return(FALSE);

   case WM_PRESPARAMCHANGED:
     getFont(); 
     WinSendMsg(parent, WM_CONTROL, MPFROM2SHORT(msg, res), MPFROMP(this));
     break;

   case WM_WINDOWENTER:
     WinSendMsg(parent, WM_CONTROL,
                MPFROM2SHORT(OGRBTN_WINDOWENTER, res),
                MPFROMP(helpText.getText()));
     break;

   case WM_WINDOWLEAVE:
     WinSendMsg(parent, WM_CONTROL,
                MPFROM2SHORT(OGRBTN_WINDOWLEAVE, res),
                MPFROMP((PSZ)""));
     break;

   case WM_ENABLE:
     isEnabled = (BOOL)SHORT1FROMMP(mp1);
     return(FALSE);
 
   case WM_PAINT:
     hps = WinBeginPaint(hwnd, 0, NULL);
     drawButton(hps);
     WinEndPaint(hps);
     break;

   default:
     return(FALSE);
  }
 return(TRUE); 
}



// The following function is strictly for internal use only!


MRESULT EXPENTRY OGraphicsButtonProc(HWND hwnd,
                                     ULONG msg,
                                     MPARAM mp1,
                                     MPARAM mp2)
{
 pOGraphicsButton ub_current = (pOGraphicsButton) WinQueryWindowPtr(hwnd, QWL_USER);

 if (ub_current)
   ub_current->hwnd = hwnd;

 switch(msg)
  {
   case WM_CREATE:
     if (!mp1)
       return(MRESULT(TRUE));
     ub_current = (pOGraphicsButton) mp1;
     WinSetWindowPtr(hwnd, QWL_USER, ub_current);
     ub_current->hwnd = hwnd;
     ub_current->UBDefaultCall(msg, mp1, mp2);
     ub_current->OCommand(msg, mp1, mp2);
     break ;

   case WM_DESTROY:
     WinSetWindowPtr(hwnd, QWL_USER, NULL);
     if(ub_current) {
       ub_current->OCommand(msg, mp1, mp2); 
       return(ub_current->UBDefaultCall(msg, mp1, mp2)); }
     break;

   default:
     if ((ub_current) &&
        (!ub_current->OCommand(msg, mp1, mp2)))
       return(ub_current->UBDefaultCall(msg, mp1, mp2));
     break;
  }
 return((MRESULT)FALSE);
}


// end of source
