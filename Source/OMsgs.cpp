// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMsgs.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMsgs.cpp 1.50 1996/08/11 23:49:23 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMsgs.hpp>
#include <OMessage.hpp>


OMsgs::OMsgs(const HMODULE moduleHandle, const HWND parent, const HWND owner)
  : Parent(parent),
    Owner(owner)
{
 handle = moduleHandle;
}


OMsgs::~OMsgs()
  {}


PSZ OMsgs::isOfType() const
{ 
 return("OMsgs"); 
}


void OMsgs::setResource(const HMODULE moduleHandle)
{
 handle = moduleHandle; 
}


void OMsgs::info(const ULONG msgID)
{
 if (loadString(msgID, 2*CCHMAXPATH, Msg))
   info(OCL::error(100), Msg);
}


void OMsgs::info(const ULONG titleID, const ULONG msgID)
{
 if ((loadString(msgID, 2*CCHMAXPATH, Msg)) && (loadString(titleID, 60, Title)))
   info(Title, Msg);
}


void OMsgs::info(PCSZ msg)
{
 info(OCL::error(100), msg);
}


void OMsgs::info(PCSZ title, PCSZ msg)
{
 WinMessageBox(Parent, Owner, (PCH) msg, (PCH) title, 0,
               MB_OK | MB_MOVEABLE | MB_INFORMATION);
}


void OMsgs::error(const ULONG msgID)
{
 if (loadString(msgID, 2*CCHMAXPATH, Msg))
   error(OCL::error(101), Msg);
}

void OMsgs::error(const ULONG titleID, const ULONG msgID)
{
 if ((loadString(msgID, 2*CCHMAXPATH, Msg)) && (loadString(titleID, 60, Title)))
   error(Title, Msg);
}


void OMsgs::error(PCSZ msg)
{
 error(OCL::error(101), msg);
}


void OMsgs::error(PCSZ title, PCSZ msg)
{
 WinMessageBox(Parent, Owner, (PCH) msg, (PCH) title, 0,
               MB_OK | MB_MOVEABLE | MB_CUAWARNING);
}


BOOL OMsgs::ask(const ULONG titleID, const ULONG msgID)
{
 if ((loadString(msgID, 2*CCHMAXPATH, Msg)) && (loadString(titleID, 60, Title)))
   return(ask(Title, Msg));
 else
   return(FALSE);
}


BOOL OMsgs::ask(PCSZ title, PCSZ msg)
{
 return(WinMessageBox(Parent, Owner, (PCH)msg, (PCH)title,
        0, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1)==MBID_YES);
}



BOOL OMsgs::loadString(const ULONG resID, const ULONG Size, PSZ str)
{
 return(WinLoadString(OApp::current().anchor(), handle, resID, Size, str)!=0);
}


void OMsgs::beeper()
{
 DosBeep(100, 100);
 DosBeep(200, 100);
 DosBeep(300, 100);
}


PSZ OMsgs::message()
{
 return((PSZ)Msg);
}

PSZ OMsgs::title()
{
 return((PSZ)Title);
}

// end of source
