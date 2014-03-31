// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OButton.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/OButton.cpp 1.50 1996/08/11 23:49:09 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OButton.hpp>


OButton::OButton(ULONG   id,
                 HWND    Parent,
                 ULONG   Style,
                 ULONG   x,
                 ULONG   y,
                 ULONG   cx,
                 ULONG   cy)
 : OWindow(id, Style, 0)
{
 sizepos.x  = x;
 sizepos.y  = y;
 sizepos.cx = cx;
 sizepos.cy = cy;
}


OButton::OButton(ULONG   id,
                 OFrame& Parent,
                 ULONG   Style,
                 ULONG   x,
                 ULONG   y,
                 ULONG   cx,
                 ULONG   cy)
 : OWindow(id, Style, 0)
{
 parent     = Parent.client;
 owner      = Parent.client; 
 sizepos.x  = x;
 sizepos.y  = y;
 sizepos.cx = cx;
 sizepos.cy = cy;
}


OButton::OButton(ULONG   id,
                 pOFrame Parent,
                 ULONG   Style,
                 ULONG   x,
                 ULONG   y,
                 ULONG   cx,
                 ULONG   cy)
 : OWindow(id, Style, 0)
{
 parent     = Parent->client;
 owner      = Parent->client; 
 sizepos.x  = x;
 sizepos.y  = y;
 sizepos.cx = cx;
 sizepos.cy = cy;
}



OButton& OButton::createButton()
{
 if ((hwnd = WinCreateWindow(parent, WC_BUTTON,
             "", style | WS_VISIBLE,
             sizepos.x, sizepos.y,
             sizepos.cx, sizepos.cy,
             owner, HWND_TOP, res, NULL, NULL))
             == NULLHANDLE)
   throw OPMException(OCL::error(150), 0);
 return(*this);
}   



OButton::~OButton()
  {}


PSZ OButton::isOfType() const
{
 return("OButton");
}


ULONG OButton::queryState()
{
 return((ULONG)WinSendMsg(hwnd, BM_QUERYCHECK, NULL, NULL));
}
  
BOOL OButton::isChecked()
{
 return(queryState() == 1);
}


BOOL OButton::isHilited()
{
 return((BOOL)WinSendMsg(hwnd, BM_QUERYHILITE, NULL, NULL));
}


OButton& OButton::check()
{
 return(setState(TRUE));
}

OButton& OButton::uncheck()
{
 return(setState(FALSE));
}

OButton& OButton::setState(ULONG state)
{
 WinSendMsg(hwnd, BM_SETCHECK, MPFROMSHORT(state), NULL);
 return(*this);
}

OButton& OButton::setDefault(BOOL displayDefault)
{
 WinSendMsg(hwnd, BM_SETDEFAULT, MPFROMSHORT(displayDefault), NULL);
 return(*this);
}

OButton& OButton::setHilite(BOOL hiliteState)
{
 WinSendMsg(hwnd, BM_SETHILITE, MPFROMSHORT(hiliteState), NULL);
 return(*this);
}

OButton& OButton::click(BOOL down)  
{
 WinSendMsg(hwnd, BM_CLICK, MPFROMSHORT(down), NULL);
 return(*this);
}


// end of source
