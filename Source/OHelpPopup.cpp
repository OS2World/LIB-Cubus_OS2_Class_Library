// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OButtonBar.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OHelpPopup.cpp 1.50 1996/08/11 23:49:17 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OHelpPopup.hpp>
#include <OMessage.hpp>

#define OBubbleRes 65001



OHelpPopup::OHelpPopup()
  : OStatusLine(OBubbleRes, HWND_DESKTOP, FALSE),
    showTime(500)
{
 style |= FCF_BORDER;
 setOrientation(DT_CENTER | DT_VCENTER);

 try
   {
    createStatusLine();
   }
 catch(OPMException ex)
   {  
    throw OPMException(OCL::error(65), 0, OException::unrecoverable);
   }
}


OHelpPopup::~OHelpPopup()
 {}


PSZ OHelpPopup::isOfType() const
{
 return("OHelpPopup");
}


ULONG OHelpPopup::showTimeout() const
{
 return(showTime);
}


OStatusLine& OHelpPopup::createStatusLine()
{
 createFrame("OHelpPopup");
 setFont("8.Helv").setBackColor(RGB_YELLOW).setForeColor(RGB_BLACK);
 return(*this);
}


OHelpPopup& OHelpPopup::setPopupTimeout(ULONG timeout)
{
 showTime = timeout;
 return(*this);
}

OHelpPopup& OHelpPopup::startPopupTimer()
{
 WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, OHELP_POPUP_SHOWTIMER, showTime);
 return(*this);
}


OHelpPopup& OHelpPopup::stopPopupTimer()
{
 WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, OHELP_POPUP_SHOWTIMER);
 return(*this);
}


OHelpPopup& OHelpPopup::timePopup(PCSZ helpText)
{
 hideFrame();

 if (helpText) {
   textToShow << (PSZ) helpText;
   startPopupTimer(); }
 else
   textToShow << (PSZ) NULL;
 return(*this);
}

OHelpPopup& OHelpPopup::showPopup(PCSZ helpText)
{
 RECTL   rect;
 POINTL  pointl;
 SWP     swp, swpSys;

 hideFrame();

 if (!helpText)
   return(*this);

 swp.cx = 200;
 swp.cy = 200;
 WinSetWindowPos(frame, NULLHANDLE, 0, 0, swp.cx, swp.cy, SWP_SIZE);

 hps = WinGetPS(client);

 rect.xLeft   = 0;
 rect.xRight  = 200;
 rect.yBottom = 0;
 rect.yTop    = 200;

 WinDrawText(hps, strlen(helpText), (PCH)helpText, &rect, 
             0L, 0L, DT_LEFT | DT_BOTTOM | DT_QUERYEXTENT);
 swp.cx = rect.xRight - rect.xLeft + 8;
 WinSetWindowPos(frame, NULLHANDLE, 0, 0, swp.cx, getHeight(), SWP_SIZE);
 WinReleasePS(hps);

 setText(helpText);
 
 WinQueryPointerPos(HWND_DESKTOP, &pointl);

 swpSys.cx=WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
 swpSys.cy=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
 swp.x = ((pointl.x + getWidth())  < swpSys.cx) ?
         pointl.x + 3 : pointl.x - getWidth() - 3;
 swp.y = ((pointl.y + getHeight()) < swpSys.cy) ?
         pointl.y + 3 : pointl.y - getHeight() - 3;
 WinSetWindowPos(frame, HWND_TOP, swp.x, swp.y, swp.cx, swp.cy,
                 SWP_MOVE | SWP_SHOW | SWP_ZORDER);
 return(*this);
}


OHelpPopup& OHelpPopup::hidePopup()
{
 stopPopupTimer().hideFrame();
 return(*this);
}

BOOL OHelpPopup::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_TIMER:
    {
     switch(SHORT1FROMMP(mp1))
      {
       case OHELP_POPUP_SHOWTIMER:
        stopPopupTimer();
        showPopup(textToShow);          
        break;
      }
    }

   case WM_DESTROY:
     break;
   case WM_CLOSE:
     destroyFrame();
     break;

   default:
     return(OStatusLine::OCommand(msg, mp1, mp2));
  } 
 return(TRUE);
}


// end of source  
