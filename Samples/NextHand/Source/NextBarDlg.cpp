// NextBaeDlg.cpp
// Next like Toolbar

// $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/NextBarDlg.cpp 1.50 1996/08/11 23:48:42 B.STEIN Release $

#include "..\Source\NextHand.hpp"

#define isChecked(item)  WinQueryButtonCheckstate(hwnd, item)

static ULONG WPSOControls[] =
{
 NHX_WORKDIR,
 NHX_PARMS,
 NHX_SETTINGS,
 NHX_SETTINGS_TXT,
 NHX_WORKDIR_TXT,
 NHX_PARMS_TXT
};

static ULONG usChild2DOS[] =
{
 NHX_SETTINGS,
 NHX_SETTINGS_TXT
};

static ULONG usChild2WINOS2[] =
{
 NHX_WINSTD,
 NHX_WINENH
};

static ULONG usSessionTypeRBs[] =
{
 NHX_OS2_FULL,
 NHX_OS2_WIN,
 NHX_PM,
 NHX_DOS_FULL,
 NHX_DOS_WIN,
 NHX_WPSO
};

static ULONG usSessionTypeIDs[] =
{ 
 SSF_TYPE_FULLSCREEN,
 SSF_TYPE_WINDOWABLEVIO,
 SSF_TYPE_PM, 
 SSF_TYPE_VDM,
 SSF_TYPE_WINDOWEDVDM,
 SSF_TYPE_WPSOBJECT
};

static ULONG usWINOS2TypeIDs[] = 
{
 PROG_WINDOW_PROT,
 PROG_31_ENH
};


NextBarDlg::NextBarDlg(pNextBarEvent  pevt, pOGraphicsButton button, BOOL newItem)
  : event(pevt), 
    actualButton(button),
    ODialog(HWND_DESKTOP, HWND_DESKTOP, NHX_DLG),
    isCreation(newItem),
    Title(NHX_TITLE, NULLHANDLE),
    Program(NHX_PROG, NULLHANDLE),
    Path(NHX_WORKDIR, NULLHANDLE),
    Parms(NHX_PARMS, NULLHANDLE),
    Icon(NHX_ICON, NULLHANDLE),
    Settings(NHX_SETTINGS, NULLHANDLE)
  {}


PSZ NextBarDlg::isOfType() const
{
 return("NextBarDlg");
}


void NextBarDlg::handleButtons(MPARAM mp1)
{
 if(SHORT2FROMMP(mp1) == BN_CLICKED)
   switch(SHORT1FROMMP(mp1))
    {
     case NHX_DOS_FULL:
     case NHX_DOS_WIN:
       OCL::enableControls(hwnd, WPSOControls, sizeof(WPSOControls));
       OCL::enableControls(hwnd, usChild2DOS, sizeof(usChild2DOS));
       OCL::disableControls(hwnd, usChild2WINOS2,sizeof(usChild2WINOS2));
       WinCheckButton(hwnd, NHX_WINSTD, FALSE);
       WinCheckButton(hwnd, NHX_WINENH, FALSE);
       break;

     case NHX_OS2_FULL:
     case NHX_OS2_WIN:
     case NHX_PM:
       OCL::enableControls(hwnd, WPSOControls, sizeof(WPSOControls));
       OCL::hideControls(hwnd, usChild2DOS, sizeof(usChild2DOS));
       OCL::disableControls(hwnd, usChild2WINOS2, sizeof(usChild2WINOS2));
       WinCheckButton(hwnd, NHX_WINSTD, FALSE);
       WinCheckButton(hwnd, NHX_WINENH, FALSE);
       break;

    case NHX_WPSO:
       OCL::hideControls(hwnd, WPSOControls, sizeof(WPSOControls));
       OCL::hideControls(hwnd, usChild2DOS, sizeof(usChild2DOS));
       OCL::disableControls(hwnd, usChild2WINOS2, sizeof(usChild2WINOS2));
       WinSetDlgItemText(hwnd, NHX_WORKDIR, "");
       WinSetDlgItemText(hwnd, NHX_PARMS, "");
       WinCheckButton(hwnd, NHX_WINSTD, FALSE);
       WinCheckButton(hwnd, NHX_WINENH, FALSE);
       break;

    case NHX_SEAMLESS:
       OCL::enableControls(hwnd, usChild2DOS, sizeof(usChild2DOS));
       OCL::enableControls(hwnd, WPSOControls, sizeof(WPSOControls));
       OCL::enableControls(hwnd, usChild2WINOS2, sizeof(usChild2WINOS2));
       break;
    }
 return;
}


