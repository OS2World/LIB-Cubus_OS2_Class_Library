// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// lOString.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/clOString.cpp 1.50 1996/08/11 23:49:37 B.STEIN Release $


#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>


#if defined(__EMX__)
  template class OList<OString>;
  template class OConstIterator<OString>;
#endif


lOString::lOString()
 : OList<OString>(TRUE)
 {}

lOString::~lOString()
 {}

PSZ lOString::isOfType() const
{ 
 return("List<OString>"); 
}


lOString& lOString::operator << (PSZ string)
{
 OString str(string);
 add(str);
 return(*this);
}

lOString& lOString::operator << (OString& string)
{
 OString str(string);
 add(str);
 return(*this);
}

lOString& lOString::operator << (OString* string)
{
 pOString str;

 if (string) {
   str = new OString(*string);
   add(str);
   delete str; }
 return(*this);
}

void lOString::print()
{
 allElementsDo(printer);
}


void lOString::lOStringPrint::applyToElement(const OString *elem) const
{
 if ((elem) && (elem->getText()))
    cout << elem->getText() << endl;
}


// end of source
