// OCL - OS/2 Class Library
// (c) Cubus 1996
// All Rights Reserved
// ORiffPlay.hpp


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


// $Header: W:/Projects/OCL/Include/rcs/ORiffPlay.hpp 1.50 1996/08/11 23:47:29 B.STEIN Release $

#ifndef ORIFFPLAY_INCLUDED
  #define ORIFFPLAY_INCLUDED


#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif

#ifndef ODYNAMICLIB_INCLUDED
  #include <ODynamicLib.hpp>
#endif


// classes



extern "C"
{
typedef ULONG  (EXPENTRY *mci_play_file)
               (HWND, PSZ, ULONG, PSZ, HWND);
typedef ULONG  (EXPENTRY *mci_play_resource)
               (HWND, HMODULE, ULONG, ULONG, ULONG, PSZ, HWND);
typedef ULONG  (APIENTRY *mci_get_error)
               (ULONG, PSZ, USHORT);
}


typedef class ORiffPlay *pORiffPlay;

class __CPP_EXPORT__ ORiffPlay
{
 public:

    enum  RiffType
      {
       midi            = 100,    // RT_RMID
       riff            = 101,    // RT_RIFF
       wave            = 102,    // RT_WAVE
       avi             = 103,    // RT_AVI
       avs             = 104     // RT_AVS
      }; 

    enum  PlayType
      {
       wait            = 0,      // wait for completition 
       ownerIsParent   = 0x0001, // digital and overlay                 
       stopActive      = 0x0002, // stop playing whatever is playing    
       asyncRendezvous = 0x0004, // play and return immediately         
       rendezvous      = 0x0008, // wait til prev is finished then play 
       async           = 0x0010, // no syncup will be done              
       repeat          = 0x0020, // repeat 
       stopOnSuspend   = 0x0040  // stop when suspended 

      };

 
    ORiffPlay              ();
                      
    ORiffPlay              (PSZ soundLibrary);

    ORiffPlay              (ODynamicLib& soundLibrary);

    virtual
      ~ORiffPlay           ();  

   virtual PSZ
      isOfType             () const;   

   void
      play                 (PSZ   waveFileName,         // load from RIFF file
                            ORiffPlay::PlayType playType),

      play                 (ULONG soundID,              // load from exe or lib
                            ORiffPlay::RiffType resType,
                            ORiffPlay::PlayType playType),

      stop                 ();

// strictly for internal use

  private:

    OString                  waveFile;
    ULONG                    waveID;
    ULONG                    waveType;
    ODynamicLib              waveLibrary;

    static mci_play_file     mci_pf;
    static mci_play_resource mci_pr;
    static mci_get_error     mci_err;
    static pODynamicLib      mciapi;
    static pODynamicLib      mdmapi;

    void
      resolve                (),
      playWave               (ORiffPlay::PlayType playType);

};



#endif // ORIFFPLAY_INCLUDED


// end of source
