// Nexthand.cpp
// Next like Toolbar

// $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/NextHand.cpp 1.50 1996/08/11 23:48:43 B.STEIN Release $

#define __OCL_RESOLVE_TEMPLATES__

#include "..\Source\NextHand.hpp"

#ifdef __EMX__
  template class OList<OIcon>;
  template class OList<NextBarEvent>;
#endif


pNextHand nxh;

void main(int argc, char *argv[])
{
 nxh = new NextHand;

 OApp::current().saveArgs(argc, argv);

 nxh->toolbar = new NextBar;

 if (nxh->toolbar->init())
   {
    OApp::current().run();
    delete nxh;
    _exit(0);
   }

 delete nxh;

 _exit(1);
}



PSZ NextHand::isOfType() const
{
 return("NextHand");
}

BOOL NextHand::ShutdownPosted()
{
 WinSendMsg(toolbar->frame, WM_CLOSE, NULL, NULL);
 return(FALSE);
}



NextBar::NextBar()
  : OHelp(MAIN_HELP_TABLE, NO_HLP_AVAIL),
    OFrame(NHX_MAIN, FCF_TASKLIST, CS_SIZEREDRAW | CS_SAVEBITS),
    floatTimer(this, NHX_FLOAT_TIMER, FLOAT_TIMER)
  {}


NextBar::~NextBar()
{
 if (ini) delete ini;
 if (nxButtons) delete nxButtons;
 events.reset();
}


PSZ NextBar::isOfType() const
{
 return("NextBar");
}


BOOL NextBar::init()
{
 OString  str(OApp::currentOApp->callName);
 pOString pstr = OApp::currentOApp->args.getFirst();
 ULONG    size = sizeof(NextInfo);

 if (pstr) {
   Profile << pstr->getText();
   str << pstr->getText();
   if (strstr(str, "."))
     str.rightCut('.');
   str + (PSZ) ".ini"; }
 else {
   str.rightCut('\\'); 
   Profile << str;
   Profile + (PSZ) "\\NextHand.dat";
   str + (PSZ) "\\NextHand.ini"; }

 ini = new OProfile(str);
 if ((!ini) || (!ini->getData("NextHand", "NextInfo 1.5", &setup, &size))) {
   strcpy(setup.bubbleFont, "8.Helv");
   setup.style = OButtonBar::left2right;
   setup.floating = FALSE;
   setup.position.x = 0;
   setup.position.y = (ULONG) WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
   setup.large = WinQuerySysValue(HWND_DESKTOP, SV_CXICON) > 32 ? TRUE : FALSE;
   buttonSize = setup.large ? 50 : 40;
   setup.position.y -= buttonSize;
   setup.position.cx = 0;
   setup.position.cy = 0; }
 else {
   setup.position.cx = 0;
   setup.position.cy = 0; }
 buttonSize = setup.large ? 50 : 40;

 winText << (PSZ)"NextHand Toolbar";

 createFrame(winText);

 menu = WinLoadMenu(frame, NULLHANDLE, NHX_MENU);
 WinSetParent(menu, HWND_OBJECT, FALSE);
 if (setup.style == OButtonBar::left2right)
   WinCheckMenuItem(menu, NHX_WAAGERECHT, TRUE);
 else
   WinCheckMenuItem(menu, NHX_SENKRECHT, TRUE);
 if (setup.large)
   WinCheckMenuItem(menu, NHX_LARGEICONS, TRUE);
 else
   WinCheckMenuItem(menu, NHX_NORMICONS, TRUE);
 WinCheckMenuItem(menu, NHX_FLOAT, setup.floating);

 nxButtons = new OButtonBar(NHX_TOOLBAR, this);
 if (!nxButtons)
    return(FALSE);
 nxButtons->setOrientation(setup.style);
 if (setup.large) {
    nxButtons->setButtonDimensions(50, 50);
    nxButtons->setPicSize(40); }

 if (!loadProfile())
    return(FALSE);

 nxButtons->createButtonBar();
 nxButtons->bubbleHelpWin.setFont(setup.bubbleFont);
 
 str << OApp::currentOApp->callName;
 str.rightCut('\\'); 
 str + (PSZ) "\\NextHand.hlp";
 initializeHelp(str, "NextHand Help", frame);

 WinSetWindowPos(frame, HWND_TOP, setup.position.x, setup.position.y,
                (setup.style == OButtonBar::left2right) ?  
                 nxButtons->buttons.numberOfElements() * buttonSize : buttonSize,
                (setup.style == OButtonBar::left2right) ?
                 buttonSize : nxButtons->buttons.numberOfElements() * buttonSize,
                 SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE);
 return(TRUE);
}


