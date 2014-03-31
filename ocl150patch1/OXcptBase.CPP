// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OXcptBase.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OXcptBase.cpp 1.50 1996/08/11 23:49:37 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OXcptBase.hpp>

#include <stdarg.h>


pOXcptBase OXcptBase::currentHandler = NULL;


OXcptBase::OXcptBase(BOOL killMessages)
   : killMsg(killMessages),
     record(NULL) {}

OXcptBase::~OXcptBase()
  {}


PSZ OXcptBase::isOfType() const
{ 
 return("OXcptBase"); 
} 



BOOL OXcptBase::setHandler(OXCPTRECORD& regRecord)
{
 if (!OXcptBase::currentHandler)
   OXcptBase::currentHandler = this;

 record = &regRecord;

 regRecord.prev_structure   = NULL;
 regRecord.ExceptionHandler = (_ERR*)&OXcptBase::OXCPT_CATCH;

 if (!DosSetExceptionHandler(&regRecord))
   return(!DosSetSignalExceptionFocus(SIG_SETFOCUS, &times));
 return(FALSE);
}


BOOL OXcptBase::unsetHandler()
{
 if (OXcptBase::currentHandler == this)
   OXcptBase::currentHandler = NULL;
 
 if (record)
   return(!DosUnsetExceptionHandler(record));
 return(FALSE);
}