void NextBarDlg::setButtons()
{
 ULONG usTemp;

 for(usTemp=0; usTemp<=(sizeof(usSessionTypeRBs)/sizeof(ULONG)); usTemp++)
   if(usSessionTypeIDs[usTemp] == event->session) {
      WinCheckButton(hwnd, usSessionTypeRBs[usTemp],  TRUE);
      WinSendMsg(hwnd, WM_CONTROL, MPFROM2SHORT(usSessionTypeRBs[usTemp], BN_CLICKED), NULL); }
  switch(event->session)
   {
    case PROG_WINDOW_REAL:
    case PROG_WINDOW_PROT:
    case PROG_31_ENH:
     for(usTemp=0; usTemp<=(sizeof(usChild2WINOS2)/sizeof(ULONG)); usTemp++)
       if(usWINOS2TypeIDs[usTemp] == event->session)
         WinCheckButton(hwnd, usChild2WINOS2[usTemp], TRUE);
         WinCheckButton(hwnd, NHX_SEAMLESS, TRUE);
     WinSendMsg(hwnd, WM_CONTROL, MPFROM2SHORT(NHX_SEAMLESS, BN_CLICKED), NULL);
     break;

    default:
      WinCheckButton(hwnd, NHX_WINSTD, TRUE);
      break;
   }

 if(event->session == SSF_TYPE_WPSOBJECT) {
   OCL::disableControls(hwnd, usChild2WINOS2, sizeof(usChild2WINOS2));
   OCL::hideControls(hwnd, WPSOControls, sizeof(WPSOControls)); }
}


void NextBarDlg::setProgram2Dialog()
{
 WinSendDlgItemMsg(hwnd, NHX_SETTINGS, MLM_DELETE,
                   MPFROMSHORT(0), MPFROMSHORT(2*CCHMAXPATH));
 Title.setText(event->title);
 Program.setText(event->name);
 Path.setText(event->dir);
 Parms.setText(event->inputs);
 Icon.setText(event->icon);

 if (strlen(event->settings) > 0)
   Settings.insertText(event->settings);
 else
   Settings.insertText("IDLE_SECONDS=5\nIDLE_SENSITIVITY=100\n");

 if (event->control & SSF_CONTROL_MAXIMIZE)
   WinCheckButton(hwnd, NHX_MAXSIZE, TRUE);
 if (event->control & SSF_CONTROL_MINIMIZE)
   WinCheckButton(hwnd, NHX_MINSIZE, TRUE);
 if(event->Bkgr & SSF_FGBG_BACK)
   WinCheckButton(hwnd, NHX_BACKGROUND, TRUE);
 setButtons();
}


void NextBarDlg::setDialog2Program()
{
 OString dosBuffer;
 PSZ     boarder;

 Title.getText(event->title);
 Program.getText(event->name);
 Path.getText(event->dir);
 Parms.getText(event->inputs);
 Icon.getText(event->icon);

 if ((isChecked(NHX_DOS_FULL)) || 
     (isChecked(NHX_DOS_WIN)) ||
     (isChecked(NHX_SEAMLESS)))
  {
   Settings.getText(dosBuffer); 
   for(boarder=strchr(dosBuffer, '\0'); boarder != dosBuffer; )
     if((*--boarder=='\r') || (*boarder=='\n')) 
       *boarder='\0';
     else 
       break;
   event->settings << dosBuffer; 
  }
 else
  event->settings << "";

 if(isChecked(NHX_OS2_FULL))
   event->session = SSF_TYPE_FULLSCREEN;
 else if(isChecked(NHX_OS2_WIN))
   event->session = SSF_TYPE_WINDOWABLEVIO;
 else if(isChecked(NHX_PM))
   event->session = SSF_TYPE_PM;
 else if(isChecked(NHX_DOS_FULL))
   event->session = SSF_TYPE_VDM;
 else if(isChecked(NHX_DOS_WIN))
   event->session = SSF_TYPE_WINDOWEDVDM;
 else if(isChecked(NHX_WPSO))
   event->session = SSF_TYPE_WPSOBJECT;
 else if(isChecked(NHX_SEAMLESS)) {
   if(isChecked(NHX_WINSTD))
     event->session = PROG_WINDOW_PROT;
   else if(isChecked(NHX_WINENH))
     event->session = PROG_31_ENH; }
 if(isChecked(NHX_MAXSIZE))
   event->control |= SSF_CONTROL_MAXIMIZE;
 if(isChecked(NHX_MINSIZE))
   event->control |= SSF_CONTROL_MINIMIZE;
 if(isChecked(NHX_BACKGROUND))
   event->Bkgr = SSF_FGBG_BACK;
 else
   event->Bkgr = SSF_FGBG_FORE;
 event->control |= SSF_CONTROL_VISIBLE | SSF_CONTROL_SETPOS;
}


