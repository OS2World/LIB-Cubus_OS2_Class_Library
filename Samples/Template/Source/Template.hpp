// OCL Sample Application
// Template.hpp
// Class Definitions

#ifndef TEMPLATE_H_INCLUDED
  #define TEMPLATE_H_INCLUDED

#include"..\Source\Template.h"

#include <ocl.hpp>
#include <OXApp.hpp>
#include <OFrame.hpp>
#include <OFcl.hpp>
#include <OSysInfo.hpp>
#include <ODialog.hpp>
#include <OStatusLine.hpp>
#include <OButtonBar.hpp>
#include <OHelp.hpp>
#include <OContainer.hpp>
#include <OIndicator.hpp>
#include <OThread.hpp>
#include <OMenu.hpp>
#include <OList.hpp>
#include <OSortedList.hpp>

typedef class OCLApp *pOCLApp;
typedef class InfoDlg *pInfoDlg;


class InfoDlg 
   : public ODialog
{
 private:
   pOCLApp  app;

 public:
   InfoDlg(pOCLApp application); 
   virtual ~InfoDlg();

   virtual PSZ isOfType() const;
   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


typedef struct CnrRecord *pCnrRecord;

struct CnrRecord
{
 RECORDCORE recordCore;
 PSZ        Name;
 ULONG      Position;
};

typedef struct MyRecord *pMyRecord;

struct MyRecord
{
 OString    Name;
 ULONG      Position;
};


typedef class slMyRecord *pslMyRecord;


class slMyRecord 
  : public OSortedList<MyRecord>
{
 public:
   slMyRecord();
   ~slMyRecord();

   virtual PSZ isOfType() const;

   BOOL isLess(const MyRecord *first, const MyRecord *second);
};

typedef class MyContainer *pMyContainer;

class MyContainer 
   : public OContainer<CnrRecord, RECORDCORE>,
     public slMyRecord
{
 public:
   OThread<MyContainer>          fillThread;
   HWND                          menu;

                MyContainer      (pOFrame Parent);
   virtual      ~MyContainer     ();
 
   virtual
     PSZ        isOfType         () const;

   BOOL         setupDetails     ();
   BOOL         setupItems       ();
   MyContainer& cleanup          ();
   MyContainer& init             ();

// thread
   void         collectFiles     ();

};


class TTBar : public OButtonBar
{
 protected:
   OIcon             ico_fill;
   OIcon             ico_except;
   OIcon             ico_info;
   OIcon             ico_help;
   OIcon             ico_quit;

 public:
   OGraphicsButton   btn_fill;
   OGraphicsButton   btn_except;
   OGraphicsButton   btn_info;
   OGraphicsButton   btn_help;
   OGraphicsButton   btn_quit;

   TTBar  (pOFrame Parent); 
   ~TTBar () {}
};


typedef class OCLApp *pOCLApp;

class OCLApp 
  : public OXApp, 
    public OHelp, 
    public OFrame
{
 private:
   BOOL        wasOutOfContainer;  // pointer was out of container area?
   TTBar       *buttonbar;
   OStatusLine *statusline;
   OIndicator  *indicator;
   MyContainer *cnr;
   OMenu       *menu;

 public:
   pInfoDlg    infoDialog;


   OCLApp               (const ULONG num, CHAR *Parms[]);
   virtual ~OCLApp      ();

   virtual PSZ isOfType () const { return("OCLApp"); } 

   void createWindows   ();
   void resizeClients   (MPARAM sizeparms);

// command handler

   BOOL OCommand        (ULONG msg, MPARAM mp1, MPARAM mp2);
};

#endif // TEMPLATE_H_INCLUDED

// end of source 
