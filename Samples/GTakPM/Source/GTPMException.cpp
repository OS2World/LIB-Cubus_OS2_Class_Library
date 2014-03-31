// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMException.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMException.cpp 1.50 1996/08/11 23:48:07 B.STEIN Release $

#include "..\Source\GTakPM.hpp"


// default exception class
// the error message is retrieved from the application resources
// assume non-fatal error
// these exceptions are caught by the catch-blocks in OXApp::run

GTPMException::GTPMException(const ULONG errResource,
                             const ULONG severity)
  : OPMException(errResource, 0, severity)
  {}

GTPMException::~GTPMException()
  {}



// implementation of system exception handling

SystemHandler::SystemHandler()
 : OXcptPM(FALSE) 
 {}

SystemHandler::~SystemHandler()
 {}

BOOL SystemHandler::killTrace()
{
 OMsgs   msg;
 OString Title(30);
 OString Question(100);

 msg.loadString(APP_TITLE, 30, Title);
 msg.loadString(SURE_TO_EXIT, 100, Question);
 if (WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, Question, Title,
                   GTPM_ICO, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON1)==MBID_YES)
    WinPostMsg(NULLHANDLE, WM_QUIT, (MPARAM)0, (MPARAM)100);
 return(TRUE);    // continue by default 
}


BOOL SystemHandler::trapTrace()  
{
 return(FALSE);   // abort after viewing the exception message
}


// end of source
