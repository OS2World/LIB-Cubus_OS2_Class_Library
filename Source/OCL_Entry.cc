// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// DLLEntry.cc

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

// $Header: W:/Projects/OCL/Source/rcs/OCL_Entry.cc 1.50 1996/08/11 23:49:10 B.STEIN Release $


#ifdef __BCPLUSPLUS__
# pragma option -Jgd
#endif

#define __OCL_RESOLVE_TEMPLATES__
#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <slOString.hpp>
#include <OBook.hpp>
#include <OProcStat.hpp>
#include <OMenu.hpp>
#include <OMemu.hpp>
#include <OThread.hpp>
#include <OMLE.hpp>
#include <OEditor.hpp>
#include <OPipeSvr.hpp>
#include <OPipeCli.hpp>
#include <OPipeTool.hpp>
#include <OPMPipeTool.hpp>
#include <OButtonBar.hpp>
#include <OCollection.hpp>
#include <OIterator.hpp>
#include <OConstIterator.hpp>
#include <OQueue.hpp>
#include <OStack.hpp>
#include <OContainer.hpp>

#if (defined (__IBMCPP__) && (__IBMCPP__ < 300))
  #pragma define (OList<ULONG>)
#endif


extern "C"
 {

#if ((defined __EMX__) || (defined __IBMCPP__))
  int  _CRT_init (void);
  void _CRT_term (void);
  void __ctordtorInit (void);
  void __ctordtorTerm (void);
#endif

  ULONG EXPENTRY _DLL_InitTerm (ULONG mod_handle, ULONG flag);

 }


ULONG EXPENTRY _DLL_InitTerm (ULONG mod_handle, ULONG flag)
{
 switch (flag)
  {
   case 0:
     #if ((defined __EMX__) || (defined __IBMCPP__))
       if (_CRT_init () == 0)
        {
         __ctordtorInit ();
         return 1;
        }
     #endif
     return 1;
 
   case 1:
     #if ((defined __EMX__) || (defined __IBMCPP__))
       __ctordtorTerm ();
       _CRT_term ();
     #endif
     return 1;

   default:
     return 0;
  }
}


// end of source 
