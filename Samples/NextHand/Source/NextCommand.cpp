// NextCommand.cpp
// Next like Toolbar

// $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/NextCommand.cpp 1.50 1996/08/11 23:48:43 B.STEIN Release $

#include "..\Source\NextHand.hpp"


BOOL NextBar::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
    case WM_CREATE:
      if (setup.floating)
        floatTimer.setNotify(hwnd).start();
      break;

    case WM_TOOLBAR_RESET:
      resetToolBar();
      break;

    case WM_CFG_CANCELED: {
      pNextBarEvent actual = (pNextBarEvent) PVOIDFROMMP(mp1);
      if (actual)
         events.del(actual);
      break; }
 
    case WM_SAVE_BUTTONS:
      saveProfile();
      resetToolBar();
      break;

    case WM_CONTROL:
      switch(SHORT1FROMMP(mp1))
       {
        case OBUTTONBAR_MOVEOVER:
          selectedButton = SHORT2FROMMP(mp1);
          break;

        case OBUTTONBAR_BUTTON2DOWN:
          selectedButton = SHORT2FROMMP(mp1);
          WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(NHX_DEL_BUTTON, FALSE),
                     MPFROM2SHORT(MIA_DISABLED, (selectedButton == NHX_MAIN) ? MIA_DISABLED : ~MIA_DISABLED));
          WinSendMsg(menu, MM_SETITEMATTR, MPFROM2SHORT(NHX_CFG_BUTTON, FALSE),
                     MPFROM2SHORT(MIA_DISABLED, (selectedButton == NHX_MAIN) ? MIA_DISABLED : ~MIA_DISABLED));
          WinPopupMenu(frame, frame, menu, SHORT1FROMMP(mp2), SHORT2FROMMP(mp2), NHX_CFG_BUTTON,
                     PU_NONE | PU_KEYBOARD | PU_MOUSEBUTTON1 |
                     PU_POSITIONONITEM | PU_HCONSTRAIN | PU_VCONSTRAIN);
          break;
       }
      break;

    case WM_TIMER:
      if (setup.floating)
        WinSetWindowPos(WinQueryWindow(hwnd,QW_PARENT), HWND_TOP, 0, 0, 0, 0, SWP_ZORDER);
      break;

    case WM_COMMAND: {
       ULONG command = SHORT1FROMMP(mp1);
       pNextBarEvent actual = events.getItem(selectedButton - NHX_FIRST_BUTTON);

       switch(command)
        {
         case NHX_MAIN:
            closeFolders(TRUE);
            break;
 
         case NHX_INFOMNU: {
            pNextBarInfoDlg  dlg = new NextBarInfoDlg;
            dlg->createDlg();
            break; }

         case NHX_FLOAT:
            if (setup.floating) {
               setup.floating = FALSE;
               floatTimer.stop(); }
            else {
               setup.floating = TRUE;
               floatTimer.setNotify(hwnd).start(); }
            WinCheckMenuItem(menu, NHX_FLOAT, setup.floating);
            break;

         case NHX_QUIT:
            WinPostMsg(hwnd, WM_CLOSE, NULL, NULL);
            break;

         case NHX_MOVE:
            trackButtons();
            break;

         case NHX_SENKRECHT:
            setNewStyle(OButtonBar::up2down);
            break;

         case NHX_WAAGERECHT:
            setNewStyle(OButtonBar::left2right);
            break;

         case NHX_NORMICONS:
            setup.large = FALSE;
            setNewStyle(setup.style);
            break;

         case NHX_LARGEICONS:
            setup.large = TRUE;
            setNewStyle(setup.style);
            break;

         case NHX_ADD_BUTTON: {
            pNextBarEvent aNew = new NextBarEvent;
            pNextBarDlg   dlg = new NextBarDlg(aNew, NULL, TRUE);

            events.addAfter(actual, aNew);
            dlg->createDlg();
            break; }

         case NHX_DEL_BUTTON:
            events.del(actual);
            resetToolBar();
            break;

         case NHX_CFG_BUTTON: {
            pOGraphicsButton button = nxButtons->buttons.getItem(selectedButton - NHX_FIRST_BUTTON + 1);
            pNextBarDlg dlg = new NextBarDlg(actual, button, FALSE);
            dlg->createDlg();
            break; }

         case NHX_HELP:
            helpRequest(PANEL_MAIN);
            break;

         default:
            if (actual)  
              actual->startEvent();
            break;
         }
       break; }

    case WM_SIZE:
      if (nxButtons)
        WinSetWindowPos(nxButtons->frame, HWND_TOP, 0, 0,
            (setup.style == OButtonBar::left2right) ?  SHORT1FROMMP(mp2) : buttonSize,
            (setup.style == OButtonBar::left2right) ?  buttonSize : SHORT2FROMMP(mp2),
             SWP_MOVE | SWP_SIZE);
      break;

    case WM_CLOSE:
      WinQueryWindowPos(frame, &setup.position);
      strcpy(setup.bubbleFont, nxButtons->bubbleHelpWin.pparms.Font); 
      ini->write("NextHand", "NextInfo 1.5", &setup, sizeof(NextInfo));
      ini->close();
      hideFrame();
      OApp::currentOApp->forceQuit();
      break;

    default:
       return(FALSE);
   }
 return(TRUE);
}




// end
