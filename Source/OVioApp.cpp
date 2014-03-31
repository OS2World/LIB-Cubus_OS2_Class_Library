// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OVioApp.cpp

// OVioApp ia a base class for VIO-Applications


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

// $Header: W:/Projects/OCL/Source/rcs/OVioApp.cpp 1.50 1996/08/11 23:49:35 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OVioApp.hpp>


OVioApp::OVioApp()
  {}

OVioApp::OVioApp(const ULONG num, CHAR *Parms[])
  : OAppBase(num, Parms)
  {}

OVioApp::~OVioApp()
  {}

PSZ OVioApp::isOfType() const
{ 
 return("OVioApp"); 
} 

void OVioApp::Shutdown()
{
 DosShutdown(0L);
}

void OVioApp::forceQuit()
{
 _exit(0);
}


void OVioApp::Reboot()
{
 HFILE  hf;
 ULONG  dummy;

 if (!DosOpen("DOS$", &hf, &dummy, 0L, FILE_NORMAL, FILE_OPEN,
              OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_FAIL_ON_ERROR, 0L))
  {
   ULONG ulParmLength = 0;
   ULONG ulDataLength = 0;

   DosShutdown(0L);
   DosDevIOCtl(hf, 0xd5, 0xab,           // Reboot
               NULL, 0L, &ulParmLength,
               NULL, 0L, &ulDataLength );
   DosClose( hf );
  }
}

// end of source