BOOL OXcptBase::handler(PEXCEPTIONREPORTRECORD report,
                        OXCPTRECORD *record,
                        CONTEXTRECORD *context,
                        PVOID pargs)
{
 BOOL    disable = TRUE;
 ULONG   nest;
 OString msg("\nException Handler registered:\n");

 DosEnterMustComplete(&nest);
 msg + except_printf("\nFatal exception: %8.8lX.\n",report->ExceptionNum);

 switch (report->ExceptionNum) 
  {
   case XCPT_PROCESS_TERMINATE:
   case XCPT_ASYNC_PROCESS_TERMINATE:
   case XCPT_UNWIND:
     DosExitMustComplete(&nest);
     return(TRUE);

   case XCPT_CPP_EXCEPTION:
     DosExitMustComplete(&nest);
     return(FALSE);
 
   case XCPT_ACCESS_VIOLATION:
     msg + except_printf("Access violation.\n");
     switch (report->ExceptionInfo[0]) 
      {
       case XCPT_READ_ACCESS:
       case XCPT_WRITE_ACCESS:
         msg + except_printf("Invalid linear address %8.8lX.\n", report->ExceptionInfo[1]);
         break;
       case XCPT_SPACE_ACCESS:
         msg + except_printf("Invalid selector %8.8lX.\n",report->ExceptionInfo[1]);
         break;
       case XCPT_LIMIT_ACCESS:
         msg + except_printf("Limit access fault.\n");
         break;
       case XCPT_UNKNOWN_ACCESS:
         msg + except_printf("Unknown access fault.\n");
         break;
       default:
         msg + except_printf("Other unknown access fault.\n");
      }
     break;
   case XCPT_INTEGER_DIVIDE_BY_ZERO:
     msg + except_printf("Integer divide by zero.\n");
     break;
   case XCPT_INTEGER_OVERFLOW:
     msg + except_printf("Integer overflow.\n");
     break;
   case XCPT_ILLEGAL_INSTRUCTION:
     msg + except_printf("Illegal instruction.\n");
     break;
   case XCPT_FLOAT_DENORMAL_OPERAND:
     msg + except_printf("Float denormal operand.\n");
     break;
   case XCPT_FLOAT_DIVIDE_BY_ZERO:
     msg + except_printf("Float divide by zero.\n");
     break;
   case XCPT_FLOAT_INEXACT_RESULT:
     msg + except_printf("Float inexact result.\n");
     break;
   case XCPT_FLOAT_INVALID_OPERATION:
     msg + except_printf("Float invalid operation.\n");
     break;
   case XCPT_FLOAT_OVERFLOW:
     msg + except_printf("Float overflow.\n");
     break;
   case XCPT_FLOAT_STACK_CHECK:
     msg + except_printf("Float stack check.\n");
     break;
   case XCPT_FLOAT_UNDERFLOW:
     msg + except_printf("Float underflow.\n");
     break;
   case XCPT_PRIVILEGED_INSTRUCTION:
     msg + except_printf("Privileged instruction.\n");
     break;
   case XCPT_NONCONTINUABLE_EXCEPTION:
     msg + except_printf("Unknown noncontinuable exception.\n");
     disable = FALSE;
     break;
   case XCPT_SIGNAL:
     msg << "Acknowledged signal: ";
     switch (report->ExceptionInfo[0]) 
      {
       case XCPT_SIGNAL_BREAK:
         msg + except_printf("Control-Break.\n");
         break;
       case XCPT_SIGNAL_INTR:
         msg + except_printf("Control-C.\n");
         break;
       case XCPT_SIGNAL_KILLPROC:
         msg + except_printf("DosKillProcess.\n");
         break;
      }
     DosExitMustComplete(&nest);
     if (killMsg)
       exceptionMessage(msg);
     if (killTrace())
      {
       DosAcknowledgeSignalException(XCPT_SIGNAL_INTR);
       DosAcknowledgeSignalException(XCPT_SIGNAL_KILLPROC);
       DosAcknowledgeSignalException(XCPT_SIGNAL_BREAK);
       return(TRUE);
      }
     else
      {
       unsetHandler(); 
       DosExit(EXIT_THREAD, 0);
      }  
  }

 except_print_context(msg, context);
 msg + except_printf("Cannot continue.\n");

 DosExitMustComplete(&nest);
 exceptionMessage(msg);
 unsetHandler();
 if (disable)
   DosError(FERR_DISABLEEXCEPTION);
 return(trapTrace());

#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif



ULONG OXcptBase::OXCPT_CATCH(EXCEPTIONREPORTRECORD *report,
                             OXCPTRECORD *record,
                             CONTEXTRECORD *context,
                             PVOID pargs)
{
 if ((!OXcptBase::currentHandler) || 
     (!OXcptBase::currentHandler->handler(report, record, context, pargs))) {
   return(XCPT_CONTINUE_SEARCH); } 
 else
   return(XCPT_CONTINUE_EXECUTION);
#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif



// C helpers


PSZ __CPP_EXPORT__ except_printf(const char *format, ...) 
{
 va_list      ap;
 static CHAR  buf[CCHMAXPATH];

 va_start(ap, format);
 vsprintf(buf, format, ap);
 va_end(ap);

 return((PSZ)buf);
}


void __CPP_EXPORT__ except_print_context(OString& msg, PCONTEXTRECORD cont) 
{
 PTIB   ptib;
 PPIB   ppib;
 APIRET rc;

 if (cont->ContextFlags & CONTEXT_CONTROL) {
   msg + except_printf("EIP : %8.8lX\n",cont->ctx_RegEip  );
   msg + except_printf("EBP : %8.8lX\n",cont->ctx_RegEbp  );
   msg + except_printf("ESP : %8.8lX\n",cont->ctx_RegEsp  );
   msg + except_printf("EFLG: %8.8lX\n",cont->ctx_EFlags  ); }

 if (cont->ContextFlags & CONTEXT_INTEGER) {
   msg + except_printf("EAX : %8.8lX\n",cont->ctx_RegEax  );
   msg + except_printf("EBX : %8.8lX\n",cont->ctx_RegEbx  );
   msg + except_printf("ECX : %8.8lX\n",cont->ctx_RegEcx  );
   msg + except_printf("EDX : %8.8lX\n",cont->ctx_RegEdx  );
   msg + except_printf("EDI : %8.8lX\n",cont->ctx_RegEdi  );
   msg + except_printf("ESI : %8.8lX\n",cont->ctx_RegEsi  ); }

 if (cont->ContextFlags & CONTEXT_CONTROL) {
   msg + except_printf("CS  : %4.4lX\n",cont->ctx_SegCs   );
   msg + except_printf("SS  : %4.4lX\n",cont->ctx_SegSs   ); }

 if (cont->ContextFlags & CONTEXT_SEGMENTS) {
   msg + except_printf("GS  : %4.4lX\n",cont->ctx_SegGs);
   msg + except_printf("FS  : %4.4lX\n",cont->ctx_SegFs);
   msg + except_printf("ES  : %4.4lX\n",cont->ctx_SegEs);
   msg + except_printf("DS  : %4.4lX\n",cont->ctx_SegDs); }

 if (cont->ContextFlags & CONTEXT_CONTROL) 
  {
   if (DosGetInfoBlocks(&ptib, &ppib) == 0) {
     static CHAR modname[CCHMAXPATH];
    
     msg + except_printf("Process id: %lu, ", ppib->pib_ulpid);
     rc = DosQueryModuleName(ppib->pib_hmte,CCHMAXPATH, modname);
     msg + except_printf(".EXE name: %s\n", rc == 0 ? modname : "?????");
     msg + except_printf("Thread id: %lu,  ordinal : %lu, priority : %p\n",
                         ptib->tib_ptib2->tib2_ultid ,
                         ptib->tib_ordinal,
                         ptib->tib_ptib2->tib2_ulpri );
     msg + except_printf("Stack bottom: %8.8lX, ", ptib->tib_pstack);
     msg + except_printf("top: %8.8lX \n",ptib->tib_pstacklimit); }
  }
}


// end of source
