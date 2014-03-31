// NextHand
// Next like toolbar

// $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/NextBarEvent.cpp 1.50 1996/08/11 23:48:43 B.STEIN Release $

#include "..\Source\NextHand.hpp"

NextBarEvent::NextBarEvent()
{
 settings << (PSZ) "";
 session=SSF_TYPE_DEFAULT;
 control=SSF_CONTROL_VISIBLE;
 Bkgr=SSF_FGBG_FORE;
}

NextBarEvent::~NextBarEvent() {}

void NextBarEvent::startEvent()
{
 OString     Inputs;
 OString     DosSettings;
 STARTDATA   StartData;
 ULONG       SessID;
 PID         Pid;
 APIRET      rc;
 ULONG       ulDriveNumber;
 ULONG       ulLogicalDriveMap;


 DosQueryCurrentDisk(&ulDriveNumber, &ulLogicalDriveMap);
 if((dir.getText()) && (dir.getText()[1]==':'))
   {
    CHAR       Drive;

    Drive=tolower(dir.getText()[0]);
    if(DosSetDefaultDisk(++Drive-'a')) {
       nxh->toolbar->error(ERR_ACCESS_DRIVE);
       return; }
    else if(DosSetCurrentDir(dir)) {
       nxh->toolbar->error(WORKDIR_NOT_FOUND);
       return; }
   }
 else
   {
    if(DosSetCurrentDir("\\")) {
      nxh->toolbar->error(ERR_ACCESS_DRIVE);
      return; }
   }

 memset(&StartData, 0, sizeof(STARTDATA));
 StartData.Length      = 50;
 StartData.Related     = SSF_RELATED_INDEPENDENT;
 StartData.FgBg        = Bkgr;
 StartData.TraceOpt    = SSF_TRACEOPT_NONE;
 StartData.PgmTitle    = title.getText();
 StartData.PgmName     = name.getText();
 StartData.PgmInputs   = inputs.getText();
 StartData.InheritOpt  = SSF_INHERTOPT_PARENT;
 StartData.SessionType = session;
 StartData.PgmControl  = control;

 switch(StartData.SessionType)
  {
   case PROG_WINDOW_PROT:
   case PROG_31_ENH:
    {
     if(session == PROG_WINDOW_PROT)
       Inputs <<  (PSZ) "/s ";
     if(session == PROG_31_ENH)
       Inputs <<  (PSZ) "/3 ";
    Inputs + name;
    Inputs +  (PSZ) " ";
    Inputs + inputs;
    StartData.PgmName     = "WINOS2.COM";
    StartData.PgmInputs   = Inputs.getText();
    StartData.SessionType = PROG_SEAMLESSCOMMON;
   }
   break;

 case SSF_TYPE_VDM:
 case SSF_TYPE_WINDOWEDVDM:
   {
    PSZ  pszTemp;

    DosSettings << settings;
    DosSettings + (PSZ) "\n\n";
    for(pszTemp = DosSettings; *pszTemp != '\0'; pszTemp++)
         if(*pszTemp == '\n') *pszTemp = '\0';
    StartData.Environment = DosSettings.getText();
   }
   break;
 }

 if(StartData.SessionType==SSF_TYPE_WPSOBJECT) {
   HOBJECT     hWPSObject;

   hWPSObject = WinQueryObject(name);
   if(hWPSObject!=NULLHANDLE)
#if ( defined (__TK_21__) || !defined (__IBMCPP__) ) 
     WinSetObjectData(hWPSObject, "OPEN=DEFAULT");
#else
     WinOpenObject(hWPSObject, 0, TRUE);
#endif
   else
     nxh->toolbar->error(NO_WPSO); }
 else {
   rc=DosStartSession(&StartData, &SessID, &Pid);
   switch(rc)
    {
     case 0:
     case 2:
       break;

     case ERROR_SMG_START_IN_BACKGROUND:
       nxh->toolbar->error(ERR_START_IN_BACKGROUND);

     default:
       nxh->toolbar->error(START_EVENT_FAILED);
    }}
 return;
}


// end of source
