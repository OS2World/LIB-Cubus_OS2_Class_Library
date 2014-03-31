// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ODate.hpp


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


// $Header: W:/Projects/OCL/Source/rcs/ODate.cpp 1.50 1996/08/11 23:49:13 B.STEIN Release $


#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ODate.hpp>
#include <OMessage.hpp>
#include <time.h>

// module constants 

static const INT
  daysToMonth [2][13] =
    {
    { 0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    { 0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
    };

static const ODate::MDY
  reformMDY = 
    {
     ODate::September, 2, 1752
    };

static const LONG
  reformJulianDayNumber = 2361221;

static const INT
  reformDays = 11;


// member functions


ODate::ODate()
{
#if (defined (__IBMCPP__) || defined (__HIGHC__))
  _tzset();
#endif
#if (defined (__EMX__) || defined (__WATCOM_CPLUSPLUS__))
  tzset();
#endif

 _now_time_t = time(0);
 _now_tm     = *localtime(&_now_time_t);
 julian      = today().julian;

 calculate();
}



ODate::ODate(INT aYear, INT aDay)
{
 ODate::MDY mdy = DYToMDY(aDay, aYear);

 init(mdy.month, mdy.day, mdy.year);
}



ODate::ODate(const _CDATE &cDate)
{
 init((ODate::Month)cDate.month, cDate.day, cDate.year);
}



ODate::ODate(INT aDay, Month aMonth, INT aYear)
{
 init(aMonth, aDay, aYear);
}



ODate::ODate(Month aMonth, INT aDay, INT aYear)
{
 init(aMonth, aDay, aYear);
}



ODate::ODate(const ODate& aDate)
  : julian(aDate.julian)
  {}



ODate::ODate(ULONG julianDayNumber)
  : julian(julianDayNumber)
  {}


ODate::~ODate()
  {}


PSZ ODate::isOfType() const
{
 return("ODate");
}


ostream& operator << (ostream &aStream, const ODate &aDate)
{
 return(aStream << (PSZ) aDate.asString());
}


OString ODate::asString(DateFormat dateFmt) const
{
 OString  temp(CCHMAXPATH);

 switch(dateFmt)
  {
   case sd_pi:          // [-31] 7837
     sprintf(temp,"[%ld] %04ld", prefix, integer);
     break;
   case sd_pif1:        // [-31] 7837.5
     sprintf(temp,"[%ld] %04ld.%01ld", prefix, integer, fraction/1000);
     break;
   case sd_pif2:        // [-31] 7837.53
     sprintf(temp,"[%ld] %04ld.%02ld", prefix, integer, fraction/100);
     break;
   case sd_pif3:        // [-31] 7837.532
     sprintf(temp,"[%ld] %04ld.%03ld", prefix, integer, fraction/10);
     break;
   case sd_pif4:        // [-31] 7837.5321
     sprintf(temp,"[%ld] %04ld.%04ld", prefix, integer, fraction);
     break;
   case sd_if:          // 7837
     sprintf(temp,"%04ld", integer);
     break;
   case sd_if1:         // 7837.5
     sprintf(temp,"%04ld.%01ld", integer, fraction/1000);
     break;
   case sd_if2:         // 7837.53 
     sprintf(temp,"%04ld.%02ld", integer, fraction/100);
     break;
   case sd_if3:         // 7837.532
     sprintf(temp,"%04ld.%03ld", integer, fraction/10);
     break;
   case sd_if4:         // 7837.5321
     sprintf(temp,"%04ld.%04ld", integer, fraction);
     break;
   default: {
     COUNTRYCODE ctryCode = { 0, 0 };
     COUNTRYINFO ctryInfo;
     ULONG       bytes;
     PSZ         fmts[] = {
                           "%m-%d-%y",
                           "%d-%m-%y",
                           "%y-%m-%d",
                           "%m-%d-%Y",
                           "%d-%m-%Y",
                           "%Y-%m-%d"
                          };

     DosQueryCtryInfo(sizeof(ctryInfo), &ctryCode, &ctryInfo, &bytes );

     ULONG x = ctryInfo.fsDateFmt;

     if (x > yy_mm_dd)
         x = mm_dd_yy;

     OString fmt(fmts[x]);
     fmt.getText()[3] = fmt.getText()[6] = ctryInfo.szDateSeparator[0];
     return(asString(fmt));  } 
  }

 return(OString(temp));
};


OString ODate::asString(PCSZ fmt) const
{
 OString   result(((fmt != NULL) ? strlen(fmt) : 0) + 3);
 OString   tempFmt(fmt);
 tm        dummy = { 0 };

 dummy.tm_mon    = (INT)(monthOfYear()) - (INT)January;
 dummy.tm_mday   = dayOfMonth();

 if ((strchr(tempFmt, 'y')) && (year() < 1900))
    dummy.tm_year = year();
 else
    dummy.tm_year = year() - 1900;

 mktime(&dummy);

 strftime((PSZ)result, result.length(), fmt, &dummy);

 return(OString(result));
}


_CDATE ODate::asCDATE() const
{
 CDATE result = {
                 (UCHAR) dayOfMonth(),
                 (UCHAR) monthOfYear(),
                 (UCHAR) year()
                };
 return(result);
}


OString ODate::dayName() const
{
 return(ODate::dayName(dayOfWeek()));
}


OString ODate::monthName() const
{
 return(ODate::monthName(monthOfYear()));
}


INT ODate::dayOfMonth() const
{
 ODate::MDY mdy = ODate::julianToMDY(julian);

 return(mdy.day);
}


INT ODate::dayOfYear() const
{
 ODate::MDY mdy = ODate::julianToMDY(julian);

 return(daysToMonth[ODate::isLeapYear(mdy.year)][mdy.month - 1] + mdy.day);
}



ODate::Month ODate::monthOfYear() const
{
 return(ODate::julianToMDY(julian).month);
}


INT ODate::year() const
{
 return(ODate::julianToMDY(julian).year);
}


OString ODate::dayName(ODate::DayOfWeek aDay)
{
 return(OString(OMessage(OCL_ODATE_MON + (ULONG) aDay, OCL::MSGFILE)));
};


OString ODate::monthName(ODate::Month aMonth)
{
 return(OString(OMessage(OCL_ODATE_JAN + (ULONG) aMonth, OCL::MSGFILE)));
}


INT ODate::daysInMonth(ODate::Month aMonth, INT aYear)
{
 BOOL leap   = (ODate::isLeapYear(aYear) != FALSE);
 INT  result = daysToMonth[leap][aMonth]
               -
               daysToMonth[leap][aMonth - 1];

 if ((aYear == reformMDY.year) &&
     (aMonth == reformMDY.month))
   result -= reformDays;
 return(result);
}


INT ODate::daysInYear(INT aYear)
{
 INT result = 365 + ODate::isLeapYear(aYear);

 if (aYear == reformMDY.year)
   result -= reformDays;

 return(result);
}



BOOL ODate::isLeapYear(INT aYear)
{
 INT  y      = aYear + (aYear < 0);

 return((y % 4 == 0) && ((aYear < reformMDY.year) || (y % 100 != 0) || (y % 400 == 0)));
}


BOOL ODate::isValid(ODate::Month aMonth, INT aDay, INT aYear)
{
 INT  days   = reformMDY.day + reformDays;

 if (aMonth >= January  &&
     aMonth <= December &&
     aDay > 0           &&
     aYear != 0)
  { 
   if ((aYear == reformMDY.year) && (aMonth == reformMDY.month))
     return (aDay <= (ODate::daysInMonth(aMonth, aYear) + reformDays) &&
            (aDay <= reformMDY.day || aDay > days));
   else
     return (aDay <= ODate::daysInMonth(aMonth, aYear));
  }

 return(FALSE);
}



ODate& ODate::init(ODate::Month aMonth, INT aDay, INT aYear)
{
 if (ODate::isValid(aMonth, aDay, aYear))
  {
   ODate::MDY mdy = { aMonth, aDay, aYear };
   julian         = ODate::MDYToJulian(mdy);
  }
 else
   julian = 0;

 return(*this);
}


ODate::MDY ODate::julianToMDY(ULONG julianDayNumber)
{
 ODate::MDY result;
 INT        century,
            days,
            j;
 BOOL       leap = FALSE;

 if (julianDayNumber > reformJulianDayNumber)
  {
   century          = (julianDayNumber - 1684595) / 36524.25;
   julianDayNumber += (century * 3L / 4L) - 2;
  }

 LONG fours = julianDayNumber / 1461,
      years = fours * 4;

 days = julianDayNumber % 1461;

 for (j = 1; j < 5; ++j)
   if (365 * j >= days) break;

 --j;

 if (j == 0)
  {
   if ( years <= 4712 + reformMDY.year )
     {
      leap = TRUE;
      ++days;
     }
   else
     {
      if ( ( years - 4712 ) % 100 != 0 || ( years - 4712 ) % 400 == 0 )
        {
         leap = TRUE;
         ++days;
        }
     }
  }
 else
  {
   days -= 365 * j;
   years += j;
  }

 for (j = 1; j < 12; ++j)
   if (days <= daysToMonth[leap][j]) break;

 result.month = (ODate::Month) j;
 result.day   = days - daysToMonth[leap][j - 1];
 result.year  = years - 4712;

 if (result.year <= 0)
   result.year--;

 return result;
}

ODate::MDY ODate::DYToMDY(INT aDay, INT aYear)
{
 ODate::MDY   result;

 result.month = ODate::January,
 result.day   = aDay,
 result.year  = aYear;

 if (ODate::isValid(aYear, aDay))
   while(TRUE)
    {
     INT maxDay = ODate::daysInMonth(result.month, result.year);
     if ( result.day > maxDay )
          result.month = (ODate::Month) ( result.month + 1 ),
          result.day -= maxDay;
     else
        break;
    }

 if (result.year == reformMDY.year &&
     result.month == reformMDY.month &&
     result.day > reformMDY.day )
   result.day += reformDays;

 return result;
}


ULONG ODate::MDYToJulian(MDY aDate)
{
 aDate.year   += (aDate.year < 0);

 INT    years = aDate.year + 4712,
        month_days,
        century;
 BOOL   leap  = FALSE;

 LONG   year_days = 365L * (LONG) years + (LONG)( years >> 2 ),
        julian_date;

 if ((years & 3) == 0)
   {
    leap = TRUE,
    year_days--;
   }

 month_days  = daysToMonth[leap][aDate.month - 1];
 julian_date = year_days + (LONG)( month_days + aDate.day);

 if (julian_date > reformJulianDayNumber)
   {
    years = aDate.year - 300;
    if ( aDate.month <= 2)
       years--;
    century = years / 100;
    julian_date -= ( ( century * 3 ) / 4 + 1 );
   }

 return(julian_date);
}


ODate ODate::today()
{
#if (defined (__IBMCPP__) || defined (__HIGHC__))
  _tzset();
#endif
#if (defined (__EMX__) || defined (__WATCOM_CPLUSPLUS__))
  tzset();
#endif

 time_t _now_time_t = time(0);
 tm     _now_tm     = *localtime(&_now_time_t);

 return(ODate(_now_tm.tm_year + 1900, _now_tm.tm_yday + 1));
}
 

ODate ODate::now()
{
 return ODate();
}


ODate::DayOfWeek ODate::dayOfWeek() const
{
 return((ODate::DayOfWeek)(julian % 7));
}


ULONG ODate::julianDate() const
{
 return(julian);
}

 
BOOL ODate::operator == (const ODate &aDate) const
{
 return(julian == aDate.julian);
}


BOOL ODate::operator != (const ODate &aDate) const
{
 return(julian != aDate.julian);
}


BOOL ODate::operator <  (const ODate &aDate) const
{
 return(julian <  aDate.julian);
}


BOOL ODate::operator <= (const ODate &aDate) const
{
 return(julian <= aDate.julian);
}


BOOL ODate::operator >  (const ODate &aDate) const
{
 return(julian >  aDate.julian);
}


BOOL ODate::operator >= (const ODate &aDate) const
{
 return(julian >= aDate.julian);
}
 

ODate ODate::operator + (INT numDays) const
{
 return(ODate(julian + numDays));
}


ODate ODate::operator - (INT numDays) const
{
 return(ODate(julian - numDays));
}


ODate& ODate::operator += (INT numDays)
{
 julian += numDays;
 return(*this);
}


ODate& ODate::operator -= (INT numDays)
{
 julian -= numDays;
 return(*this);
}


LONG ODate::operator - (const ODate &aDate) const
{
 return(julian - aDate.julian);
}
 

BOOL ODate::isValid(INT aDay, ODate::Month aMonth, INT aYear)
{
 return(ODate::isValid(aMonth, aDay, aYear));
}


BOOL ODate::isValid(INT aYear, INT aDay)
{
 return(aYear != 0 && aDay <= ODate::daysInYear(aYear));
}


ODate& ODate::calculate()
{
 _now_time_t = mktime(&_now_tm);
 fraction    = ((_now_time_t%17280) * 3125) / 5400;
 integer     = _now_time_t/17280 + 9350;
 prefix      = (integer/10000) - 36;
 integer    %= 10000;

 return(*this);
}


// end of source

