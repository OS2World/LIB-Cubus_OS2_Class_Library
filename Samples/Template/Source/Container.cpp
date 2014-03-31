// OCL Sample Application
// Container.cpp
// Implementation


// includes

#include "..\Source\Template.hpp"


#if defined(__EMX__)
  template class OSortedList<MyRecord>;
  template class OThread<MyContainer>;
  template class OContainer<CnrRecord, RECORDCORE>;
#endif


MyContainer::MyContainer(pOFrame Parent)
  : OContainer<CnrRecord, RECORDCORE>(SAMPLE_CNR,
                                      Parent,
                                      CCS_AUTOPOSITION,
                                      CV_DETAIL | CA_DETAILSVIEWTITLES |
                                      CA_CONTAINERTITLE | CA_TITLESEPARATOR),
    fillThread(this, &MyContainer::collectFiles, 32768) 
  {}


MyContainer::~MyContainer()
{
 cleanup();
}


PSZ MyContainer::isOfType() const
{ 
 return("MyContainer"); 
} 

MyContainer& MyContainer::init()
{
 winText << "Sample";
 createContainer();
 return(*this);
}



MyContainer& MyContainer::cleanup()
{
 freeContainer();
 reset();
 return(*this);
}


BOOL MyContainer::setupDetails()
{
 PFIELDINFO       firstFieldInfo;
 PFIELDINFO       pFieldInfo;
 FIELDINFOINSERT  fieldInfoInsert;

 pFieldInfo = (PFIELDINFO) WinSendMsg(hwnd,
                                      CM_ALLOCDETAILFIELDINFO,
                                      MPFROMLONG(2), NULL);
 firstFieldInfo = pFieldInfo;
 pFieldInfo->cb = sizeof(FIELDINFO);
 pFieldInfo->flData = CFA_STRING | CFA_HORZSEPARATOR | CFA_LEFT | CFA_SEPARATOR;
 pFieldInfo->flTitle = CFA_CENTER;
 pFieldInfo->pTitleData =  "Directory Name";
 pFieldInfo->offStruct = (ULONG)offsetof(CnrRecord, Name);
 pFieldInfo = pFieldInfo->pNextFieldInfo;

 pFieldInfo->cb = sizeof(FIELDINFO);
 pFieldInfo->flData = CFA_ULONG | CFA_HORZSEPARATOR | CFA_RIGHT |  CFA_SEPARATOR;
 pFieldInfo->flTitle = CFA_CENTER;
 pFieldInfo->pTitleData = "Position in List";
 pFieldInfo->offStruct = (ULONG)offsetof(CnrRecord, Position);
 pFieldInfo = pFieldInfo->pNextFieldInfo;

 fieldInfoInsert.cb = sizeof(FIELDINFOINSERT);
 fieldInfoInsert.pFieldInfoOrder = (PFIELDINFO)CMA_END;
 fieldInfoInsert.cFieldInfoInsert = 2;
 fieldInfoInsert.fInvalidateFieldInfo = TRUE;

 return((insertDetailInfo(firstFieldInfo, &fieldInfoInsert)) &&
        (invalidateDetails()));
}



BOOL MyContainer::setupItems()
{
 pCnrRecord  pcn;
 HPOINTER    hptr;

 if (isEmpty())
   return(TRUE);

 hptr = WinLoadPointer(HWND_DESKTOP, 0, SAMPLE_MAIN);

 pcn = allocRecords(numberOfElements());

 if(pcn)
  {
   RECORDINSERT  ri;
   ULONG         counter = 1;
   pCnrRecord    pcnFirst = pcn;
   pMyRecord     record = getFirst();

   while(record)
    {
     record->Position = counter;
     pcn->recordCore.cb = sizeof(RECORDCORE);
     pcn->recordCore.pszText = record->Name;
     pcn->recordCore.pszIcon = record->Name;
     pcn->recordCore.pszName = record->Name;
     pcn->recordCore.hptrIcon = hptr;
     pcn->Name = record->Name;
     pcn->Position = record->Position;
     pcn = (pCnrRecord) pcn->recordCore.preccNextRecord;
     record = getNext();
     counter++;
    }

   memset(&ri, 0, sizeof(RECORDINSERT));
   ri.cb                = sizeof(RECORDINSERT);
   ri.pRecordOrder      = (PRECORDCORE) CMA_END;
   ri.pRecordParent     = (PRECORDCORE) NULL;
   ri.zOrder            = (USHORT) CMA_TOP;
   ri.cRecordsInsert    = numberOfElements();
   ri.fInvalidateRecord = TRUE;

   // insert them in one shot
   if (insertRecord(pcnFirst, &ri))
    {
     WinSendMsg(parent, WM_CNR_STATUS, MPFROMP("Completed."), NULL);
     return(TRUE);
    }
  }
 return(FALSE);
}


void MyContainer::collectFiles()
{
 OSysInfo  info;
 OFcl      fcl;
 pOString  temp;
 pMyRecord record;
 ULONG     percent = 0;
 ULONG     counter = 1;

 WinSendMsg(parent, WM_CNR_PERCENTAGE, MPFROMSHORT(percent), NULL);

 info.getBootDrive();
 info.SysInfoVar + "\\OS2\\*";

 WinSendMsg(parent, WM_CNR_STATUS, MPFROMP("Collecting files..."), NULL);

 fcl.collect(info.SysInfoVar, TRUE, FALSE);

 WinSendMsg(parent, WM_CNR_STATUS, MPFROMP("Sorting records..."), NULL);
 temp = fcl.files.getFirst();
 while(temp) {
   record = new MyRecord;
   record->Name << temp;
   add(record);
   percent = (100 * counter) / fcl.files.numberOfElements();
   WinSendMsg(parent, WM_CNR_PERCENTAGE, MPFROMSHORT(percent), NULL);
   counter++;
   temp = fcl.files.getNext();
  }

 WinSendMsg(parent, WM_CNR_STATUS, MPFROMP("Inserting Records..."), NULL);
 WinSendMsg(parent, WM_CNR_FILLCNR, NULL, NULL);
 WinSendMsg(parent, WM_CNR_FILLED, NULL, NULL);
}

// end of source