void NextBarDlg::install2Dialog(PSZ FileName, BOOL bObject)
{
 CHAR    Buffer[260];
 PSZ     pszTemp;
 BOOL    Batch=FALSE;
 ULONG   AppType;

 Icon.setText("");
 Parms.setText("");

 if(bObject) {
   event->session = SSF_TYPE_WPSOBJECT;
   WinSetDlgItemText(hwnd, NHX_TITLE, FileName);
   WinSetDlgItemText(hwnd, NHX_PROG, FileName); }
 else {
   DosQueryAppType(FileName, &AppType);
   event->session = SSF_TYPE_DEFAULT;
   if ((AppType & 0x7) == FAPPTYP_WINDOWAPI)
      event->session = SSF_TYPE_PM;
   else if ((AppType & 0x7) == FAPPTYP_WINDOWCOMPAT)
      event->session = SSF_TYPE_WINDOWABLEVIO;
   else if (AppType & FAPPTYP_DOS)
      event->session = SSF_TYPE_WINDOWEDVDM;
   else if (AppType & FAPPTYP_WINDOWSREAL)
      event->session = PROG_WINDOW_REAL;
   else if (AppType & FAPPTYP_WINDOWSPROT)
      event->session = PROG_WINDOW_PROT;
   else if (AppType & FAPPTYP_WINDOWSPROT31)
      event->session = PROG_31_ENH; }

 if(!bObject) {
   if(strstr(FileName, ".CMD")) {
     Batch = TRUE;
     event->session = SSF_TYPE_WINDOWABLEVIO;
     if(strchr(FileName, ' ')) {
       strcpy(Buffer, "/c \"\"");
       strcat(Buffer, FileName);
       strcat(Buffer, "\"\""); }
     else {
       strcpy(Buffer, "/c ");
       strcat(Buffer, FileName); }}
   else if(strstr(FileName, ".BAT")) {
     Batch = TRUE;
     event->session = SSF_TYPE_WINDOWEDVDM;
     strcpy(Buffer, "/c ");
     strcat(Buffer, FileName); }
   if (Batch) {
     WinSetDlgItemText(hwnd, NHX_PARMS, Buffer);
     WinSetDlgItemText(hwnd, NHX_PROG, ""); }
   else
     WinSetDlgItemText(hwnd, NHX_PROG, FileName);
   strcpy(Buffer, FileName);
   pszTemp = FileName+strlen(FileName);
   for( ; (*pszTemp!='\\') && (pszTemp>=FileName); pszTemp--);
   WinSetDlgItemText(hwnd, NHX_TITLE, (pszTemp+1));
   *pszTemp='\0';
   WinSetDlgItemText(hwnd, NHX_WORKDIR, FileName); }

 setButtons();
}


void NextBarDlg::loadProgram()
{
 FILEDLG     fdFileDlg;
 HWND        hwndFileDlg;

 memset(&fdFileDlg, 0, sizeof(FILEDLG));
 fdFileDlg.cbSize=sizeof(FILEDLG);
 fdFileDlg.fl=FDS_CENTER | FDS_OPEN_DIALOG;
 fdFileDlg.pszTitle="NextHand 1.5 - Configuration";
 strcpy(fdFileDlg.szFullFile, "C:\\*");
 hwndFileDlg=WinFileDlg(HWND_DESKTOP, hwnd, &fdFileDlg);
 if (hwndFileDlg && (fdFileDlg.lReturn==DID_OK))
    install2Dialog(fdFileDlg.szFullFile, FALSE);
}




