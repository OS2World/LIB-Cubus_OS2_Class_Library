// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMWin.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMWin.cpp 1.50 1996/08/11 23:48:08 B.STEIN Release $


#include "..\Source\GTakPM.hpp"


GTPMWin::GTPMWin()
 : OFrame(GTPM_ICO, 
          FCF_SIZEBORDER | 
          FCF_ICON | 
          FCF_TASKLIST | 
          FCF_SYSMENU | 
          FCF_MINMAX | 
          FCF_TITLEBAR | 
          FCF_SHELLPOSITION,
          CS_SIZEREDRAW | CS_HITTEST),
   wasOutOfContainer(TRUE),
   showMonitor(FALSE),
   processing (FALSE),
   toolbar    (NULL),
   tapebar    (NULL),
   monitor    (NULL),
   Drives     (NULL),
   Files      (NULL),
   statline   (NULL),
   frameMenu  (NULLHANDLE),
   expander   (this, &GTPMWin::expandFolder, 65536), 
   backupThr  (this, &GTPMWin::backup, 65536), 
   restoreThr (this, &GTPMWin::restore, 65536), 
   pmpipe     ((PSZ)NULL, (PSZ)NULL),
   bmp_monitor   (HWND_DESKTOP, CMD_MONITOR,       NULLHANDLE, 32, 32),
   bmp_rescan    (HWND_DESKTOP, CMD_RESCAN,        NULLHANDLE, 32, 32),
   bmp_procedures(HWND_DESKTOP, CMD_PROCEDURES,    NULLHANDLE, 32, 32),
   bmp_tape      (HWND_DESKTOP, CMD_TAPE,          NULLHANDLE, 32, 32),
   bmp_backup    (HWND_DESKTOP, CMD_BACKUP,        NULLHANDLE, 32, 32),
   bmp_restore   (HWND_DESKTOP, CMD_RESTORE,       NULLHANDLE, 32, 32),
   bmp_compare   (HWND_DESKTOP, CMD_COMPARE,       NULLHANDLE, 32, 32),
   bmp_settings  (HWND_DESKTOP, CMD_SETTINGS,      NULLHANDLE, 32, 32),
   bmp_quit      (HWND_DESKTOP, CMD_QUIT,          NULLHANDLE, 32, 32),
   bmp_load      (HWND_DESKTOP, TAPEBAR_LOAD,      NULLHANDLE, 32, 32),
   bmp_unload    (HWND_DESKTOP, TAPEBAR_UNLOAD,    NULLHANDLE, 32, 32),
   bmp_rewind    (HWND_DESKTOP, TAPEBAR_REWIND,    NULLHANDLE, 32, 32),
   bmp_erase     (HWND_DESKTOP, TAPEBAR_ERASE,     NULLHANDLE, 32, 32),
   bmp_eraseq    (HWND_DESKTOP, TAPEBAR_ERASEQ,    NULLHANDLE, 32, 32),
   bmp_lock      (HWND_DESKTOP, TAPEBAR_LOCK,      NULLHANDLE, 32, 32),
   bmp_unlock    (HWND_DESKTOP, TAPEBAR_UNLOCK,    NULLHANDLE, 32, 32),
   bmp_stop_asap (HWND_DESKTOP, TAPEBAR_STOP_ASAP, NULLHANDLE, 32, 32),
   btn_monitor   (CMD_MONITOR,       this, &bmp_monitor,    "Monitor on/off"),
   btn_rescan    (CMD_RESCAN,        this, &bmp_rescan,     "Rescan Drives"),
   btn_procedures(CMD_PROCEDURES,    this, &bmp_procedures, "Procedures"),
   btn_tape      (CMD_TAPE,          this, &bmp_tape,       "Device Information"),
   btn_backup    (CMD_BACKUP,        this, &bmp_backup,     "Backup"),
   btn_restore   (CMD_RESTORE,       this, &bmp_restore,    "Restore"),
   btn_compare   (CMD_COMPARE,       this, &bmp_compare,    "Compare"),
   btn_settings  (CMD_SETTINGS,      this, &bmp_settings,   "Settings"),
   btn_quit      (CMD_QUIT,          this, &bmp_quit,       "Quit"),
   btn_load      (TAPEBAR_LOAD,      this, &bmp_load,       "Load"),
   btn_unload    (TAPEBAR_UNLOAD,    this, &bmp_unload,     "Unload"),
   btn_rewind    (TAPEBAR_REWIND,    this, &bmp_rewind,     "Rewind"),
   btn_erase     (TAPEBAR_ERASE,     this, &bmp_erase,      "Erase"),
   btn_eraseq    (TAPEBAR_ERASEQ,    this, &bmp_eraseq,     "Erase Quick"),
   btn_lock      (TAPEBAR_LOCK,      this, &bmp_lock,       "Lock"),
   btn_unlock    (TAPEBAR_UNLOCK,    this, &bmp_unlock,     "Unlock"),
   btn_stop_asap (TAPEBAR_STOP_ASAP, this, &bmp_stop_asap,  "Stop current operation!")
{
#ifdef __TK21__
 PSZ   tapeEnv;
#else
 PCSZ  tapeEnv;
#endif 

 DosError(FERR_DISABLEHARDERR);

 if (!DosScanEnv("TAPE", &tapeEnv))
   tape = new Tape(&pmpipe, (PSZ)tapeEnv, 0);
 else
   tape = new Tape(&pmpipe, "C:\\GTAKPM.TAR", 0);
   
 createFrame("GTakPM Develop");

 frameMenu = WinLoadMenu(frame, NULLHANDLE, GTPM_MENU);
 if (!frameMenu)
   throwGTPM(ERROR_LOAD_MENU);

 // setup toolbar
 toolbar = new OButtonBar(GTPM_TOOLBAR, this);
 toolbar->setButtonDimensions(40, 40); // set size of buttons
 toolbar->setPicSize(32);              // set size of button pictures
 toolbar->buttons.add(btn_monitor);
 toolbar->buttons.add(btn_rescan);   
 toolbar->buttons.add(btn_procedures);
 toolbar->buttons.add(btn_tape);      
 toolbar->buttons.add(btn_backup);    
 toolbar->buttons.add(btn_restore);   
 toolbar->buttons.add(btn_compare);   
 toolbar->buttons.add(btn_settings);  
 toolbar->createButtonBar();

 // setup tapebar
 tapebar = new OButtonBar(GTPM_TAPEBAR, this);
 tapebar->setButtonDimensions(40, 40); // set size of buttons
 tapebar->setPicSize(32);              // set size of button pictures
 tapebar->buttons.add(btn_quit);      
 tapebar->buttons.add(btn_load);      
 tapebar->buttons.add(btn_unload);    
 tapebar->buttons.add(btn_rewind);    
 tapebar->buttons.add(btn_erase);     
 tapebar->buttons.add(btn_eraseq);    
 tapebar->buttons.add(btn_lock);      
 tapebar->buttons.add(btn_unlock);    
 tapebar->buttons.add(btn_stop_asap); 
 tapebar->createButtonBar();


// setup statuslines
 statline = new OStatusLine(GTPM_STATLINE, this, TRUE); 
 statline->style |= FCF_BORDER;
 statline->createStatusLine();

// setup listboxes

 Excludes = new OListBox(GTPM_EX, this, LS_NOADJUSTPOS | LS_HORZSCROLL);
 Excludes->createListBox(0,0,0,0);
 Excludes->setBackColor(SYSCLR_WINDOW); 
 Excludes->setForeColor(SYSCLR_WINDOWTEXT);
 Excludes->setFont("8.Helv");

 Includes = new OListBox(GTPM_INC, this, LS_NOADJUSTPOS | LS_HORZSCROLL);
 Includes->createListBox(0,0,0,0);
 Includes->setBackColor(SYSCLR_WINDOW);
 Includes->setForeColor(SYSCLR_WINDOWTEXT);
 Includes->setFont("8.Helv");

 monitor  = new OListBox(GTPM_MON, this, LS_NOADJUSTPOS | LS_HORZSCROLL, TRUE);
 monitor->createListBox(0,0,0,0);
 monitor->setBackColor(SYSCLR_WINDOW);
 monitor->setForeColor(SYSCLR_WINDOWTEXT);
 monitor->setFont("8.Helv");

// setup containers
 
 Drives = new DrivesCnr(this);
 Drives->winText << ("Drives");
 Drives->createContainer();
 Drives->setBackColor(SYSCLR_WINDOW);
 Drives->setForeColor(SYSCLR_WINDOWTEXT);
 Drives->setFont("8.Helv");

 Files = new FilesCnr(this);
 Files->winText << ("Files");
 Files->createContainer();
 Files->setBackColor(SYSCLR_WINDOW);
 Files->setForeColor(SYSCLR_WINDOWTEXT);
 Files->setFont("8.Helv");

 pmpipe.setNotify(this);

// ready
 statline->setText("Ready");
}



