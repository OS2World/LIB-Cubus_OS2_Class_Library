// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OString.cpp


// class member functions


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

// $Header: W:/Projects/OCL/Source/rcs/OString.cpp 1.50 1996/08/11 23:49:31 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>


OString::OString()
{ 
 text = NULL; 
}


OString::OString(PCSZ iText)
{
 if (iText) {
   text = new CHAR[strlen(iText)+1];
   strcpy(text, iText); }
 else
   text = NULL;
}


OString::OString(const OString& String)
{
 if ((String.getText())) {
   text = new CHAR[strlen(String)+1];
   strcpy(text, String); }
 else
   text = NULL; 
}

OString::OString(const pOString String)
{
 if ((String) && (String->getText())) {
   text = new CHAR[strlen(String->getText())+1];
   strcpy(text, String->getText()); }
 else
   text = NULL; 
}



OString::OString(int iLength)
{
 text = new char[iLength+1]; 
 text[0] = '\0';
}


struct STRRES
{
 BYTE len;
 PSZ  str;
};

#pragma pack()


OString::OString(ULONG res, HMODULE mod)
{
 PVOID  resPtr  = NULL;
 STRRES *str    = NULL;

 if (DosGetResource(mod, RT_STRING, res / 16 + 1, &resPtr))
   *this << "ERROR";
 else
   {
    str = (STRRES*) resPtr + sizeof(USHORT);

    for(ULONG i = 0; i < 15; i++)
      {
       str +=  atoi((PCSZ)&str->len);
      }

    DosFreeResource(resPtr);
   }    
}


OString::~OString() 
{
 delete[] text;
 text = NULL; 
}


PSZ OString::isOfType() const
{ 
 return("OString"); 
}


PSZ OString::getText() const
{
 return  text; 
}


ULONG OString::length() const
{
 if (text)
   return(strlen(text));
 return(0);
}



int OString::compare(const OString&  s1, const OString& s2) const
{
 return strcmp(s1, s2);
}



OString& OString::leftCut(int Letter)
{
 PSZ tmp;
 PSZ newText;

 if ((!text) || ((tmp = strchr(text, Letter)) == NULL))
   return(*this);

 tmp++;
 if (!tmp) {
   delete text;
   text = NULL;
   return(*this); }

 newText = new CHAR[strlen(tmp)+1];
 strcpy(newText, tmp);
 delete text;
 text = newText; 
 return(*this);
}


OString& OString::rightCut(int Letter)
{
 PSZ newText;

 if ((!text) || (!strrchr(text, Letter)))
   return(*this);

 strcpy(strrchr(text, Letter), "");

 newText = new CHAR[strlen(text)+1];
 strcpy(newText, text);
 delete text;
 text = newText; 
 return(*this);
}


OString& OString::stripLeading(int Letter)
{
 PSZ   tmp = NULL;
 PSZ   newText = NULL;
 ULONG len;
 ULONG index = 0;

 if ((!text) || (Letter == '\0') || (!strchr(text, Letter)))
    return(*this);
 
 len = strlen(text);

 while(index <= len)
  {
   tmp = &text[index];
   if (!tmp) {
     delete text;
     text = NULL;
     return(*this); } 
   if (*tmp != Letter)
     break;
   index++;
  }
      
 newText = new CHAR[strlen(tmp)+1];
 strcpy(newText, tmp);
 delete text;
 text = newText; 
 return(*this);
}



OString& OString::stripTrailing(int Letter)
{
 PSZ   tmp;
 PSZ   newText;
 LONG  index;

 if ((!text) || (Letter == '\0') || (!strchr(text, Letter)))
    return(*this);
 
 index = strlen(text) - 1;

 while(index >= 0)
  {
   tmp = &text[index];
   if (!tmp) {
     delete text;
     text = NULL;
     return(*this); } 
   if (*tmp != Letter)
     break;
   else
     *tmp = '\0';
   index--;
  }
      
 newText = new CHAR[strlen(text)+1];
 strcpy(newText, text);
 delete text;
 text = newText; 
 return(*this);
}


