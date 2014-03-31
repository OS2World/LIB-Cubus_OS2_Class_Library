// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSysLevel.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/OSysLevel.cpp 1.50 1996/08/11 23:49:33 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OSysLevel.hpp>
#include <OMessage.hpp>


OSysLevel::OSysLevel()
{
 memset(&slfheader, 0, sizeof(SLFHEADER));
 strcpy((PSZ)&slfheader.achSignature, "SYSLEVEL");
 slfheader.usSignature   = 1;
 slfheader.usSlfVersion  = 1;
 slfheader.ulTableOffset = sizeof(SLFHEADER);
 memset(&systable, 0, sizeof(SYSTABLE));
}


OSysLevel::OSysLevel(SLFHEADER& header, SYSTABLE&  table)
{
 memcpy(&slfheader, &header, sizeof(SLFHEADER));
 memcpy(&systable,  &table,  sizeof(SYSTABLE));
}   


OSysLevel::OSysLevel(const OSysLevel& sl)
{
 setHeader(sl.getHeader());
 setSysTable(sl.getSysTable());
}
   

OSysLevel::OSysLevel(PCSZ fileName)
 : slfile(fileName)
{
 memset(&slfheader, 0, sizeof(SLFHEADER));
 strcpy((PSZ)&slfheader.achSignature, "SYSLEVEL");
 slfheader.usSignature   = 1;
 slfheader.usSlfVersion  = 1;
 slfheader.ulTableOffset = sizeof(SLFHEADER);
 memset(&systable, 0, sizeof(SYSTABLE));
}


OSysLevel::~OSysLevel()
 {}


PSZ OSysLevel::isOfType() const
{
 return("OSysLevel");
} 



OSysLevel& OSysLevel::readFromFile(PCSZ fileName)
{
#ifdef __IBMCPP__
 ifstream sysfile(fileName);
#else
 ifstream sysfile((PSZ)fileName);
#endif
 OString  stamp(10);

 if (!sysfile)
   throw OVioException(OMessage(220, OCL::MSGFILE, (PSZ)fileName),
                       ERROR_READ_FAULT);

 sysfile.read((PSZ)&slfheader, sizeof(SLFHEADER));
 sysfile.read((PSZ)&systable, sizeof(SYSTABLE));

 memcpy(stamp.getText(), &slfheader.achSignature,
        sizeof(slfheader.achSignature));

 if (stamp != "SYSLEVEL")
   throw OVioException(OMessage(221, OCL::MSGFILE, (PSZ)fileName),
                       ERROR_INVALID_DATA);

 return(*this);
}

OSysLevel& OSysLevel::writeToFile(PCSZ fileName)
{
#ifdef __IBMCPP__
 ofstream sysfile(fileName);
#else
 ofstream sysfile((PSZ)fileName);
#endif

 if (!sysfile)
   throw OVioException(OMessage(220, OCL::MSGFILE, (PSZ)fileName),
                       ERROR_WRITE_FAULT);

 sysfile.write((PSZ)&slfheader, sizeof(SLFHEADER));
 sysfile.write((PSZ)&systable, sizeof(SYSTABLE));

 return(*this);
}


OSysLevel& OSysLevel::read()
{
 if (!slfile)
   throw OVioException(OCL::error(222), 0);

 return(readFromFile(slfile));
}


OSysLevel& OSysLevel::write()
{
 if (!slfile)
   throw OVioException(OCL::error(222), 0);

 return(writeToFile(slfile));
}


OSysLevel& OSysLevel::setSysTable(const SYSTABLE& stable)
{
 memcpy(&systable,  &stable, sizeof(SYSTABLE));
 return(*this);
}
 
OSysLevel& OSysLevel::setHeader(const SLFHEADER& slh)
{
 memcpy(&slfheader, &slh, sizeof(SLFHEADER));
 return(*this);
}

OSysLevel& OSysLevel::setFileName(PCSZ fileName)
{
 slfile << fileName;
 return(*this);
}


