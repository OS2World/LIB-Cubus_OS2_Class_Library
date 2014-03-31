// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// slOProcRecord.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/slOProcRecord.hpp 1.50 1996/08/11 23:47:37 B.STEIN Release $

#ifndef SLOPROCREC_INCLUDED
  #define SLOPROCREC_INCLUDED

#include <OProcStat.h>

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef SORTEDLIST_INCLUDED
  #include <OSortedList.hpp>
#endif

// a processes status List

// class definitions

typedef class OProcRecord *pOProcRecord;

class __CPP_EXPORT__ OProcRecord
  : public OCLObject
{
 public:
   OString         Module;  // full qualified module name or DOS-Process for SYSINIT
   ULONG           Threads; // number of threads
   ULONG           Pid;     // Process ID
   ULONG           PPid;    // Parent Process ID
   ULONG           Sid;     //  Session ID


   OProcRecord     ();
   OProcRecord     (const OProcRecord& newRecord);
   OProcRecord     (const pOProcRecord newRecord);
   virtual
      ~OProcRecord ();

   virtual
      PSZ isOfType () const;
};


    

// sorted linked List of OProcRecords

typedef class slOProcRecord *pslOProcRecord;

class __CPP_EXPORT__ slOProcRecord
  : public OSortedList<OProcRecord>
{
 public:
  slOProcRecord      ();

  virtual 
     ~slOProcRecord  ();

  virtual
     PSZ isOfType    () const;

  slOProcRecord
    &operator <<     (OProcRecord* newRecord),
    &operator <<     (OProcRecord& newRecord);

  BOOL isLess        (const OProcRecord *first, const OProcRecord *second);
};


#endif // SLOPROC_INCLUDED

// end of source
