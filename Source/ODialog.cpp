// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ODialog.cpp

// member functions of ODialog

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


// $Header: W:/Projects/OCL/Source/rcs/ODialog.cpp 1.50 1996/08/11 23:49:13 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ODialog.hpp>


ODialog::ODialog(const ULONG idDlg)
  : OWindow(idDlg, 0, 0),
    module(NULLHANDLE)
{
 parent = HWND_DESKTOP;
 owner = HWND_DESKTOP;
}


ODialog::ODialog(const HWND Parent, const HWND Owner, const ULONG idDlg)
  : OWindow(idDlg, 0, 0),
    module(NULLHANDLE)
{
 parent = Parent;
 owner = Owner;
}


ODialog::ODialog(const HWND Parent, const HWND Owner, const HMODULE resource, const ULONG idDlg)
  : OWindow(idDlg, 0, 0),
    module(resource)
{
 parent = Parent;
 owner = Owner;
}


ODialog::~ODialog()
{
 destroyDlg();
}


PSZ ODialog::isOfType() const
{ 
 return("ODialog"); 
}


ODialog& ODialog::createDlg()
{
 if (!WinLoadDlg(parent, owner, OWinDefDlgProc, module, res, this))
   throw OPMException(OCL::error(160), 0);
 return(*this);
}



ODialog& ODialog::showDlg()
{
 WinSetWindowPos(hwnd, 0, 0, 0, 0, HWND_TOP, SWP_ACTIVATE | SWP_SHOW);
 return(*this);
}


BOOL ODialog::showDlgModal()
{
 return((BOOL)WinDlgBox(parent, owner, OWinDefDlgProc, module, res, this));
}


ODialog& ODialog::dismissDlg(BOOL success)
{
 WinDismissDlg(hwnd, success);
 return(*this);
}

ODialog& ODialog::hideDlg()
{
 WinShowWindow(hwnd, FALSE);
 return(*this);
}


ODialog& ODialog::destroyDlg()
{
 WinDestroyWindow(hwnd);
 return(*this);
}


ODialog& ODialog::centerDlg(const ULONG parentWindow)
{
 SWP swpParent;
 SWP swp;

 switch(parentWindow)
   {
    case CENTER_ONSCREEN:
      swpParent.cx=WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
      swpParent.cy=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
      WinQueryWindowPos(hwnd, &swp);
      WinSetWindowPos(hwnd, HWND_TOP,
                     (swpParent.cx-swp.cx)/2,
                     (swpParent.cy-swp.cy)/2, 0, 0, SWP_MOVE);
      break;

    case CENTER_ONPARENT: {
      LONG ScreenWidth, ScreenHeight;
      LONG PosX, PosY;

      /* Bildschirmabmessungen holen */
      ScreenWidth  = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
      ScreenHeight = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
      /* Fensterabmessungen holen */
      WinQueryWindowPos(parent, &swpParent);
      WinQueryWindowPos(hwnd, &swp);

      PosX = (swpParent.cx - swp.cx) / 2;
      PosY = (swpParent.cy - swp.cy) / 2;

      /* Korrektur, falls Teile des Fensters aus dem sichtbaren Bereich
       * des Fensters herausfallen wÅrden: */
      if (PosX < 0)
         PosX = 0;
      else if (PosX + swp.cx > ScreenWidth)
         PosX = ScreenWidth - swp.cx;

      if (PosY < 0)
         PosY = 0;
      else if (PosY + swp.cy > ScreenHeight)
         PosY = ScreenHeight - swp.cy;

      WinSetWindowPos(hwnd, HWND_TOP, PosX, PosY, 0, 0, SWP_MOVE);
      break; }
   }
 return(*this);
}

// end of source
