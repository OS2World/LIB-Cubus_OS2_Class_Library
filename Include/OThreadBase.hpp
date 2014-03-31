// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OThreadBase.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OThreadBase.hpp 1.50 1996/08/11 23:47:33 B.STEIN Release $

#ifndef OTHREADBASE_INCLUDED
  #define OTHREADBASE_INCLUDED

#ifndef OCLOBJECT_INCLUDED
  #include <OCLObject.hpp>
#endif


#ifndef OPMINIT_INCLUDED
  #include <OPMinit.hpp>
#endif


typedef class OThreadBase *pOThreadBase;

class __CPP_EXPORT__ OThreadBase
  : virtual public OCLObject
{
 private:
   ULONG     stack;
   BOOL      initPM;

 public:
   TID    tid;

   OThreadBase(ULONG stackSize, BOOL forPM);
   virtual ~OThreadBase();
   virtual PSZ isOfType() const;

// control
   BOOL run();                             // start thread
   BOOL isRunning();                       // is the thread currently running?
   void stop();                            // stop thread
   void suspend();                         // suspend execution
   void resume();                          // resume execution
   BOOL waitFor();                         // wait for termination of this OThreadBase
   void setPrty(ULONG Class = PRTYC_REGULAR,
                ULONG Delta = 0);          // set priority

   virtual void async() = 0;               // this method will be executed

// this member is strictly for internal use only

   static void OTHREADBASE_dispatch(PVOID pvData);
};


#endif // OTHREADBASE_INCLUDED


// end of source
