// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OString.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OString.hpp 1.50 1996/08/11 23:47:31 B.STEIN Release $

#ifndef OSTRING_INCLUDED
  #define OSTRING_INCLUDED


#ifndef OCLOBJECT_INCLUDED
  #include <OCLObject.hpp>
#endif


// single text-line with unknown length
typedef class OString *pOString;

class __CPP_EXPORT__ OString
  : public OCLObject
{
 protected:
    PSZ               text;

 public:

    OString           ();
    OString           (PCSZ iText);
    OString           (const OString& String);
    OString           (const pOString String);
    OString           (INT iLength);

    virtual
       ~OString       ();

    virtual 
       PSZ isOfType   () const;

    virtual
       PSZ getText    () const;
 
    ULONG length      () const;

    int compare       (const OString& s1,
                       const OString& s2) const;

    OString
       &leftCut       (INT Letter),
       &rightCut      (INT Letter),
       &stripLeading  (INT Letter),
       &stripTrailing (INT Letter),
       &replace       (PCSZ string, PCSZ anOther),        
       &operator <<   (PCSZ  string),
       &operator <<   (const pOString string),
       &operator <<   (INT     i),
       &operator <<   (UINT   ui),
       &operator <<   (LONG    l),
       &operator <<   (ULONG  ul),
       &operator <<   (double db),
       &operator +    (PCSZ  string),
       &operator +    (const pOString string),
       &operator +    (INT     i),
       &operator +    (UINT   ui),
       &operator +    (LONG    l),
       &operator +    (ULONG  ul),
       &operator +    (double db),
       &operator =    (PCSZ  anOther);

    BOOL
       operator ==    (PCSZ anOther) const,
       operator !=    (PCSZ anOther) const,
       operator <     (PCSZ anOther) const,
       operator >     (PCSZ anOther) const,
       operator <=    (PCSZ anOther) const,
       operator >=    (PCSZ anOther) const;

    friend istream
       &operator >>   (istream& in, OString& s),
       &operator >>   (istream& in, pOString s);

    friend ostream
       &operator <<   (ostream& out, pOString s);

    inline
       operator char* () const { return((char*)text); }
};



#if ((defined OINCL_LOSTRING) || (defined OINCL_BASE))
  #include <lOString.hpp>
#endif


#ifdef OINCL_SLOSTRING
  #include <slOString.hpp>
#endif


#endif // OSTRING_INCLUDED


// end of source
