// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OWindow.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OWindow.cpp 1.50 1996/08/11 23:49:36 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OWindow.hpp>


OWindow::OWindow(const ULONG id, const ULONG winstyle, const ULONG winbits)
   : termFlag(FALSE),
     parent(HWND_DESKTOP),
     owner(HWND_DESKTOP),
     res(id),
     style(winstyle),
     bits(winbits),
     hps(0)
{
 memset(&sizepos, 0, sizeof(SWP));
}




OWindow& OWindow::inherit(const HWND hwndDlg)
{
 if ((hwnd = WinWindowFromID(hwndDlg, res)) == NULLHANDLE)
   throw OPMException(OCL::error(138), 0);

 parent = hwndDlg;
 owner = hwndDlg;
 
 return(*this);
}


OWindow::~OWindow() 
{ 
 destroy(); 
#ifdef __IBMCPP__ 
   _heapmin();  // return all unused memory to OS/2
#endif
}


PSZ OWindow::isOfType() const
{ 
 return("OWindow"); 
} 


OWindow& OWindow::show()
{
 if (hwnd)
    WinSetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOW | SWP_RESTORE | SWP_ACTIVATE);
 return(*this);
}

OWindow& OWindow::hide()
{
 if (hwnd)
    WinSetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_HIDE | SWP_DEACTIVATE);
 return(*this);
}

OWindow& OWindow::activate()
{
 if (hwnd)
    WinSetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOW | SWP_ACTIVATE);
 return(*this);
}


OWindow& OWindow::enable()
{
 if (hwnd)
    WinEnableWindow(hwnd, TRUE);
 return(*this);
}


OWindow& OWindow::disable()
{
 if (hwnd)
    WinEnableWindow(hwnd, FALSE);
 return(*this);
}


OWindow& OWindow::destroy()
{
 if (hwnd)
    WinDestroyWindow(hwnd);
 return(*this);
}

OWindow& OWindow::setFocus()
{
 if (hwnd)
    WinSetFocus(HWND_DESKTOP, hwnd);
 return(*this);
}


OWindow& OWindow::setParent(const HWND handle)
{
 parent = handle; 
 WinSetParent(hwnd, parent, TRUE);
 return(*this);
}


OWindow& OWindow::setOwner(const HWND handle)
{
 owner = handle;
 WinSetOwner(hwnd, owner);
 return(*this);
}

OWindow& OWindow::setForeColor(COLOR color)
{
 pparms.Fore = color;
 WinSetPresParam(hwnd, PP_FOREGROUNDCOLOR, sizeof(COLOR), &pparms.Fore);
 WinUpdateWindow(hwnd);
 return(*this);
}


OWindow& OWindow::setBackColor(COLOR color)
{
 pparms.Back = color;
 WinSetPresParam(hwnd, PP_BACKGROUNDCOLOR, sizeof(COLOR), &pparms.Back);
 WinUpdateWindow(hwnd);
 return(*this);
}


OWindow& OWindow::setFont(PSZ fontnamesize)
{
 strcpy(pparms.Font, fontnamesize);
 WinSetPresParam(hwnd, PP_FONTNAMESIZE, strlen(pparms.Font)+1, pparms.Font);
 WinUpdateWindow(hwnd);
 return(*this);
}



OWindow& OWindow::setPresentation(pPresParms presentation)
{
 pparms.Fore = presentation->Fore;
 pparms.Back = presentation->Back;
 WinSetPresParam(hwnd, PP_FOREGROUNDCOLOR, sizeof(COLOR), &pparms.Fore);
 WinSetPresParam(hwnd, PP_BACKGROUNDCOLOR, sizeof(COLOR), &pparms.Back);
 setFont(presentation->Font);
 return(*this);
}


COLOR OWindow::getForeColor()
{
 ULONG ppid;

 WinQueryPresParam(hwnd, PP_FOREGROUNDCOLOR, 0, &ppid,
                   sizeof(COLOR), &pparms.Fore, 0);
 return(pparms.Fore);
}



COLOR OWindow::getBackColor()
{
 ULONG ppid;

 WinQueryPresParam(hwnd, PP_BACKGROUNDCOLOR, 0, &ppid,
                   sizeof(COLOR), &pparms.Back, 0);
 return(pparms.Back);
}


PSZ OWindow::getFont()
{
 ULONG ppid;

 WinQueryPresParam(hwnd, PP_FONTNAMESIZE, 0, &ppid, sizeof(pparms.Font), &pparms.Font, 0);
 return(pparms.Font);
}

OWindow& OWindow::getPresentation(pPresParms presentation)
{
 presentation->Fore = getForeColor();
 presentation->Back = getBackColor();
 strcpy(presentation->Font, getFont());
 return(*this);
}


OWindow& OWindow::initReplace(const ULONG id, SWP& swp)
{
 HWND _hwnd = WinWindowFromID(parent, id);
 
 if (!_hwnd)
   throw OPMException(OCL::error(137), 0);

 WinQueryWindowPos(_hwnd, &swp);
 WinDestroyWindow(_hwnd);
 
 return(*this);
}

OWindow& OWindow::cancelClose()
{
 WinSetWindowULong(hwnd, QWL_USER, (ULONG)this);
 return(*this);
}


// end of source
