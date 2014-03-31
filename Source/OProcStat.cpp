// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OProcStat.cpp



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

// $Header: W:/Projects/OCL/Source/rcs/OProcStat.cpp 1.50 1996/08/11 23:49:29 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OProcStat.hpp>
#include <OBuffer.hpp>

#define PROCSTAT_PID  1
#define PROCSTAT_PPID 2


// member funtions of OProcStat

OProcStat::OProcStat()
  : ProcCount(0), TaskCount(0)
 {}


OProcStat::~OProcStat()
{
 ProcList.reset();
}


PSZ OProcStat::isOfType() const
{ 
 return("OProcStat"); 
}


BOOL OProcStat::getProcesses()
{
 OProcRecord record;
 qsPtrRec_t  *MainIndex;
 OBuffer     buffer(OBuffer::TILESIZE,
                    OBuffer::ALLOC |
                    OBuffer::TILED);

// clean up

  ProcList.reset();
  ProcCount = 0;
  TaskCount = 0;

// Use DosQuerySysState - a new 32bit-API - for Warp and PPC.

if(DosQuerySysState(0x17, 0, 0, 0, (PBYTE)buffer, PROCSTAT_BUFFER_SIZE))
  {
   DosFreeMem(buffer);
   return(FALSE); 
  }
else
  {
   qsLrec_t  *module;
   MainIndex = (qsPtrRec_t*) buffer.getPtr();
   module    = MainIndex->pLibRec;     // Start at first module

   while(module)
    {
     qsPrec_t *proc = MainIndex->pProcRec;

     while((proc) && (proc->RecType != PROCESS_END_INDICATOR))
       {
        if(proc->hMte == module->hmte)       // Module found
         {
          if (!strcmp((PSZ)module->pName, "SYSINIT"))
            record.Module << (PSZ) "MDOS Process";
          else
            record.Module << (PSZ) module->pName;
          record.Pid     = proc->pid;
          record.PPid    = proc->ppid;
          record.Sid     = proc->sgid;
          record.Threads = proc->cTCB;
          ProcList << &record;
          TaskCount++;
         }
        proc = (qsPrec_t *)(proc->pThrdRec + proc->cTCB);       // point to next process
       }
     ProcCount++;
     module = module->pNextRec;  // point to next module
    }
  }
 return(TRUE);
}



ULONG OProcStat::getPid(PSZ module)
{
 return(getNumInfo(module, PROCSTAT_PID));
}


ULONG OProcStat::getPPid(PSZ module)
{
 return(getNumInfo(module, PROCSTAT_PPID));
}


ULONG OProcStat::getNumInfo(PSZ module, ULONG flag)
{
 OString                tmpString;
 OListItem<OProcRecord> *tmp;

 if (!getProcesses())
   return(0);

 tmp = ProcList.first();
 tmpString << module;

 while((tmp) && (tmp->item))
  {
   if (tmpString.getText() == tmp->item->Module.getText())
    {
     switch (flag)
      {
       case PROCSTAT_PID:
         return(tmp->item->Pid);

       case PROCSTAT_PPID:
         return(tmp->item->PPid);
      }     
    }
   tmp = tmp->next;
  }
 return(0);
}


PSZ OProcStat::getModule(ULONG pid)
{
 OListItem<OProcRecord> *tmp;

 if (!getProcesses())
   return(0);

 tmp = ProcList.first();

 while((tmp) && (tmp->item))
  {
   if (tmp->item->Pid == pid)
     return(strdup(tmp->item->Module));
   tmp = tmp->next;
  }
 return(NULL);
}


ULONG OProcStat::getProcCount() 
{
 if (getProcesses())
    return(ProcCount);
 else return(0); 
}


ULONG OProcStat::getTaskCount() 
{
 if (getProcesses())
    return(TaskCount);
 else return(0); 
}


// end of source
