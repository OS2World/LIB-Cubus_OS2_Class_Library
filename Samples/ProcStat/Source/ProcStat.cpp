// OCL Sample
// Procstat.cpp


#ifdef __BCPLUSPLUS__
  #define __MSC
#endif


#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\Procstat.hpp"

#if defined(__EMX__)
  template class OContainer<MINIRECORDCORE, MINIRECORDCORE>;
#endif

void main(void)
{
 Procstat sample;

 try
  {        
   sample.init(); 
  }

 catch(OException &err)
  {     
   OMsgs msg;

   msg.error("Application Exception", err.description);
   _exit(1);
  }         

 OApp::current().run();

 _exit(0);
}


Procstat::Procstat()
 : OFrame(PROCSTAT_MAIN) 
 {}

Procstat::~Procstat()
{
 if (cnr) delete cnr; 
}


void Procstat::init()
{
 createFrame("OS/2 Processes");
 
 cnr = new PContainer(this);
 cnr->createContainer();
 cnr->setFont("8.Helv");

 showFrame();
}



BOOL Procstat::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
  {
   case WM_SIZE:
     if (cnr)
       WinSetWindowPos(cnr->hwnd, 0, 0, 0, 
                       SHORT1FROMMP(mp2), SHORT2FROMMP(mp2), 
                       SWP_SIZE);
     break;

   case WM_COMMAND:
     switch(SHORT1FROMMP(mp1))
      {
       case PROCSTAT_SETFONT: {
        OString font(OFontDialog().getFont("Set Font", "Tree Font"));
        if (font.getText())
          cnr->setFont(font);
        break; }

       case PROCSTAT_QUIT:
        WinSendMsg(hwnd, WM_CLOSE, NULL, NULL);
        break; 

       case PROCSTAT_REFRESH:
        if (cnr) {
         cnr->freeContainer();
         cnr->setupItems(); }
        break;
      }
     break;

   case WM_CLOSE:
     OApp::current().forceQuit();
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



BOOL PContainer::setupItems()
{
 PMINIRECORDCORE  prec;
 RECORDINSERT     ri;

 if (!getProcesses())         // OProcStat::getProcesses()
   OThrowPM("OProcStat::getProcesses() failed", 0, OException::unrecoverable);


 if ((prec = allocRecords(1)) == NULL)
   return(FALSE);

 prec->cb = sizeof(MINIRECORDCORE);
 prec->flRecordAttr = CRA_EXPANDED;
 prec->pszIcon = "OS2KRNL";
 prec->hptrIcon = hptr;

 memset(&ri, 0, sizeof(RECORDINSERT));
 ri.cb                = sizeof(RECORDINSERT);
 ri.pRecordOrder      = (PRECORDCORE) CMA_END;
 ri.pRecordParent     = (PRECORDCORE) NULL;
 ri.zOrder            = (USHORT) CMA_TOP;
 ri.cRecordsInsert    = 1;
 ri.fInvalidateRecord = FALSE;

 // insert them in one shot
 insertRecord(prec, &ri);

 return((insertChilds(prec, 0)) &&   // insert childs of kernel
        (insertChilds(prec, 1)) &&
        (setCnrInfo(CMA_LINESPACING | CMA_CXTREEINDENT)) &&
        (invalidateRecord()));
}


BOOL PContainer::insertChilds(PMINIRECORDCORE parentRecord, ULONG ulParent)
{
 PMINIRECORDCORE       prec;
 RECORDINSERT          ri;
 // we cannot use getFirst() because this member
 // is recursive and must not change the list cursors
 OListItem<OProcRecord> *cursor = ProcList.first();

 while(cursor)
  {
   if (cursor->item->PPid == ulParent)
    {
    if ((prec = allocRecords(1)) == NULL)
      return(FALSE);

     prec->cb = sizeof(MINIRECORDCORE);
     prec->flRecordAttr = CRA_EXPANDED;
     prec->pszIcon = cursor->item->Module;
     prec->hptrIcon = hptr;

     memset(&ri, 0, sizeof(RECORDINSERT));
     ri.cb                = sizeof(RECORDINSERT);
     ri.pRecordOrder      = (PRECORDCORE) CMA_END;
     ri.pRecordParent     = (PRECORDCORE) parentRecord;
     ri.zOrder            = (USHORT) CMA_TOP;
     ri.cRecordsInsert    = 1;
     ri.fInvalidateRecord = FALSE;
    
     if ((!insertRecord(prec, &ri)) ||
         (!insertChilds(prec, cursor->item->Pid)))
       return(FALSE);
    }
   cursor = cursor->next;
  }
 return(TRUE);
}



PContainer::PContainer(pOFrame Parent)
  : OContainer<MINIRECORDCORE, 
               MINIRECORDCORE>(PROCSTAT_CNR, Parent,
               CCS_AUTOPOSITION | CCS_MINIRECORDCORE,
               CV_TREE | CA_TREELINE | CV_TEXT),
    hptr(WinLoadPointer(HWND_DESKTOP, NULLHANDLE, PROCSTAT_MAIN))
{
 cnri.cyLineSpacing = 0;
 cnri.cxTreeIndent = 15;
}

PContainer::~PContainer() 
{
 freeContainer(); 
}


BOOL PContainer::setupDetails() 
{
 return(TRUE);
}

// end of source