OString& OString::replace(PCSZ string, PCSZ anOther)
{
 PSZ    tmp,
        tmpPtr, 
        cursor;

 if ((!text) || (!string) || (!anOther) || (!strstr(text, string)))  
   return(*this);

 cursor  = text;
 tmpPtr  = new CHAR[strlen(text)+1];
 tmp     = tmpPtr;

 strcpy(tmp, text);

 while(TRUE)
  {
   *strstr(strstr(text, tmp), string) = '\0';
   cursor = &strstr(tmp, string)[strlen(string)];
   *this + anOther + cursor;
   tmp = cursor;
   if (!strstr(tmp, string))
     break;
  }  

 delete tmpPtr;
 return(*this);
}



OString& OString::operator << (PCSZ string) 
{    // set or replace the string
 PSZ tmp = NULL;

 if (string) {
   tmp = new CHAR[strlen(string)+1];
   strcpy(tmp, string); }
 if (text)
   delete[] text;
 
 text = tmp;
 return(*this);
}


OString& OString::operator << (const pOString string) 
{
 if (string)
   return(*this << string->getText());
 return(*this);
}


OString& OString::operator <<   (INT     i)
{
 return(*this << (LONG) i);
}

OString& OString::operator <<   (UINT   ui)
{
 return(*this << (ULONG) ui);
}

OString& OString::operator <<   (LONG    l)
{
 OString buffer(32);

 sprintf(buffer.getText(), "%ld", l);
 return(*this << buffer.getText());
}

OString& OString::operator <<   (ULONG  ul)
{
 OString buffer(32);

 sprintf(buffer.getText(), "%lu", ul);
 return(*this << buffer.getText());
}

OString& OString::operator <<   (double db)
{
 OString buffer(32);

 sprintf(buffer, "%.*g", DBL_DIG, db);
 return(*this << buffer.getText());
}

OString& OString::operator +    (INT     i)
{
 return(*this + (LONG) i);
}

OString& OString::operator +    (UINT   ui)
{
 return(*this + (ULONG) ui);
}

OString& OString::operator +    (LONG    l)
{
 OString buffer(32);

 sprintf(buffer.getText(), "%ld", l);
 return(*this + buffer.getText());
}

OString& OString::operator +    (ULONG  ul)
{
 OString buffer(32);

 sprintf(buffer.getText(), "%lu", ul);
 return(*this + buffer.getText());
}

OString& OString::operator +    (double db)
{
 OString buffer(32);

 sprintf(buffer, "%.*g", DBL_DIG, db);
 return(*this + buffer.getText());
}

OString& OString::operator + (PCSZ string) 
{     // add String to the end of text
 if ((text) && (string)) {
   PSZ tmp = new CHAR[strlen(text)+strlen(string)+1];

   strcpy(tmp, text);
   strcat(tmp, string);
   *this << tmp;
   delete[] tmp; }
 return(*this);
}


OString& OString::operator + (const pOString string)
{
 if (string)
   return(*this + string->getText());
 return(*this);
} 


OString& OString::operator = (PCSZ string)
{
 *this << string;
 return(*this);
}



BOOL OString::operator == (PCSZ anOther)const 
{
 return (strcmp(text, anOther) == 0); 
}


BOOL OString::operator != (PCSZ anOther)const 
{
 return !(*this == anOther); 
}


BOOL OString::operator < (PCSZ anOther)const 
{
 return (strcmp(text, anOther) < 0); 
}


BOOL OString::operator > (PCSZ anOther)const 
{
 return (strcmp(text, anOther) > 0); 
}


BOOL OString::operator <= (PCSZ anOther)const 
{
 return !(*this > anOther); 
}


BOOL OString::operator >= (PCSZ anOther)const 
{
 return !(*this < anOther); 
}



istream& operator >> (istream& in, OString& s)
{
 PSZ Buf = new CHAR[CCHMAXPATH];

 in >> Buf;
 s << Buf;
 delete[] Buf;
 return(in);
}


istream& operator >> (istream& in, pOString s)
{
 return((s != NULL) ? (in >> *s) : in);
}


ostream& operator <<   (ostream& out, pOString s)
{
 if (s)
   out << s->getText();
 return(out);
}


// end of source
