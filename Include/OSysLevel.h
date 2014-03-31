// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSysLevel.h

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


// $Header: W:/Projects/OCL/Include/rcs/OSysLevel.h 1.50 1996/08/11 23:47:32 B.STEIN Release $


/*

  The following diagram shows the general format of a syslevel file.

     ษอออออออออออออออออออออออออออออป
     บ header (SLFHEADER)          บ
     บ       ...                   บ
ฺฤฤฤฤืฤฤฤฤฤฤ ulTableOffset         บ
ณ    บ                             บ
ณ    ศอออออออออออออออออออออออออออออผ
ณ
ณ
ภฤฤ>>ษอออออออออออออออออออออออออออออป
     บ SYSTABLE                    บ
     บ       ...                   บ
     บ       ...                   บ
     บ       ...                   บ
     ศอออออออออออออออออออออออออออออผ
   **ษอออออออออออออออออออออออออออออป
     บ Updated directory list      บ
     บ       ...                   บ
     บ       ...                   บ
     บ       ...                   บ
     ศอออออออออออออออออออออออออออออผ

   ** Added after successful service

*/


#ifndef OSYSLEVEL_H_INCLUDED
  #define OSYSLEVEL_H_INCLUDED


// SLFHEADER - This structure contains the information in a
//             SYSLEVEL file header.  The first 2 fields are used
//             to verify that the file is actually a SYSLEVEL file.
//             Also identified is the version, date, and offset to
//             the SYSTABLE information -- see SYSTABLE


#pragma pack(1)

typedef struct _SLFHEADER
{
 USHORT    usSignature;          // special # for id of syslevel file
 CHAR      achSignature[8];      // id, must be 'SYSLEVEL'
 CHAR      achJulian[5];         // date of version
 USHORT    usSlfVersion;         // version of syslevel file, must be 1
 USHORT    ausReserved[8];       // reserved
 ULONG     ulTableOffset;        // offset of SYSTABLE
} SLFHEADER, *PSLFHEADER;


// SYSTABLE - This structure contains the information about
//            a specific component of a particular system. This
//            info includes date and level information about the
//            system /subsystem and the particular component.

// defines for bSysEdition field

#define SYSED_SE         0x00     // os/2 standard edition
#define SYSED_EE         0x01     // os/2 extended edition
#define SYSED_ES         0x02     // os/2 extended services
#define SYSED_GENERAL    0x0F     // all others


typedef struct _SYSTABLE
{
 USHORT    usSysId;               // identifies system/subsytem
 BYTE      bSysEdition;           // edition of system, eg SE=00, EE=01
 BYTE      bSysVersion;           // version, eg 1.00=10, 1.10=11
 BYTE      bSysModify;            // modify, eg 1.00=00, 1.01=01
 USHORT    usSysDate;             // date of system
 CHAR      achCsdLevel[8];        // subsytem CSD level, eg, XR?0000_
 CHAR      achCsdPrev[8];         // as above, except for prev system
 CHAR      achSysName[80];        // Title of system / subsytem (ASCIIZ)
 CHAR      achCompId[9];          // component ID of subsytem
 BYTE      bRefreshLevel;         // eg, for version 1.30.1, use 1
 BYTE      bReserved;             // reserved, must be 0
 CHAR      achType[9];            // Null terminated type (8 chars +'\0')
 BYTE      usReserved[6];         // reserved, must be 0
} SYSTABLE, *PSYSTABLE;


#pragma pack()

/*

Detailed SYSTABLE Field Descriptions
------------------------------------

  This is a number that is assigned to each product that is supported for
service.

  Currently assigned SYSIDs:

     SYSID   EXTENSION    (partial list)
     -----   ---------

  [note:  other SYSIDs in the range A0x0 - F0x0 are used by IBM]

     C010  -    LMU   LAN Manager Utilities/2
     C020  -    X25   IBM X25 Net Manager
     C040  -    OSI   Communications Subsystem For OS/2 EE
     C060  -    SNP   IBM Snap Dump
     C070  -    ISB   ISDN Coprocessor Support Program Version 1.2
     C080  -    CS2   C SET/2
     C081  -    WF2   Work Frame/2
     1000  -          OS/2 SE
     1010  -          OS/2 Toolkit
     2000  -          OS/2 Comm Mgr
     2010  -          OS/2 Feature group 1  (3270 emulator)
     2020  -          OS/2 Feature group 2  (Async)
     4000  -          OS/2 Database Mgr
     4010  -          OS/2 Query Mgr
     5000  -          OS/2 LAN Requester
     5010  -          OS/2 LAN Server


bSysEdition
-----------

  A number between 0 and 255 (x0-xFF) that represents the type 
of product being serviced.

  OS/2 Standard Edition is 0
  OS/2 Extended Edition is 1
  OS/2 Extended Services is 2
  All other products are classified with a general sysedition of 15 (x0F)

bSysVersion
-----------

  A number between 1 and 255 (x1-xFF) that represents the
major and minor version of the product being serviced.
  The hi-order byte is the major version.  The lo-order byte is the
minor version.  For example:

  version 1.0, use x10
  version 1.1, use x11
  version 2.0, use x20

bSysModify
----------

  This is a number between 0 and 255 (x0-xFF) that represents a
modification version (eg, 2.01 is major version 2, minor version 0,
and modify version 1)

usSysDate   
---------

  This date is the date of the product.
This is represented by a 16-bit bitfield as follows (FDATE):

  unsigned day     : 5;
  unsigned month   : 4;
  unsigned year    : 7;

achCsdLevel
-----------

  This field is very important.  It specifies the level of the product.
It must be exactly 8 characters with underscore ('_') as its last
character.
  The first two characters are specific to the product:

  OS/2 Standard Edition - XR
  OS/2 Extended Edition - WR

  The third character represents the country:

0 - United States (Note: This is the digit zero, not letter O)
C - Canada (French speaking)
D - Denmark
F - France
G - German
H - Netherlands
I - Italy
J - Japan
L - Finland
N - Norway
P - Portugal
S - Spain
U - United Kingdom
W - Sweden

achCsdPrev
----------

  This represents the previous level of the system and has the same
form as achCsdLevel.  For an initial release, this should be the same
as achCsdLevel.

achSysName
----------

  This is the translated name of the system.  This must be null-
terminated and has a maximum length of 80 characters.

achCompId
---------

  This is a 9-digit ascii number that represents sub-products.
  For IBM OS/2 Base Operating System, this is 560109001.

bRefreshLevel
-------------

  This represents the refresh level.  This field is not matched
by the service tool, but is displayed from syslevel.exe.
  For version 1.30.1, use 1 for bRefreshLevel.

achType
-------

  This field contains an optional, NULL terminated alphanumeric type that is
defined by the application.  This field is only used by the OS/2 2.0 version
of SYSLEVEL.EXE.  The OS/2 1.3 SYSLEVEL.EXE will ignore this field.  If
no type is desired, this field must be all zero's (0).  Because the field is
NULL terminated, it has a maximum length of 8 characters (+ NULL = 9).

usReserved
----------

All reserved fields must be zero (0).

*/

#endif // OSYSLEVEL_H_INCLUDED


// end of source
