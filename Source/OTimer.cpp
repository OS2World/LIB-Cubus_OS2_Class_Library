// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OTimer.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OTimer.cpp 1.50 1996/08/11 23:49:33 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OTimer.hpp>


OTimer::OTimer(HWND    notifyWin,
               ULONG   id,
               ULONG   timeout)
  : isStarted(FALSE),
    _id(id),
    _timeout(timeout),
    notifyHwnd(notifyWin)
  {}

OTimer::OTimer(OFrame& notifyWin,
               ULONG   id,
               ULONG   timeout)
  : isStarted(FALSE),
    _id(id),
    _timeout(timeout),
    notifyHwnd(notifyWin.hwnd)
  {}


OTimer::OTimer(pOFrame notifyWin,
               ULONG   id,
               ULONG   timeout)
  : isStarted(FALSE),
    _id(id),
    _timeout(timeout),
    notifyHwnd(notifyWin->hwnd)
  {}


OTimer::~OTimer()
{
 if (isStarted) 
   stop();
}

PSZ OTimer::isOfType () const
{
 return("OTimer");
} 


OTimer& OTimer::start()
{
 WinStartTimer(OApp::current().anchor(), notifyHwnd, _id, _timeout);
 return(*this);
}


OTimer& OTimer::start(ULONG timeout)
{
 _timeout = timeout;
 WinStartTimer(OApp::current().anchor(), notifyHwnd, _id, _timeout);
 return(*this);
}


OTimer& OTimer::stop()
{
 WinStopTimer(OApp::current().anchor(), notifyHwnd, _id);
 return(*this);
}

OTimer& OTimer::setId(ULONG id)
{
 _id = id;
 return(*this);
}
 
OTimer& OTimer::setTimeout(ULONG timeout)
{
 _timeout = timeout;
 return(*this);
}

OTimer& OTimer::setNotify(HWND notifyWin)
{
 notifyHwnd = notifyWin;
 return(*this);
}

OTimer& OTimer::setNotify(OFrame& notifyWin)
{
 notifyHwnd = notifyWin.hwnd;
 return(*this);
}

OTimer& OTimer::setNotify(pOFrame notifyWin)
{
 notifyHwnd = notifyWin->hwnd;
 return(*this);
}

// end of source
