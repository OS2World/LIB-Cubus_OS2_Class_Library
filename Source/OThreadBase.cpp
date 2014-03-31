// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OThreadBase.cpp
// asynchronous threads


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

// $Header: W:/Projects/OCL/Source/rcs/OThreadBase.cpp 1.50 1996/08/11 23:49:33 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OThread.hpp>



OThreadBase::OThreadBase(ULONG stackSize, BOOL forPM)
 : initPM(forPM),
   stack(stackSize), 
   tid(0)
 {}


OThreadBase::~OThreadBase()
{
 stop();
}


PSZ OThreadBase::isOfType() const
{ 
 return("OThreadBase"); 
}


BOOL OThreadBase::run()                              // start thread
{
 if (isRunning())
   return(FALSE);
#if (defined (__BCPLUSPLUS__) || defined (__HIGHC__))
 tid = _beginthread((pOThread_mbrfn)OTHREADBASE_dispatch, stack, this);
#else
 tid = _beginthread((pOThread_mbrfn)OTHREADBASE_dispatch, NULL, stack, this);
#endif
 return(tid != 0);
}


BOOL OThreadBase::isRunning()
{
 if (tid != 0)
   return(DosWaitThread(&tid, DCWW_NOWAIT) == ERROR_THREAD_NOT_TERMINATED);
 else return(FALSE);
}


BOOL OThreadBase::waitFor()
{
 if (tid != 0)
   return(DosWaitThread(&tid, DCWW_WAIT) != ERROR_THREAD_NOT_TERMINATED);
 else return(FALSE);
}


void OThreadBase::setPrty(ULONG Class, ULONG Delta)
{
 if (isRunning())
   DosSetPriority(PRTYS_THREAD, Class, Delta, tid);
}


void OThreadBase::stop()
{
 if (isRunning())
   DosKillThread(tid); 
}


void OThreadBase::suspend()
{
 if (isRunning())
   DosSuspendThread(tid);
}


void OThreadBase::resume()
{
 if (isRunning())
   DosResumeThread(tid);
}


void OThreadBase::OTHREADBASE_dispatch(PVOID pvData)
{
 pOThreadBase thread = (pOThreadBase) pvData;
 pOPMinit     init   = NULL;

 if (!thread)
   _endthread();

 if (thread->initPM)
   init = new OPMinit;

 thread->async();

 if ((thread->initPM) && (init))
   delete init;

 thread->tid = 0;
 _endthread();
}



// end of source
