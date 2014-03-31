// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSysInfoVIO.cpp
// System Utility Functions

// class member functions


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

// $Header: W:/Projects/OCL/Source/rcs/OSysInfoVio.cpp 1.50 1996/08/11 23:49:32 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OSysInfo.hpp>

// Class OSysInfo


OSysInfoVIO::OSysInfoVIO()
  {}


OSysInfoVIO::~OSysInfoVIO()
{
 SysInfoList.reset();
}


PSZ OSysInfoVIO::isOfType() const
{ 
 return("OSysInfoVIO"); 
}


BOOL OSysInfoVIO::getDrives()
{
 ULONG   DriveNumber;
 ULONG   LogicalDriveMap;
 UCHAR   Drive[] = "C:";
 ULONG   Temp;
 HFILE   hfDiskHandle;
 ULONG   Action;
 CHAR    LABEL[30], tLABEL[30];

 if (DosQueryCurrentDisk(&DriveNumber, &LogicalDriveMap))
    return(FALSE);

 for(Temp=(ULONG)Drive[0]-'A', LogicalDriveMap>>=2;
     Temp<=(ULONG)('Z'-'A');
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
               if (!DosQueryFSInfo(Drive[0]-'@', FSIL_VOLSER, tLABEL, sizeof(tLABEL)))
                sprintf(LABEL, " [%s]", &tLABEL[5]);
              else
                strcpy(LABEL, " [ ]"); 
             }
           else
              strcpy(LABEL, " [ ]");
           SysInfoVar << (PSZ) Drive;
           SysInfoVar + (PSZ) LABEL;
           SysInfoList << SysInfoVar;
          }
     }

 return(TRUE);
}



BOOL OSysInfoVIO::getAllDrives()
{
 ULONG   DriveNumber;
 ULONG   LogicalDriveMap;
 UCHAR   Drive[] = "C:";
 ULONG   Temp;
 HFILE   hfDiskHandle;
 ULONG   Action;
 CHAR    LABEL[30], tLABEL[30];

 if (DosQueryCurrentDisk(&DriveNumber, &LogicalDriveMap))
    return(FALSE);

 for(Temp=(ULONG)Drive[0]-'A', LogicalDriveMap>>=2;
     Temp<=(ULONG)('Z'-'A');
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
               if (!DosQueryFSInfo(Drive[0]-'@', FSIL_VOLSER, tLABEL, sizeof(tLABEL)))
                sprintf(LABEL, " [%s]", &tLABEL[5]);
               else
                strcpy(LABEL, " [ ]"); 
             }
           else
              strcpy(LABEL, " [ ]");
           SysInfoVar << (PSZ) Drive;
           SysInfoVar + (PSZ) LABEL;
           SysInfoList << SysInfoVar;
          }
      else
       {  
        strcpy(LABEL, " [ ]");
        SysInfoVar << (PSZ) Drive;
        SysInfoVar + (PSZ) LABEL;
        SysInfoList << SysInfoVar;
       }
     }

 return(TRUE);
}

// check if "Drive" is a non-removable local drive

