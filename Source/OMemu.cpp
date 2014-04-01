// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMemu.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMemu.cpp 1.50 1996/08/11 23:49:22 B.STEIN Release $


#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMemu.hpp>
#include <OMessage.hpp>


#if defined(__EMX__)
  template class OList<gi_process_data_s>;
#endif


OMemu::OMemu()
  : memu_library(NULL),
    EP_get_general_info(NULL),
    EP_get_process_info(NULL)
{
 HFILE  hf;
 ULONG  dummy;

 if(!DosOpen("OS20MMU$", &hf, &dummy, 0L, FILE_NORMAL, FILE_OPEN,
             OPEN_ACCESS_WRITEONLY | 
             OPEN_SHARE_DENYNONE | 
             OPEN_FLAGS_FAIL_ON_ERROR, 0L))
  {
   try
    {
     memu_library = new ODynamicLib("OS20MEMU");
     EP_get_general_info = (PMEMU_GGI) memu_library->queryFn("EP_get_general_info"); 
     EP_get_process_info = (PMEMU_GPI) memu_library->queryFn("EP_get_process_info"); 
    }
   catch(OVioException& ex)
    {
     if (memu_library)
       delete memu_library;
     throw ex;
    }
   DosClose(hf); 
  }
 else
  throw OVioException(OCL::error(77), ERROR_FILE_NOT_FOUND);
}


OMemu::~OMemu()
{
 reset();
 if (memu_library)
   delete memu_library;
}


PSZ OMemu::isOfType() const
{ 
 return("OMemu"); 
}



BOOL OMemu::querySystem()
{
 pos20memu_general_info  pgi = NULL;
 pgi_process_data_s temp = NULL;

 reset();

 if (DosAllocMem((PPVOID)&pgi, 0x0000ffffL, 
     PAG_READ | PAG_WRITE | PAG_COMMIT | OBJ_TILE))
   return(FALSE);
 
 pgi->gi_cpids = 0x0000ffffL - sizeof(os20memu_general_info);
 
 if (EP_get_general_info(pgi) == ERROR_FAULT_OCCURRED)
  {
   DosFreeMem(pgi);
   return(FALSE);
  }

 gi_version             = pgi->gi_version;
 gi_phys_mem            = pgi->gi_phys_mem;
 gi_free_mem            = pgi->gi_free_mem;
 gi_tot_res             = pgi->gi_tot_res;
 gi_res_sys_mem         = pgi->gi_res_sys_mem;
 gi_swp_sys_mem         = pgi->gi_swp_sys_mem;
 gi_swappable_sys_mem   = pgi->gi_swappable_sys_mem;
 gi_inmem_swp           = pgi->gi_inmem_swp;
 gi_inmem_dsc           = pgi->gi_inmem_dsc;
 gi_ondisk_dsc          = pgi->gi_ondisk_dsc;
 gi_ondisk_swp          = pgi->gi_ondisk_swp;
 gi_notacc_swp          = pgi->gi_notacc_swp;
 gi_slock_swp           = pgi->gi_slock_swp;
 gi_slock_dsc           = pgi->gi_slock_dsc;
 gi_llock_swp           = pgi->gi_llock_swp;
 gi_llock_dsc           = pgi->gi_llock_dsc;
 gi_swapfile_size       = pgi->gi_swapfile_size;
 gi_swapfile_inuse      = pgi->gi_swapfile_inuse;
 gi_swapfile_max_inuse  = pgi->gi_swapfile_max_inuse;
 gi_app_sys_mem_res     = pgi->gi_app_sys_mem_res;
 gi_app_sys_mem_im      = pgi->gi_app_sys_mem_im;
 gi_app_sys_mem_od      = pgi->gi_app_sys_mem_od;
 gi_shr_sys_mem_res     = pgi->gi_shr_sys_mem_res;
 gi_shr_sys_mem_im      = pgi->gi_shr_sys_mem_im;
 gi_shr_sys_mem_od      = pgi->gi_shr_sys_mem_od;
 gi_cshr_im             = pgi->gi_cshr_im;
 gi_cshr_od             = pgi->gi_cshr_od;
 gi_cshr_nt             = pgi->gi_cshr_nt;
 gi_cpids               = pgi->gi_cpids;

 for(ULONG i = 0; i < gi_cpids; i++) {
   temp = new gi_process_data_s;
   memcpy((PVOID)temp, (PVOID)&pgi->gi_process_data[i], sizeof(gi_process_data_s)); 
   add(temp); }

 DosFreeMem(pgi);
 return(TRUE); 
}


BOOL OMemu::queryGeneralInfo()
{
 os20memu_general_info info;

 memset(&info, 0, sizeof(os20memu_general_info));
 if (EP_get_general_info(&info) == ERROR_FAULT_OCCURRED)
   return(FALSE);

 gi_version             = info.gi_version;
 gi_phys_mem            = info.gi_phys_mem;
 gi_free_mem            = info.gi_free_mem;
 gi_tot_res             = info.gi_tot_res;
 gi_res_sys_mem         = info.gi_res_sys_mem;
 gi_swp_sys_mem         = info.gi_swp_sys_mem;
 gi_swappable_sys_mem   = info.gi_swappable_sys_mem;
 gi_inmem_swp           = info.gi_inmem_swp;
 gi_inmem_dsc           = info.gi_inmem_dsc;
 gi_ondisk_dsc          = info.gi_ondisk_dsc;
 gi_ondisk_swp          = info.gi_ondisk_swp;
 gi_notacc_swp          = info.gi_notacc_swp;
 gi_slock_swp           = info.gi_slock_swp;
 gi_slock_dsc           = info.gi_slock_dsc;
 gi_llock_swp           = info.gi_llock_swp;
 gi_llock_dsc           = info.gi_llock_dsc;
 gi_swapfile_size       = info.gi_swapfile_size;
 gi_swapfile_inuse      = info.gi_swapfile_inuse;
 gi_swapfile_max_inuse  = info.gi_swapfile_max_inuse;
 gi_app_sys_mem_res     = info.gi_app_sys_mem_res;
 gi_app_sys_mem_im      = info.gi_app_sys_mem_im;
 gi_app_sys_mem_od      = info.gi_app_sys_mem_od;
 gi_shr_sys_mem_res     = info.gi_shr_sys_mem_res;
 gi_shr_sys_mem_im      = info.gi_shr_sys_mem_im;
 gi_shr_sys_mem_od      = info.gi_shr_sys_mem_od;
 gi_cshr_im             = info.gi_cshr_im;
 gi_cshr_od             = info.gi_cshr_od;
 gi_cshr_nt             = info.gi_cshr_nt;
 gi_cpids               = info.gi_cpids;

 return(TRUE);
}


ULONG OMemu::makeKByte(ULONG pages)
{
 ULONG bytes = pages * 4096;

 if (bytes < 1024)
   return(0);
 else
   return(bytes/1024);
}


// end of source
