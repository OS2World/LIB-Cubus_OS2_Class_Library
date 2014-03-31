// OCL Sample
// Editor.cpp

#ifdef __BCPLUSPLUS__
  #define __MSC
#endif


#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Editor.hpp"


void main(void)
{
 Editor editor;

 try
   {
    editor.createFrame("A simple editor");
    editor.textfield = new OEditor(ID_TEXTFIELD, editor);
    editor.textfield->createMLE();
    editor.showFrame();
   }

 catch(OPMException ex)
   {
    ex.viewError();
    _exit(1);
   }

 OApp::current().run();

 _exit(0);
}


Editor::Editor()
  : OFrame(EDITOR_MAIN) 
  {}



Editor::~Editor() 
{
 if (textfield) delete textfield; 
}



PSZ Editor::isOfType() const
{ 
 return("Editor");  
} 



BOOL Editor::TasklistKill()
{
 OMsgs msg;
 return(!msg.ask("Tasklist Kill", "Do you really want to quit?"));
}



BOOL Editor::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_SIZE:
     WinSetWindowPos(textfield->hwnd, HWND_TOP, 0, 0, 
                     SHORT1FROMMP(mp2),  SHORT2FROMMP(mp2), 
                     SWP_MOVE | SWP_SIZE);
     textfield->setFocus();
     break; 


   case WM_COMMAND:
     switch(SHORT1FROMMP(mp1))
      {
       case EDITOR_QUIT:
        WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
        break;

       case EDITOR_LOAD:
        textfield->loadFile();
        setWindowText(textfield->openedFile);
        break;

       case EDITOR_SAVE:
        textfield->saveFileThr.run();
        break;

       case EDITOR_SAVEAS:
        textfield->saveFileAs(); 
        setWindowText(textfield->openedFile);
        break; 
      }
     break;

   case WM_CLOSE:
     forceQuit();
     break; 

   default:
     return(OFrame::OCommand(msg, mp1, mp2));
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
