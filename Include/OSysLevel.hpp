// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSysLevel.hpp

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


// $Header: W:/Projects/OCL/Include/rcs/OSysLevel.hpp 1.50 1996/08/11 23:47:32 B.STEIN Release $


#ifndef OSYSLEVEL_HPP_INCLUDED
  #define OSYSLEVEL_HPP_INCLUDED


#ifndef OCLOBJECT_INCLUDED
  #include <OCLObject.hpp>
#endif

 
#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif


#ifndef OSYSLEVEL_H_INCLUDED
  #include <OSysLevel.h>
#endif


typedef class OSysLevel *pOSysLevel;



class __CPP_EXPORT__ OSysLevel
  : public OCLObject
{
 private:
    void
      JulianToDT      (LONG, DATETIME&) const;

    LONG
      DTToJulian      (DATETIME&) const;

 protected:
   OString             slfile;
   SLFHEADER           slfheader;
   SYSTABLE            systable;
 
   OSysLevel
      &readFromFile    (PCSZ fileName),
      &writeToFile     (PCSZ fileName);

 public:

   OSysLevel           ();

   OSysLevel           (const OSysLevel& sl);

   OSysLevel           (SLFHEADER& header, SYSTABLE&  table);  

   OSysLevel           (PCSZ fileName);

   virtual
     ~OSysLevel        ();

   virtual
      PSZ isOfType     () const; 

   OSysLevel
      &read            (),
      &write           (),
      &setSysTable     (const SYSTABLE&), 
      &setHeader       (const SLFHEADER&),
      &setFileName     (PCSZ fileName),
      &setDate         (),          // uses current DATETIME
      &setDate         (DATETIME&),
      &setDate         (PSZ),
      &setTableOffset  (ULONG), 
      &setSysId        (USHORT),    // identifies system/subsytem
      &setSysEdition   (BYTE),      // edition of system, eg SE=00, EE=01
      &setSysVersion   (BYTE),      // version, eg 1.00=10, 1.10=11
      &setSysModify    (BYTE),      // modify, eg 1.00=00, 1.01=01
      &setSysDate      (USHORT),    // date of system
      &setCsdLevel     (PSZ),       // subsytem CSD level, eg, XR?0000_
      &setCsdPrev      (PSZ),       // as above, except for prev system
      &setSysName      (PSZ),       // Title of system / subsytem (ASCIIZ)
      &setCompId       (PSZ),       // component ID of subsytem
      &setRefreshLevel (BYTE),      // eg, for version 1.30.1, use 1
      &setType         (PSZ);       // Null terminated type (8 chars +'\0')

   const OSysLevel
      &getDate         (DATETIME&) const;

   ULONG
      getTableOffset   () const; 

   USHORT
      getSysId         () const,
      getSysDate       () const;

   PCSZ
      getFileName      () const,
      getDateAsStr     (OString&) const,
      getCsdLevel      () const,
      getCsdPrev       () const,
      getSysName       () const,
      getCompId        () const,
      getType          () const;

   BYTE
      getSysEdition    () const,
      getSysVersion    () const,
      getSysModify     () const,
      getRefreshLevel  () const;

   const SLFHEADER&
      getHeader        () const;

   const SYSTABLE&
      getSysTable      () const;

};




#endif // OSYSLEVEL_HPP_INCLUDED


// end of source