OSysLevel& OSysLevel::setDate()
{
 DATETIME dt;

 DosGetDateTime(&dt);
 sprintf((PSZ)&slfheader.achJulian, "%ld", DTToJulian(dt));

 return(*this);
}

OSysLevel& OSysLevel::setDate(DATETIME& dt)
{
 sprintf((PSZ)&slfheader.achJulian, "%ld", DTToJulian(dt));
 return(*this);
}


OSysLevel& OSysLevel::setDate(PSZ dateStr)
{
 if (!dateStr)
   memset(&slfheader.achJulian, 0, sizeof(slfheader.achJulian));
 else
   memcpy(&slfheader.achJulian, dateStr,
          strlen(dateStr) < sizeof(slfheader.achJulian) ?
          strlen(dateStr) : sizeof(slfheader.achJulian));
 return(*this);
}


OSysLevel& OSysLevel::setTableOffset(ULONG offset) 
{
 slfheader.ulTableOffset = offset;
 return(*this);
}


OSysLevel& OSysLevel::setSysId(USHORT sysId)
{
 systable.usSysId = sysId;
 return(*this);
}


OSysLevel& OSysLevel::setSysEdition(BYTE sysEd)
{
 systable.bSysEdition = sysEd;
 return(*this);
}


OSysLevel& OSysLevel::setSysVersion(BYTE sysVer)
{
 systable.bSysVersion = sysVer;
 return(*this);
}


OSysLevel& OSysLevel::setSysModify(BYTE sysMod)
{
 systable.bSysModify = sysMod;
 return(*this);
}


OSysLevel& OSysLevel::setSysDate(USHORT usDate)
{
 systable.usSysDate = usDate;
 return(*this);
}


OSysLevel& OSysLevel::setCsdLevel(PSZ level)
{
 if (!level)
   memset(&systable.achCsdLevel, 0, sizeof(systable.achCsdLevel));
 else
   memcpy(&systable.achCsdLevel, level,
          strlen(level) < sizeof(systable.achCsdLevel) ?
          strlen(level) : sizeof(systable.achCsdLevel));
 return(*this);
}


OSysLevel& OSysLevel::setCsdPrev(PSZ level)
{
 if (!level)
   memset(&systable.achCsdPrev, 0, sizeof(systable.achCsdPrev));
 else
   memcpy(&systable.achCsdPrev, level,
          strlen(level) < sizeof(systable.achCsdPrev) ?
          strlen(level) : sizeof(systable.achCsdPrev));
 return(*this);
}


OSysLevel& OSysLevel::setSysName(PSZ sysname)
{
 if (!sysname)
   memset(&systable.achSysName, 0, sizeof(systable.achSysName));
 else
   memcpy(&systable.achSysName, sysname,
          strlen(sysname) < sizeof(systable.achSysName) ?
          strlen(sysname) : sizeof(systable.achSysName));
 return(*this);
}


OSysLevel& OSysLevel::setCompId(PSZ compid)
{
 if (!compid)
   memset(&systable.achCompId, 0, sizeof(systable.achCompId));
 else
   memcpy(&systable.achCompId, compid,
          strlen(compid) < sizeof(systable.achCompId) ?
          strlen(compid) : sizeof(systable.achCompId));
 return(*this);
}


OSysLevel& OSysLevel::setRefreshLevel(BYTE refLevel)
{
 systable.bRefreshLevel = refLevel;
 return(*this);
}


OSysLevel& OSysLevel::setType(PSZ type)
{
 if (!type)
   memset(&systable.achType, 0, sizeof(systable.achType));
 else
   memcpy(&systable.achType, type,
          strlen(type) < sizeof(systable.achType) ?
          strlen(type) : sizeof(systable.achType));
 return(*this);
}


const OSysLevel& OSysLevel::getDate(DATETIME& dt) const
{
 memset(&dt, 0, sizeof(DATETIME));
 JulianToDT(atol((PSZ)&slfheader.achJulian), dt);
 return(*this);
}



ULONG OSysLevel::getTableOffset() const
{
 return(slfheader.ulTableOffset);
}


 
USHORT OSysLevel::getSysId() const
{
 return(systable.usSysId);
}



