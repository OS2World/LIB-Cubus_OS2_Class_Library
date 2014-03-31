// OCL - OS/2 Class Library
// (c) Cubus 1996
// All Rights Reserved
// OCLVer.cpp

// this is the OCL Version Logo
// we place the template stuff here

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

// $Header: W:/Projects/OCL/Source/rcs/OCL.cpp 1.50 1996/08/11 23:49:09 B.STEIN Release $


#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMessage.hpp>


OString OCL::transport;
OString OCL::MSGFILE("OCL0001.MSG");


OString& OCL::Version()
{
 return(OCL::Version(OCL::transport));
}


OString& OCL::Version(OString& str)
{
 OMessage copyright(OCL_COPYRIGHT, OCL::MSGFILE);

#ifdef __BCPLUSPLUS__
   OMessage compiler(OCL_BORLAND, OCL::MSGFILE);
#elif __WATCOM_CPLUSPLUS__
   OMessage compiler(OCL_WATCOM, OCL::MSGFILE);
#elif ((__IBMCPP__) && (__IBMCPP__ == 300))
   OMessage compiler(OCL_VA, OCL::MSGFILE);
#elif __IBMCPP__
   OMessage compiler(OCL_CSET, OCL::MSGFILE);
#elif __HIGHC__
   OMessage compiler(OCL_METAWARE, OCL::MSGFILE);
#elif __EMX__
   OMessage compiler(OCL_EMX, OCL::MSGFILE);
#endif  
 
 str << OMessage(OCL_VER_MSG, OCL::MSGFILE, compiler, copyright).getText();
 return(str);
}


OString& OCL::error(ULONG x)
{
 return(OCL::transport << OMessage(x, OCL::MSGFILE).getText());
}


OString& OCL::apierror(ULONG x, APIRET rc)
{
 OString apimessage(OMessage((ULONG)rc).getText());
 
 return(OCL::transport <<  OMessage(x, OCL::MSGFILE, apimessage.getText()).getText());
}


// Enable/Disable DialogItems

void OCL::disableDialogItem(HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount, ULONG ulStyle)
{
ULONG  usTemp;

if(ulStyle&WS_DISABLED)
    for(usTemp=0; usTemp<usItemCount; usTemp++)
       WinEnableWindow(WinWindowFromID(hwnd, usDialogIDs[usTemp]), FALSE);
else
    for(usTemp=0; usTemp<usItemCount; usTemp++)
       WinEnableWindow(WinWindowFromID(hwnd, usDialogIDs[usTemp]), TRUE);
if(ulStyle&WS_VISIBLE)
    for(usTemp=0; usTemp<usItemCount; usTemp++)
       WinSetWindowPos(WinWindowFromID(hwnd, usDialogIDs[usTemp]), 0, 0, 0, 0, 0, SWP_SHOW);
else
    for(usTemp=0; usTemp<usItemCount; usTemp++)
       WinSetWindowPos(WinWindowFromID(hwnd, usDialogIDs[usTemp]), 0, 0, 0, 0, 0, SWP_HIDE);
return;
}



// DialogItem unsichtbar machen


void OCL::hideDialogItem(HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount)
{
 ULONG  usTemp;

 for(usTemp=0; usTemp<usItemCount; usTemp++)
   WinSetWindowPos(WinWindowFromID(hwnd, usDialogIDs[usTemp]), 0, 0, 0, 0, 0, SWP_HIDE);
 return;
}


// DialogItem sichtbar machen

void OCL::showDialogItem(HWND hwnd, ULONG usDialogIDs[], ULONG usItemCount)
{
 ULONG  usTemp;

 for(usTemp=0; usTemp<usItemCount; usTemp++)
   WinSetWindowPos(WinWindowFromID(hwnd, usDialogIDs[usTemp]), 0, 0, 0, 0, 0, SWP_SHOW);
 return;
}


// Desktop-ID wiederherstellen

BOOL OCL::saveID(PCH DESK)
{
 HOBJECT hObject;

 hObject=WinQueryObject((PCH) DESK);
 if (hObject==NULLHANDLE)
   return(FALSE);
 if ((WinSetObjectData(hObject, "OBJECTID=<WP_DESKTOP>")==TRUE))
   return(TRUE);
 else
   return(FALSE);
}


void OCL::disableControls(HWND hwnd, ULONG usDialogIDs[], ULONG count)
{
 disableDialogItem(hwnd, usDialogIDs, count/sizeof(ULONG), WS_VISIBLE | WS_DISABLED);
}

void OCL::enableControls(HWND hwnd, ULONG usDialogIDs[], ULONG count)
{
 disableDialogItem(hwnd, usDialogIDs, count/sizeof(ULONG), WS_VISIBLE | 0);
}

void OCL::hideControls(HWND hwnd, ULONG usDialogIDs[], ULONG count)
{
 hideDialogItem(hwnd, usDialogIDs, count/sizeof(ULONG));
}

void OCL::showControls(HWND hwnd, ULONG usDialogIDs[], ULONG count)
{
 showDialogItem(hwnd, usDialogIDs, count/sizeof(ULONG));
}


APIRET OCL::startSession(STARTDATA *SessionData)
{
 ULONG       SessID;
 PID            Pid;
 CHAR         ObjBuf[100];
 APIRET       rc;
 STARTDATA StartData;

 memset(&StartData, 0, sizeof(StartData));

 StartData.Length = sizeof(STARTDATA);
 if (SessionData->Related == 0)
    StartData.Related = SSF_RELATED_INDEPENDENT;
 else
    StartData.Related = SessionData->Related;
 if (SessionData->FgBg == 0)
    StartData.FgBg = SSF_FGBG_FORE;
 else
    StartData.FgBg = SessionData->FgBg;
 StartData.TraceOpt = SSF_TRACEOPT_NONE;
 StartData.PgmTitle = SessionData->PgmTitle;
 StartData.PgmName = SessionData->PgmName;
 StartData.TermQ = 0;
 StartData.Environment = 0;
 StartData.InheritOpt = SSF_INHERTOPT_PARENT;
 if (SessionData->SessionType == 0)
    StartData.SessionType = SSF_TYPE_DEFAULT;
 else
    StartData.SessionType = SessionData->SessionType;
 StartData.IconFile = 0;
 StartData.PgmHandle = 0;
 if (SessionData->PgmControl == 0)
    StartData.PgmControl = SSF_CONTROL_VISIBLE;
 else
    StartData.PgmControl = SessionData -> PgmControl;
 StartData.InitXPos = 50;
 StartData.InitYPos = 50;
 StartData.InitXSize = 400;
 StartData.InitYSize = 400;
 StartData.Reserved = 0;
 StartData.ObjectBuffer = ObjBuf;
 StartData.ObjectBuffLen = 100;
 StartData.PgmInputs = SessionData->PgmInputs;

 rc = DosStartSession(&StartData, &SessID, &Pid);

 return (APIRET) rc;
}
// end of source