BOOL NextBar::loadProfile()
{
 ifstream         Dat(Profile.getText());
 pNextBarEvent    event = NULL;
 pOGraphicsButton button = NULL;
 CHAR             Buffer[CCHMAXPATH];
 CHAR             *Match;
 ULONG            i = 1;
 pOIcon           ico;

 events.reset();
 nxButtons->buttons.reset();
 iconList.reset();

// Add the NEXT-Button

 ico    = new OIcon(NHX_MAIN, NULLHANDLE);
 button = new OGraphicsButton(NHX_MAIN, nxButtons, ico, "Ordner schlieáen"); 
 iconList.add(ico);
 nxButtons->buttons.add(button);

 if (!Dat) return(TRUE);

 Dat.getline(Buffer, sizeof(Buffer)-1);
 if(!strstr(Buffer, "NEXTHAND BEGIN")) 
   {
    error(NO_NEXTHAND_FILE);
    return(FALSE); 
   }

 while(!Dat.fail())
   {
    if(strstr(Buffer, "NEXTHAND END"))
      break;
    while((Dat.getline(Buffer, sizeof(Buffer)-1)) &&
            (!strstr(Buffer, "MENUITEM")) &&
            (!strstr(Buffer, "NEXTHAND END"))) 
      {
       Buffer[strlen(Buffer)]='\0';
       Match=strchr(Buffer, ':');
       if(Match=='\0')
         Match=strchr(Buffer, '\0');
       else if ((Match=strchr(Match, ' '))==NULL)
         Match=strchr(Buffer, '\0');
       else
         for( ; (*Match==' ') && (*Match!='\0'); Match++);
       if(strstr(Buffer, "PgmTitle"))
         event->title << (PSZ) Match;
       else if(strstr(Buffer, "PgmIcon"))
         event->icon << (PSZ) Match;
       else if(strstr(Buffer, "PgmName"))
         event->name << (PSZ) Match;
       else if(strstr(Buffer, "PgmDirectory"))
         event->dir << (PSZ) Match;
       else if(strstr(Buffer, "PgmInputs"))
         event->inputs << (PSZ) Match;
       else if(strstr(Buffer, "DOSSETTINGS BEGIN")) {
         Dat.getline(Buffer, sizeof(Buffer)-1);
         while(!strstr(Buffer, "DOSSETTINGS END")) {
           event->settings + (PSZ) Buffer;
           event->settings + (PSZ) "\n";
           Dat.getline(Buffer, sizeof(Buffer)-1); }}
       else if(strstr(Buffer, "SessionType"))
         event->session = atol(Match);
       else if(strstr(Buffer, "PgmControl"))
         event->control = atol(Match);
       else if(strstr(Buffer, "FgBg"))
         event->Bkgr = atol(Match); 
      }

   if (event)
     events.add(event);
   if(strstr(Buffer, "NEXTHAND END"))
     break;
   else if(strstr(Buffer, "MENUITEM"))
     event = new NextBarEvent;
  }

 Dat.close();

 event = events.getFirst();
 while(event){
    try {
      ico = new OIcon((!event->icon) ? event->name : event->icon); }
    catch(OPMException& ex) {
      ico = new OIcon; }

    button = new OGraphicsButton(NHX_FIRST_BUTTON + i,
                                 nxButtons, ico, event->title); 
    nxButtons->buttons.add(button);
    iconList.add(ico);
    i++;
    event = events.getNext(); }

 return(TRUE);
}


BOOL NextBar::saveProfile()
{
 ofstream       Dat(Profile);
 pNextBarEvent  event = events.getFirst();

 Dat << "NEXTHAND BEGIN" << endl;
 while(event)
   {
    Dat << "MENUITEM" << endl;
    if (event->title)
       Dat << "PgmTitle: " << event->title.getText() << endl;
    if (event->name)
       Dat << "PgmName: " << event->name.getText() << endl;
    if (event->icon)
       Dat << "PgmIcon: " << event->icon.getText() << endl;
    if (event->dir)
       Dat <<  "PgmDirectory: " << event->dir.getText() << endl;
    if (event->inputs)
       Dat << "PgmInputs: " << event->inputs.getText() << endl;
    if (((event->session == SSF_TYPE_VDM) || 
         (event->session == SSF_TYPE_WINDOWEDVDM) ||
         (event->session == PROG_WINDOW_PROT) ||
         (event->session == PROG_31_ENH)) &&
         (strlen(event->settings)!=0))
       Dat << "DOSSETTINGS BEGIN" << endl
           << event->settings.getText()
           << "\nDOSSETTINGS END" << endl;
    if (event->session != SSF_TYPE_DEFAULT)
       Dat << "SessionType: " <<  (ULONG) event->session << endl;
    if (event->control != SSF_CONTROL_VISIBLE)
       Dat << "PgmControl: " << (ULONG) event->control << endl;
    if (event->Bkgr & SSF_FGBG_BACK)
       Dat << "FgBg: " << (ULONG) event->Bkgr << endl;
    event = events.getNext();
   }
 Dat << "NEXTHAND END" << endl;
 Dat.close();
 return(TRUE);
}


