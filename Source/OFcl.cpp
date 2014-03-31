// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFcl.CPP

// member functions of fcl FileCollector

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Neither the name Cubus nor the name Team OCL may be used to
 *    endorse or promote products derived from this software
 *    without specific prior written permission.
 * 3. See OCL.INF for a detailed copyright notice.
 *
 *              THIS SOFTWARE IS PROVIDED ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


// $Header: W:/Projects/OCL/Source/rcs/OFcl.cpp 1.50 1996/08/11 23:49:15 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OFcl.hpp>


OFcl::OFcl()    // default constructor
   : ulMaxFiles(200), space(0), found(0),
   checkDate(FALSE), checkTime(FALSE),
   AttrMask(FILE_SYSTEM | FILE_HIDDEN | FILE_ARCHIVED | FILE_READONLY),
   DateTime(NULL),
   stopASAP(FALSE)
{
 bufSize = sizeof(FILEFINDBUF3) * ulMaxFiles;
 setupFilebuf();
}


OFcl::~OFcl()   // destructor
{
 fclstop();
 DosFreeMem(pffb);
 // cleanup the Lists
 dirs.reset();
 files.reset();
}


PSZ OFcl::isOfType() const
{ 
 return("OFcl"); 
}


void OFcl::setupFilebuf()      // allocate the filefind3 buffer
{
 DosAllocMem((PPVOID)&pffb,  bufSize, PAG_READ | PAG_WRITE | PAG_COMMIT);
}


void OFcl::fclinit()
{
 // cleanup the Lists
 dirs.reset();
 files.reset();
 space = 0;
 found = 0;
 checkDate = FALSE;
 checkTime = FALSE;
 DateTime = NULL;
 AttrMask = FILE_SYSTEM | FILE_HIDDEN | FILE_ARCHIVED | FILE_READONLY;
 ulMaxFiles = 200;
 stopASAP = FALSE;
}


void OFcl::setCheck(BOOL date, BOOL time)
{
 checkTime = time;
 checkDate = date; 
}


void OFcl::fclstop()
{
 stopASAP = TRUE;
}


// this member handles the collect

void OFcl::collect(PCSZ spec, BOOL rec, BOOL local)
{
 ULONG    sDrive;
 ULONG    ulDriveMap, ulDriveNum=0L;
 PSZ      pathname = new CHAR[CCHMAXPATH];
 OString  Spec(spec);

 strupr(Spec);

 recurse = rec;

 if (local)
  {
   finddrives(spec);
   return;
  }

 if(*(Spec.getText()+1)==':')
   {
    sDrive = (ULONG) ((*Spec.getText()) - '@');
    if (DosSetDefaultDisk(sDrive))
      return;
    dirs << Spec;
   }
 else
   {
    if (strchr(Spec, '\\'))
      return;
    DosQueryCurrentDisk(&ulDriveNum, &ulDriveMap);
    DosQueryCurrentDir(ulDriveNum, (PBYTE)pathname, &ulDriveMap);
    strcat(pathname, "\\");
    strcat(pathname, Spec);
    dirs << pathname;
   }

 ext << (PSZ) strrchr(Spec, '\\');
 findfiles(dirs.last());
 delete[] pathname;
 return;
}


void OFcl::finddirs(PSZ dir)
{
 HDIR dhdir = HDIR_CREATE;

 strcpy(strrchr(dir, '\\'), "\\*");
 ulMaxFiles = 200;

 rc = DosFindFirst(dir, &dhdir, MUST_HAVE_DIRECTORY,
                       pffb, bufSize, &ulMaxFiles, FIL_STANDARD);
 while((!rc) && (!stopASAP))
   {
    if (ulMaxFiles)
       adddirs(dir);
    ulMaxFiles = 200;
    rc = DosFindNext(dhdir, pffb, bufSize, &ulMaxFiles);
   }

 DosFindClose(dhdir);
}


void OFcl::findfiles(OListItem<OString> *tmp)  // find all files
{
 OListItem<OString> *strItem = tmp;

 while((strItem) && (!stopASAP))
  {
   HDIR hdir = HDIR_CREATE;

   ulMaxFiles = 200;
   filespec << strItem->item->getText();

   rc = DosFindFirst(strItem->item->getText(), &hdir, (ULONG) AttrMask,
                     pffb, bufSize, &ulMaxFiles, FIL_STANDARD);

   while((!rc) && (!stopASAP))
    {
     if (ulMaxFiles)
       addfiles();
     ulMaxFiles = 200;
     rc = DosFindNext(hdir, pffb, bufSize, &ulMaxFiles);
    }

   DosFindClose(hdir);

   if ((recurse) && (!stopASAP)) {
    finddirs(strItem->item->getText());
    strItem = strItem->next; }
   else
     break;
  }
}


