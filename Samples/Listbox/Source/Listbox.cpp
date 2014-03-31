// OCL Sample
// Listbox.cpp

#ifdef __BCPLUSPLUS__
  #define __MSC
#endif

#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Listbox.hpp"


void main(void)
{
 BoxSample sample;
 
 try
  {
   sample.init(); 
  }

 catch(OPMException err)
  {
   err.viewError();
   _exit(1);
  }

 OApp::current().run();
}


BoxSample::BoxSample()
 : OFrame(BOX_MAIN) 
 {}

BoxSample::~BoxSample()
{
 if (box) delete box;
}


void BoxSample::run()
{
 BOOL continuable = TRUE;

 while(continuable)
  {
   continuable = FALSE;

   try
    {
     OApp::run(); 
    }

   catch(LBException *except)
    {
     OString str("Exception of type \"");
   
     str + except->isOfType();
     str + "\" caught and handled.";       
     DosBeep(100, 100);
     box->insertItem(str);
     delete except;
     continuable = TRUE;
    }

   catch(OPMException except)
    {
     except.viewError();
    }
  }
}


void BoxSample::init()
{
 winText << "ListBox Sample";
 createFrame(winText);

 box = new OListBox(ID_LISTBOX, this, LS_NOADJUSTPOS | LS_HORZSCROLL);
 box->createListBox(0, 0, 0, 0).setFont("10.Helv").setForeColor(RGB_BLUE);

 sizepos.cx = 400;
 sizepos.cy = 300;
 setSizePosFrame(HWND_TOP, sizepos, SWP_SIZE | SWP_SHOW | SWP_ACTIVATE);
}



BOOL BoxSample::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_SIZE:
     if (box)
       WinSetWindowPos(box->hwnd, 0, 0, 0, SHORT1FROMMP(mp2), SHORT2FROMMP(mp2), SWP_SIZE | SWP_SHOW );
     break;

   case WM_COMMAND:
     switch(SHORT1FROMMP(mp1))
      {
       case BOX_QUIT:
        WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
        break;

       case BOX_EXCEPTION:
        throw new LBException;
      }
     break;

   case WM_CLOSE:
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


LBException::LBException()
  : OException(NULL, 0, OException::unrecoverable) 
  {}

LBException::~LBException() 
  {}

void LBException::viewError() 
  {}


// end of source