GTPMWin::~GTPMWin()
{
 if (Drives) delete Drives;
 if (Files) delete Files;
 if (toolbar) delete toolbar;
 if (tapebar) delete tapebar;
 if (statline) delete statline;
 if (tape) delete tape;
 if (monitor) delete monitor;
} 
   

void GTPMWin::resizeClients(MPARAM sizeparms)
{
 ULONG width      = SHORT1FROMMP(sizeparms);
 ULONG height     = SHORT2FROMMP(sizeparms);
 ULONG lineHeight, cnrHeight;

 if ((!statline) || (!toolbar) || 
     (!Drives) || (!Files) || (!monitor) ||
     (!Includes) || (!Excludes) || (!tapebar))
    return;   // please don't trap!

 lineHeight = statline->getHeight();
 cnrHeight = lineHeight + 3*tapebar->getHeight();

// set toolbar
 WinSetWindowPos(toolbar->frame, HWND_TOP,
                 0,
                 height - toolbar->getHeight(),
                 width, 
                 toolbar->getHeight(),
                 SWP_SIZE | SWP_MOVE);

// set tapebar
 WinSetWindowPos(tapebar->frame, HWND_TOP,
                 0,
                 lineHeight,
                 width, 
                 tapebar->getHeight(),
                 SWP_SIZE | SWP_MOVE);

// set includes LB
 WinSetWindowPos(Includes->hwnd, HWND_TOP,
                 0,
                 lineHeight + tapebar->getHeight(),
                 width/2, 
                 2*tapebar->getHeight(),
                 SWP_SIZE | SWP_MOVE);

// set excludes LB
 WinSetWindowPos(Excludes->hwnd, HWND_TOP,
                 width/2,
                 lineHeight + tapebar->getHeight(),
                 width/2, 
                 2*tapebar->getHeight(),
                 SWP_SIZE | SWP_MOVE);

// set statline
 WinSetWindowPos(statline->frame, HWND_TOP, 
                 0, 
                 0,
                 width,
                 lineHeight,
                 SWP_SIZE | SWP_MOVE);
if ((!processing) && (!showMonitor)) {
  // set Drives
   WinSetWindowPos(Drives->hwnd, HWND_TOP,
                   0,
                   cnrHeight,
                   width/2,
                   height - toolbar->getHeight() - cnrHeight,
                   SWP_SIZE | SWP_MOVE);
  // set Files
   WinSetWindowPos(Files->hwnd, HWND_TOP,
                   width/2,
                   cnrHeight,
                   width/2,
                   height - toolbar->getHeight() - cnrHeight,
                   SWP_SIZE | SWP_MOVE);
  // set monitor LB
   WinSetWindowPos(monitor->hwnd, HWND_TOP,
                   0, 0, 0, 0,
                   SWP_SIZE | SWP_MOVE); }
 else {
  // set Drives
   WinSetWindowPos(Drives->hwnd, HWND_TOP,
                   0, 0, 0, 0,
                   SWP_SIZE | SWP_MOVE);
  // set Files
   WinSetWindowPos(Files->hwnd, HWND_TOP,
                   0, 0, 0, 0,
                   SWP_SIZE | SWP_MOVE);
  // set monitor LB
   WinSetWindowPos(monitor->hwnd, HWND_TOP,
                   0,
                   cnrHeight,
                   width, 
                   height - toolbar->getHeight() - cnrHeight,
                   SWP_SIZE | SWP_MOVE); }
}


