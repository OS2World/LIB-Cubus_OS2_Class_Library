// OCL Sample Application
// Template.cpp
// Implementation


// includes

#define __OCL_RESOLVE_TEMPLATES__

#include "..\Source\Template.hpp"


// prototypes

// extern "C" void main(int argc, char *argv[]);


// source

void  main(int argc, char *argv[])
{
 OCLApp sample(argc, argv);

 try
  {
   sample.createWindows();
   OApp::current().run();
  }

 catch(OPMException err)
  {
   err.exMsg.error(err.description);
  }
}


// setup for Toolbar

TTBar::TTBar(pOFrame Parent)
 : OButtonBar (ID_BUTTONBAR, Parent),
   ico_fill   (SAMPLE_FILL, NULLHANDLE),
   ico_except (SAMPLE_EXCEPT, NULLHANDLE),
   ico_info   (SAMPLE_INFO, NULLHANDLE),
   ico_help   (SAMPLE_HELP, NULLHANDLE),
   ico_quit   (SAMPLE_QUIT, NULLHANDLE),
   btn_fill   (SAMPLE_FILL,   this, &ico_fill,   "Fill Container"),
   btn_except (SAMPLE_EXCEPT, this, &ico_except, "Throw Exception from within command handler"),
   btn_info   (SAMPLE_INFO,   this, &ico_info,   "Application Information"),
   btn_help   (SAMPLE_HELP,   this, &ico_help,   "Application Help"),
   btn_quit   (SAMPLE_QUIT,   this, &ico_quit,   "Quit")
{
 ULONG screenDimension;

 buttons.add(btn_fill); 
 buttons.add(btn_except); 
 buttons.add(btn_info); 
 buttons.add(btn_help); 
 buttons.add(btn_quit); 
 screenDimension = WinQuerySysValue(HWND_DESKTOP, SV_CXICON);
 setButtonDimensions(screenDimension > 32 ? 50 : 40, screenDimension > 32 ? 50 : 40);
}



// public methods of OCLApp


OCLApp::OCLApp(const ULONG num, CHAR *Parms[])
  : OXApp(num, Parms),
    OFrame(SAMPLE_MAIN,
           FCF_SIZEBORDER | FCF_ICON | FCF_TASKLIST | 
           FCF_SYSMENU | FCF_MINMAX | FCF_TITLEBAR | FCF_SHELLPOSITION,
           CS_SIZEREDRAW | CS_HITTEST),
    statusline(NULL),
    buttonbar(NULL),
    cnr(NULL),
    indicator(NULL),
    menu(NULLHANDLE),
    infoDialog(NULL),
    wasOutOfContainer(TRUE),
    OHelp(MAIN_HELP_TABLE, HELP_ERROR) 
  {}


OCLApp::~OCLApp() 
{
 if (menu) delete menu;
 if (buttonbar) delete buttonbar;
 if (cnr) delete cnr;
 if (indicator) delete indicator;
 if (statusline) delete statusline; 
}


void OCLApp::createWindows()
{
 OString helpName(callName);

 createFrame("OCL Sample Application");

 menu = new OMenu(SAMPLE_MENU, frame, frame, NULLHANDLE);

// setup the buttonbar

 buttonbar = new TTBar(this);
 buttonbar->createButtonBar();

// setup container

 cnr = new MyContainer(this);
 cnr->init();
 cnr->menu = WinLoadMenu(cnr->hwnd, NULLHANDLE, CNR_MENU);
 cnr->setTitle("OCL Sample Container");

// setup indicator

 indicator = new OIndicator(ID_INDICATOR, this);
 indicator->createIndicator();

// setup the statusline

 statusline = new OStatusLine(ID_STATUSLINE, this, TRUE);
 statusline->style |= FCF_BORDER;
 statusline->createStatusLine();

// setup help (error is not fatal, just notify the user)
  
 try
  {
   helpName.rightCut('\\');
   helpName + "\\TEMPLATE.HLP";
   initializeHelp(helpName, "OCL Sample Help", frame);
  }
 catch(OPMException err)
  {
//   err.exMsg.error(err.description);
   err.viewError();
  }

 setSizePosFrame(HWND_TOP, sizepos, SWP_SHOW | SWP_ACTIVATE);
}


// resize method

void OCLApp::resizeClients(MPARAM sizeparms)
{
 ULONG width  = SHORT1FROMMP(sizeparms);
 ULONG height = SHORT2FROMMP(sizeparms);
 ULONG iPos   = indicator->getSliderArmPos();

 if ((!buttonbar) || (!statusline))
   return;

 WinSetWindowPos(cnr->hwnd, HWND_TOP,
                 0,
                 statusline->getHeight(),
                 width,
                 height - statusline->getHeight() - buttonbar->getHeight() - 50,
                 SWP_SIZE | SWP_MOVE);
 WinSetWindowPos(indicator->hwnd, HWND_TOP,
                 0,
                 height - buttonbar->getHeight() - 50,
                 width,
                 50,
                 SWP_SIZE | SWP_MOVE);
 indicator->setSliderArmPos(iPos);
 WinSetWindowPos(buttonbar->frame, HWND_TOP, 0, 
                 height - buttonbar->getHeight(),
                 width, 
                 buttonbar->getHeight(), 
                 SWP_SIZE | SWP_MOVE);
 WinSetWindowPos(statusline->frame, HWND_TOP, 0, 0,
                 width,
                 statusline->getHeight(),
                 SWP_SIZE | SWP_MOVE);
}


