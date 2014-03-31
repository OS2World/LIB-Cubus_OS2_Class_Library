// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OCircSlider.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OCircSlider.cpp 1.50 1996/08/11 23:49:11 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include "OCircSlider.hpp"



OCircSlider::OCircSlider(const ULONG id,
                         const HWND  Parent,
                         const ULONG scale,
                         const ULONG space,
                         const ULONG Style)
  : OWindow(id, 0, 0),
    Scale(scale),
    Space(space)
{
 parent = Parent;
 owner  = Parent;
 style  = Style;
}



OCircSlider::OCircSlider(const ULONG id,
                         const OFrame& Parent,
                         const ULONG scale,
                         const ULONG space,
                         const ULONG Style)
  : OWindow(id, 0, 0),
    Scale(scale),
    Space(space)
{
 parent = Parent.hwnd;
 owner  = Parent.hwnd;
 style  = Style;
}


OCircSlider::OCircSlider(const ULONG id,
                         const pOFrame Parent,
                         const ULONG scale,
                         const ULONG space,
                         const ULONG Style)
  : OWindow(id, 0, 0),
    Scale(scale),
    Space(space)
{
 parent = Parent->hwnd;
 owner  = Parent->hwnd;
 style  = Style;
}



OCircSlider::~OCircSlider() {}


PSZ OCircSlider::isOfType() const
{ 
 return("OCircSlider"); 
}


OCircSlider& OCircSlider::createCircSlider(const SHORT x, const SHORT y,
                                   const SHORT cx, const SHORT cy)
{
 memset(&ctlData, 0, sizeof(CSBITMAPDATA));

#ifdef __OS2_30__
 if (!WinRegisterCircularSlider())
   throw OPMException(OCL::error(155), 0);
#endif

 if ((hwnd = WinCreateWindow(parent, WC_CIRCULARSLIDER, NULL, style | WS_VISIBLE,
                             x, y, cx, cy,
                             owner, HWND_TOP, 0,
                             (PVOID)&ctlData, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(156), 0);  
 return(*this);
}


// end of source
