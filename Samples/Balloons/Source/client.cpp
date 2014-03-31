// Client.cpp (Client.exe)
// Client Application Game for Balloons

#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Client.hpp"

#if defined(__EMX__)
  template class  OThread<BalloonClient>;
#endif


BalloonClient client;

// code

void main(void)
{
 try
  {
   client.init();
  }


 catch(OPMException err)
  {
   err.exMsg.error(err.errRes);
   _exit(1);
  }

 OApp::current().run();
}


BalloonClient::BalloonClient()
  : OFrame(ID_MAIN, FCF_STANDARD, CS_SAVEBITS | CS_SIZEREDRAW),
    goDown(FALSE),
    drawThread(this, &BalloonClient::draw)
{
 BallCount = 1;
 Speed = 6;
}


void BalloonClient::init()
{

 try
  {
   ONSem svrSem(BALL_SEM);              // Try to create Server semaphore.
   throw OPMException(NO_SERVER, 0);    // If it was succesful the real server isnt running.
  }

// ONSem::ONSem(...) throws an OVioException
// when the server semaphore  cannot be created.
// This is expected. So we catch it and
// continue processing.
 
 catch(OVioException err)
   {}              

 Buffer = &pipeMessage;
 if (!beginPiping(BALL_PIPE))
   throw OPMException(PIPE_FAILED, 0);

 createFrame("Balloon Client");

 sizepos.cx = 310;
 sizepos.cy = 310;
 setSizePosFrame(HWND_TOP, sizepos, SWP_SHOW | SWP_SIZE | SWP_ACTIVATE);
}




BOOL BalloonClient::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_CREATE:
     setWindowText("Balloons Client: Connected.");
     break;

   case WM_SIZE:
   case WM_ERASEBACKGROUND:
     hps = WinGetPS(hwnd);
     WinQueryWindowRect(hwnd, &rcl);
     WinFillRect(hps, &rcl, CLR_BLACK);
     cx = rcl.xRight - rcl.xLeft - 40;
     cy = rcl.yTop - rcl.yBottom - 40;
     WinReleasePS(hps);
     break;

   case WM_COMMAND:
     switch(SHORT1FROMMP(mp1)) {
        case ID_EXIT:
        case PIPE_STOP_CLIENT:
          goDown = TRUE;
          WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
          break;

        case PIPE_STOP_BALLOONS:
         goDown = TRUE;
         break;

        case PIPE_START_BALLOONS:
          if (!drawThread.isRunning()) {
            goDown = FALSE;
            WinSendMsg(hwnd, WM_ERASEBACKGROUND, NULL, NULL);
            drawThread.run(); }
          break;

        case PIPE_SERVER_EXIT:
          goDown = TRUE;
          WinSendMsg(hwnd, WM_ERASEBACKGROUND, NULL, NULL);
          setWindowText("Balloons Client: Disconnected.");
          break;

        case PIPE_SET_NUM:
          BallCount = SHORT1FROMMP(mp2);
          break;

        case PIPE_SET_SPEED:
          Speed = 6 - SHORT1FROMMP(mp2);
          break;
       } break;

   case WM_CLOSE:
    stopPiping();
    goDown = TRUE;
    if (drawThread.isRunning())
      drawThread.waitFor();
    forceQuit();
    break;

   default:
    return(OFrame::OCommand(msg, mp1, mp2));
  }
 return(TRUE);
}



void BalloonClient::draw()
{
 ULONG     i;
 ULONG     ulTemp = BallCount;
 DATETIME  Time;

 hps = WinGetPS(hwnd);
 hbm = GpiLoadBitmap(hps, NULLHANDLE, ID_BITMAP, 0L, 0L);
 memset(&Balls, 0, sizeof(BALLPTL)*5);
 WinReleasePS(hps);

 DosGetDateTime(&Time);
 srand(Time.hundredths);

 for (i = 0; i < 5  ; i++)
  {
   Balls[i].Ptl.x = LRAND(cx);
   Balls[i].Ptl.y = LRAND(cy);
   Balls[i].deltax = -1;
   Balls[i].deltay = 1;
  }


 drawThread.setPrty(PRTYC_REGULAR, 10);

 while(!goDown) {
   hps = WinGetPS(hwnd);
   if (ulTemp != BallCount) {
      WinQueryWindowRect(hwnd, &rcl);
      WinFillRect(hps, &rcl, CLR_BLACK);
      ulTemp = BallCount; }

   for (i = 0; ((i < BallCount) && (!goDown)); i++) {
      calculate(&Balls[i]);
      WinDrawBitmap(hps, hbm, NULL, &Balls[i].Ptl, 0L, 0L, DBM_IMAGEATTRS); }
   WinReleasePS(hps);
   DosSleep(20*Speed); }

 GpiDeleteBitmap(hbm);
}


void BalloonClient::calculate(PBALLPTL pBptl)
{
 if ((pBptl->Ptl.x + pBptl->deltax) > cx)
   pBptl->deltax = -pBptl->deltax;
 if ((pBptl->Ptl.x + pBptl->deltax) < 1)
   pBptl->deltax = -pBptl->deltax;
 if ((pBptl->Ptl.y + pBptl->deltay) > cy)
   pBptl->deltay = -pBptl->deltay;
 if ((pBptl->Ptl.y + pBptl->deltay) < 1)
   pBptl->deltay = -pBptl->deltay;
 pBptl->Ptl.x += pBptl->deltax;
 pBptl->Ptl.y += pBptl->deltay;
}


void BPipeClient::OPipeCommand(PVOID pvData)
{
 pOPMinit init  = new OPMinit;     // this is a thread and must be initialized for PM
 PPIPEMSG msg = (PPIPEMSG) pvData; // because the OPipe threads are not pm-initialized by default

 WinSendMsg(client.hwnd, WM_COMMAND,
            MPFROMSHORT(msg->Type),
            MPFROMSHORT(msg->Data));
 delete init;
}


// end of source
