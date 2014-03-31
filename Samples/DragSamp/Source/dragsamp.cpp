// dragsamp.cpp

// $Header: W:/Projects/OCL/Samples/DragSamp/Source/rcs/dragsamp.cpp 1.50 1996/08/11 23:47:57 B.STEIN Release $

#define __OCL_RESOLVE_TEMPLATES__

#include "..\Source\dragsamp.hpp"

void main(void)
{
 DragSamp sample;

 try
  {
   sample.createDlg();
   sample.centerDlg();
   sample.showDlg();
   sample.run();
  }

 catch(OPMException &except)
  {
   except.viewError();
   _exit(1);
  }

 _exit(0);
}



DragSamp::DragSamp()
  : ODialog (DRAGSAMP_DLG),
    odf_a   (DRAGSAMP_A, NULLHANDLE),
    odf_b   (DRAGSAMP_B, NULLHANDLE),
    odf_c   (DRAGSAMP_C, NULLHANDLE)
  {}



DragSamp::~DragSamp()
  {}



BOOL DragSamp::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_INITDLG:
     odf_a.inherit(hwnd);
     odf_b.inherit(hwnd);
     odf_c.inherit(hwnd);
     break;

   case WM_COMMAND:
     WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
     break;

   case WM_CLOSE:
     hideDlg();
     forceQuit();
     break;

   default:
     return(FALSE);
  } 
 return(TRUE);
}



// end of source
