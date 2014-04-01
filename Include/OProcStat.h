// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OProcStat.h

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

// $Header: W:/Projects/OCL/Include/rcs/OProcStat.h 1.50 1996/08/11 23:47:27 B.STEIN Release $

#ifndef OSYSTEMH_INCLUDED
  #define OSYSTEMH_INCLUDED



#define PROCESS_END_INDICATOR   3       /* Indicates end of process structs */
#define PROCSTAT_BUFFER_SIZE    65536



#pragma pack(1)

extern "C" 
{
   APIRET APIENTRY DosQuerySysState(ULONG ul1, ULONG ul2,
                                    ULONG ul3, ULONG ul4,
                                    PBYTE buf, ULONG bufsize);
}


typedef struct qsGrec_s {
        ULONG         cThrds;    /* number of threads in use */
        ULONG         cProcs;    /* number of processes */
        ULONG         cModule;   /* number of modules */
} qsGrec_t;

typedef struct qsTrec_s {
        ULONG         RecType;        /* Record Type */
                                      /* Thread rectype = 100 */
        USHORT        tid;            /* thread ID */
        USHORT        slot;           /* "unique" thread slot number */
        ULONG         sleepid;        /* sleep id thread is sleeping on */
        ULONG         priority;       /* thread priority */
        ULONG         systime;        /* thread system time */
        ULONG         usertime;       /* thread user time */
        UCHAR         state;          /* thread state */
        CHAR          pad1;
        SHORT         pad2;
} qsTrec_t;

typedef struct qsPrec_s {
        ULONG         RecType;        /* type of record being processed */
                                      /* process rectype = 1            */
        qsTrec_t  FAR   *pThrdRec;    /* ptr to 1st thread rec for this prc*/
        USHORT        pid;            /* process ID */
        USHORT        ppid;           /* parent process ID */
        ULONG         type;           /* process type */
        ULONG         stat;           /* process status */
        ULONG         sgid;           /* process screen group */
        USHORT        hMte;           /* program module handle for process */
        USHORT        cTCB;           /* # of TCBs in use in process */
        ULONG         Reserved1;
        void    FAR   *Reserved2;
        USHORT        c16Sem;         /*# of 16 bit system sems in use by proc*/
        USHORT        cLib;           /* number of runtime linked libraries */
        USHORT        cShrMem;        /* number of shared memory handles */
        USHORT        Reserved3;
        USHORT  FAR   *p16SemRec;     /*ptr to head of 16 bit sem inf for proc*/
        USHORT  FAR   *pLibRec;       /*ptr to list of runtime lib in use by  */
                                      /*process*/
        USHORT  FAR   *pShrMemRec;    /*ptr to list of shared mem handles in  */
                                      /*use by process*/
        USHORT  FAR   Reserved4;
} qsPrec_t;

typedef struct qsS16Headrec_s {
        ULONG         SRecType;   /* semaphore rectype = 3 */
        ULONG         Reserved1;  /* overlays NextRec of 1st qsS16rec_t*/
        ULONG         Reserved2;
        ULONG         S16TblOff;  /* index of first semaphore,SEE PSTAT OUTPUT*/
                                  /* System Semaphore Information Section     */
} qsS16Headrec_t;

typedef struct qsS16rec_s {
        ULONG           NextRec;          /* offset to next record in buffer*/
        UINT            s_SysSemOwner ;   /* thread owning this semaphore   */
        UCHAR           s_SysSemFlag ;    /* system semaphore flag bit field*/
        UCHAR           s_SysSemRefCnt ;  /* number of references to this   */
                                          /*   system semaphore             */
        UCHAR           s_SysSemProcCnt ; /*number of requests by sem owner*/
        UCHAR           Reserved1;
        ULONG           Reserved2;
        UINT            Reserved3;
        CHAR            SemName;          /* start of semaphore name string */
} qsS16rec_t;

typedef struct qsLrec_s {
        qsLrec_s  FAR *pNextRec;    /* pointer to next record in buffer */
        USHORT        hmte;           /* handle for this mte */
        USHORT        Reserved1;      /* Reserved */
        ULONG         ctImpMod;       /* # of imported modules in table */
        ULONG         Reserved2;      /* Reserved */
        void      FAR *Reserved3;   /* Reserved */
        UCHAR     FAR *pName;         /* ptr to name string following stru*/
} qsLrec_t;

