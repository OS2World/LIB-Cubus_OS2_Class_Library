// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMuxSem.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMuxSem.cpp 1.50 1996/08/11 23:49:24 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMuxSem.hpp>
#include <OMessage.hpp>


OMuxSem::OMuxSem(HMTX handle) throw (OVioException&)
  : hmtx(handle),
    muxState(0)
{
 if (!openMuxSem(handle))
   throw OVioException(OCL::apierror(110, muxState), muxState);
}

OMuxSem::OMuxSem(PCSZ name, ULONG action, BOOL shared) throw (OVioException&)
{
 APIRET rc = 0;

 switch(action)
  {
   case OMuxSem::create: {
    ULONG  shareFlag = 0;

    if ((!name) && (shared))
      shareFlag = DC_SEM_SHARED;
    if((rc = DosCreateMutexSem(name, &hmtx, shareFlag, FALSE))!=0)
      throw OVioException(OCL::apierror(111, rc), rc);
    break; }

   case OMuxSem::open:
    if (!openMuxSem(name))
      throw OVioException(OCL::apierror(112, rc), rc);
    break;
  }
}


OMuxSem::~OMuxSem()
{
 if (hmtx)
   closeMuxSem();
}


PSZ OMuxSem::isOfType() const
{ 
 return("OMuxSem"); 
}


BOOL OMuxSem::openMuxSem(HMTX handle)
{
 hmtx = handle;
 muxState = DosOpenMutexSem((PSZ)NULL, &hmtx);
 return(muxState == 0);
}


BOOL OMuxSem::openMuxSem(PCSZ name)
{
 muxName << (PSZ) name;
 muxState = DosOpenMutexSem(muxName, &hmtx);
 return(muxState == 0);
}


BOOL OMuxSem::closeMuxSem()
{
 muxState = DosCloseMutexSem(hmtx);
 hmtx = (HMUX)NULL;
 return(muxState == 0);
}


BOOL OMuxSem::requestMuxSem(ULONG timeOut)
{
 muxState = DosRequestMutexSem(hmtx, timeOut);
 return(muxState == 0);
}


BOOL OMuxSem::releaseMuxSem()
{
 muxState = DosReleaseMutexSem(hmtx);
 return(muxState == 0);
}


void OMuxSem::setMuxSemHandle(HMTX handle)
{
 hmtx = handle;
}


HMTX OMuxSem::getMuxSemHandle()
{
 return(hmtx);
}


// end of source
