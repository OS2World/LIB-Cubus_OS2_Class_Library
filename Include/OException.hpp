// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OException.hpp


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

// $Header: E:/Projects/OCL/Include/rcs/OException.hpp 1.13 1996/01/16 10:12:18 B.STEIN Release B.STEIN $

#ifndef OEXCEPTION_INCLUDED
  #define OEXCEPTION_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


typedef class OException *pOException;

class __CPP_EXPORT__ OException
  : virtual public OCLObject
{
 protected:
   ULONG   state;

 public:
   OString description;
   OString Source;
   ULONG   Line;
   ULONG   rc;

 enum Severity {
   recoverable = 0,
   unrecoverable,
   fatal };

   OException       (const PSZ err,           // supplied error message
                     const ULONG retcode,     // an API return code
                     const ULONG severity,    // severity code
                     const PSZ source = "",   // module name
                     const ULONG line = 0);   // line number

   OException       (const OString& err,      // supplied error message
                     const ULONG retcode,     // an API return code
                     const ULONG severity,    // severity code
                     const PSZ source = "",   // module name
                     const ULONG line = 0);   // line number

   OException        (const OException& ex);

   virtual
      ~OException    ();

   virtual
      PSZ isOfType   () const;

   inline ULONG
          severity   () { return(state); }

   virtual
      void viewError () = 0;
};



#endif // OEXCEPTION_INCLUDED

// end of source
