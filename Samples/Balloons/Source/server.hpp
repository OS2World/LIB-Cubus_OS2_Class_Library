// Server.hpp (SERVER.EXE)
// common header


#define INCL_WIN
#define INCL_DOS

#include <ocl.hpp>
#include <OApp.hpp>
#include <OPipeSvr.hpp>
#include <ONSem.hpp>
#include <OSlider.hpp>
#include <OMsgs.hpp>
#include <OBook.hpp>
#include <OPMException.hpp>


#include "..\Source\Balloons.hpp"
#include "..\Source\Server.h"



// first page in book

typedef class CtrlPanel *pCtrlPanel;

class CtrlPanel 
   : public OBookPage
{
 public:
 
   CtrlPanel()
     : OBookPage("Control Panel", "Control Panel",
                 ID_CONTROL, CONTROL_TXT1, FALSE, BKA_MAJOR)
     {}

   ~CtrlPanel() {}
   virtual PSZ isOfType() const { return("CtrlPanel");  } 

   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// second and third page in Book

typedef class NumSpeedControl *pNumSpeedControl;

class NumSpeedControl
   : public OBookPage
{
 private:
   BOOL     isSpeedCtrl;
   OSlider  *slider;
 
 public:

   NumSpeedControl(BOOL speeder, PSZ Text)  // is it the speed page
    : OBookPage(Text, Text, ID_NUM, NUM_TXT1, FALSE, BKA_MAJOR),
      isSpeedCtrl(speeder)
     {}

   ~NumSpeedControl() 
     {
      if (slider) delete slider;
     }

   virtual PSZ isOfType() const { return("NumSpeedControl");  } 

   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};



// pipe server

typedef class BPipeServer *pBPipeServer;

class BPipeServer : public OPipeSvr
{
 public:
  BPipeServer();
  virtual ~BPipeServer();

  virtual PSZ isOfType() const { return("BPipeServer");  } 

  void OPipeCommand(PVOID pvData);
};


typedef class BalloonServer *pBalloonServer;

class BalloonServer
   : public OApp, 
     public OBook,
     public BPipeServer
{
 private:
  ONSem           *svrSem;
  CtrlPanel       firstPage;
  NumSpeedControl secondPage;
  NumSpeedControl thirdPage;

 public:
  PIPEMSG         pipeMessage;


  BalloonServer();
  virtual ~BalloonServer();
  virtual PSZ isOfType() const { return("BalloonServer");  } 

  void init();
  BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