typedef struct qsMrec_s {
        ULONG         MemNextRec;       /* offset to next record in buffer */
        USHORT        hmem;             /* handle for shared memory */
        USHORT        sel;              /* shared memory selector */
        USHORT        refcnt;           /* reference count */
        CHAR          Memname;          /* start of shared memory name string */
} qsMrec_t;

typedef struct qsPtrRec_s {
        qsGrec_t        *pGlobalRec;    /* ptr to the global data section */
        qsPrec_t        *pProcRec;      /* ptr to process record section  */
        qsS16Headrec_t  *p16SemRec;     /* ptr to 16 bit sem section      */
        ULONG           Reserved;
        qsMrec_t        *pShrMemRec;    /* ptr to shared mem section      */
        qsLrec_t        *pLibRec;       /*ptr to exe module record section*/
} qsPtrRec_t;


#ifdef INCL_OCLDOSGETINFOSEG

// 16-Bit DosGetInfoSeg 

typedef struct _GINFOSEG {
   ULONG   time;               /* time in seconds */
   ULONG   msecs;              /* milliseconds    */
   UCHAR   hour;               /* hours */
   UCHAR   minutes;            /* minutes */
   UCHAR   seconds;            /* seconds */
   UCHAR   hundredths;         /* hundredths */
   USHORT  timezone;           /* minutes from UTC */
   USHORT  cusecTimerInterval; /* timer interval (units = 0.0001 seconds) */
   UCHAR   day;                /* day */
   UCHAR   month;              /* month */
   USHORT  year;               /* year */
   UCHAR   weekday;            /* day of week */
   UCHAR   uchMajorVersion;    /* major version number */
   UCHAR   uchMinorVersion;    /* minor version number */
   UCHAR   chRevisionLetter;   /* revision letter */
   UCHAR   sgCurrent;          /* current foreground session */
   UCHAR   sgMax;              /* maximum number of sessions */
   UCHAR   cHugeShift;         /* shift count for huge elements */
   UCHAR   fProtectModeOnly;   /* protect mode only indicator */
   USHORT  pidForeground;      /* pid of last process in foreground session */
   UCHAR   fDynamicSched;      /* dynamic variation flag */
   UCHAR   csecMaxWait;        /* max wait in seconds */
   USHORT  cmsecMinSlice;      /* minimum timeslice (milliseconds) */
   USHORT  cmsecMaxSlice;      /* maximum timeslice (milliseconds) */
   USHORT  bootdrive;          /* drive from which the system was booted */
   UCHAR   amecRAS[32];        /* system trace major code flag bits */
   UCHAR   csgWindowableVioMax;/* maximum number of VIO windowable sessions */
   UCHAR   csgPMMax;           /* maximum number of pres. services sessions */
} GINFOSEG;
 
typedef GINFOSEG *PGINFOSEG;

typedef struct _LINFOSEG {
   PID     pidCurrent;        /* current process id */
   PID     pidParent;         /* process id of parent */
   USHORT  prtyCurrent;       /* priority of current thread */
   TID     tidCurrent;        /* thread ID of current thread */
   USHORT  sgCurrent;         /* session */
   UCHAR   rfProcStatus;      /* process status */
   UCHAR   dummy1;
   BOOL    fForeground;       /* current process has keyboard focus */
   UCHAR   typeProcess;       /* process type */
   UCHAR   dummy2;
   SEL     selEnvironment;    /* environment selector */
   USHORT  offCmdLine;        /* command line offset */
   USHORT  cbDataSegment;     /* length of data segment */
   USHORT  cbStack;           /* stack size */
   USHORT  cbHeap;            /* heap size */
   HMODULE hmod;              /* module handle of the application */
   SEL     selDS;             /* data segment handle of the application */
} LINFOSEG;
  
typedef LINFOSEG *PLINFOSEG;

#define MAKEPGINFOSEG(sel) ((PGINFOSEG)MAKEP(sel, 0))
#define MAKEPLINFOSEG(sel) ((PLINFOSEG)MAKEP(sel, 0))
#define DosGetInfoSeg Dos16GetInfoSeg

extern "C" 
{
 APIRET16 APIENTRY16 DosGetInfoSeg(PSEL GlobalSeg, PSEL LocalSeg);
} 

#endif // INCL_OCLDOSGETINFOSEG

#pragma pack()


#endif // OSYSTEMH_INCLUDED

/* end of source */
