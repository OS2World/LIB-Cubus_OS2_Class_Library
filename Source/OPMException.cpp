// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPMException.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OPMException.cpp 1.50 1996/08/11 23:49:25 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OPMException.hpp>
#include <OMessage.hpp>


OPMException::OPMException(const PSZ err,
                           const ULONG retcode,
                           const ULONG severity,
                           const PSZ source,
                           const ULONG line)
  : OException(err, retcode, severity, source, line),
    errRes(0)
  {}



OPMException::OPMException(const ULONG errResource, 
                           const ULONG retcode,     
                           const ULONG severity,
                           const HMODULE mod,
                           const PSZ source,
                           const ULONG line)        
  : OException(NULL, retcode, severity, source, line),
    exMsg(mod),
    errRes(errResource)
  {
   if (errRes)
    {
     exMsg.loadString(errRes, 2*CCHMAXPATH, exMsg.message());
     description << exMsg.message();
    }
  }


OPMException::OPMException(const OPMException& ex)
  : OException(ex.description, ex.rc, ex.state, ex.Source, ex.Line),
    exMsg((HMODULE)ex.exMsg),
    message(ex.message),
    errRes(ex.errRes)
  {
   if (errRes) {
     exMsg.loadString(errRes, 2*CCHMAXPATH, exMsg.message());
     description << exMsg.message(); }
  }


OPMException::~OPMException()
  {}


PSZ OPMException::isOfType() const
{ 
 return("OPMException"); 
}




void OPMException::viewError()
{
 OString   err;
 PERRINFO  pErrInfoBlk;
 PSZ       pszOffset;
 CHAR      ErrBuffer[512];

 err <<  OMessage(190, OCL::MSGFILE);
 err +   "\n";
 err +   OMessage(191, OCL::MSGFILE, Source);
 sprintf(ErrBuffer, "%d", Line);
 err +   OMessage(192, OCL::MSGFILE, ErrBuffer);
 err +   OMessage(193, OCL::MSGFILE, isOfType());
 sprintf(ErrBuffer, "%d", rc);
 err +   OMessage(194, OCL::MSGFILE, ErrBuffer);
 sprintf(ErrBuffer, "%d", WinGetLastError(OApp::current().anchor()));
 err +   OMessage(197, OCL::MSGFILE, ErrBuffer);

 strcpy(ErrBuffer, "");

 while((pErrInfoBlk = WinGetErrorInfo(OApp::current().anchor())) != (PERRINFO)NULL)
  {
   pszOffset = ((PSZ)pErrInfoBlk) + pErrInfoBlk->offaoffszMsg;
   strcat(ErrBuffer, (((PSZ)pErrInfoBlk) + *((PSHORT)pszOffset)));
   WinFreeErrorInfo(pErrInfoBlk);
  }

 err +   OMessage(198, OCL::MSGFILE, ErrBuffer);

 if (!description) 
  description << OMessage(190, OCL::MSGFILE);

 err +   OMessage(195, OCL::MSGFILE, "\n", description);

 exMsg.error("Note!", err);
}


// end of source
