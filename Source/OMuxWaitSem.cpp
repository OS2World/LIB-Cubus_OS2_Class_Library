// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMuxWaitSem.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMuxWaitSem.cpp 1.50 1996/08/11 23:49:24 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMuxWaitSem.hpp>
#include <OMessage.hpp>


OMuxWaitSem::OMuxWaitSem(HMUX handle) throw (OVioException&)
  : hmux((HMUX)NULL),
    muxwaitState(0)
{
 if (!openMuxWaitSem(handle))
   throw OVioException(OCL::apierror(120, muxwaitState), muxwaitState);
}


OMuxWaitSem::OMuxWaitSem(PCSZ name, 
                         ULONG numSem, 
                         PSEMRECORD semArray,  
                         ULONG action,
                         ULONG attrib) throw (OVioException&)
  : hmux((HMUX)NULL),
    muxwaitState(0)
{
 switch(action)
  {
   case OMuxWaitSem::create: {
    APIRET rc;

    if ((rc=DosCreateMuxWaitSem(name, &hmux, numSem, semArray, attrib))!=0)
      throw OVioException(OCL::apierror(121, rc), rc);
    break; }

   case OMuxWaitSem::open:
    if (!openMuxWaitSem(name))
      throw OVioException(OCL::apierror(122, muxwaitState), muxwaitState);
    break;
  }
}


OMuxWaitSem::~OMuxWaitSem()
{
 if (hmux)
   closeMuxWaitSem();
}


PSZ OMuxWaitSem::isOfType() const
{ 
 return("OMuxWaitSem"); 
}


ULONG OMuxWaitSem::waitMuxWaitSem(ULONG timeout)
{
 ULONG posted = 0;

 muxwaitState = DosWaitMuxWaitSem(hmux, timeout, &posted);
 if (muxwaitState)
   return(0);
 return(posted);
}



BOOL OMuxWaitSem::openMuxWaitSem(HMUX handle)
{
 muxwaitState = DosOpenMuxWaitSem((PSZ)NULL, &handle);
 return(muxwaitState == 0);
}


BOOL OMuxWaitSem::openMuxWaitSem(PCSZ name)
{
 hmux = (HMUX)NULL;
 muxwaitState = DosOpenMuxWaitSem((PSZ)name, &hmux);
 return(muxwaitState == 0);
}



BOOL OMuxWaitSem::addSemaphore(PSEMRECORD record)
{
 muxwaitState = DosAddMuxWaitSem(hmux, record);
 return(muxwaitState == 0);
}


BOOL OMuxWaitSem::addSemaphore(ONSem *sema)
{
 SEMRECORD semRec;

 if (!sema) {
   muxwaitState = ERROR_INVALID_PARAMETER;
   return(FALSE); }

 semRec.hsemCur = (HSEM) sema->getSemHandle();
 return(addSemaphore(&semRec));
}


BOOL OMuxWaitSem::addSemaphore(OMuxSem *sema)
{
 SEMRECORD semRec;

 if (!sema) {
   muxwaitState = ERROR_INVALID_PARAMETER;
   return(FALSE); }

 semRec.hsemCur = (HSEM) sema->getMuxSemHandle();
 return(addSemaphore(&semRec));
}


BOOL OMuxWaitSem::delSemaphore(HSEM handle)
{
 muxwaitState = DosDeleteMuxWaitSem(hmux, handle);
 return(muxwaitState == 0);
}


BOOL OMuxWaitSem::queryMuxWaitSem(PULONG num,
                                  PSEMRECORD semArray,
                                  PULONG attributes)
{
 muxwaitState = DosQueryMuxWaitSem(hmux, num, semArray, attributes);
 return(muxwaitState == 0);
}


void OMuxWaitSem::setMuxWaitSemHandle(HMUX handle)
{
 hmux = handle;
}


HMUX OMuxWaitSem::getMuxWaitSemHandle()
{
 return(hmux);
}


BOOL OMuxWaitSem::closeMuxWaitSem()
{
 muxwaitState = DosCloseMuxWaitSem(hmux);
 return(muxwaitState == 0);
}


// end of source
