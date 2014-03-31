// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OAutoRadioButton.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/OAutoRadioButton.cpp 1.50 1996/08/11 23:49:07 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OAutoRadioButton.hpp>


OAutoRadioButton::OAutoRadioButton(ULONG   id,
                                   HWND    Parent,
                                   ULONG   x,
                                   ULONG   y,
                                   ULONG   cx,
                                   ULONG   cy,
                                   ULONG   extraStyle)
     : ORadioButton(id, Parent, x, y, cx, cy)
{
 style = BS_AUTORADIOBUTTON | extraStyle;
}


OAutoRadioButton::OAutoRadioButton(ULONG   id,
                                   OFrame& Parent,
                                   ULONG   x,
                                   ULONG   y,
                                   ULONG   cx,
                                   ULONG   cy,
                                   ULONG   extraStyle)
     : ORadioButton(id, Parent, x, y, cx, cy)
{
 style = BS_AUTORADIOBUTTON | extraStyle;
}


OAutoRadioButton::OAutoRadioButton(ULONG   id,
                                   pOFrame Parent,
                                   ULONG   x,
                                   ULONG   y,
                                   ULONG   cx,
                                   ULONG   cy,
                                   ULONG   extraStyle)
     : ORadioButton(id, Parent, x, y, cx, cy)
{
 style = BS_AUTORADIOBUTTON | extraStyle;
}


OAutoRadioButton::~OAutoRadioButton()
     {}


PSZ OAutoRadioButton::isOfType() const
{
 return("OAutoRadioButton");
}


// end of source
