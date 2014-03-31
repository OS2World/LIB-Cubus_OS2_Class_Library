// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OXApp.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OXApp.hpp 1.50 1996/08/11 23:47:36 B.STEIN Release $

#ifndef OXAPP_INCLUDED
  #define OXAPP_INCLUDED

#ifndef OAPP_INCLUDED
  #include <OApp.hpp>
#endif



typedef class OXApp *pOXApp;

class __CPP_EXPORT__ OXApp
  : public OApp
{
 public:
   OXApp           (ULONG queueSize = 10);

   OXApp           (const ULONG num,
                    CHAR  *Parms[],
                    ULONG queueSize = 10);

   virtual
      ~OXApp       ();

   virtual
      PSZ isOfType () const;

   virtual
      void run     (); // enhanced message loop with automatic exception handling
};


#endif // OXAPP_INCLUDED


// end of source
