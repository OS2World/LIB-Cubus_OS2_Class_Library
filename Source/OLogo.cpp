// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OLogo.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OLogo.cpp 1.50 1996/08/11 23:49:21 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OLogo.hpp>


OLogo::OLogo(const HMODULE module, const ULONG bitmapID, const ULONG cx, const ULONG cy)
  : OFrame(bitmapID, 0, CS_SIZEREDRAW),
    bmp(NULL),
    mod(module)
{
 sizepos.cx = cx;
 sizepos.cy = cy;
 sizepos.x = (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN)-cx)/2;
 sizepos.y = (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN)-cy)/2;
 dest.x = 0;
 dest.y = 0;
}


OLogo::OLogo(const PSZ filename, const ULONG frameID, const ULONG cx, const ULONG cy)
  : OFrame(frameID, 0, CS_SIZEREDRAW),
    bmp(NULL),
    bmpfile((PSZ)filename),
    mod(NULLHANDLE)
{
 sizepos.cx = cx;
 sizepos.cy = cy;
 sizepos.x = (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN)-cx)/2;
 sizepos.y = (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN)-cy)/2;
 dest.x = 0;
 dest.y = 0;
}


OLogo::~OLogo() 
{
 if (bmp) delete bmp;
}


PSZ OLogo::isOfType() const
{ 
 return("OLogo"); 
}


OLogo& OLogo::showLogo(const ULONG timeout)
{
 createFrame("OLogo");

 if (timeout != 0)
   {
    DosSleep(timeout);
    destroyFrame();
   }
 return(*this);
}


BOOL OLogo::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
   {
    case WM_CREATE:
      WinSetWindowPos(frame, HWND_BOTTOM, sizepos.x, sizepos.y,
                      sizepos.cx, sizepos.cy,
                      SWP_MOVE | SWP_SIZE | SWP_SHOW);
      try
       {
        if (bmpfile)
          bmp = new OBitmap(hwnd, bmpfile);
        else
          bmp = new OBitmap(hwnd, res, mod);
       }
      catch(OPMException ex)
       {
        bmp = NULL;
        ex.viewError();
        return(TRUE);
       }
      hps = WinGetPS(hwnd);
      WinDrawBitmap(hps, bmp->hbm, NULL, &dest, 0L, 0L, DBM_IMAGEATTRS);
      break;

    case WM_ERASEBACKGROUND:
      dest.x = 0;
      dest.y = 0;
      if (bmp)
        WinDrawBitmap(hps, bmp->hbm, NULL, &dest, 0L, 0L, DBM_IMAGEATTRS);
      return(TRUE);

    case WM_CLOSE:
    case WM_DESTROY:
      WinReleasePS(hps);
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
