// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipeCli.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OPipeCli.hpp 1.50 1996/08/11 23:47:26 B.STEIN Release $

#ifndef OPIPECLI_INCLUDED
  #define OPIPECLI_INCLUDED

#ifndef ONPIPE_INCLUDED
  #include <ONPipe.hpp>
#endif


typedef class OPipeCli *pOPipeCli;   // a pipe Client


class __CPP_EXPORT__ OPipeCli
  : public ONPipe
{
 private:
   BOOL              waitForInstance;

   BOOL
      connectPipe    (PCSZ pipeName),
      disconnectPipe ();
 
 public:
   OThread<OPipeCli> pipeThread;
   OString           Name;
   HPIPE             Pipe;
   BOOL              connected;

   OPipeCli         (const ULONG Size,
                     const ULONG openMode = CLI_PIPE_OPEN_DEFAULT,
                     const ULONG pipeMode = SVR_PIPE_PIPE_DEFAULT,
                     const ULONG timeout = PIPE_TIMEOUT_DEFAULT,
                     const BOOL  waitFor = FALSE);
                          // if waitFor == TRUE
                          // beginPiping() will return only
                          // when a pipe instance became available
                          // default is to return FALSE when no
                          // pipe instance could be opened

   virtual
      ~OPipeCli     ();

   virtual
      PSZ isOfType  () const;

   void
      setSize       (const ULONG Size);

   BOOL
      beginPiping   (PCSZ pipeName),
      stopPiping    (),
      postPipe      (PVOID pvData, ULONG client = 0);  // unused

   void
      Pipe_IO       ();

   virtual void
      OPipeCommand  (PVOID pvData) = 0;
};



#endif // OPIPECLI_INCLUDED

// end of source