BOOL GTPMWin::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_SIZE:
    resizeClients(mp2);
    break;

   case WM_COMMAND:
     return(command(mp1, mp2));
 
   case WM_CONTROL:
     return(control(mp1, mp2));

   case WM_HITTEST:
     if ((wasOutOfContainer) && (statline) && (tapebar))
      {
       ULONG  topControls, bottomControls;

       WinQueryWindowPos(Files->hwnd, &sizepos);
       bottomControls = statline->getHeight() + tapebar->getHeight();
       topControls = bottomControls + sizepos.cy;
       if ((SHORT2FROMMP(mp1) < topControls) &&
           (SHORT2FROMMP(mp1) > bottomControls))
      {
         statline->setText("File Selection");
         wasOutOfContainer = FALSE; }
      }
     break;

   case WM_APPTERMINATENOTIFY: {
    CHAR    retMsg[25];
    ULONG   rc = SHORT1FROMMP(mp2);
 
    processing = FALSE;
    if (rc != 0)
      sprintf(retMsg, "Error! rc = %ld", rc);
    else
      sprintf(retMsg, "Done.");
    if (!pmpipe.printer.isRunning())
      pmpipe.printer.stop();
    monitor->insertItem(retMsg);
    break; }

   case WM_CLOSE:
    OFrame::OCommand(msg, mp1, mp2);
    GTPMApp::GTakPM->forceQuit();
    delete this;
    break;
 
   default:
    return(OFrame::OCommand(msg, mp1, mp2));
  } 
 return(TRUE); 
} 


