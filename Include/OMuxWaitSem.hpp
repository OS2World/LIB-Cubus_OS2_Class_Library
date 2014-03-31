// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMuxWaitSem.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OMuxWaitSem.hpp 1.50 1996/08/11 23:47:23 B.STEIN Release $

#ifndef OMUXWAITSEM_INCLUDED
  #define OMUXWAITSEM_INCLUDED


#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif


#ifndef ONSEM_INCLUDED
  #include <ONSem.hpp>
#endif

#ifndef OMUXSEM_INCLUDED
  #include <OMuxSem.hpp>
#endif


// in case of any return value !TRUE check muxwaitState for error number


typedef class OMuxWaitSem *pOMuxWaitSem;

class __CPP_EXPORT__ OMuxWaitSem
  : public OCLObject
{
 private:
   HMUX                   hmux;
 
 public:
   ULONG                  muxwaitState;


 enum OMuxWaitSemActions {
                          open = 0,
                          create
                         };

 enum OMuxWaitOptions    {
                          nowait = SEM_IMMEDIATE_RETURN,
                          indefinite = SEM_INDEFINITE_WAIT,
                          waitAll = DCMW_WAIT_ALL,
                          waitAny = DCMW_WAIT_ANY,
                          shared = DC_SEM_SHARED
                         };

 OMuxWaitSem             (HMUX handle) throw (OVioException&);

 OMuxWaitSem             (PCSZ name,             // named MuxWaitSem name
                          ULONG numSem,          // number of semaphores in semArray
                          PSEMRECORD semArray,   // array of semaphores
                          ULONG action = OMuxWaitSem::create,
                          ULONG attrib = OMuxWaitSem::waitAny | OMuxWaitSem::shared)
                         throw (OVioException&);

 virtual
    ~OMuxWaitSem         ();

 virtual
    PSZ isOfType         () const;

 ULONG
    waitMuxWaitSem       (ULONG waitFlag = OMuxWaitSem::indefinite);
                         // lets OMuxWaitSem wait
                         // returns posted or last posted event semaphore
 BOOL
    openMuxWaitSem       (HMUX handle),
    openMuxWaitSem       (PCSZ name),
    closeMuxWaitSem      (),
    addSemaphore         (PSEMRECORD record),  // add semaphore to wait list
    addSemaphore         (ONSem *sema),        // add ONSem object to wait list
    addSemaphore         (OMuxSem *sema),      // add OMuxSem object to wait list
    delSemaphore         (HSEM handle),        // delete semaphore from the wait list
    queryMuxWaitSem      (PULONG num,          // return number of semaphores in wait list
                          PSEMRECORD semArray, // return array of semapores in wait list
                          PULONG attributes);  // return creation flags of current OMuxWaitSem

 void
    setMuxWaitSemHandle  (HMUX handle);
 HMUX
    getMuxWaitSemHandle  ();
};





#endif // OMUXWAITSEM_INCLUDED

// end of source
