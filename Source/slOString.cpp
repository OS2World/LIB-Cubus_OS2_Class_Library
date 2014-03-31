// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// slOString.cpp

// String Functions sorted String list


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

// $Header: W:/Projects/OCL/Source/rcs/slOString.cpp 1.50 1996/08/11 23:49:38 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <slOString.hpp>

#if defined(__EMX__)
  template class OSortedList<OString>;
#endif


slOString::slOString() 
  : OSortedList<OString>(TRUE)
  {}

slOString::~slOString() 
  {}

PSZ slOString::isOfType() const
{ 
 return("slOString"); 
} 


slOString& slOString::operator << (PCSZ string)
{
 OString str(string);
 add(str);
 return(*this);
}

slOString& slOString::operator << (OString& string)
{
 return(*this << string.getText());
}


slOString& slOString::operator << (pOString string)
{
 pOString str;

 if (string) {
   str = new OString(string->getText());
   add(str);
   delete str; }
 return(*this);
}


BOOL slOString::isLess(const OString *first, const OString *second)
{
 if (!first)
   return(TRUE);
 else if (!second)
   return(FALSE);
 else
   return(strcmpi(first->getText(), second->getText()) <= 0);
}


// end of source