// CommandHandler for our frame window


BOOL OCLApp::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
// messages from MyContainer
   case WM_CNR_FILLED:
    cnr->enable();
    buttonbar->enableButtons();
    break;

   case WM_CNR_STATUS:
    statusline->setText((PSZ)PVOIDFROMMP(mp1));
    break;

   case WM_CNR_PERCENTAGE:
    indicator->setSliderArmPos(SHORT1FROMMP(mp1));
    break;

   case WM_CNR_FILLCNR:
    cnr->setupDetails();
    cnr->setupItems(); 
    break;

// frame messages
   case WM_SIZE:
    resizeClients(mp2);
    break;

   case WM_CONTROL:
    switch(SHORT1FROMMP(mp1))
     {
      case OBUTTONBAR_MOVEOVER:
       statusline->setText((PSZ) PVOIDFROMMP(mp2));
       wasOutOfContainer = TRUE;
       break;
     }
    break;

   case WM_BUTTON2DOWN:
     WinPopupMenu(frame, frame, cnr->menu, SHORT1FROMMP(mp1), SHORT2FROMMP(mp1), CNR_MENU,
                  PU_NONE | PU_KEYBOARD | PU_MOUSEBUTTON1 | PU_HCONSTRAIN | PU_VCONSTRAIN);
     break;

   case WM_HITTEST:
     if (wasOutOfContainer)
      {
       WinQueryWindowPos(cnr->hwnd, &sizepos);
       if ((SHORT2FROMMP(mp1) > statusline->getHeight()) &&
           (SHORT2FROMMP(mp1) < (statusline->getHeight() + sizepos.cy)))
        {
         statusline->setText("OCL Sample Container");
         wasOutOfContainer = FALSE;
        }
      }
     break;

   case WM_COMMAND:
    switch(SHORT1FROMMP(mp1))
     {
      case SAMPLE_FILL:
       WinPostMsg(hwnd, WM_COMMAND, MPFROMSHORT(CNR_REFILL), NULL);
       break;

      case SAMPLE_QUIT:
       postQuit();
       break;

      case SAMPLE_INFO: {
       infoDialog = new InfoDlg(this);
       infoDialog->showDlgModal();
       break; }

      case SAMPLE_HELP:
       helpRequest(PANEL_MAIN);
       break;

      case CNR_ICONVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_ICON);
       break;
      case CNR_TEXTVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_TEXT);
       break;
      case CNR_NAMEVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_NAME);
       break;
      case CNR_DETAILVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_DETAIL | CA_DETAILSVIEWTITLES);
       break;
      case CNR_MINIICONVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_ICON | CV_MINI);
       break;
      case CNR_MININAMEVIEW:
       cnr->setView(CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_NAME | CV_MINI);
       break;

      case CNR_REFILL:
       cnr->cleanup();
       cnr->fillThread.run();
       cnr->disable();
       buttonbar->disableButtons();
       break;

      case SAMPLE_EXCEPT:
       OThrowPM("This exception was thrown from within OCLApp::OCommand.", 
                0, OException::unrecoverable);
     }
    break;

   case WM_HELP:
    helpRequest(PANEL_MAIN);
    break;

// draw message from OIndicator
   case WM_DRAWITEM:
   {
    POWNERITEM item = (POWNERITEM) mp2;
    switch(item->idItem)
     {
      case SDA_RIBBONSTRIP:
       indicator->drawSliderElement(item, CLR_RED);
       break;
      case SDA_SLIDERSHAFT:
       indicator->drawSliderElement(item, SYSCLR_WINDOW);
       break;
     }
    break;
   }

   default:
    return(FALSE);
  }
 return(TRUE);
}


// information dialog

InfoDlg::InfoDlg(pOCLApp application) 
 : app(application), 
   ODialog(HWND_DESKTOP, application->hwnd, SAMPLE_DLG) 
 {}

InfoDlg::~InfoDlg()
 {}

PSZ InfoDlg::isOfType() const
{
 return("InfoDlg");
}

BOOL InfoDlg::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_INITDLG:
    centerDlg(CENTER_ONSCREEN);
    showDlg();
    break;

   case WM_COMMAND:
    dismissDlg();
    break;

   case WM_CLOSE:
   case WM_DESTROY:
    delete this;
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


// slMyRecord

slMyRecord::slMyRecord()
 {}

slMyRecord::~slMyRecord() 
 {}

PSZ slMyRecord::isOfType() const 
{ 
 return("slMyRecord"); 
} 

BOOL slMyRecord::isLess(const MyRecord *first, const MyRecord *second)
{
 return(strcmpi(first->Name, second->Name) <= 0);
}

// end of source
