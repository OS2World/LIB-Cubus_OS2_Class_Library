// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ONSem.cpp
// Named Semaphores

// class member functions

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


// $Header: W:/Projects/OCL/Source/rcs/ONSem.cpp 1.50 1996/08/11 23:49:25 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ONSem.hpp>
#include <OMessage.hpp>


ONSem::ONSem(HEV handle) throw (OVioException&)
  : sema(handle),
    semState(0)
{
 if (!openSem(sema))
   throw OVioException(OCL::apierror(125, semState), semState);
}


ONSem::ONSem(PCSZ name, ULONG action, BOOL initialState) throw (OVioException&)
  : sema((HEV)NULL), 
    semState(0),
    semName((PSZ)name)
{
 switch(action)
  {
   case ONSem::create: {
    if((semState = DosCreateEventSem(semName, &sema, 0, initialState)) != 0)
      throw OVioException(OCL::apierror(126, semState), semState);
    break; }

   case ONSem::open:
    if (!openSem(name))
      throw OVioException(OCL::apierror(127, semState), semState);
    if (initialState)
      postSem();
    break;
  }
}



ONSem::~ONSem()
{
 if (sema) closeSem();
}


PSZ ONSem::isOfType() const
{ 
 return("ONSem"); 
}


void ONSem::setSemHandle(HEV hev) 
{
 sema = hev;
}


HEV  ONSem::getSemHandle()
{ 
 return(sema); 
}


BOOL ONSem::waitSem(const ULONG timeout)
{
 semState = DosWaitEventSem(sema, timeout);
 return(semState == 0);
}



BOOL ONSem::postSem()
{
 semState = DosPostEventSem(sema);
 return(semState == 0);
}


BOOL ONSem::closeSem()
{
 semState = DosCloseEventSem(sema);
 sema = (HEV)NULL;
 return(semState == 0);
}


BOOL ONSem::openSem(PCSZ name)
{
 
 if (!name) {
   semState = ERROR_INVALID_NAME;
   return(FALSE); }
 else {
   sema = (HEV) NULL;
   semName << (PSZ) name;
   semState = DosOpenEventSem(semName, &sema); }
 return(semState == 0);
}


BOOL ONSem::openSem(const HEV aSem)
{
 sema = aSem;
 semName << (PSZ) NULL;
 semState = DosOpenEventSem(semName, &sema);
 return(semState == 0);
}


ULONG ONSem::resetSem()
{
 ULONG  postCount = 0;

 semState = DosResetEventSem(sema, &postCount);
 return(postCount);
}


ULONG ONSem::querySem()
{
 ULONG  postCount = 0;

 semState = DosQueryEventSem(sema, &postCount);
 return(postCount);
}


// end of source
