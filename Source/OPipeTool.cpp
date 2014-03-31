// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipeTool.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OPipeTool.cpp 1.50 1996/08/11 23:49:27 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OPipeTool.hpp>

#if defined(__EMX__)
  template class OThread<OPipeTool>;
#endif


OPipeTool::OPipeTool(PCSZ exename, PCSZ parms, 
                     const ULONG sessionType,
                     const ULONG pipeBuffer)
  : printer(this, &OPipeTool::printout, 8192, FALSE),
    bufferSize(pipeBuffer),
    pipe(pipeBuffer),
    readBuffer(pipeBuffer),
    sType(sessionType),
    childName(exename),
    childParms(parms),
    childPID(0),
    childSID(0)  
 {}


OPipeTool::~OPipeTool()
 {}


PSZ OPipeTool::isOfType() const
{ 
 return("OPipeTool"); 
}


void OPipeTool::detachChild()
{
 APIRET    rc;
 STARTDATA StartData;
 HFILE     hfNewStdOut = -1, 
           hfNewStdErr = -1,
           hfStdOut = 1, 
           hfStdErr = 2;
 OString   Title("Spawned: ");

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

 memset(&StartData, 0, sizeof(STARTDATA));
 StartData.Length      = sizeof(STARTDATA);
 StartData.Related     = SSF_RELATED_CHILD;
 StartData.FgBg        = SSF_FGBG_BACK;
 StartData.TraceOpt    = SSF_TRACEOPT_NONE;
 StartData.PgmTitle    = Title;
 StartData.PgmName     = childName;
 StartData.PgmInputs   = (PBYTE) childParms.getText();
 StartData.InheritOpt  = SSF_INHERTOPT_PARENT;
 StartData.SessionType = sType;
 StartData.PgmControl  = SSF_CONTROL_INVISIBLE;

 rc = DosStartSession(&StartData, &childSID, &childPID);

// Get back original handles
 DosDupHandle(hfNewStdOut, &hfStdOut);
 DosDupHandle(hfNewStdErr, &hfStdErr);
 DosClose(hfNewStdOut);
 DosClose(hfNewStdErr);

 if (rc != 0)
   throw OVioException("Spawn failed.", rc);
}


void OPipeTool::stopChild()
{
 APIRET rc;

 if (!childPID)
   return;

 if ((rc = DosKillProcess(DKP_PROCESS, childPID)) != 0)
   throw OVioException("Killing spawnded process failed.", rc);
 
 childSID = 0;
 childPID = 0;
}

void OPipeTool::printout()
{
 while(pipe) {
   if (pipe.getline(readBuffer, bufferSize))
      cout << (PSZ)readBuffer << endl; }
}


// end of source
