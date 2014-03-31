// OCL Sample
// Menus.cpp

#ifdef __BCPLUSPLUS__
  #define __MSC
#endif


#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Menus.hpp"

void main(void)
{
 MenuSample *sample = NULL;

 try
  {
   sample = new MenuSample;
  }

 catch(OPMException &err)
  {
   err.viewError();
   _exit(err.rc);
  }

 OApp::current().run();

 delete sample;
 _exit(0);
}


MenuSample::MenuSample()
  : OFrame(MENU_MAIN, FCF_STANDARD & ~FCF_MENU)
{
 createFrame("OMenu - Sample Application");
 menu = new OMenu(MENU_MENU, frame, client, NULLHANDLE);
 showFrame();
}


MenuSample::~MenuSample()
{
 if (menu)
   delete menu;
}


BOOL MenuSample::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_COMMAND:
     switch(SHORT1FROMMP(mp1))
      {
       case MENU_MENU_QUIT:
        WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
        break;

       case MENU_CHECK:
        if (menu->isChecked(MENU_CHECK))
          {
           menu->checkItem(MENU_CHECK, FALSE);
           menu->setItemText(MENU_CHECK, TEXT_UNCHECKED);
          }  
        else 
          {
           menu->checkItem(MENU_CHECK, TRUE);
           menu->setItemText(MENU_CHECK, TEXT_CHECKED);
          } 
        break; 

       case MENU_DISABLE:
        if (menu->isEnabled(MENU_DISABLE))
          {
           menu->enableItem(MENU_DISABLE, FALSE);
           menu->setItemText(MENU_DISABLE, TEXT_DISABLED);
          }  
        else 
          {
           menu->enableItem(MENU_DISABLE, TRUE);
           menu->setItemText(MENU_DISABLE, TEXT_ENABLED);
          } 
        break; 

       default:
        DosBeep(100, 100);
        break;
      }
     break;

   case WM_CLOSE:
     WinPostMsg(hwnd, WM_QUIT, NULL, NULL);
     break;

   default:
     return(FALSE);
  }
 return(TRUE);
#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif


// end of source
