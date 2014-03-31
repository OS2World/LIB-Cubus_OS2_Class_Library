// OCL - OS/2 Class Library
// (c) Cubus 1995
// (c) Glenn Brew, Cook, Benjamin Stein 1995
// All Rights Reserved
// OMemu.h

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

// $Header: W:/Projects/OCL/Include/rcs/OMemu.h 1.50 1996/08/11 23:47:20 B.STEIN Release $

#ifndef OMEMU_H_INCLUDED
  #define OMEMU_H_INCLUDED


// The following information is taken from OS20MEMU.H
// written by Glenn Brew & Ross Cook and delivered with OS2-MEMU 1.02.
// OMemu uses 32bit calls rather than their 16bit counterparts
// documented by the authors of OS2-MEMU.


// Purpose:  Header file and definition of variables returned from the       
//           OS20MEMU dynalink - OS20MEMU.DLL                                 
//  Author:  Glenn Brew & Ross Cook                                            


#pragma pack(1)

#define OS20MEMU_VERSION        0x0001  // Version Number
#define ERROR_UNKNOWN_KERNEL    0xffff
#define ERROR_FAULT_OCCURRED    0xfffe  // A fault occurred while scanning
                                        // the OS/2 system control blocks.    
                                        // The request should be reissued.    
struct gi_process_data_s 
{
 USHORT  pd_pid;              // process id
 USHORT  pd_ppid;             // parent process id
 ULONG   pd_cpriv_im;         // count of private pages in memory
 ULONG   pd_cpriv_od;         // count of private pages on disk
 ULONG   pd_cpriv_nt;         // count of private pages not accessed
 ULONG   pd_cshr_im;          // count of shared pages in memory for process
 ULONG   pd_cshr_od;          // count of shared pages on disk for process
 ULONG   pd_cshr_nt;          // count of shared pages not accessed for proc.
 UCHAR   pd_name[14];         // name of process
};
typedef gi_process_data_s *pgi_process_data_s;


struct os20memu_general_info 
{
 ULONG   gi_version;          // version
 ULONG   gi_phys_mem;         // amount of physical storage, in pages
 ULONG   gi_free_mem;         // count of free pages
 ULONG   gi_tot_res;          // total resident (fixed) memory not including locked
 ULONG   gi_res_sys_mem;      // total number of resident pages contained within the system arena
 ULONG   gi_swp_sys_mem;      // total number of swapped out pages that
                              //  reside in the system arena
                              //  NOTE: subset of gi_ondisk_swp
 ULONG   gi_swappable_sys_mem;// total number of swappable pages that are
                              //  currently in memory that are located
                              //  within the system arena
                              //  NOTE: subset of gi_inmem_swp
 ULONG   gi_inmem_swp;        // total number of swappable pages that are
                              //  currently in memory includes both
                              //  system and user pages
 ULONG   gi_inmem_dsc;        // total number of discardable pages that are
                              //  currently in memory includes both
                              //  system and user pages
 ULONG   gi_ondisk_dsc;       // total number of discardable pages that are
                              //  not in memory
 ULONG   gi_ondisk_swp;       // total number of swappable pages that are
                              //  not in memory
 ULONG   gi_notacc_swp;       // total number of swappable pages that were
                              //  allocated (with the commit bit set) but
                              //  have never been accessed
 ULONG   gi_slock_swp;        // short term locks on swappable pages, in pgs
                              //  NOTE: subset of inmem_swp
 ULONG   gi_slock_dsc;        // short term locks on discardable pages, in pgs
                              //  NOTE: subset of inmem_dsc
 ULONG   gi_llock_swp;        // long term locks on swappable pages, in pages
                              //  NOTE: subset of inmem_swp
 ULONG   gi_llock_dsc;        // long term locks on discardable pages, in pgs
                              //  NOTE: subset of inmem_dsc
 ULONG   gi_swapfile_size;    // size of swapfile in pages
 ULONG   gi_swapfile_inuse;   // number of pages with valid information
 ULONG   gi_swapfile_max_inuse;// maximum inuse page

