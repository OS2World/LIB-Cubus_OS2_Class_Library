// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OProcStat.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OProcStat.hpp 1.50 1996/08/11 23:47:27 B.STEIN Release $

#ifndef OPROCSTAT_INCLUDED
  #define OPROCSTAT_INCLUDED



#ifndef SLOPROC_INCLUDED
  #include <slOProcRecord.hpp>
#endif


// System Status Report

typedef class OProcStat *pOProcStat;

class __CPP_EXPORT__ OProcStat
   : public OCLObject
{
 private:
    ULONG getNumInfo  (PSZ module, ULONG flag);

 public:
    slOProcRecord     ProcList;
    ULONG             TaskCount;
    ULONG             ProcCount;

   OProcStat          ();

   virtual
      ~OProcStat      ();

   virtual
      PSZ isOfType    () const;

   BOOL  getProcesses ();
   PSZ   getModule    (ULONG pid);    // get a module name from a PID
   ULONG getPid       (PSZ module),   // get a PID from a module name
         getPPid      (PSZ module),   // get a PPID from a module name
         getProcCount (),
         getTaskCount ();
};

 
#endif // OPROCSTAT_INCLUDED

// end of source