BOOL NextBarDlg::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg) {
    case WM_INITDLG:
       centerDlg();
       Title.inherit(hwnd);
       Program.inherit(hwnd);
       Path.inherit(hwnd);
       Parms.inherit(hwnd);
       Icon.inherit(hwnd);
       Settings.inherit(hwnd);
       Settings.setFont("8.Helv");
       setProgram2Dialog();
       if (actualButton)
         WinSendMsg(WinWindowFromID(hwnd, NHX_ICONFIELD), SM_SETHANDLE, 
                    MPFROMP(actualButton->pIco->hptr), NULL);
       break;

    case WM_CONTROL:
       handleButtons(mp1);
       break; 

    case DM_DRAGOVER:
     {
      PDRAGINFO  pdinfo = (PDRAGINFO) mp1;
      PDRAGITEM  pditem = NULL;

      DrgAccessDraginfo(pdinfo);
      pditem = DrgQueryDragitemPtr(pdinfo, 0);
      if (DrgVerifyRMF(pditem, "DRM_OS2FILE", NULL))
       {
        DrgFreeDraginfo (pdinfo) ;
        return(TRUE);
       }
      else
       {
        DrgFreeDraginfo (pdinfo) ;
        return(FALSE);
       }
     }

   case DM_DROP: {
     PDRAGINFO       pDragInfo;              /* Pointer to DRAGINFO structure */
     PDRAGITEM       pDragItem;              /* Pointer to DRAGITEM structure */
     CHAR            Buffer[CCHMAXPATH];
     CHAR            ObjectType[CCHMAXPATH];
     PSZ             pszBuffer;
     OString         tmpBuf; 

     pDragInfo = (PDRAGINFO)mp1;
     if(DrgAccessDraginfo(pDragInfo)==FALSE) break;
     pDragItem = DrgQueryDragitemPtr(pDragInfo, 0);
     DrgQueryStrName(pDragItem->hstrRMF, sizeof(ObjectType), ObjectType);
     if(!strstr(ObjectType, "<DRM_OBJECT, DRF_OBJECT>"))
      { // this is not a WPS object
       DrgQueryStrName(pDragItem->hstrContainerName, sizeof(Buffer), Buffer);
       pszBuffer = ((PSZ) Buffer)+strlen(Buffer);
       DrgQueryStrName(pDragItem->hstrSourceName, sizeof(Buffer)-strlen(pszBuffer), pszBuffer);
       tmpBuf << Buffer;
       strupr(tmpBuf);
       if (strstr(tmpBuf, ".ICO")) {
          hps = WinGetPS(WinWindowFromID(hwnd, NHX_ICONFIELD));
          GpiCreateLogColorTable(hps, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL);
          WinQueryWindowRect(WinWindowFromID(hwnd, NHX_ICONFIELD), &rcl);
          GpiSetColor(hps, SYSCLR_DIALOGBACKGROUND);
          GpiBox(hps, DRO_FILL, (PPOINTL) &rcl.xRight, 0L, 0L);
          WinReleasePS(hps);
          if (actualButton->pIco) 
            delete actualButton->pIco;
          try {
            actualButton->pIco = new OIcon(Buffer); }
          catch(...) {
            delete actualButton->pIco;
            actualButton->pIco = new OIcon(); }
          WinSendMsg(WinWindowFromID(hwnd, NHX_ICONFIELD), SM_SETHANDLE, 
                     MPFROMP(actualButton->pIco->hptr), NULL);
          WinSetDlgItemText(hwnd, NHX_ICON, Buffer); }
       else if ((!strstr(tmpBuf, ".EXE")) &&  (!strstr(tmpBuf, ".COM")) &&
                (!strstr(tmpBuf, ".BAT")) &&  (!strstr(tmpBuf, ".CMD")))
          install2Dialog(Buffer, TRUE);
       else
          install2Dialog(Buffer, FALSE);
      }
     else {
       DrgQueryStrName(pDragItem->hstrSourceName, sizeof(Buffer), Buffer);
       install2Dialog(Buffer, TRUE); }
    break; }

    case WM_COMMAND:
      switch(SHORT1FROMMP(mp1)) 
       {
        case NHX_SAVE:
          setDialog2Program();
          if (isCreation)
             WinPostMsg(nxh->toolbar->hwnd, WM_TOOLBAR_RESET, NULL, NULL);
          else
             WinPostMsg(nxh->toolbar->hwnd, WM_SAVE_BUTTONS, NULL, NULL);
          event = NULL;
          WinPostMsg(hwnd, WM_CLOSE, NULL, NULL);
          break;

        case NHX_CANCEL:
          WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
          break;

        case NHX_LOAD:
          loadProgram();
          break;
       }
      break;

    case WM_HELP:
       nxh->toolbar->helpRequest(PANEL_CFGS);
       break;

    case WM_CLOSE:
       WinSendMsg(WinWindowFromID(hwnd, NHX_ICONFIELD), SM_SETHANDLE,
                  MPFROMP(NULLHANDLE), NULL);
       if (isCreation)
         WinPostMsg(nxh->toolbar->hwnd, WM_CFG_CANCELED, MPFROMP(event), NULL);
       delete this;
       break;

    default:
       return(FALSE); }
 return(TRUE);
#ifdef __BORLANDC__
  #pragma warn -par
#endif
}
#ifdef __BORLANDC__
  #pragma warn .par
#endif



// Information Dialog

PSZ NextBarInfoDlg::isOfType() const
{
 return("NextBarInfoDlg");
}


BOOL NextBarInfoDlg::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg) {
    case WM_INITDLG:
      centerDlg();
      break;

    case WM_COMMAND:
       WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
       break;

    case WM_CLOSE:
       delete this;
       break;

    default:
      return(FALSE); }
 return(TRUE);
#ifdef __BORLANDC__
  #pragma warn -par
#endif
}
#ifdef __BORLANDC__
  #pragma warn .par
#endif


// end of source