 ULONG   gi_app_sys_mem_res;  // total amount of resident system memory
                              //  used to run all processes (IN BYTES)
                              //  NOTE: subset of res_sys_mem
 ULONG   gi_app_sys_mem_im;   // total amount of in memory system storage
                              //  used to run all processes (IN BYTES)
                              //  NOTE: subset of swappable_sys_mem
 ULONG   gi_app_sys_mem_od;   // total amount of swapped system storage
                              //  used to run all processes (IN BYTES)
                              //  NOTE: subset of swp_sys_mem
// shared arena info
 ULONG   gi_shr_sys_mem_res;  // total amount of resident system memory
 ULONG   gi_shr_sys_mem_im;   // total number of shared pages in memory
 ULONG   gi_shr_sys_mem_od;   // total number of shared pages in memory
 ULONG   gi_cshr_im;          // total number of shared pages in memory
                              //  NOTE: subset of inmem_swp and inmem_dsc
 ULONG   gi_cshr_od;          // total number of shared pages on disk
                              //  NOTE: subset of ondisk_swp and ondisk_dsc
 ULONG   gi_cshr_nt;          // total number of shared pages not accessed
                              //  NOTE: subset of notacc_swp
 ULONG   gi_cpids;            // count of processes in gi_process_data array
 // per process info
 struct  gi_process_data_s gi_process_data[1]; // array of process records
                              // The number of entries in this array is
                              // variable and its contents is complete only
                              // if its size is => gi_cpids.
};
typedef os20memu_general_info *pos20memu_general_info;


//   Structure of the detail record of a memory object.                       
//   An array of these structures is returned at the last entry of the        
//   os20memu_process_details; see pi_object_data.                            
//   That array is variable length and its size should be set = the sum of    
//   pi_cprivate + pi_cshared.                                                


struct pi_object_data_s 
{
 ULONG   od_linaddr;          // linear address of object
 ULONG   od_flags;            // object flags
 ULONG   od_size;             // size of object in pages
 ULONG   od_inmem;            // number of pages in memory
 ULONG   od_ondisk;           // number of pages on  disk
 ULONG   od_notacc;           // number of pages that were not accessed
 UCHAR   od_owner_name[14];   // name of executable that allocated the object
};
typedef pi_object_data_s *ppi_object_data_s;


struct os20memu_process_details 
{
 ULONG   pi_sys_memory_used_res; // current amount of resident system
                                 //  memory being used to run this process
                                 //  (IN BYTES)
 ULONG   pi_sys_memory_used_im;  // current amount of in memory swappable
                                 //  system storage being used to run
                                 //  this process (IN BYTES)
 ULONG   pi_sys_memory_used_od;  // current amount of swapped system memory
                                 //  being used to run this process
                                 //  (IN BYTES)
 USHORT  pi_cprivate;            // On return, this value will reflect the
                                 // number of objects in the private arena
                                 // This variable must be set to the number of
                                 // entries in the pi_object_data array before
                                 // issuing an EP16_GET_PROCESS_INFO request.
 USHORT  pi_cshared;             // number of objects in the shared arena

 struct pi_object_data_s pi_object_data[1]; // array of object data records
                                 // The number of entries in this array is
                                 // variable and its contents is complete only
                                 // if its size is => the sum of
                                 // pi_cprivate + pi_cshared.
};
typedef os20memu_process_details *pos20memu_process_details;


#define OB_DISCARDABLE 0x40000  // Discardable Object
#define OB_SWAPPABLE   0x20000  // Swappable Object
#define OB_RESIDENT    0x10000  // Resident Object

#define OB_LALIAS       0x1000  // Object has aliases
#define OB_SHARED       0x0800  // Object's contents are shared
#define OB_UVIRT        0x0400  // UVirt object
#define OB_ZEROINIT     0x0200  // Object is zero-initialized
#define OB_RES_INIT     0x0100  // Initial allocation was resident
#define OB_LOWMEM       0x0040  // Object is in low memory