void OFcl::addfiles()  // add all found files to a List
{
 PFILEFINDBUF3   pffbFile;
 ULONG           i;
 PSZ             Buf = new CHAR[CCHMAXPATH];

 strcpy(Buf, filespec);

 tmp = (PBYTE) pffb;

 for(i = 0; (i < ulMaxFiles) && (!stopASAP); i++)
   {
    BOOL matches = TRUE;

    pffbFile = (PFILEFINDBUF3) tmp;
    strcpy(strrchr(Buf, '\\')+1, pffbFile->achName);
    if (checkDate)
      matches = hasDate(pffbFile);
    if (matches)
      if (checkTime)
        matches = hasTime(pffbFile);
    if (matches)
      files << Buf;
    found++;
    space += pffb->cbFileAlloc;
    tmp += pffbFile->oNextEntryOffset;                // Point to the next file in the buffer
   }
 delete[] Buf;
}


void OFcl::adddirs(PCSZ dir)
{
 PFILEFINDBUF3   pffbFile;
 ULONG           i;
 PSZ             Buf = new CHAR[CCHMAXPATH];

 tmp = (PBYTE) pffb;

 for(i = 0; (i < ulMaxFiles) && (!stopASAP); i++)
   {
    pffbFile = (PFILEFINDBUF3) tmp;

    if (((BOOL)(pffbFile->attrFile&FILE_DIRECTORY)) && (pffbFile->achName[0]!='.'))
     {
      strcpy(Buf, dir);
      strcpy(strrchr(Buf, '\\')+1, pffbFile->achName);
      strcat(Buf, ext.getText());
      dirs << Buf;
     }
    tmp += pffbFile->oNextEntryOffset;                // Point to the next file in the buffer
   }

 delete[] Buf;
}


void OFcl::finddrives(PCSZ spec)
{
 ULONG   DriveNumber; 
 ULONG   LogicalDriveMap;
 UCHAR   Drive[] = "c:";
 ULONG   Temp;
 HFILE   hfDiskHandle;
 ULONG   Action;

 if (DosQueryCurrentDisk(&DriveNumber, &LogicalDriveMap))
    return;

 for(Temp=(ULONG)Drive[0]-'a', LogicalDriveMap>>=2;
     Temp<=(ULONG)('z'-'a');
     Temp++, Drive[0]++, LogicalDriveMap>>=1)
      {
       if(!(LogicalDriveMap&0x1))
          continue;

       if (!DosOpen((PSZ)Drive, &hfDiskHandle, &Action, 0, FILE_NORMAL,
                       OPEN_ACTION_OPEN_IF_EXISTS, OPEN_FLAGS_DASD | 
                       OPEN_FLAGS_FAIL_ON_ERROR | OPEN_FLAGS_NOINHERIT | 
                       OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_READONLY, 0))
           {
            struct _PPF  
             {
              BYTE        bCommandInformation;
              BYTE        bDriveUnit;
             } PPF={0, 0};

            struct _DDF                
             {
              BYTE        bData;
             } DDF;

            ULONG       ulParamLengthInOut=sizeof(PPF);
            ULONG       ulDataLengthInOut=sizeof(DDF);

            DosDevIOCtl(hfDiskHandle, IOCTL_DISK, DSK_BLOCKREMOVABLE,
                &PPF, ulParamLengthInOut, &ulParamLengthInOut,
                &DDF, ulDataLengthInOut, &ulDataLengthInOut);
            DosClose(hfDiskHandle);
            if(DDF.bData)
              {
               OString buffer((PSZ) Drive);

               buffer + (PSZ) strchr(spec, '\\');
               collect(buffer, recurse, FALSE);
              }
          }
      }
 return;
}


BOOL OFcl::hasTime(PFILEFINDBUF3 buf)
{
 if (!DateTime)
   return(FALSE);
 return((buf->ftimeCreation.minutes == DateTime->minutes) &&
         (buf->ftimeCreation.hours == DateTime->hours));
}


BOOL OFcl::hasDate(PFILEFINDBUF3 buf)
{
 if (!DateTime)
   return(FALSE);
 return((buf->fdateCreation.day == DateTime->day) &&
        (buf->fdateCreation.month == DateTime->month) &&
        (buf->fdateCreation.year == DateTime->year));
}


// end of source
