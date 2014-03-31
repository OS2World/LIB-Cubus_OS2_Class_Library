// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ODynamicLib.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/ODynamicLib.cpp 1.50 1996/08/11 23:49:14 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ODynamicLib.hpp>
#include <OMessage.hpp>


ODynamicLib::ODynamicLib(HMODULE mod)
  : modHandle(mod)
  {}


ODynamicLib::ODynamicLib(PCSZ libname)
{
 APIRET rc;
 CHAR   errBuffer[100];
 
 rc = DosLoadModule(errBuffer, 100, (PSZ)libname, &modHandle);
 if ((rc != 0) || (!modHandle))
   throw OVioException(errBuffer, rc);
}


ODynamicLib::~ODynamicLib()
{
 freeModule();
}


PSZ ODynamicLib::isOfType() const
{ 
 return("ODynamicLib"); 
}


ODynamicLib& ODynamicLib::freeModule()
{
 if (modHandle)
   DosFreeModule(modHandle);
 return(*this);
}



HMODULE ODynamicLib::getLibHandle()
{
 return( modHandle );                           
}



ODynamicLib&  ODynamicLib::setLibHandle(HMODULE mod)
{
 modHandle = mod;
 return(*this);
}



PFN ODynamicLib::queryFn(ULONG ordinal)
{
 APIRET rc;
 PFN    fn = (PFN) NULL;
 
 rc = DosQueryProcAddr(modHandle, ordinal, (PSZ)NULL, &fn);
 if ((rc != 0) || (!fn))
   throw OVioException(OCL::apierror(50, rc), rc);
 return(fn);
}


PFN ODynamicLib::queryFn(PCSZ fnName)
{
 APIRET rc;
 PFN    fn = (PFN) NULL;
 
 rc = DosQueryProcAddr(modHandle, 0, (PSZ)fnName, &fn);
 if ((rc != 0) || (!fn))
   throw OVioException(OCL::apierror(51, rc), rc);
 return(fn);
}



ULONG ODynamicLib::queryFnType(ULONG ordinal)
{
 APIRET  rc;
 ULONG   ul;

 rc = DosQueryProcType(modHandle, ordinal, (PSZ)NULL, &ul);
 if (rc != 0)
   throw OVioException(OCL::apierror(52, rc), rc);
 return( (ul == PT_16BIT) ? 16 : 32);
}


ULONG ODynamicLib::queryFnType(PCSZ fnName)
{
 APIRET  rc;
 ULONG   ul;

 rc = DosQueryProcType(modHandle, 0, (PSZ)fnName, &ul);
 if (rc != 0)
   throw OVioException(OCL::apierror(53, rc), rc);
 return( (ul == PT_16BIT) ? 16 : 32);
}


PSZ ODynamicLib::queryModuleName()
{
 APIRET  rc;
 OString Buffer(CCHMAXPATH);

 rc = DosQueryModuleName(modHandle, CCHMAXPATH, Buffer);
 if (rc != 0)
   throw OVioException(OCL::apierror(54, rc), rc);
 return(Buffer);
}


ULONG ODynamicLib::queryAppType()
{
 APIRET  rc;
 ULONG   ul;

 try {
   rc = DosQueryAppType(queryModuleName(), &ul); }
 catch(OVioException ex) {
   rc = ex.rc; }

 if (rc != 0)
   throw OVioException(OCL::apierror(55, rc), rc);

 return(ul);
}


PVOID ODynamicLib::getResource(ULONG resType, ULONG resID)
{
 APIRET rc;
 PVOID  pv;

 rc = DosGetResource(modHandle, resType, resID, &pv);
 if (rc != 0)
   throw OVioException(OCL::apierror(56, rc), rc);

 return(pv);
}



ODynamicLib& ODynamicLib::freeResource(PVOID resOffset)
{
 if (resOffset)
   DosFreeResource(resOffset);
 return(*this);
}


ULONG ODynamicLib::queryResourceSize(ULONG resType, ULONG resID)
{
 APIRET rc;
 ULONG  ul;

 rc = DosQueryResourceSize(modHandle, resType, resID, &ul);
 if (rc != 0)
   throw OVioException(OCL::apierror(57, rc), rc);

 return(ul);
}


// end of source