#define OB_GUARD        0x0080  // Page attribute/permission flags
#define OB_EXEC         0x0020
#define OB_READ         0x0010
#define OB_USER         0x0008
#define OB_WRITE        0x0004


#ifdef __cplusplus
  extern "C" {
#endif

    /**************************************************************************/
    /* The EP16_GET_GENERAL_INFO function returns a snapshot of memory.       */
    /*                                                                        */
    /* It should be called at any time it is felt the state of system memory  */
    /* has changed such as following the allocation/reallocation of any       */
    /* private data segments.  Also, when programs have started or stopped.   */
    /*                                                                        */
    /* The only parameter to this function is a pointer to a structure of     */
    /* type 'os20memu_general_info'.                                          */
    /*                                                                        */
    /**************************************************************************/

#if ( (defined (__BCPLUSPLUS__)) || (defined (__WATCOM_CPLUSPLUS__)) )
  USHORT APIENTRY16 EP16_GET_GENERAL_INFO(pos20memu_general_info __far16 pgi);
#else
  USHORT APIENTRY16 EP16_GET_GENERAL_INFO(pos20memu_general_info _Seg16 pgi);
#endif
APIRET APIENTRY   EP_get_general_info(pos20memu_general_info pgi);

    /**************************************************************************/
    /* The EP16_GET_PROCESS_INFO function returns detailed data for a process.*/
    /*                                                                        */
    /* It may be called at any time to obtain several data items for a        */
    /* particular process.                                                    */
    /*                                                                        */
    /* The input to this function is a process ID.  Typically, this would be  */
    /* a process ID returned on a previous call to EP16_GET_GENERAL_INFO.     */
    /* The process must be active or an error will be returned.               */
    /*                                                                        */
    /* The output from this function is described in the structure of type    */
    /* 'os20memu_process_details'.                                            */
    /*                                                                        */
    /**************************************************************************/

#if ( (defined (__BCPLUSPLUS__)) || (defined (__WATCOM_CPLUSPLUS__)) )
  USHORT APIENTRY16 EP16_GET_PROCESS_INFO(USHORT pid, pos20memu_process_details __far16 ppi);
#else
  USHORT APIENTRY16 EP16_GET_PROCESS_INFO(USHORT pid, pos20memu_process_details _Seg16 ppi);
#endif
APIRET APIENTRY   EP_get_process_info(ULONG pid, pos20memu_process_details ppi);


#if ( (defined (__BCPLUSPLUS__)) || (defined (__WATCOM_CPLUSPLUS__)) )
 typedef USHORT (APIENTRY16 MEMU16_GGI)(pos20memu_general_info __far16 pgi);
#else
 typedef USHORT (APIENTRY16 MEMU16_GGI)(pos20memu_general_info _Seg16 pgi);
#endif
typedef MEMU16_GGI *PMEMU16_GGI;

typedef APIRET (APIENTRY MEMU_GGI)(pos20memu_general_info pgi);
typedef MEMU_GGI *PMEMU_GGI;

#if ( (defined (__BCPLUSPLUS__)) || (defined (__WATCOM_CPLUSPLUS__)) )
 typedef USHORT (APIENTRY16 MEMU16_GPI)(USHORT pid, pos20memu_process_details __far16 ppi);
#else
 typedef USHORT (APIENTRY16 MEMU16_GPI)(USHORT pid, pos20memu_process_details _Seg16 ppi);
#endif
typedef MEMU16_GPI *PMEMU16_GPI;

typedef APIRET (APIENTRY MEMU_GPI)(ULONG pid, pos20memu_process_details ppi);
typedef MEMU_GPI *PMEMU_GPI;

#ifdef __cplusplus
  }
#endif


#pragma pack()

#endif // OMEMU_H_INCLUDED


// end of source
