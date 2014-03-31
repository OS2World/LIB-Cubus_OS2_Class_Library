// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipeSvr.cpp

// members of OPipeSvr


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

// $Header: W:/Projects/OCL/Source/rcs/OPipeSvr.cpp 1.50 1996/08/11 23:49:27 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OPipeSvr.hpp>

#if defined(__EMX__)
  template class OThread<OPipeSvr>;
#endif


OPipeSvr::OPipeSvr(const ULONG inSize,
                   const ULONG outSize,
                   const ULONG Size,
                   const ULONG openMode,
                   const ULONG pipeMode,
                   const ULONG timeout,
                   const ULONG inst)
  : pipeThread(this, &OPipeSvr::Pipe_IO)
{
 oMode = openMode;
 pMode = pipeMode;
 timeOut = timeout;
 instances = inst;
 inBuf = inSize;
 outBuf = outSize;
 BufSize = Size;
}


OPipeSvr::~OPipeSvr()
{
 destroyPipe();
 pipes.reset();
}


PSZ OPipeSvr::isOfType() const
{ 
 return("OPipeSvr"); 
}



BOOL OPipeSvr::beginPiping(PCSZ pipeName)
{
 return(createPipe(pipeName)); 
}


BOOL OPipeSvr::stopPiping() 
{
 return(destroyPipe()); 
}


void OPipeSvr::setBufSizes(const ULONG in, const ULONG out, const ULONG Size)
{
 inBuf = in;
 outBuf = out;
 BufSize = Size;
}


BOOL OPipeSvr::createPipe(PCSZ pipeName)
{
 if ((!oMode) || (!pMode) || (!timeOut) || (!inBuf) || (!outBuf) || (!Buffer) || (!BufSize))
   return(FALSE);

 pMode |= instances;
 connectedClients = 0;

 for (ULONG i=0; i < instances; i++) {
   pPipeStatus status = new PipeStatus;

   status->connected = FALSE;
   if (DosCreateNPipe((PSZ) pipeName,  &status->pipe,  oMode, pMode, outBuf, inBuf, timeOut))
     delete status;
   else
     pipes.addLast(status);
  }

 if (pipes.isEmpty())
   return(FALSE);

 return(pipeThread.run());
}


BOOL OPipeSvr::destroyPipe()
{
 close = TRUE;
 pipeThread.waitFor();
 actual = pipes.getFirst();
 while(actual) {
   actual->connected = FALSE;
   DosDisConnectNPipe(actual->pipe);
   DosClose(actual->pipe); 
   actual = pipes.getNext(); }
 return(TRUE);
}


BOOL OPipeSvr::getPipeData()
{
 ULONG read = 0;
 if ((!actual->connected) || (DosRead(actual->pipe, Buffer, BufSize, &read)))
   return(FALSE);
 if (read == 0)
   return(FALSE);
 OPipeCommand(Buffer);
 return(TRUE);
}

BOOL OPipeSvr::postPipe(PVOID pvData, ULONG client)
{
 ULONG                written = 0;
 pPipeStatus          postTo = NULL;
 OListItem<PipeStatus> *tmp = (OListItem<PipeStatus>*)pipes.last();

 if (client == 0)
  {
   BOOL fSuccess = TRUE;

   for(ULONG client2post = 1; 
      ((client2post <= connectedClients) && (fSuccess));
      client2post++)
     fSuccess = postPipe(pvData, client2post);
   return(fSuccess);
  }

 if ((pipes.isEmpty()) || (client < 1))
   return(FALSE);
 if (client > 1)
  {
   for (ULONG i=1; i < client; i++)
    {
     tmp = tmp->prev;
     if (!tmp)
       return(FALSE);
    }
  }
 
 if (tmp)
   postTo = tmp->item;

 return((postTo != NULL) &&
        (postTo->connected) && 
        (!DosWrite(postTo->pipe, pvData, BufSize, &written)) && 
        (written != 0)); 
}


void OPipeSvr::Pipe_IO()
{
 APIRET     rc;
 
 pipeThread.setPrty(PRTYC_IDLETIME, 0);  // initially run at idle priority

 actual = pipes.getFirst();

 while((!close) && (actual))
  {
   rc = DosConnectNPipe(actual->pipe);
   switch(rc) 
    {
     case NO_ERROR:
       if (actual->connected == FALSE) {
           actual->connected = TRUE;
           connectedClients++; }
       if (connectedClients > 0)
         pipeThread.setPrty(PRTYC_REGULAR, 0);
       getPipeData();
       break;
 
     case ERROR_BROKEN_PIPE:
       actual->connected = FALSE;
       connectedClients--;
       DosDisConnectNPipe(actual->pipe);
       if (connectedClients == 0)
         pipeThread.setPrty(PRTYC_IDLETIME, 0);
       break;

     case ERROR_PIPE_NOT_CONNECTED:
       actual->connected = FALSE;
       break;
    }

   actual = pipes.getNext();
   if (!actual) {
      actual = pipes.getFirst();
      DosSleep(100); }
  }

 _endthread();
}

// end of source
