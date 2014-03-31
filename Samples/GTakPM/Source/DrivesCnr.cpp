// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// DrivesCnr.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/DrivesCnr.cpp 1.50 1996/08/11 23:48:06 B.STEIN Release $

#include "..\Source\GTakPM.hpp"


DrivesCnr::DrivesCnr(pGTPMWin Parent)
  : ParentWindow(Parent),
    OContainer<DirInfo, RECORDCORE>(GTPM_DRIVECNR, Parent,
               CCS_AUTOPOSITION | CCS_READONLY,
               CA_CONTAINERTITLE | CA_TITLESEPARATOR | CV_TREE | CA_TREELINE),
    populate(this, &DrivesCnr::collectDirectories, 65536),
    select(this, &DrivesCnr::beginSelect, 65536),
    hd_ico(HD_ICO, NULLHANDLE),
    hdS_ico(HD_INC_ICO, NULLHANDLE),
    cd_ico(CD_ICO, NULLHANDLE),
    cdS_ico(CD_INC_ICO, NULLHANDLE),
    folder_ico(FOLDER_ICO, NULLHANDLE),
    folderS_ico(FOLDER_INC_ICO, NULLHANDLE),
    openfolder_ico(FOPEN_ICO, NULLHANDLE),
    openfolderS_ico(FOPEN_INC_ICO, NULLHANDLE),
    dontKnow_ico(DONTKNOW_ICO, NULLHANDLE)
  {}


DrivesCnr::~DrivesCnr()
{
 DriveList.init();
}


BOOL DrivesCnr::setupDetails()
{
 return(TRUE);
}


BOOL DrivesCnr::setupItems()
{
 cnri.cxTreeIndent = -1;
 cnri.cxTreeLine   = -1;
 cnri.slBitmapOrIcon.cx = 32;
 cnri.slBitmapOrIcon.cy = 32;
 setCnrInfo(CMA_LINESPACING | CMA_CXTREEINDENT);

 populate.run();

 return(TRUE);
}


void DrivesCnr::collectDirectories()
{
 OSysInfo     info;
 CHAR         drive[40];
 pOString     tmp;
 pDirInfo     pdi, pdiFirst;
 RECORDINSERT ri;


 if (!info.getAllDrives())
   return;

 DosError(FERR_DISABLEHARDERR);

 ParentWindow->statline->setText("Scanning...");
 ParentWindow->statline->setRDOnly(TRUE);
 
 freeItems();
 DriveList.reset();
 DirList.reset();
 
 tmp = info.SysInfoList.getFirst();
 while (tmp) {
   strcpy(drive, tmp->getText());
   drive[2] = '\0';
   DriveList << drive;
   tmp = info.SysInfoList.getNext(); }

 pdi = allocRecords(DriveList.numberOfElements());
 pdiFirst = pdi;

 tmp = DriveList.getFirst();

 while (tmp) {
    ULONG       cbBuffer=sizeof(FSQBUFFER2) + (3 * CCHMAXPATH);
    PBYTE       pszFSDName;
    PVOID       fsqBuffer = (PVOID) new CHAR[cbBuffer];
    PFSQBUFFER2 pfsqBuffer = (PFSQBUFFER2) fsqBuffer;
    OString     FSystem;
    pDirItem    item;

    if (!DosQueryFSAttach(tmp->getText(), 0, FSAIL_QUERYNAME, pfsqBuffer, &cbBuffer)) {
      pszFSDName = ((PBYTE)pfsqBuffer->szName) + pfsqBuffer->cbName + 1;
      FSystem << (PSZ) pszFSDName; }
    delete pfsqBuffer;

    item = new DirItem;
    item->fullName << tmp->getText();
    item->fullName + "\\";
    item->name << tmp->getText();
    pdi->rc.pszIcon  = item->name;
    pdi->rc.pszText  = item->name;
    pdi->rc.pszName  = item->name;
    pdi->rc.pszTree  = item->name;
    pdi->dirItem     = item;
    pdi->selected    = FALSE;
    pdi->expanded    = FALSE;
    pdi->wasExpanded = FALSE;

    if (!FSystem)
      pdi->rc.hptrIcon = dontKnow_ico.hptr;
    else if (!strcmpi(FSystem, "CDFS"))
      pdi->rc.hptrIcon = cd_ico.hptr;
    else
      pdi->rc.hptrIcon = hd_ico.hptr;

    pdi = (pDirInfo) pdi->rc.preccNextRecord;
    tmp = DriveList.getNext();
 }

 memset(&ri, 0, sizeof(RECORDINSERT));
 ri.cb                = sizeof(RECORDINSERT);
 ri.pRecordOrder      = (PRECORDCORE) CMA_END;
 ri.pRecordParent     = (PRECORDCORE) NULL;
 ri.zOrder            = (USHORT) CMA_TOP;
 ri.cRecordsInsert    = DriveList.numberOfElements();
 ri.fInvalidateRecord = TRUE;
 insertRecord(pdiFirst, &ri);

 recurse(NULL, FALSE);

 ParentWindow->statline->setRDOnly(FALSE);
 ParentWindow->statline->setText("Ready.");

 DosError(FERR_ENABLEHARDERR);
}


