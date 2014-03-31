// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OHelp.cpp

// help for PM applications

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


// $Header: W:/Projects/OCL/Source/rcs/OHelp.cpp 1.50 1996/08/11 23:49:17 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OHelp.hpp>


OHelp::OHelp(const ULONG mainTable, const ULONG errorID)
  : table(mainTable), 
    errid(errorID), 
    isHlpAvail(FALSE) 
  {}


OHelp::~OHelp() 
{
 terminateHelp(); 
}


PSZ OHelp::isOfType() const
{ 
 return("OHelp"); 
}


OHelp& OHelp::terminateHelp()
{
 if (helpInstance)
   WinDestroyHelpInstance(helpInstance);
 return(*this);
}


OHelp& OHelp::initializeHelp(PSZ helpLibrary,
                             PSZ title,
                             const HWND associated)
{
 HELPINIT        HelpInit;

 if ((isHlpAvail) &&
     (associated == assoc))
    return(*this);
 else
    assoc = associated;

 HelpInit.cb                       = sizeof(HELPINIT);
 HelpInit.ulReturnCode             = 0;
 HelpInit.pszTutorialName          = (PSZ)NULL;
 HelpInit.phtHelpTable             = (PHELPTABLE)MAKEULONG(table, 0xFFFF);
 HelpInit.hmodHelpTableModule      = NULLHANDLE;
 HelpInit.hmodAccelActionBarModule = NULLHANDLE;
 HelpInit.idAccelTable             = 0;
 HelpInit.idActionBar              = 0;
 HelpInit.pszHelpWindowTitle       = title;
 HelpInit.pszHelpLibraryName       = helpLibrary;
 HelpInit.fShowPanelId             = 0;

 helpInstance = WinCreateHelpInstance(OApp::current().anchor(), &HelpInit);

 if ((!helpInstance) || (HelpInit.ulReturnCode))
   throw OPMException(OCL::error(180), HelpInit.ulReturnCode);

 isHlpAvail = (BOOL) WinAssociateHelpInstance(helpInstance, associated);

 if(!isHlpAvail)
   throw OPMException(OCL::error(181), 0);

 return(*this);
}



OHelp& OHelp::helpRequest(const ULONG id)
{
 if(!isHlpAvail)
   throw OPMException(OCL::error(182), 0);

 switch(id)
   {
    case help:
      WinSendMsg(helpInstance, HM_DISPLAY_HELP, NULL, NULL);
      break;

    case general:
      WinSendMsg(helpInstance, HM_GENERAL_HELP, NULL, NULL);
      break;

    case keys:
      WinSendMsg(helpInstance, HM_KEYS_HELP, NULL, NULL);
      break;

    case index:
      WinSendMsg(helpInstance, HM_HELP_INDEX, NULL, NULL);
      break;

    case contents:
      WinSendMsg(helpInstance, HM_HELP_CONTENTS, NULL, NULL);
      break;

    default:
      WinSendMsg(helpInstance, HM_DISPLAY_HELP, MPFROMSHORT(id), HM_RESOURCEID);
      break;
   }

 return(*this);
}


// end of source
