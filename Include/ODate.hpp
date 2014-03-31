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


// $Header: E:/Projects/OCL/Include/rcs/O3State.hpp 1.6 1996/01/25 03:46:36 B.STEIN Exp B.STEIN $


#ifndef ODATE_INCLUDED
  #define ODATE_INCLUDED

#include <time.h>

typedef class ODate *pODate;


class __CPP_EXPORT__ ODate
    : public OCLObject
{
 public:

   typedef enum
      {
       Monday = 0,
       Tuesday,
       Wednesday,
       Thursday,
       Friday,
       Saturday,
       Sunday
      }
   DayOfWeek;

   typedef enum
      {
       January = 1,
       February,
       March,
       April,
       May,
       June,
       July,
       August,
       September,
       October,
       November,
       December
      }
   Month;

   typedef enum
      {

// earth style date formats
       mm_dd_yy = 0,   // mm. dd. yy
       dd_mm_yy,       // dd. mm. yy
       yy_mm_dd,       // yy  mm. dd.
       mm_dd_yyyy,     // mm. dd. yyyy
       dd_mm_yyyy,     // dd. mm. yyyy
       yyyy_mm_dd,     // yyyy  mm. dd.

// stardate date formats
       sd_pi,          // [-31] 7837
       sd_pif1,        // [-31] 7837.5
       sd_pif2,        // [-31] 7837.53
       sd_pif3,        // [-31] 7837.532
       sd_pif4,        // [-31] 7837.5321
       sd_if,          // 7837
       sd_if1,         // 7837.5
       sd_if2,         // 7837.53 
       sd_if3,         // 7837.532
       sd_if4          // 7837.5321
      }
   DateFormat;

// imbedded structs and classes

   struct MDY
      {
       ODate::Month    month;
       INT             day;
       INT             year;
      };
    
 private:

    ULONG       julian;
    tm          _now_tm;
    time_t      _now_time_t;
    LONG        prefix;     // before or after star time
    LONG        integer;    // before comma
    LONG        fraction;   // after comma

 protected:

    ODate
      &init      (ODate::Month aMonth,
                  INT          aDay,
                  INT          aYear),
      &calculate ();


 public:

// ctors
 
   ODate          ();

   ODate          (ODate::Month aMonth,
                   INT          aDay,
                   INT          aYear);

   ODate          (INT          aDay,
                   ODate::Month aMonth,
                   INT          aYear);

   ODate          (INT   aYear,
                   INT   aDay);

   ODate          (const ODate &aDate);

   ODate          (ULONG julianDayNumber);

   ODate          (const _CDATE &cDate);

// dtor

   virtual
     ~ODate       ();

// utility members

  virtual
     PSZ isOfType () const;

  static ODate
      today       (),
      now         ();


  OString
      asString    (DateFormat  dateFmt = dd_mm_yy) const,
      asString    (PCSZ        fmt)                const;

  friend ostream
      &operator << (ostream     &aStream,
                    const ODate &aDate);

  ODate::DayOfWeek
      dayOfWeek   () const;

  OString
      dayName     () const;

  INT
      dayOfMonth  () const,
      dayOfYear   () const;

  ODate::Month
      monthOfYear () const;

  OString
      monthName   () const;

  INT
      year        () const;

  ULONG
      julianDate  () const;

  _CDATE
      asCDATE     () const;

  BOOL
      operator == (const ODate &aDate) const,
      operator != (const ODate &aDate) const,
      operator <  (const ODate &aDate) const,
      operator <= (const ODate &aDate) const,
      operator >  (const ODate &aDate) const,
      operator >= (const ODate &aDate) const;

 ODate
      operator +  (INT numDays) const,
      operator -  (INT numDays) const;

 ODate
     &operator += (INT numDays),
     &operator -= (INT numDays);

 LONG
      operator -  (const ODate &aDate) const;

 static OString
      dayName     (ODate::DayOfWeek aDay),
      monthName   (ODate::Month     aMonth);

 static INT
    daysInMonth   (Month aMonth,
                   INT   aYear),
    daysInYear    (INT   aYear);

 static BOOL
    isLeapYear    (INT   aYear),
    isValid       (Month aMonth,
                   INT   aDay,
                   INT   aYear),
    isValid       (INT   aDay,
                   Month aMonth,
                   INT   aYear),
    isValid       (INT   aYear,
                   INT   aDay);

 static ODate::MDY
    julianToMDY   (ULONG julianDate),
    DYToMDY       (INT aDay, INT aYear);

 static unsigned long
    MDYToJulian   (ODate::MDY aMDY);

};




#endif // ODATE_INCLUDED

// end of source

