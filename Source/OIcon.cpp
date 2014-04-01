// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OIcon.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OIcon.cpp 1.50 1996/08/11 23:49:21 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIcon.hpp>
#include <OMessage.hpp>


OIcon::OIcon()
  : OPicture(0, 0),
    hptr(NULLHANDLE)
  {}


OIcon::OIcon(const ULONG resID, const HMODULE module)
  : OPicture((ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CXICON),
             (ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CYICON)), 
    hptr(WinLoadPointer(HWND_DESKTOP, module, resID))
{
 if (!hptr)
   throw OPMException(OCL::error(70), 0, OException::recoverable);
}



OIcon::OIcon(const HPOINTER ptrHandle)
  : OPicture((ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CXICON),
             (ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CYICON)), 
    hptr(ptrHandle)
{
 if (!hptr)
   throw OPMException(OCL::error(71), 0, OException::recoverable);
}


OIcon::OIcon(PCSZ fileName)
  : OPicture((ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CXICON),
             (ULONG)WinQuerySysValue(HWND_DESKTOP, SV_CYICON)), 
    hptr(WinLoadFileIcon((PSZ)fileName, TRUE))
{
 if (!hptr)
   throw OPMException(OCL::error(72), 0, OException::recoverable);
}


OIcon::~OIcon()
{
 destroy();
}


PSZ OIcon::isOfType() const
{ 
 return("OIcon"); 
}


OIcon& OIcon::load(const ULONG resID, const HMODULE module)
{
 destroy();
 hptr = WinLoadPointer(HWND_DESKTOP, module, resID);

 if (!hptr)
   throw OPMException(OCL::error(70), 0, OException::recoverable);
 
 return(*this);
}

OIcon& OIcon::loadFromFile(PSZ fileName)
{
 destroy();
 hptr = WinLoadFileIcon(fileName, FALSE);

 if (!hptr)
   throw OPMException(OCL::error(70), 0, OException::recoverable);
 
 return(*this);
}

OIcon& OIcon::destroy()
{
 if (hptr)
   WinDestroyPointer(hptr);

 return(*this);
}

// end of source
