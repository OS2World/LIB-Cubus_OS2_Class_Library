// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ODynamicLib.hpp

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

// $Header: E:/Projects/OCL/Include/rcs/ODynamicLib.hpp 1.9 1996/01/16 10:12:18 B.STEIN Release B.STEIN $

#ifndef ODYNAMICLIB_INCLUDED
  #define ODYNAMICLIB_INCLUDED

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif

typedef class ODynamicLib *pODynamicLib;

class __CPP_EXPORT__ ODynamicLib
  : virtual public OCLObject
{
 private:
   HMODULE modHandle;

 public:

   ODynamicLib          (HMODULE mod = (HMODULE)NULL);

   ODynamicLib          (PCSZ libname);

   virtual
      ~ODynamicLib      (); // frees the module!!

   virtual
      PSZ isOfType      () const;

   HMODULE getLibHandle ();

   PSZ queryModuleName  ();

   ODynamicLib
     &setLibHandle      (HMODULE mod = (HMODULE)NULL),
     &freeModule        (),
     &freeResource      (PVOID resOffset);
                        // frees resource (offset returned by ::getResource)
   PFN
     queryFn            (ULONG ordinal),  // query fn by ordinal **
     queryFn            (PCSZ fnName);    // query fn by name **

   ULONG
     queryFnType        (ULONG ordinal),  // query fn type (16 or 32) by ordinal **
     queryFnType        (PCSZ fnName),    // query fn type (16 or 32) by name **
     queryAppType       (),               // query application type **
     queryResourceSize  (ULONG resType,   // query size of this resource object (RC-bound) **
                         ULONG resID);

   PVOID getResource    (ULONG resType,   // get offset of a resource (RC-bound) **
                         ULONG resID);
};

// ** throws OVioException in case of any error



#endif // ODYNAMICLIB_INCLUDED

// end of source
