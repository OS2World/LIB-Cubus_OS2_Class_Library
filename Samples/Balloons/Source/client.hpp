// Balloons Game  (BALLOONS.EXE)
// OCL Sample
// balloons.hpp


#define INCL_WIN
#define INCL_PM
#define INCL_DOS


#include <ocl.hpp>
#include <OApp.hpp>
#include <OFrame.hpp>
#include <OPipeCli.hpp>
#include <ONSem.hpp>
#include <OMsgs.hpp>
#include <OPMException.hpp>


#include "..\Source\Balloons.hpp"
#include "..\Source\Client.h"


// definitions

#define LRAND(a)     ((LONG)rand() % a)


// structs

typedef struct _BALLPTL
{
 POINTL  Ptl;
 LONG    deltax;
 LONG    deltay;
} BALLPTL, *PBALLPTL;



class BPipeClient
   : public OPipeCli
{
 public:
   BPipeClient()
     : OPipeCli(sizeof(PIPEMSG)) {}

   virtual ~BPipeClient() {}
   virtual PSZ isOfType() const { return("BPipeClient");  } 

   void OPipeCommand(PVOID pvData);
};


typedef class BalloonClient *pBalloonClient;

class BalloonClient
   : public OApp, 
     public OFrame,
     private BPipeClient
{
 private:
   OThread<BalloonClient> drawThread;

 public:
   PIPEMSG                pipeMessage;
   BALLPTL                Balls[5];
   HBITMAP                hbm;
   ULONG                  BallCount;
   ULONG                  Speed;
   ULONG                  cx;
   ULONG                  cy;
   BOOL                   goDown;

   BalloonClient();
   ~BalloonClient() {}
   virtual PSZ isOfType() const { return("BalloonClient");  } 
 
   void init();
   void draw();
   void calculate(PBALLPTL pBptl);
   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
