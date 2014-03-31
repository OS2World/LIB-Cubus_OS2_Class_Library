// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OCreate.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OCreate.cpp 1.50 1996/08/11 23:49:12 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OCreate.hpp>
#include <OMessage.hpp>

// member functions

OCreate::OCreate() : Created((HOBJECT)NULL)
  {}

OCreate::~OCreate()
  {}

PSZ OCreate::isOfType() const
{ 
 return("OCreate"); 
}


void OCreate::Create()
{
 if (!File)
   return;
 
 if (!Location)
   Location << (PSZ) "<WP_DESKTOP>";

 
 if (is(".INF"))
   CreateBook();
 else if (is(".EXE") | is(".COM") |
           is(".BAT") | is(".CMD"))
   CreateExe();
 else
   CreateDoc();
 Title << (PSZ)NULL;
 File << (PSZ)NULL;
}


void OCreate::CreateBook()
{
 PSZ Setup = new CHAR[3*CCHMAXPATH];

 if (!Title)
  {
#ifndef __IBMCPP__
   ifstream file((PCSZ)File);
#else
   ifstream file(File);
#endif
   PSZ BTitle = new CHAR[50];
   BTitle[0] = '\0';
   file.seekg(107L);
   file.getline(BTitle, 48);
   if (strlen(BTitle) > 0)
     Title << BTitle;
   else
     Title << File;
   file.close();
   delete[] BTitle;
  }
 
 sprintf(Setup, "EXENAME=VIEW.EXE;PARAMETERS=%s", File.getText());
 Created = WinCreateObject("WPProgram", Title,
                           Setup, Location, CO_REPLACEIFEXISTS);
 delete[] Setup;
}


void OCreate::CreateExe()
{
 PSZ Setup = new CHAR[2*CCHMAXPATH];
 PSZ Dir   = new CHAR[CCHMAXPATH];

 strcpy(Dir, File);
 strcpy(strrchr(Dir, '\\'), "");

 if (!Title)
   Title << File;

 sprintf(Setup, "EXENAME=%s;STARTUPDIR=%s", File.getText(), Dir);
 Created = WinCreateObject("WPProgram", Title,
                           Setup, Location, CO_REPLACEIFEXISTS);
 delete[] Setup;
 delete[] Dir;
}


void OCreate::CreateDoc()
{
 PSZ Setup = new CHAR[2*CCHMAXPATH];

 if (!Viewer)
   Viewer << (PSZ) "E.EXE";

 Title << OCL::error(38);
 Title + File;
 sprintf(Setup, "EXENAME=%s;PARAMETERS=\"%s\"", Viewer.getText(), File.getText());
 Created = WinCreateObject("WPProgram", Title,
                           Setup, Location, CO_REPLACEIFEXISTS);
 delete[] Setup;
}


BOOL OCreate::is(PCSZ Ext) 
{
 return(strstr(strupr(File), Ext)!=NULL); 
}


// end of source
