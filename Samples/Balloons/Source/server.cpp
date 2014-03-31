// Server.cpp (Server.EXE)
// OCL Sample - Server Apllication for Balloons

#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\server.hpp"

#include <..\source\obook.cpp>

// globals

BalloonServer server;

// code

void main(void)
{
 try
  {
   server.init();
  }

 catch(OPMException err)
  {
   err.exMsg.error(err.errRes);
   _exit(1);
  }

 OApp::current().run();
}


BPipeServer::BPipeServer()
  : OPipeSvr(2*sizeof(PIPEMSG),   // inSize
             2*sizeof(PIPEMSG),   // outSize
             sizeof(PIPEMSG),     // packet size
             SVR_PIPE_OPEN_DEFAULT,
             SVR_PIPE_PIPE_DEFAULT,
             PIPE_TIMEOUT_DEFAULT,
             5)                  // max allowed clients
  {}

BPipeServer::~BPipeServer()
  {}


void BPipeServer::OPipeCommand(PVOID pvData) 
  {}



BalloonServer::BalloonServer()
 : OBook(ID_ICON),
   secondPage(FALSE, "Count"),
   thirdPage(TRUE, "Speed") 
 {}
   

   
BalloonServer::~BalloonServer() 
{
 if (svrSem) 
   delete svrSem;
}



void BalloonServer::init()
{
 try
  {
   svrSem = new ONSem(BALL_SEM);
  }
 catch(OVioException ex)
  {
   throw OPMException(SERVER_RUNNING, 0);
  }

 Buffer = &pipeMessage;
 if (!beginPiping(BALL_PIPE))
   throw OPMException(PIPE_FAILED, 0);

 Pages.add(&firstPage);
 Pages.add(&secondPage);
 Pages.add(&thirdPage);

 try 
  {
   createBook("Balloons Server", 270, 170, NB_STANDARD);
  }

 catch(OPMException err)
  {
   err.viewError();
   throw err;
  }

 showFrame();
}



// notebook pages

// control panel

BOOL BalloonServer::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_CLOSE:
    if (connectedClients > 0) {
      pipeMessage.Type = PIPE_SERVER_EXIT;
      pipeMessage.Data = 0;
      postPipe(&pipeMessage, 0); }   // post to all clients
    OBook::OCommand(msg, mp1, mp2);
    stopPiping();
    forceQuit();
    break;

   default:
    return(OBook::OCommand(msg, mp1, mp2));
  }
 return(TRUE);
}


BOOL CtrlPanel::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_COMMAND:
    switch(SHORT1FROMMP(mp1))
     {
      case CONTROL_STOP:
       if (server.connectedClients > 0) {
         server.pipeMessage.Type = PIPE_STOP_BALLOONS;
         server.pipeMessage.Data = 0;
         server.postPipe(&server.pipeMessage, 0); }   // post to all clients
       break;

      case CONTROL_START:
       if (server.connectedClients > 0) {
         server.pipeMessage.Type = PIPE_START_BALLOONS;
         server.pipeMessage.Data = 0;
         server.postPipe(&server.pipeMessage, 0); }   // post to all clients
       break;

      case CONTROL_XSERV:
       WinSendMsg(server.hwnd, WM_CLOSE, NULL, NULL);
       break;

      case CONTROL_XCLIENT:
       if (server.connectedClients > 0) {
         server.pipeMessage.Type = PIPE_STOP_CLIENT;
         server.pipeMessage.Data = 0;
         server.postPipe(&server.pipeMessage, 0); }   // post to all clients
       break;
      }
    break;

   default:
    return(OBookPage::OCommand(msg, mp1, mp2));
  }
 return(TRUE);
}


BOOL NumSpeedControl::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_INITDLG: {
    SWP swp;

    slider = new OSlider(NUM_SLIDER, hwnd, 5, 0, 5, 0,
                         SLS_HORIZONTAL | SLS_CENTER | SLS_SNAPTOINCREMENT |
                         SLS_BUTTONSLEFT | SLS_HOMELEFT | SLS_PRIMARYSCALE1 |
                         SLS_RIBBONSTRIP);
    WinQueryWindowPos(WinWindowFromID(hwnd, NUM_SLIDER_PLACE), &swp);
    slider->createSlider(swp.x, swp.y, swp.cx, swp.cy);
    slider->setTickSize(5);
    slider->setFont("8.Helv");
    slider->setSliderScaleText("1", 0);
    slider->setSliderScaleText("2", 1);
    slider->setSliderScaleText("3", 2);
    slider->setSliderScaleText("4", 3);
    slider->setSliderScaleText("5", 4);
    if (isSpeedCtrl)
      WinSetDlgItemText(hwnd, NUM_TXT1, "Select the speed of flying balloons...");
    break; }

   case WM_CONTROL:
    switch(SHORT2FROMMP(mp1)) {
     case SLN_CHANGE:
       if (server.connectedClients > 0) {
        if (isSpeedCtrl)
          server.pipeMessage.Type = PIPE_SET_SPEED;
        else
          server.pipeMessage.Type = PIPE_SET_NUM;
        server.pipeMessage.Data = 1 + slider->getSliderArmPos();
        server.postPipe(&server.pipeMessage, 0); }     // post to all clients
      break; }
    break;

   default:
    return(OBookPage::OCommand(msg, mp1, mp2));
  }
 return(TRUE);
}


// end of source
