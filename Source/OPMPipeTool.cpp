// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPMPipeTool.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OPMPipeTool.cpp 1.50 1996/08/11 23:49:26 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OPMPipeTool.hpp>

#if defined(__EMX__)
  template class OThread<OPMPipeTool>;
#endif


OPMPipeTool::OPMPipeTool(PCSZ exename, PCSZ parms, 
                         HWND notifyWindow,
                         const ULONG sessionType,
                         const ULONG pipeBuffer)
  : printer(this, &OPMPipeTool::printout, 8192, FALSE),
    bufferSize(pipeBuffer),
    pipe(pipeBuffer),
    readBuffer(pipeBuffer),
    sType(sessionType),
    childName(exename),
    childParms(parms),
    happ(NULLHANDLE),
    hwndNotify(notifyWindow)
 {}


OPMPipeTool::~OPMPipeTool()
 {}


PSZ OPMPipeTool::isOfType() const
{ 
 return("OPMPipeTool"); 
}


void OPMPipeTool::detachChild()
{
 HFILE       hfNewStdOut = -1, 
             hfNewStdErr = -1,
             hfStdOut = 1, 
             hfStdErr = 2;
 OString     Title("Spawned: ");
 PROGDETAILS Details;

// Duplicate handles

 DosDupHandle(hfStdOut, &hfNewStdOut);
 DosDupHandle(hfStdErr, &hfNewStdErr);

// Close existing handles for current process

 DosClose(hfStdOut);
 DosClose(hfStdErr);

// Redirect existing handles to new file
 DosDupHandle(pipe.ofh, &hfStdOut);
 DosDupHandle(pipe.ofh, &hfStdErr);

// start printout thread
 if (!printer.isRunning())
   printer.run(); 

// Start new session

 Title + childName;
 
 memset(&Details, 0, sizeof(PROGDETAILS));
 Details.Length          = sizeof(PROGDETAILS);
 Details.progt.progc     = sType;
 Details.progt.fbVisible = SHE_INVISIBLE;
 Details.pszTitle        = Title;
 Details.pszExecutable   = childName;
 Details.pszParameters   = childParms;
 Details.pszStartupDir   = "";
 Details.swpInitial.fl   = SWP_HIDE | SWP_DEACTIVATE;
 Details.swpInitial.hwndInsertBehind = HWND_TOP;
 Details.swpInitial.hwnd             = HWND_DESKTOP;
 
 happ = WinStartApp(hwndNotify, 
                    &Details, 
                    NULL, 
                    NULL, 
                    SAF_STARTCHILDAPP | SAF_INSTALLEDCMDLINE);

 WinSetWindowPos(hwndNotify, HWND_TOP, 0, 0, 0, 0, SWP_ACTIVATE);

// Get back original handles
 DosDupHandle(hfNewStdOut, &hfStdOut);
 DosDupHandle(hfNewStdErr, &hfStdErr);
 DosClose(hfNewStdOut);
 DosClose(hfNewStdErr);

 if (!happ)
   throw OVioException("Spawn failed.", 0);
}


void OPMPipeTool::stopChild()
{
 if (!happ)
   return;
 if (WinTerminateApp(happ))
   throw OVioException("Killing spawnded process failed.", 0);
}


void OPMPipeTool::setNotify(HWND notifyWindow)
{
 hwndNotify = notifyWindow;
}

void OPMPipeTool::setNotify(OFrame& notifyWindow)
{
 hwndNotify = notifyWindow.frame;
}

void OPMPipeTool::setNotify(pOFrame notifyWindow)
{
 hwndNotify = notifyWindow->frame;
}



void OPMPipeTool::printout()
 {}

// end of source