USHORT OSysLevel::getSysDate() const
{
 return(systable.usSysDate);
}



PCSZ OSysLevel::getFileName() const
{
 return(slfile.getText());
}



PCSZ OSysLevel::getDateAsStr(OString& str) const
{
 DATETIME dt;

 str << "00.00.0000";
 JulianToDT(atol((PSZ)&slfheader.achJulian), dt);
 sprintf(str.getText(), "%02ld.%02ld.%ld", dt.day, dt.month, dt.year);
 return(str.getText());
}



PCSZ OSysLevel::getCsdLevel() const
{
 return((PCSZ)systable.achCsdLevel);
}



PCSZ OSysLevel::getCsdPrev() const
{
 return((PCSZ)systable.achCsdPrev);
}



PCSZ OSysLevel::getSysName() const
{
 return((PCSZ)systable.achSysName);
}



PCSZ OSysLevel::getCompId() const
{
 return((PCSZ)systable.achCompId);
}



PCSZ OSysLevel::getType() const
{
 return((PCSZ)systable.achType);
}



BYTE OSysLevel::getSysEdition() const
{
 return(systable.bSysEdition);
}



BYTE OSysLevel::getSysVersion() const
{
 return(systable.bSysVersion);
}



BYTE OSysLevel::getSysModify() const
{
 return(systable.bSysModify);
}



BYTE OSysLevel::getRefreshLevel() const
{
 return(systable.bRefreshLevel);
}



const SLFHEADER& OSysLevel::getHeader() const
{
 return(slfheader);
}


const SYSTABLE& OSysLevel::getSysTable() const
{
 return(systable);
}


// conversion routines for julian dates
// these funtions are strictly for internal use only
// and will be moved to the ODate when this class
// is ready for shipping

const INT daysToMonth[2][13] =
{
{ 0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
{ 0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

const LONG ReformJulianDay = 2361221;
const INT  ReformDays      = 11;
const INT  ReformYEAR      = 1752;
const INT  ReformDAY       = 2;
const INT  ReformMONTH     = 9;

void OSysLevel::JulianToDT(LONG julian, DATETIME& dt) const
{
 INT  century;
 INT  days;
 INT  j;
 LONG fours = julian / 1461;
 LONG years = fours * 4;
 BOOL leap  = FALSE;

 if (julian > ReformJulianDay) {
   century = (INT) ((julian - 1684595 ) / 36524.25);
   julian += (century * 3L / 4L) - 2;  }

 days = julian % 1461;

 for (j = 1; j < 5; ++j) if (365 * j >= days) break;
 --j;

 if (j == 0)
  {
   if (years <= 4712 + ReformYEAR) {
     leap = TRUE;
     ++days; }
   else {
     if ((years - 4712 ) % 100 != 0 || (years - 4712 ) % 400 == 0) {
       leap = TRUE;
       ++days; }}
  }
 else
   days -= 365 * j, years += j;

 for (j = 1; j < 12; ++j)
   if (days <= daysToMonth[leap][j]) break;

 dt.month = j;
 dt.day   = days - daysToMonth[leap][j - 1];
 dt.year  = years - 4712;
 if (dt.year <= 0 ) dt.year--;
}

LONG OSysLevel::DTToJulian (DATETIME& dt) const
{
 INT  month_days;
 INT  century;
 INT  years      = dt.year + 4712;
 BOOL leap       = FALSE;
 LONG year_days  = 365L * (LONG) years + (LONG)(years >> 2);
 LONG julian_date;

 if (dt.year <= 0) dt.year++;

 if ((years & 3 ) == 0) {
      leap = TRUE;
      year_days--; }

 month_days  = daysToMonth[leap][dt.month - 1];
 julian_date = year_days + (long int)(month_days + dt.day);

 if (julian_date > ReformJulianDay)
  {
   years = dt.year - 300;
   if (dt.month <= 2) years--;
   century = years / 100;
   julian_date -= ((century * 3) / 4 + 1);
  }
 return(julian_date);
}

// end of source
