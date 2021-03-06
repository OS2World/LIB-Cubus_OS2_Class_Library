// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// scanfcl.cpp
// scanner classes


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

// $Header: W:/Projects/OCL/Source/rcs/OScan.cpp 1.50 1996/08/11 23:49:30 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OFcl.hpp>

// members of scan


OScanFcl::OScanFcl()
{
 setCheck(FALSE, FALSE); 
}

OScanFcl::~OScanFcl() 
{
 good.reset(); 
}


PSZ OScanFcl::isOfType() const
{ 
 return("OScanFcl"); 
}


BOOL OScanFcl::init(PCSZ FileName, PCSZ toScan)
{
 Filename << FileName;
 return(check(toScan));
}


void OScanFcl::init(PCSZ FileName)
{
 Filename << FileName;
}


BOOL OScanFcl::check(PCSZ string)
{
 OFuzzSearch  *searcher = NULL;
 BOOL         retValue;

 ToScan << string;;

 searcher = new OFuzzSearch(Filename.getText(), ToScan.getText()); 
 searcher->startSearch();

 retValue = (searcher->matches.numberOfElements() != 0) ? TRUE : FALSE;

 ToScan << (PSZ) NULL; 
 delete searcher;

 return(retValue);  
}


void OScanFcl::checkFiles(PCSZ text)
{
 pOString temp = files.getFirst();

 while((temp) && (!stopASAP))
  {
   init(temp->getText());
   if (check(text))
     good << temp->getText();
   temp = files.getNext(); 
  }
}

// end of source
