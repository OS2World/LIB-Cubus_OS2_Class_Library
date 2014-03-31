// NextHand.hpp
// Next like toolbar

// $Header: W:/Projects/OCL/Samples/NextHand/Source/rcs/NextHand.hpp 1.50 1996/08/11 23:48:44 B.STEIN Release $

#define OINCL_BASE
#include <ocl.hpp>

#include <OString.hpp>
#include <OPMinit.hpp>
#include <OCommand.hpp>
#include <OXApp.hpp>
#include <OWindow.hpp>
#include <OFrame.hpp>
#include <OProfile.hpp>
#include <ODialog.hpp>
#include <OMSGS.hpp>
#include <OButtonBar.hpp>
#include <OHelp.hpp>
#include <OXcptPM.hpp>
#include <OMLE.hpp>
#include <OEntryField.hpp>
#include <OTimer.hpp>

#include "..\Source\NextHand.h"

#include <ctype.h>

#define USERITEMFIRST NHX_FIRST_BUTTON
#define USERITEMLAST  NHX_FIRST_BUTTON+50

#define WM_TOOLBAR_RESET  WM_USER+1
#define WM_CFG_CANCELED   WM_USER+2
#define WM_SAVE_BUTTONS   WM_USER+3
#define NHX_FLOAT_TIMER   TID_USERMAX-1
#define FLOAT_TIMER       3000

#define SSF_TYPE_WPSOBJECT 21
#define FAPPTYP_WINDOWSPROT31 0x1000

#ifdef __BORLANDC__
  #define PROG_31_ENH  (PROGCATEGORY)19
#endif

extern "C" 
{
  VOID EXPENTRY closeFolders(BOOL close);
  BOOL EXPENTRY initHooks(HAB hab);
} 

typedef struct NextInfo *pNextInfo;

struct NextInfo
{
 ULONG  style;
 ULONG  large;
 SWP    position;
 BOOL   floating;
 CHAR   bubbleFont[50]; 
};

typedef class NextBarEvent *pNextBarEvent;

class NextBarEvent
{
 public:
   OString   title;
   OString   name;
   OString   dir;
   OString   inputs;
   OString   icon;
   OString   settings;
   USHORT    session;
   USHORT    control;
   USHORT    Bkgr;

   NextBarEvent();
   virtual ~NextBarEvent();
   void startEvent();
};

typedef class OList<NextBarEvent> EventList;
typedef EventList *pEventList;

typedef class NextBarDlg *pNextBarDlg;

class NextBarDlg : public ODialog
{
 private:
   pNextBarEvent   event;
   OGraphicsButton *actualButton;
   BOOL            isCreation;
   OEntryField     Title;
   OEntryField     Program;
   OEntryField     Path;
   OEntryField     Parms;
   OEntryField     Icon;
   OMLE            Settings;

 public:
   NextBarDlg(pNextBarEvent  pevt, pOGraphicsButton button, BOOL newItem);
   virtual ~NextBarDlg() {}
   virtual PSZ isOfType() const; 

   void handleButtons(MPARAM mp1);
   void setButtons();
   void setProgram2Dialog();
   void setDialog2Program();
   void install2Dialog(PSZ FileName, BOOL bObject);
   void loadProgram();

// Command Handler
   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


typedef class NextBarInfoDlg *pNextBarInfoDlg;

class NextBarInfoDlg : public ODialog
{
 public:
    NextBarInfoDlg() : ODialog(NHX_INFO_DLG) {}
    virtual ~NextBarInfoDlg() {}
    virtual PSZ isOfType() const; 

    BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


#define SWITCH_TO_DEFAULT  1
#define SWITCH_TO_PROGRAM  2
#define SWITCH_TO_SORT       3

typedef class NextBar *pNextBar;

class NextBar
   : virtual public OHelp, 
     virtual public OMsgs,
     virtual public OFrame
{
 private:
     pOButtonBar  nxButtons;
     OList<OIcon> iconList;
     pOProfile    ini;
     OString      Profile;
     NextInfo     setup;
     HWND         menu;
     ULONG        selectedButton;
     ULONG        buttonSize;
     OTimer       floatTimer;     

 public:
     EventList    events;

     NextBar();
     virtual ~NextBar();
     virtual PSZ isOfType() const; 

     BOOL init();
     BOOL loadProfile();
     BOOL saveProfile();
     void setNewStyle(ULONG flag);
     void trackButtons();
     void resetToolBar();
     void closeFolders(BOOL close);

     BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


typedef class NextHand *pNextHand;

class NextHand 
{
 protected:
    OXApp    app;

 public:
    pNextBar toolbar;

    NextHand() {}
    ~NextHand() {}
    virtual PSZ isOfType() const; 

    BOOL ShutdownPosted();
};


extern pNextHand nxh;

// end
