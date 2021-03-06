// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OXcptBase.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OXcptBase.hpp 1.50 1996/08/11 23:47:36 B.STEIN Release $

#ifndef OXCPTBASE_INCLUDED
  #define OXCPTBASE_INCLUDED

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


typedef class OXcptBase *pOXcptBase;

typedef EXCEPTIONREGISTRATIONRECORD OXCPTRECORD;


class __CPP_EXPORT__ OXcptBase
  : virtual public OCLObject
{
 protected:
  OXCPTRECORD         *record;
  BOOL                killMsg;

 public:
  ULONG               times;

  OXcptBase           (BOOL killMessages); // provide detailed information about kill cases

  virtual
     ~OXcptBase       ();

  virtual
     PSZ isOfType     () const;

  virtual BOOL
     trapTrace        () = 0,
     killTrace        () = 0,
     handler          (PEXCEPTIONREPORTRECORD report,
                       OXCPTRECORD            *record,
                       CONTEXTRECORD          *context,
                       PVOID                  pargs);

  virtual void
     exceptionMessage (PCSZ msg) = 0;

  BOOL
     setHandler       (OXCPTRECORD& regRecord),
     unsetHandler     ();


// for internal use, do not change

  static ULONG
     OXCPT_CATCH      (EXCEPTIONREPORTRECORD *report,
                       OXCPTRECORD *record,
                       CONTEXTRECORD *context,
                       PVOID pargs);

  static
     OXcptBase        *currentHandler;
};


extern "C"
{
 PSZ  __CPP_EXPORT__ 
    except_printf        (const char *format, ...); 
 void __CPP_EXPORT__
    except_print_context (OString& msg, PCONTEXTRECORD cont); 
}

#define XCPT_CPP_EXCEPTION 0x00020000


#endif // OXCPTBASE_INCLUDED

// end of source
