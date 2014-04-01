// OCL Sample OValueSet
// Value.cpp

#ifdef __BCPLUSPLUS__
  #define __MSC
#endif


#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Value.hpp"

#include <..\Source\OString.cpp>

void main(void)
{
 ValueSample sample;

 try
  {
   sample.init(); 
   OApp::current().run();
  }

 catch(OPMException &err)
  {
   err.viewError();
  }
}


ValueSample::ValueSample()
  : ODialog(VALUE_DLG),
    logo("..\\..\\LOGO.BMP", VALUE_MAIN, 80, 80),
    VSet(VALUE_SET, NULLHANDLE, 3, 4)
  {}

ValueSample::~ValueSample() 
  {}

PSZ ValueSample::isOfType() const
{ 
 return("ValueSample"); 
}


void ValueSample::init()
{
 COLOR color[] = { CLR_RED, CLR_GREEN, CLR_BLUE, CLR_YELLOW };

 logo.showLogo(1500);

 createDlg();
 if (!hwnd)
   OThrowPM("Dialog creation failed.", 0, OException::unrecoverable);

 VSet.inherit(hwnd);
 VSet.setItemAttr(1, 0, VIA_ICON);
 VSet.setItemAttr(2, 0, VIA_BITMAP);
 VSet.setItemAttr(3, 0, VIA_COLORINDEX);

 if ((VSet.selected.icon = WinLoadPointer(HWND_DESKTOP, NULLHANDLE, VALUE_ICON)) == NULLHANDLE)
   OThrowPM("Loading icon failed.", 0, OException::unrecoverable);
 
 if (!VSet.setItem(1, 0, (ULONG)VSet.selected.icon))
   OThrowPM("Could not set icons.", 0, OException::unrecoverable);

 if ((VSet.selected.bitmap = GpiLoadBitmap(WinGetPS(hwnd), NULLHANDLE, VALUE_BMP, 0, 0)) == NULLHANDLE)
   OThrowPM("Loading bitmap failed.", 0, OException::unrecoverable);

 if (!VSet.setItem(2, 0, (ULONG)VSet.selected.bitmap))
   OThrowPM("Could not set bitmaps.", 0, OException::unrecoverable);

 for (ULONG count = 1; count <= 4; count++)
   if (!VSet.setItem(3, count, color[count-1]))
     OThrowPM("Could not set color.", 0, OException::unrecoverable);
 
 centerDlg();
 showDlg();
}



BOOL ValueSample::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_CONTROL:
    switch(SHORT2FROMMP(mp1)) {
     case VN_SELECT:
     case VN_ENTER: {
       OString Notification;
       CHAR    pszTmp[5];

       VSet.querySelected();
       if ((SHORT2FROMMP(mp1)) == VN_SELECT)
         Notification << OString(STR_VN_SELECT, NULLHANDLE);
       else
         Notification << OString(STR_VN_ENTER, NULLHANDLE);
       _itoa(VSet.selected.row, pszTmp, 10);
       Notification + pszTmp;
       Notification + " Column ";
       _itoa(VSet.selected.col, pszTmp, 10);
       Notification + pszTmp;
       WinSetDlgItemText(hwnd, VALUE_STATUS, Notification);
       break; }}
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
#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif




// end of source
