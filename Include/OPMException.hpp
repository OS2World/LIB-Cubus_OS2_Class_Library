// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPMException.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OPMException.hpp 1.50 1996/08/11 23:47:24 B.STEIN Release $

#ifndef OPMEXCEPTION_INCLUDED
  #define OPMEXCEPTION_INCLUDED


#ifndef OEXCEPTION_INCLUDED
  #include <OException.hpp>
#endif

#ifndef OAPP_INCLUDED
 #include <OApp.hpp>
#endif

#ifndef OMSGS_INCLUDED
 #include <OMsgs.hpp>
#endif

#ifndef OMESSAGE_INCLUDED
 #include <OMessage.hpp>
#endif

 
typedef class OPMException *pOPMException;


class __CPP_EXPORT__ OPMException 
  : public OException
{
 public:
   OMsgs             exMsg; 
   OString           message;
   ULONG             errRes;


   OPMException     (const PSZ err,                     // supplied error message
                     const ULONG retcode = 0,           // an API return code
                     const ULONG severity = OException::unrecoverable,
                     const PSZ source = "",             // module name
                     const ULONG line = 0);             // source code line

   OPMException     (const ULONG errResource,           // resource id in stringtable
                     const ULONG retcode = 0,           // an API return code
                     const ULONG severity = OException::unrecoverable,
                     const HMODULE mod = NULLHANDLE,    // module to load errResource from
                     const PSZ source = "",             // module name
                     const ULONG line = 0);             // source code line

   OPMException     (const OPMException& ex);


   virtual
      ~OPMException ();

   virtual
      PSZ isOfType  () const;

   virtual void
      viewError     (); // error box with formatted error message
};


#define OThrowPM(a, b, c) (throw OPMException(a, b, c, __FILE__, __LINE__));


#endif // OPMEXCEPTION_INCLUDED


// end of source
