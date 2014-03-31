// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OApp.hpp


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OApp.hpp 1.1 1996/08/12 00:01:08 B.STEIN Release $

#ifndef OAPP_INCLUDED
  #define OAPP_INCLUDED


#ifndef OPMINIT_INCLUDED
  #include <OPMinit.hpp>
#endif

#ifndef OAPPBASE_INCLUDED
  #include <OAppBase.hpp>
#endif

#ifndef OCOMMAND_INCLUDED
  #include <OCommand.hpp>
#endif


// classes


typedef class OApp *pOApp;

class __CPP_EXPORT__ OApp
  : public OAppBase
    
{
 private:
   OCommandHandler    OCMD_NullHandler;

 protected:
   QMSG               qmsg;
   OPMinit            init;

 public:

   static pOApp       currentOApp;


      OApp           (ULONG queueSize = 10);      
      OApp           (const ULONG num,
                      CHAR *Parms[],
                      ULONG queueSize = 10);

   virtual
      ~OApp          ();

   virtual
      PSZ isOfType   () const; 

   virtual
      void run       ();       // enhanced message loop

   HAB
      anchor         ();

   HMQ
      mqueue         ();   

   virtual BOOL
      QuitPosted     (),       // a window posted a quit message,  default is ret FALSE = to quit
      TasklistKill   (),       // user tried to close a window from the tasklist,  default is ret FALSE = to quit
      ShutdownPosted ();       // system posted shutdown-message,  default is ret FALSE = to quit


   pOCommandHandler
      NullHandler    ();


   static OApp&
      current        ();
 
   // although public this function is for internal use only and must not be used !!
 
   static BOOL
      OCMDTrace      (const HWND hwnd,
                      const ULONG msg,
                      const MPARAM mp1, 
                      const MPARAM mp2);

// overloaded from OAppBase

   virtual void 
      forceQuit      (),      // force OApp::run() to return
      Shutdown       (),      // force PM-Shutdown
      Reboot         ();      // force DOS-Shutdown and reboot
};


#endif // OAPP_INCLUDED


// end of source
