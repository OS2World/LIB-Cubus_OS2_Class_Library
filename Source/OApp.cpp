// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OApp.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OApp.cpp 1.50 1996/08/11 23:49:06 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OCommand.hpp>
#include <OApp.hpp>


// OApp


pOApp OApp::currentOApp = (pOApp)NULL;


OApp::OApp(ULONG queueSize) 
  : init(queueSize)
{
 if (!OApp::currentOApp)
   OApp::currentOApp = this;
}


OApp::OApp(const ULONG num, CHAR *Parms[], ULONG queueSize)
  : OAppBase(num, Parms),
    init(queueSize)
{
 if (!OApp::currentOApp)
   OApp::currentOApp = this;
}


OApp::~OApp() 
{
 if (OApp::currentOApp == this)
   OApp::currentOApp = NULL;
}


PSZ OApp::isOfType() const
{ 
 return("OApp"); 
}


OApp& OApp::current()
{
 if(OApp::currentOApp)
   return(*OApp::currentOApp);
 else
   throw OVioException(OCL::error(131), 0);
}


HAB OApp::anchor()
{
 return(init.anchor());
}


HMQ OApp::mqueue()
{
 return(init.anchor());
}


BOOL OApp::OCMDTrace(const HWND hwnd,
                     const ULONG msg,
                     const MPARAM mp1,
                     const MPARAM mp2)
{
 pOCommandHandler pcm = (pOCommandHandler) WinQueryWindowULong(hwnd, QWL_USER);

 if (pcm) {
   pcm->hwnd = hwnd;
   return(pcm->OCommand(msg, mp1, mp2)); }
 else
   return(FALSE);
}


BOOL OApp::QuitPosted() 
{
 return(FALSE); 
} 

BOOL OApp::TasklistKill() 
{
 return(FALSE); 
}


BOOL OApp::ShutdownPosted() 
{
 return(FALSE); 
}


// message loop

void OApp::run()
{
 BOOL dispatched = FALSE;

 while(TRUE)
   {
    if (!WinGetMsg(init.anchor(), &qmsg, NULLHANDLE, 0, 0))
     {
      if (qmsg.hwnd == NULLHANDLE) {
        if (!ShutdownPosted()) return; }
      else if (qmsg.hwnd == HWNDFROMMP(qmsg.mp2)) {
        if (!TasklistKill()) return; }
      else if (!QuitPosted())
        return;
      else
        dispatched = TRUE;
     }
    else 
      dispatched = FALSE;

    if (!dispatched) 
      WinDispatchMsg(init.anchor(), &qmsg);    // default processing
   }
}

void OApp::forceQuit()
{
 WinPostMsg(NULLHANDLE, WM_QUIT, NULL, NULL);
}


pOCommandHandler OApp::NullHandler()
{
 return(&OCMD_NullHandler);
}


void OApp::Shutdown()
{
 WinShutdownSystem(init.anchor(), init.mqueue());
}


void OApp::Reboot()
{
 HFILE  hf;
 ULONG  dummy;

 if (!DosOpen("DOS$", &hf, &dummy, 0L, FILE_NORMAL, FILE_OPEN,
              OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYNONE | OPEN_FLAGS_FAIL_ON_ERROR, 0L))
  {
   ULONG ulParmLength = 0;
   ULONG ulDataLength = 0;

   WinBroadcastMsg(HWND_DESKTOP, WM_CLOSE, NULL, NULL, BMSG_SEND | BMSG_DESCENDANTS);
   SyncDisks();
   DosSleep(2000);
   DosBeep(100, 1000);
   DosShutdown(0L);
   DosDevIOCtl(hf, 0xd5, 0xab,           // Reboot
               NULL, 0L, &ulParmLength,
               NULL, 0L, &ulDataLength );
   DosClose(hf);
  }
}


// end of source
