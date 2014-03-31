// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPMPipeTool.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OPMPipeTool.hpp 1.50 1996/08/11 23:47:25 B.STEIN Release $

#ifndef OPMPIPETOOL_INCLUDED
  #define OPMPIPETOOL_INCLUDED


#ifndef OPIPE_INCLUDED
  #include <OPipe.hpp>
#endif

#ifndef OTHREAD_INCLUDED
  #include <OThread.hpp>
#endif


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


typedef class OPMPipeTool *pOPMPipeTool;

class __CPP_EXPORT__ OPMPipeTool
  : public OCLObject
{
 public:
   HWND                 hwndNotify;
   HAPP                 happ;
   OPipe_istream        pipe;
   OString              readBuffer;
   ULONG                sType;
   ULONG                bufferSize;
   OThread<OPMPipeTool> printer;

   OString              childName;
   OString              childParms;

   OPMPipeTool         (PCSZ exename, 
                        PCSZ parms, 
                        HWND notifyWindow = HWND_DESKTOP,
                        const ULONG sessionType = PROG_WINDOWABLEVIO,
                        const ULONG pipeBuffer = USHRT_MAX);

   virtual
      ~OPMPipeTool     ();

   virtual
      PSZ isOfType     () const;

   void 
      setNotify        (HWND notifyWindow),
      setNotify        (OFrame& notifyWindow),
      setNotify        (pOFrame notifyWindow),
      detachChild      (),        // spawn child process
      stopChild        ();        // kill the spawned process  

   virtual
      void printout    ();        // thread must read redirected output cerr/cout
                                  // from the pipe, you must implement this member! 
};


#endif // OPMPIPETOOL_INCLUDED

// end of source
