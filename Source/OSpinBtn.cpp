// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 Matthias StÅbner
// All Rights Reserved
// OSpinBtn.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OSpinBtn.cpp 1.50 1996/08/11 23:49:31 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OSpinBtn.hpp>


OSpinBtn::OSpinBtn(const ULONG id,
                   const HWND  Parent,  // becomes parent and owner of the slider
                   const ULONG Style)
  : OWindow(id, 0, 0)
{
 style  = Style;
 parent = Parent;
 owner  = Parent;
}


OSpinBtn::OSpinBtn(const ULONG id,
                   const OFrame& Parent,
                   const ULONG Style)
  : OWindow(id, 0, 0)
{
 style  = Style;
 parent = Parent.hwnd;
 owner  = Parent.hwnd;
}


OSpinBtn::OSpinBtn(const ULONG id,
                   const pOFrame Parent,
                   const ULONG Style)
 : OWindow(id, 0, 0)
{
 style  = Style;
 parent = Parent->hwnd;
 owner  = Parent->hwnd;
}

// dtor

OSpinBtn::~OSpinBtn()
  {}


PSZ OSpinBtn::isOfType() const
{ 
 return("OSpinBtn"); 
}


BOOL OSpinBtn::createSpinBtn(const SHORT x, const SHORT y, 
                             const SHORT cx, const SHORT cy)
{
 hwnd = WinCreateWindow(parent, WC_SPINBUTTON, NULL, style | WS_VISIBLE,
                        x, y, cx, cy,
                        owner, HWND_TOP, 0, NULL, NULL);

 return(hwnd != NULLHANDLE);
}


BOOL OSpinBtn::setArray(PSZ array, ULONG num)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SETARRAY,
                     MPFROMP (array),
                     MPFROMLONG (num)));
}

BOOL OSpinBtn::setCurrent(LONG index)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SETCURRENTVALUE,
                     MPFROMLONG(index),0));
}

BOOL OSpinBtn::setLimits(LONG upper, LONG lower)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SETLIMITS,
                     MPFROMLONG(upper),
                     MPFROMLONG(lower)));
}

BOOL OSpinBtn::setMaster(HWND master)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SETMASTER,
                     MPFROMP(master),0));
}

BOOL OSpinBtn::setTextLimit(USHORT length)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SETTEXTLIMIT,
                     MPFROMSHORT(length),0));
}

BOOL OSpinBtn::overrideLimits(LONG upper, LONG lower)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_OVERRIDESETLIMITS,
                     MPFROMLONG(upper),
                     MPFROMLONG(lower)));
}

BOOL OSpinBtn::incSpin(ULONG delta)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SPINUP,
                     MPFROMLONG(delta),0));
}

BOOL OSpinBtn::decSpin(ULONG delta)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_SPINDOWN,
                     MPFROMLONG(delta),0));
}

BOOL OSpinBtn::getLimits(LONG *upper, LONG *lower)
{
  return((BOOL)WinSendMsg(hwnd,SPBM_QUERYLIMITS,
                     MPFROMP(upper),MPFROMP(lower)));
}

BOOL OSpinBtn::getCurrent(PVOID addr, USHORT size, USHORT control)
{
  return((BOOL)WinSendMsg (hwnd, SPBM_QUERYVALUE,
                     MPFROMP(addr),
                     MPFROM2SHORT(size,control)));
}

BOOL OSpinBtn::jumptoEnd()
{
  while(WinSendMsg(hwnd,SPBM_SPINUP,MPFROMLONG(1),0)) {}
  return(TRUE);
}

BOOL OSpinBtn::jumptoStart()
{
  while(WinSendMsg(hwnd,SPBM_SPINDOWN,MPFROMLONG(1),0)) {}
  return(TRUE);
}















