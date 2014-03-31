// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMApp.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMApp.cpp 1.50 1996/08/11 23:48:06 B.STEIN Release $


#include "..\Source\GTakPM.hpp"

pGTPMApp GTPMApp::GTakPM = NULL;


GTPMApp::GTPMApp(const ULONG num, CHAR *parms[])
  : OXApp(num, parms),
    waitThread(this, &GTPMApp::wait, 8192, FALSE)
{
 OLogo       *logo = NULL;
 GTPMWin     *applicationWindow = NULL;

 GTPMApp::GTakPM = this;

 waitThread.run();              // start logo timer

 try
   {
    logo = new OLogo(NULLHANDLE, GTPM_LOGO, 300, 225);
    logo->showLogo(0);
    applicationWindow = new GTPMWin;
   }

 catch(OPMException &ex)
   {
    ex.viewError();
    throw ex;
   }
 
 if (logo) {
   waitThread.waitFor();        // show logo min. 2 sec. 
   delete logo; }               // destroy logo

 applicationWindow->showFrame();
}   


GTPMApp::~GTPMApp()
{
 GTPMApp::GTakPM = NULL;
}


void GTPMApp::initArgs(PCSZ argStr)
{
 return;
}


void GTPMApp::wait()
{
 DosSleep(2000);
}



// overridden members of OApp


BOOL GTPMApp::TasklistKill()   // deny task list kill and continue
{
 OMsgs msg;

 msg.error(APP_TITLE, DENY_TASK_KILL);
 return(TRUE);   
}



BOOL GTPMApp::ShutdownPosted()
{
 return(FALSE);
}


// end of source