BOOL OSysInfoVIO::checkRemovable(PCSZ Drive)
{
 HFILE    hfDiskHandle;
 ULONG    Action;
 OString  drive((PSZ)Drive);

 if (!DosOpen(drive, &hfDiskHandle, &Action, 0, FILE_NORMAL,
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
     if (DDF.bData) return(TRUE);
  }
 return(FALSE);
}


// get var from system environment

BOOL OSysInfoVIO::getEnv(PCSZ env)
{
 PCSZ Buffer = "";

 if(DosScanEnv(env, &Buffer))
    return(FALSE);
 else
   {
    SysInfoVar << (PSZ) Buffer;
    return(TRUE);
   }
}


// get boot drive

BOOL OSysInfoVIO::getBootDrive()
{
 ULONG      ulDrive;
 UCHAR      Buffer[10];

 memset(&Buffer, 0, sizeof(Buffer));

 if(DosQuerySysInfo(QSV_BOOT_DRIVE, QSV_BOOT_DRIVE, &ulDrive, sizeof(ulDrive)))
   return(FALSE);
 else
   {
    Buffer[0] = (char) (ulDrive + 'A' - 1 ) ;
    Buffer[1] = ':';
    Buffer[2] = '\0';
    SysInfoVar << (PSZ) Buffer;
    return(TRUE);
   }
}


// get an env string from config.sys

BOOL OSysInfoVIO::getCfgEnv(PSZ env)
{
 ifstream config;
 PSZ      Buffer;
 OString  a(env);

 strupr(a);

 if (DosAllocMem((PPVOID) &Buffer,  0x0000ffffL, PAG_READ | PAG_WRITE | PAG_COMMIT))
   return(FALSE);

 if (getBootDrive())
   {
    SysInfoVar + (PSZ) "\\CONFIG.SYS";
    config.open(SysInfoVar);
    if (config.rdbuf())
     {
      while (config.getline(Buffer, 0x0000ffffL))
       {
        OString b(strupr(Buffer));
 
        if (strstr(b, a))
         {
          config.close();
          SysInfoVar << Buffer;
          DosFreeMem(Buffer);
          return(TRUE);
         }
       }
      config.close();
     }
   }

 DosFreeMem(Buffer);

 return(FALSE);
}


// find a file in path

BOOL OSysInfoVIO::findPathFile(PCSZ file)
{
 BYTE  Buffer[CCHMAXPATH];

 if (getEnv("PATH")) {
   if (!DosSearchPath(SEARCH_CUR_DIRECTORY, SysInfoVar, (PSZ) file, Buffer, sizeof(Buffer))) {
     SysInfoVar << (PSZ) Buffer;
     return(TRUE); }}
 return(FALSE);
}

// get OS/2-Version

BOOL OSysInfoVIO::getOSVer()
{
 ULONG major;
 ULONG minor;
 CHAR  Buffer[10];

 if ((!DosQuerySysInfo(QSV_VERSION_MAJOR, QSV_VERSION_MAJOR, &major, sizeof(major))) &&
     (!DosQuerySysInfo(QSV_VERSION_MINOR, QSV_VERSION_MINOR, &minor, sizeof(minor))) )
  {
   sprintf(Buffer, "%ld.%ld\0", major/10, minor);
   SysInfoVar << (PSZ) Buffer;
   return(TRUE);
  }

 return(FALSE);
}


BOOL OSysInfoVIO::getOSVer(double& version)
{
 ULONG major;
 ULONG minor;

 if ((!DosQuerySysInfo(QSV_VERSION_MAJOR, QSV_VERSION_MAJOR, &major, sizeof(major))) &&
     (!DosQuerySysInfo(QSV_VERSION_MINOR, QSV_VERSION_MINOR, &minor, sizeof(minor))) )
  {
   version = minor;
   version /= 100;
   version += major/10;
   return(TRUE);
  }
 return(FALSE);
}


BOOL OSysInfoVIO::clearRDOnly(PCSZ FileName)
{
 FILESTATUS  FileInfoBuf;
 APIRET        rc=3;

 if (!DosQueryPathInfo((PSZ) FileName, 1, &FileInfoBuf, sizeof(FILESTATUS)))
   {
    FileInfoBuf.attrFile = FILE_NORMAL;
#ifdef __BCPLUSPLUS__
    rc = DosSetPathInfo((PSZ)FileName, 1, &FileInfoBuf, sizeof(FILESTATUS), DSPI_WRTTHRU);
#else
    rc = DosSetPathInfo(FileName, 1, &FileInfoBuf, sizeof(FILESTATUS), DSPI_WRTTHRU);
#endif
   }
 return((rc==0) || (rc==2));
}


// end of source
