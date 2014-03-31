// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFrame.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/OFrame.cpp 1.50 1996/08/11 23:49:16 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OFrame.hpp>
#include <OPMException.hpp>

OFrame::OFrame(const ULONG id,
               const ULONG Style,
               const ULONG winbits)
 : OWindow(id, Style, winbits),
   frame(NULLHANDLE),
   client(NULLHANDLE)
 {}


OFrame::~OFrame()
{ 
 if (frame)
   WinDestroyWindow(frame); 
}


PSZ OFrame::isOfType() const
{ 
 return("OFrame"); 
}


OFrame& OFrame::createFrame(PSZ className)
{
 FRAMECDATA fcdata;

 fcdata.cb            = sizeof(FRAMECDATA);
 fcdata.flCreateFlags = style;
 fcdata.hmodResources = (HMODULE)NULL;
 fcdata.idResources   = res;

 if (!WinRegisterClass(OApp::current().anchor(), 
                       className, 
                       OWinDefWindowProc,
                       bits,
                       sizeof(PVOID)))
   throw OPMException(OCL::error(132), 0);


 if ((frame = WinCreateWindow(parent, WC_FRAME,  "",
                              0, 0, 0, 0, 0,
                              owner, HWND_TOP, res, &fcdata, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(133), 0);

 if ((client = WinCreateWindow(frame, className, "", 0, 0, 0, 0, 0, frame,
                               HWND_TOP, FID_CLIENT, this, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(134), 0);

 if (!winText)
   winText << className;

 WinSetWindowText(frame, winText);

 return(*this);
}


OFrame& OFrame::centerFrame()
{
 SWP swpScreen;

 swpScreen.cx=WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
 swpScreen.cy=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

 WinSetWindowPos(frame, NULLHANDLE, (swpScreen.cx-sizepos.cx)/2,
                        (swpScreen.cy-sizepos.cy)/2, sizepos.cx, sizepos.cy,
                        SWP_SIZE | SWP_MOVE | SWP_RESTORE | SWP_ACTIVATE);
 return(*this);
}


OFrame& OFrame::setSizePosFrame(const HWND behind, SWP dimensions, const ULONG flag)
{
 if (frame) {
   WinSetWindowPos(frame, behind, dimensions.x, dimensions.y, dimensions.cx, dimensions.cy, flag);
   WinQueryWindowPos(frame, &sizepos); }

 return(*this);
}


OFrame& OFrame::trackFrame()
{
 TRACKINFO         TrackInfo;

 WinQueryWindowPos(frame, &sizepos);
 memset (&TrackInfo, 0, sizeof(TrackInfo));  // init the trackinfo struct

 TrackInfo.cxBorder = 1;
 TrackInfo.cyBorder = 1;
 TrackInfo.cxGrid = 1;
 TrackInfo.cyGrid = 1;
 TrackInfo.cxKeyboard = 8;
 TrackInfo.cyKeyboard = 8;
 TrackInfo.rclTrack.xLeft   = sizepos.x;
 TrackInfo.rclTrack.xRight  = sizepos.x + sizepos.cx;
 TrackInfo.rclTrack.yBottom = sizepos.y;
 TrackInfo.rclTrack.yTop = sizepos.y + sizepos.cy;
 WinQueryWindowPos(HWND_DESKTOP, &sizepos);
 TrackInfo.rclBoundary.xLeft   = sizepos.x;
 TrackInfo.rclBoundary.xRight  = sizepos.x + sizepos.cx;
 TrackInfo.rclBoundary.yBottom = sizepos.y;
 TrackInfo.rclBoundary.yTop = sizepos.y + sizepos.cy;
 TrackInfo.ptlMinTrackSize.x = 0;
 TrackInfo.ptlMinTrackSize.y = 0;
 TrackInfo.ptlMaxTrackSize.x = sizepos.cx;
 TrackInfo.ptlMaxTrackSize.y = sizepos.cy;
 TrackInfo.fs = TF_MOVE | TF_STANDARD | TF_ALLINBOUNDARY;

 if (WinTrackRect(HWND_DESKTOP, 0, &TrackInfo))   // now we move ourselves
    WinSetWindowPos(frame, 0, (SHORT) TrackInfo.rclTrack.xLeft,
                              (SHORT) TrackInfo.rclTrack.yBottom, 0, 0, SWP_MOVE);
 WinSetWindowPos(frame, 0, 0, 0, 0, 0, SWP_SHOW | SWP_ACTIVATE);

 return(*this);
}


OFrame& OFrame::showFrame() 
{
 if (frame)
    WinShowWindow(frame, TRUE);

 return(*this);
}


OFrame& OFrame::hideFrame() 
{
 if (frame)
   WinShowWindow(frame, FALSE);

 return(*this);
}


OFrame& OFrame::destroyFrame() 
{
 if (frame) {
    termFlag = TRUE;
    WinDestroyWindow(frame); }

 return(*this);
}

OFrame& OFrame::postQuit()
{
 if (frame) {
    termFlag = TRUE;
    WinPostMsg(frame, WM_QUIT, NULL, NULL); }

 return(*this);
}


OFrame& OFrame::setWindowText(PCSZ text) 
{
  if (text) {
     winText << (PSZ) text;
     WinSetWindowText(frame, winText); }

 return(*this);
}



BOOL OFrame::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
   {
    case WM_PRESPARAMCHANGED:
      switch(LONGFROMMP(mp1))
       {
        case PP_FONTNAMESIZE:
          getFont();
          WinInvalidateRect(hwnd, 0, TRUE);
          WinQueryWindowPos(parent, &sizepos);
          WinSendMsg(parent, WM_SIZE, NULL, MPFROM2SHORT(sizepos.cx, sizepos.cy));
          break;

        case PP_FOREGROUNDCOLOR:
          getForeColor();
          WinInvalidateRect(hwnd, 0, TRUE);
          break;

        case PP_BACKGROUNDCOLOR:
          getBackColor();
          WinInvalidateRect(hwnd, 0, TRUE);
          break;
       }
      break;

    default:
      return(FALSE);
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