void GTPMWin::expandFolder()
{
 pDirInfo record = Drives->queryEmphasis();

 if(record)
   Drives->recurse(record, FALSE, record->selected);
}


void GTPMWin::addExclude(PSZ str)
{
 OString  string("- ");

 string + str;
 Excludes->insertItem(string, LIT_SORTASCENDING);
}

void GTPMWin::addInclude(PSZ str)
{
 OString  string("+ ");

 string + str;
 Includes->insertItem(string, LIT_SORTASCENDING);
}


void GTPMWin::updateListbox(PSZ str)
{
 ULONG     item;
 
 while ((item = Includes->searchString(str, 
                          LIT_FIRST, 
                          LSS_SUBSTRING | LSS_CASESENSITIVE)) != LIT_NONE)
   Includes->deleteItem(item);
 while ((item = Excludes->searchString(str, 
                          LIT_FIRST, 
                          LSS_SUBSTRING | LSS_CASESENSITIVE)) != LIT_NONE)
   Excludes->deleteItem(item);
}


void GTPMWin::printout()
{
 OPMinit     init;

 while(pmpipe.pipe)
  {
   if (pmpipe.pipe.getline(pmpipe.readBuffer, pmpipe.bufferSize))
    {
     pmpipe.readBuffer.rightCut('\r');
     if (!monitor->insertItem(pmpipe.readBuffer)) {
       monitor->deleteAll();
       monitor->insertItem(pmpipe.readBuffer); }
    }
  }
}


// end of source
