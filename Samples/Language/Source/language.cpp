// language.cpp

#define __OCL_RESOLVE_TEMPLATES__

#include "..\Source\language.hpp"


Language::lang  Language::language = Language::english;  


void main(void)
{
 Language l;

 try
  {
   l.selectLang().showDialog();
  }
 
 catch(OPMException ex)
  {
   ex.viewError();
  }

 catch(OVioException ex)
  {
   ex.description + "\n";
   ex.description + OMessage(ex.rc);
   OMsgs().error(ex.description);
  }

 _exit(0); 
}


Language::Language()
 : reslib(NULL)
 {}


Language::~Language()
{
 if (reslib) delete reslib;
}


Language& Language::selectLang()
{
 SelectDlg().showDlgModal();
 return(*this);
}
 

Language& Language::showDialog()
{
 switch(Language::language)
  {
   case Language::english:
     reslib = new ODynamicLib(".\\RESENG.DLL");
     break; 

   case Language::german:  
     reslib = new ODynamicLib(".\\RESGER.DLL");
     break;
  }

 LanguageDlg(reslib->getLibHandle()).showDlgModal();

 return(*this);
}



SelectDlg::SelectDlg()   
  : ODialog(DLG_SELECT),
    box(DLG_SELECT_LB, NULLHANDLE)  
  {}


BOOL SelectDlg::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_INITDLG:
     box.inherit(hwnd);
     box.insertItem("English");
     box.insertItem("Deutsch");
     box.selectItem(Language::english); 
     break;
  
   case WM_COMMAND:
     WinSendMsg(hwnd, WM_CLOSE, NULL, NULL); 
     break;

   case WM_CLOSE:
     Language::language = (Language::lang) box.querySelection();
     dismissDlg(TRUE);
     break;
        
   default:
     return(FALSE);
  }
 return(TRUE);
} 




LanguageDlg::LanguageDlg(HMODULE mod)
 : ODialog(HWND_DESKTOP,
           HWND_DESKTOP,
           mod,
           DLG_LANG)    
 {}


BOOL LanguageDlg::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_COMMAND:
     dismissDlg(TRUE);
     break;

   default:
     return(FALSE);  
  }
 return(TRUE);
} 
