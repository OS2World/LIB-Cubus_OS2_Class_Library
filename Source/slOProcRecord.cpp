// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// slOProcRecord.cpp



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

// $Header: W:/Projects/OCL/Source/rcs/slOProcRecord.cpp 1.50 1996/08/11 23:49:38 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <slOProcRecord.hpp>


#if defined(__EMX__)
  template class OListItem<OProcRecord>;
  template class OSortedList<OProcRecord>;
#endif


OProcRecord::OProcRecord(const pOProcRecord newRecord)
    : Threads(newRecord->Threads), Pid(newRecord->Pid),
      PPid(newRecord->PPid), Sid(newRecord->Sid)
{
 Module << newRecord->Module;
}

OProcRecord::OProcRecord(const OProcRecord& newRecord)
    : Threads(newRecord.Threads), Pid(newRecord.Pid),
      PPid(newRecord.PPid), Sid(newRecord.Sid)
{
 Module << newRecord.Module;
}

OProcRecord::OProcRecord()
  {}

OProcRecord::~OProcRecord()
  {}

PSZ OProcRecord::isOfType() const
{ 
 return("OProcRecord"); 
}


slOProcRecord::slOProcRecord()
  {}

slOProcRecord::~slOProcRecord()
  {}

PSZ slOProcRecord::isOfType() const
{ 
 return("slOProcRecord"); 
}

slOProcRecord& slOProcRecord::operator << (OProcRecord* newRecord)
{
 pOProcRecord tmp = new OProcRecord(newRecord);
 addSorted(tmp);
 return(*this);
}

slOProcRecord& slOProcRecord::operator << (OProcRecord& newRecord)
{
 pOProcRecord tmp = new OProcRecord(newRecord);
 addSorted(tmp);
 return(*this);
}


BOOL slOProcRecord::isLess(const OProcRecord *first, const OProcRecord *second)
{
 return(first->Pid < second->Pid);
}


// end of source