void DrivesCnr::getDirectories(pDirInfo Parent, PSZ Directory, 
                               BOOL recursive, BOOL selected)
{
 PFILEFINDBUF3 pffb = NULL;
 OString       FileSpec(Directory);
 ULONG         bufSize = sizeof(FILEFINDBUF3) * 100;
 HDIR          hdir = HDIR_CREATE;
 ULONG         ulMaxFiles = 100;
 APIRET        rc;

 DosAllocMem((PPVOID)&pffb, bufSize, PAG_READ | PAG_WRITE | PAG_COMMIT);

 if (!pffb)
   return;

 FileSpec + "\\*";

 rc = DosFindFirst(FileSpec, &hdir, 
                   MUST_HAVE_DIRECTORY | FILE_HIDDEN | FILE_SYSTEM,
                   pffb, bufSize, &ulMaxFiles, FIL_STANDARD);

 while((!rc) && (ulMaxFiles > 2))
  {
   insertDirs(Parent, FileSpec, pffb, ulMaxFiles, selected);
   rc = DosFindNext(hdir, pffb, bufSize, &ulMaxFiles);
   if (recursive)
     recurse(Parent, FALSE, selected);
  }
 DosFindClose(hdir);

 DosFreeMem(pffb);
}


void DrivesCnr::insertDirs(pDirInfo Parent, PSZ Directory, 
                           PFILEFINDBUF3 pffb, ULONG cFiles, BOOL selected)
{
 PBYTE          pbBuf = (PBYTE) pffb;
 pDirInfo       pdiFirst, pdi;
 ULONG          i;
 PFILEFINDBUF3  pffbFile;
 RECORDINSERT   ri;
 ULONG          cFilesInserted = cFiles;

 if (!cFiles)
   return;

 pdi = allocRecords(cFiles);
 pdiFirst = pdi;

 for(i = 0; i < cFiles; i++)
  {
   pffbFile = (PFILEFINDBUF3) pbBuf;

   if (pffbFile->achName[0] != '.')
    {
     pDirItem item = new DirItem;

     item->fullName << Directory;
     item->fullName.rightCut('\\');
     item->fullName + "\\" + pffbFile->achName;
     item->name     << pffbFile->achName;

     pdi->rc.pszIcon        = item->name;
     pdi->rc.pszText        = item->name;
     pdi->rc.pszName        = item->name;
     pdi->rc.pszTree        = item->name;
     pdi->dirItem           = item;
     pdi->rc.hptrIcon       = selected ? folderS_ico.hptr : folder_ico.hptr;
     pdi->selected          = selected;
     pdi->expanded          = FALSE;
     pdi->wasExpanded       = FALSE;

     DirList.add(item);
     pdi = (pDirInfo) pdi->rc.preccNextRecord;   // Get the next container record
    }
   else
     cFilesInserted--;

   pbBuf += pffbFile->oNextEntryOffset;          // Point to the next file in the buffer
  }

 memset(&ri, 0, sizeof( RECORDINSERT));
 ri.cb                 = sizeof(RECORDINSERT);
 ri.pRecordOrder       = (PRECORDCORE) CMA_END;
 ri.pRecordParent      = (PRECORDCORE) Parent;
 ri.zOrder             = (USHORT) CMA_TOP;
 ri.cRecordsInsert     = cFilesInserted;
 ri.fInvalidateRecord  = TRUE;

 insertRecord(pdiFirst, &ri);
}



// Recurse into Subdirs

void DrivesCnr::recurse(pDirInfo Parent, BOOL recursive, BOOL selected)
{
 ULONG     scanFlag = CMA_FIRSTCHILD;
 pDirInfo  pdi = Parent;

 while(TRUE)
  {
   pdi = queryRecord(pdi, scanFlag, CMA_ITEMORDER);
   if ((!pdi) || ((LONG) pdi == -1))
     break;
   if (!Parent)
     getDirectories(pdi, pdi->dirItem->name, recursive, selected);
   else
     getDirectories(pdi, pdi->dirItem->fullName, recursive, selected);
   scanFlag = CMA_NEXT;
  }
}


void DrivesCnr::beginSelect()
{
 pDirInfo record = queryEmphasis();

 if (!record) 
   return;
 selectDirRecord(record);
 invalidateRecord(record);
}


void DrivesCnr::selectDirRecord(pDirInfo Parent)
{
 ULONG     scanFlag = CMA_FIRSTCHILD;
 pDirInfo  pdi = Parent;

 if (pdi->rc.pszTree[1] == ':') // its a drive, not a folder
   pdi->rc.hptrIcon = pdi->selected ? hdS_ico.hptr : hd_ico.hptr;
 else { // its a folder 
   if (pdi->expanded) 
     pdi->rc.hptrIcon = 
     pdi->selected ? openfolderS_ico.hptr : openfolder_ico.hptr;
   else
     pdi->rc.hptrIcon = 
     pdi->selected ? folderS_ico.hptr : folder_ico.hptr; }

 while(TRUE)
  {
   pdi = queryRecord(pdi, scanFlag, CMA_ITEMORDER);
   if ((!pdi) || ((LONG) pdi == -1))
     break;
   pdi->selected = Parent->selected;
   selectDirRecord(pdi);
   scanFlag = CMA_NEXT;
  }
}


// end of source