void NextBar::setNewStyle(ULONG flag)
{
 WinQueryWindowPos(frame, &setup.position);
 hideFrame();
 WinCheckMenuItem(menu, NHX_WAAGERECHT, (flag == OButtonBar::left2right) ? TRUE : FALSE);
 WinCheckMenuItem(menu, NHX_SENKRECHT, (flag == OButtonBar::left2right) ? FALSE : TRUE);
 WinCheckMenuItem(menu, NHX_LARGEICONS, setup.large ? TRUE : FALSE);
 WinCheckMenuItem(menu, NHX_NORMICONS, setup.large ? FALSE : TRUE);
 if (setup.large) {
    nxButtons->setButtonDimensions(50, 50);
    nxButtons->setPicSize(40); }
 else {
    nxButtons->setButtonDimensions(40, 40);
    nxButtons->setPicSize(32); }
 buttonSize = setup.large ? 50 : 40;

 nxButtons->destroyButtons();
 setup.style = flag;
 nxButtons->setOrientation(setup.style);
 WinSetWindowPos(frame, HWND_TOP, 0, 0,
                (setup.style == OButtonBar::left2right) ?
                 nxButtons->buttons.numberOfElements() * buttonSize : buttonSize,
                (setup.style == OButtonBar::left2right) ?
                 buttonSize : nxButtons->buttons.numberOfElements() * buttonSize,
                 SWP_SIZE | SWP_ACTIVATE);
 nxButtons->setupButtons();
 showFrame();
}


void NextBar::trackButtons()
{
 TRACKINFO         TrackInfo;

 WinQueryWindowPos(frame, &sizepos);
 memset (&TrackInfo, 0, sizeof(TrackInfo));  // init the trackinfo struct

 TrackInfo.cxBorder = 1;
 TrackInfo.cyBorder = 1;
 TrackInfo.cxGrid = 1;
 TrackInfo.cyGrid = 1;
 TrackInfo.cxKeyboard = 8;
 TrackInfo.cyKeyboard = 8;
 TrackInfo.rclTrack.xLeft   = sizepos.x;
 TrackInfo.rclTrack.xRight  = sizepos.x + sizepos.cx;
 TrackInfo.rclTrack.yBottom = sizepos.y;
 TrackInfo.rclTrack.yTop = sizepos.y + sizepos.cy;
 WinQueryWindowPos(HWND_DESKTOP, &sizepos);
 TrackInfo.rclBoundary.xLeft   = sizepos.x;
 TrackInfo.rclBoundary.xRight  = sizepos.x + sizepos.cx;
 TrackInfo.rclBoundary.yBottom = sizepos.y;
 TrackInfo.rclBoundary.yTop = sizepos.y + sizepos.cy;
 TrackInfo.ptlMinTrackSize.x = 0;
 TrackInfo.ptlMinTrackSize.y = 0;
 TrackInfo.ptlMaxTrackSize.x = sizepos.cx;
 TrackInfo.ptlMaxTrackSize.y = sizepos.cy;
 TrackInfo.fs = TF_MOVE | TF_STANDARD | TF_ALLINBOUNDARY;

 if (WinTrackRect(HWND_DESKTOP, 0, &TrackInfo))   // now we move ourselves
    WinSetWindowPos(frame, 0, (SHORT) TrackInfo.rclTrack.xLeft,
                              (SHORT) TrackInfo.rclTrack.yBottom, 0, 0, SWP_MOVE);
 WinSetWindowPos(frame, 0, 0, 0, 0, 0, SWP_SHOW | SWP_ACTIVATE);
 WinQueryWindowPos(frame, &setup.position);
}


void NextBar::resetToolBar()
{
 hideFrame();
 saveProfile();
 nxButtons->destroyButtons();
 loadProfile();
 nxButtons->setupButtons();
 WinSetWindowPos(frame, HWND_TOP, setup.position.x, setup.position.y,
                (setup.style == OButtonBar::left2right) ?
                 nxButtons->buttons.numberOfElements() * buttonSize : buttonSize,
                (setup.style == OButtonBar::left2right) ?
                 buttonSize : nxButtons->buttons.numberOfElements() * buttonSize,
                 SWP_SIZE | SWP_MOVE | SWP_SHOW | SWP_ACTIVATE);
}


void NextBar::closeFolders(BOOL close)
{
 CHAR  Class[33];
 HENUM henum;
 HWND  hwndd, hwndNext;

 hwndd = WinQueryWindow(HWND_DESKTOP, QW_BOTTOM);
 henum = WinBeginEnumWindows(HWND_DESKTOP);

 while ((hwndNext = WinGetNextWindow(henum)) != NULLHANDLE) 
  {
   WinQueryClassName(hwndNext, 32, Class);
   if ((hwndNext != hwndd) && 
       (!strcmp(Class, "wpFolder window")))
    {
     WinSetFocus(HWND_DESKTOP, hwndNext);
     if (close)
       WinPostMsg(hwndNext, WM_CLOSE, NULL, NULL);
     else
       WinSetWindowPos(hwndNext, HWND_BOTTOM, 0, 0, 0, 0, SWP_HIDE);
    }
  }
 WinEndEnumWindows(henum);
}

// end
