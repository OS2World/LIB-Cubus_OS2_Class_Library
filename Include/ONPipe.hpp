// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ONPipe.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/ONPipe.hpp 1.50 1996/08/11 23:47:23 B.STEIN Release $

#ifndef ONPIPE_INCLUDED
  #define ONPIPE_INCLUDED

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OTHREAD_INCLUDED
  #include <OThread.hpp>
#endif

#ifndef OLIST_INCLUDED
  #include <OList.hpp>
#endif


#define SVR_PIPE_OPEN_DEFAULT  NP_ACCESS_DUPLEX | \
                               NP_NOINHERIT | \
                               NP_WRITEBEHIND

#define SVR_PIPE_PIPE_DEFAULT  NP_NOWAIT | \
                               NP_READMODE_MESSAGE | \
                               NP_TYPE_MESSAGE

#define CLI_PIPE_OPEN_DEFAULT  OPEN_ACCESS_READWRITE | \
                               OPEN_SHARE_DENYNONE | \
                               OPEN_FLAGS_WRITE_THROUGH

#define PIPE_TIMEOUT_DEFAULT   1000  // milliseconds to pipe timeout


typedef class ONPipe *pONPipe;       // pure base


typedef struct _PipeStatus
{
 HPIPE pipe;       // pipe handle
 BOOL connected;   // is pipe connected?
} PipeStatus, *pPipeStatus;


typedef OList<PipeStatus>  pipelist;
typedef pipelist *ppipelist;

class __CPP_EXPORT__ ONPipe
  : public OCLObject
{
 public:
   ULONG           oMode;
   ULONG           pMode;
   ULONG           timeOut;
   BOOL            close;
   PVOID           Buffer;
   ULONG           BufSize;

   ONPipe          ();

   virtual
      ~ONPipe      ();

   virtual
      PSZ isOfType () const;

   void
      setOpenMode  (const ULONG mode),
      setPipeMode  (const ULONG mode),
      setTimeOut   (const ULONG timeout);


// pure virtuals

   virtual BOOL
      beginPiping  (PCSZ pipeName) = 0,
      stopPiping   () = 0,
      postPipe     (PVOID pvData, ULONG client) = 0;
};


#endif // OPIPE_INCLUDED

// end of source
