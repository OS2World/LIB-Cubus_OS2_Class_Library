// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ONSem.hpp    
// Named Semaphores

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

// $Header: W:/Projects/OCL/Include/rcs/ONSem.hpp 1.50 1996/08/11 23:47:24 B.STEIN Release $
 
#ifndef ONSEM_INCLUDED
  #define ONSEM_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif

typedef class ONSem *pONSem;


class __CPP_EXPORT__ ONSem
  : public OCLObject
{
 private:
   OString          semName;
   HEV              sema;
   ULONG            semState;

 public:

 enum ONSemStates  {
                    indefinite = SEM_INDEFINITE_WAIT,
                    immediate = SEM_IMMEDIATE_RETURN 
                   };

 enum ONSemCtorActions 
                   {
                    create = 0, // constructor should try to create the semaphore
                    open        // constructor should try to open the semaphore
                   };

                                // construct from an existing semaphore
   ONSem           (HEV handle) throw (OVioException&);

   ONSem           (PCSZ name = NULL,
                    ULONG action = ONSem::create,
                    BOOL initialState = FALSE) throw (OVioException&); 


   virtual
      ~ONSem       ();

   virtual
      PSZ isOfType () const;


   BOOL
      waitSem      (const ULONG timeout = ONSem::indefinite),
      postSem      (),               // post the semaphore
      closeSem     (),               // close the semaphore
      openSem      (PCSZ name),      // open existing semaphore by name
      openSem      (const HEV aSem); // open existing semaphore by handle

   ULONG
      resetSem     (),               // reset semaphore, returns postCount since last reset
      querySem     ();               // query semaphore, returns postCount

   void
      setSemHandle (HEV hev);

   HEV
      getSemHandle ();          // retrieve sema
};


#endif // ONSEM_INCLUDED

// end of source
