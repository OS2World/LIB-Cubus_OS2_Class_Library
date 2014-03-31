// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OStatusLine.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OStatusLine.cpp 1.50 1996/08/11 23:49:31 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OStatusLine.hpp>

OStatusLine::OStatusLine(const ULONG id,
                         const HWND parentWindow,
                         const BOOL DDStyle)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW),
    ddStyle(DDStyle)
{
 setParent(parentWindow);
 setOwner(parentWindow);
 initStatlineDefaults();
}


OStatusLine::OStatusLine(const ULONG id,
                         const OFrame& parentWindow,
                         const BOOL DDStyle)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW),
    ddStyle(DDStyle)
{
 setParent(parentWindow.hwnd);
 setOwner(parentWindow.hwnd);
 initStatlineDefaults();
}


OStatusLine::OStatusLine(const ULONG id,
                         const pOFrame parentWindow,
                         const BOOL DDStyle)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW),
    ddStyle(DDStyle)
{
 initStatlineDefaults().setParent(parentWindow->hwnd).setOwner(parentWindow->hwnd);
}


OStatusLine::~OStatusLine()
  {}


PSZ OStatusLine::isOfType() const
{
 return("OStatusLine");
}


OStatusLine& OStatusLine::initStatlineDefaults()
{
 orientation = DT_LEFT | DT_VCENTER;
 readOnly = FALSE;
 statlineText << (PSZ) "";
 pparms.Fore = SYSCLR_WINDOWTEXT;
 if (ddStyle)
   pparms.Back = SYSCLR_BUTTONMIDDLE;
 else
   pparms.Back = SYSCLR_WINDOW;
 return(*this);
}


OStatusLine& OStatusLine::createStatusLine()
{
 createFrame("OStatusLine");
 setFont("8.Helv");
 showFrame();
 return(*this);
}


OStatusLine& OStatusLine::refreshText()
{
 WinInvalidateRect(hwnd, 0, TRUE);
 return(*this);
}


OStatusLine& OStatusLine::setText(PCSZ text)
{
 if ((text) && (!readOnly)) {
   statlineText << (PSZ) " ";
   statlineText + (PSZ) text;
   statlineText + (PSZ) " ";
   refreshText(); }
 return(*this);
}


ULONG OStatusLine::getHeight()
{
 ULONG statlineHeight;

 hps = WinGetPS(client);
 WinQueryWindowRect(HWND_DESKTOP, &rcl);
 WinDrawText(hps, 1, " ", &rcl, 0L, 0L, orientation | DT_QUERYEXTENT);
 WinFillRect(hps, &rcl, pparms.Back);
 WinReleasePS(hps);
 statlineHeight = rcl.yTop - rcl.yBottom + 10;
 return(statlineHeight);
}

ULONG OStatusLine::getWidth()
{
 ULONG statlineWidth;

 hps = WinGetPS(client);
 WinQueryWindowRect(HWND_DESKTOP, &rcl);
 WinDrawText(hps, strlen(statlineText), statlineText,
             &rcl, 0L, 0L, orientation | DT_QUERYEXTENT);
 WinFillRect(hps, &rcl, pparms.Back);
 WinReleasePS(hps);

 statlineWidth = rcl.xRight - rcl.xLeft + 10;
 return(statlineWidth);
}


OStatusLine& OStatusLine::setOrientation(const ULONG Orientation)
{
 orientation = Orientation;
 return(*this);
}


OStatusLine& OStatusLine::setRDOnly(BOOL readonly)
{
 readOnly = readonly;
 return(*this);
}


BOOL OStatusLine::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
   {
    case WM_PAINT:
     if (ddStyle)
      {
       ULONG   height = getHeight() - 3;
       ULONG   width  = 0;
       ULONG   offset = 3;
       POINTL  ptl;

       hps = WinBeginPaint(hwnd, 0, NULL);
       WinQueryWindowRect(hwnd, &rcl);
       width =  rcl.xRight - rcl.xLeft;
   
       GpiCreateLogColorTable(hps, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL);
       GpiSetColor(hps, pparms.Back);
       ptl.x = width; ptl.y = height;
       GpiBox(hps, DRO_FILL, &ptl, 0, 0);
       GpiSetColor(hps, CLR_WHITE);
       ptl.x = ptl.y = 0;
       GpiMove(hps, &ptl);
       ptl.x = 0; ptl.y = height;
       GpiLine(hps, &ptl);
       ptl.x = width; ptl.y = height;
       GpiLine(hps, &ptl);
       GpiSetColor(hps, CLR_DARKGRAY);
       ptl.x = width; ptl.y = 0;
       GpiLine(hps, &ptl);
       ptl.x = ptl.y = 0;
       GpiLine(hps, &ptl);
       GpiSetColor(hps, CLR_WHITE);
       ptl.x = ptl.y = offset;
       GpiMove(hps, &ptl);
       ptl.x = width - offset; ptl.y = offset;
       GpiLine(hps, &ptl);
       ptl.x = width - offset; ptl.y = height - offset;
       GpiLine(hps, &ptl);
       GpiSetColor(hps, CLR_DARKGRAY);
       ptl.x = offset; ptl.y = height - offset;
       GpiLine(hps, &ptl);
       ptl.x = ptl.y = offset;
       GpiLine(hps, &ptl);
       rcl.xLeft = 3;
       WinDrawText(hps, strlen(statlineText), statlineText, &rcl,
                   pparms.Fore, pparms.Back, orientation);
       WinEndPaint(hps);
      }
     else
      {
       hps = WinBeginPaint(hwnd, 0, 0);
       GpiCreateLogColorTable(hps, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL);
       WinQueryWindowRect(hwnd, &rcl);
       GpiSetColor(hps, pparms.Back);
       GpiBox(hps, DRO_FILL, (PPOINTL) &rcl.xRight, 0L, 0L);
       WinDrawText(hps, strlen(statlineText), statlineText, &rcl,
                   pparms.Fore, pparms.Back, orientation | DT_ERASERECT);
       WinEndPaint(hps);
      } 
     break;

    default:
      return(OFrame::OCommand(msg, mp1, mp1));
   }
 return(TRUE);

#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif

// end of source
