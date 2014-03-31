// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ORiffPlay.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/ORiffPlay.cpp 1.50 1996/08/11 23:49:30 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ORiffPlay.hpp>


mci_play_file     ORiffPlay::mci_pf  = NULL;
mci_play_resource ORiffPlay::mci_pr  = NULL;
mci_get_error     ORiffPlay::mci_err = NULL;
pODynamicLib      ORiffPlay::mciapi  = NULL;
pODynamicLib      ORiffPlay::mdmapi  = NULL;


ORiffPlay::ORiffPlay()
  : waveID       (0),
    waveType     (0)
{
 if (!OApp::currentOApp)
   throw OPMException(OCL::error(250), OException::unrecoverable);
 resolve();
}

   
ORiffPlay::ORiffPlay(PSZ soundLibrary)
  : waveID       (0),
    waveType     (0),
    waveLibrary  (soundLibrary)
{
 if (!OApp::currentOApp)
   throw OPMException(OCL::error(250), OException::unrecoverable);
 resolve();
}


ORiffPlay::ORiffPlay(ODynamicLib& soundLibrary)
  : waveID       (0),
    waveType     (0),
    waveLibrary  (soundLibrary.getLibHandle())
{
 if (!OApp::currentOApp)
   throw OPMException(OCL::error(250), OException::unrecoverable);
 resolve();
}


ORiffPlay::~ORiffPlay()
{
 stop();
}
  

PSZ ORiffPlay::isOfType() const
{
 return("ORiffPlay");
}


void ORiffPlay::play(PSZ waveFileName,
                     ORiffPlay::PlayType playType)
{
 waveFile << waveFileName;

 playWave(playType);
}


void ORiffPlay::play(ULONG soundID,
                     ORiffPlay::RiffType resType,
                     ORiffPlay::PlayType playType)
{
 waveID   = soundID;
 waveType = resType;

 playWave(playType);
}


void ORiffPlay::playWave(ORiffPlay::PlayType playType)
{
 APIRET            rc = 0;

 stop();

 if (!waveFile)
   rc = ORiffPlay::mci_pr(NULLHANDLE,
                          waveLibrary.getLibHandle(),
                          waveType,
                          waveID,
                          playType,
                          NULL,
                          NULLHANDLE);
 else
   rc = ORiffPlay::mci_pf(NULLHANDLE,
                          waveFile,
                          playType,
                          0, 0);

 if (rc != 0)
  {
   OString Buffer(CCHMAXPATH);

   ORiffPlay::mci_err(rc, Buffer, CCHMAXPATH);
   throw OPMException(OMessage(252, OCL::MSGFILE, Buffer), rc, OException::recoverable); 
  }
}


void ORiffPlay::stop()
{
 ORiffPlay::mci_pf(NULLHANDLE,
                   NULL,
                   ORiffPlay::stopActive, 0, 0);
}

// This member loads MCIAPI.DLL and MDM.DLL
// and resolves the entry points for the desired functions.
// This is because the OCL should not be linked against
// MMPM2.LIB.


void ORiffPlay::resolve()
{
 if (ORiffPlay::mciapi && ORiffPlay::mdmapi) // initialize only once!
   return;

 try
   {
    ORiffPlay::mciapi  = new ODynamicLib("MCIAPI");   
    ORiffPlay::mdmapi  = new ODynamicLib("MDM");   
    ORiffPlay::mci_pf  = (mci_play_file)
                         ORiffPlay::mciapi->queryFn("mciPlayFile");
    ORiffPlay::mci_pr  = (mci_play_resource)
                         ORiffPlay::mciapi->queryFn("mciPlayResource");
    ORiffPlay::mci_err = (mci_get_error)
                         ORiffPlay::mdmapi->queryFn("mciGetErrorString");
   }
 catch(OVioException &ex)
   {
    throw OPMException(OCL::error(251), OException::unrecoverable);
   } 
}


// end of source

