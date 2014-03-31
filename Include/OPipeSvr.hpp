// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipeSvr.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OPipeSvr.hpp 1.50 1996/08/11 23:47:26 B.STEIN Release $

#ifndef OPIPESVR_INCLUDED
  #define OPIPESVR_INCLUDED

#ifndef ONPIPE_INCLUDED
  #include <ONPipe.hpp>
#endif


typedef class OPipeSvr *pOPipeSvr;   // a pipe Server


class __CPP_EXPORT__ OPipeSvr
  : public ONPipe
{
 private:
   ULONG            inBuf;
   ULONG            outBuf;
   ULONG            instances;

   BOOL
      createPipe    (PCSZ pipeName),
      destroyPipe   ();

 public:
   OThread<OPipeSvr> pipeThread;
   pipelist          pipes;
   pPipeStatus       actual;
   ULONG             connectedClients;


   OPipeSvr         (const ULONG inSize,
                     const ULONG outSize,
                     const ULONG Size,
                     const ULONG openMode = SVR_PIPE_OPEN_DEFAULT,
                     const ULONG pipeMode = SVR_PIPE_PIPE_DEFAULT,
                     const ULONG timeout = PIPE_TIMEOUT_DEFAULT,
                     const ULONG inst = 1);

   virtual
      ~OPipeSvr     ();

   virtual
      PSZ isOfType  () const;

   void
      setBufSizes   (const ULONG in, const ULONG out, const ULONG Size);

   BOOL
      beginPiping   (PCSZ pipeName),
      stopPiping    (),
      getPipeData   (),
      postPipe      (PVOID pvData, ULONG client = 0);
                    // default 0 means: post to all connected clients

   void Pipe_IO     ();

// override this
   virtual void
      OPipeCommand  (PVOID pvData) = 0;
};



#endif // OPIPESVR_INCLUDED

// end of source
