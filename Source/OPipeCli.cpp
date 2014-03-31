// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipeCli.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OPipeCli.cpp 1.50 1996/08/11 23:49:27 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OPipeCli.hpp>

#if defined(__EMX__)
  template class OThread<OPipeCli>;
#endif


// members of OPipeCli


OPipeCli::OPipeCli(const ULONG Size,
                   const ULONG openMode,
                   const ULONG pipeMode,
                   const ULONG timeout,
                   const BOOL  waitFor)
  : pipeThread(this, &OPipeCli::Pipe_IO)
{
 oMode = openMode;
 pMode = pipeMode;
 timeOut = timeout;
 BufSize = Size;
 waitForInstance = waitFor;
 connected = FALSE;
 Pipe = (HPIPE)NULL;
}



OPipeCli::~OPipeCli()
{
 if (connected) disconnectPipe();
}


PSZ OPipeCli::isOfType() const
{ 
 return("OPipeCli"); 
}


BOOL OPipeCli::beginPiping(PCSZ pipeName) 
{
 return(connectPipe(pipeName)); 
}


BOOL OPipeCli::stopPiping() 
{
 return(disconnectPipe()); 
}


void OPipeCli::setSize(const ULONG Size) 
{
 BufSize = Size; 
}


BOOL OPipeCli::connectPipe(PCSZ pipeName)
{
 ULONG     Action;
 APIRET    rc;

 if ((!oMode) || (connected) || (!Buffer) || (!BufSize))
   return(FALSE);

 while(!close)
  {
   rc = DosOpen((PSZ)pipeName, (PHFILE)&Pipe, &Action, 0L, 0L, 
                OPEN_ACTION_OPEN_IF_EXISTS, oMode, NULL);
   switch(rc)
    {
     case NO_ERROR:
       connected = TRUE;
       return(pipeThread.run());

     case ERROR_PIPE_BUSY:
       if (!waitForInstance)
         return(FALSE);
       DosWaitNPipe((PSZ)pipeName, 0);
       break;
    }
  }
 return(FALSE);
}

BOOL OPipeCli::disconnectPipe()
{
 close = TRUE;
 DosClose(Pipe);
 connected = FALSE;
 if (pipeThread.isRunning())
   pipeThread.stop();
 return(TRUE);
}

BOOL OPipeCli::postPipe(PVOID pvData, ULONG client)
{
 ULONG written = 0;

 return((connected) && 
        (!DosWrite(Pipe, pvData, BufSize, &written)) &&
        (written != 0));
#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif


void OPipeCli::Pipe_IO()
{
 ULONG read = 0;

 while (!close)
   {
    if (!DosRead(Pipe, Buffer, BufSize, &read) && read > 0)
      OPipeCommand(Buffer); 
    else
      DosSleep(100); 
   }

 connected = FALSE;
 _endthread();
}

// end of source
