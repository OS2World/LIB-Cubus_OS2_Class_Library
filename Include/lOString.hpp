// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// lOString.hpp

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

// $Header: W:/Projects/OCL/INCLUDE/rcs/lOString.hpp 1.1 1996/08/12 00:01:17 B.STEIN Release $

#ifndef LOSTRING_INCLUDED
  #define LOSTRING_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


#ifndef OLIST_INCLUDED
  #include <OList.hpp>
#endif

typedef class lOString      *plOString;


class __CPP_EXPORT__ lOString 
  : public OList<OString>
{
 private:

    class __CPP_EXPORT__ lOStringPrint
     : public OConstIterator<OString>
     {
      public:
        void applyToElement(const OString* elem) const;
     };

    lOStringPrint   printer;

 public:

    lOString        ();

  virtual
    ~lOString       ();

  virtual
    PSZ isOfType    () const;

  lOString
    &operator <<    (PSZ string),
    &operator <<    (OString& string),
    &operator <<    (OString* string);

  virtual
    void print      ();
};



#endif // LOSTRING_INCLUDED


// end of source
