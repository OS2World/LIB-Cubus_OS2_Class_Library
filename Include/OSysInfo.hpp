// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSysInfo.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OSysInfo.hpp 1.50 1996/08/11 23:47:32 B.STEIN Release $

#ifndef OSYSINFO_INLUDED
  #define OSYSINFO_INLUDED

// a System Information Class


#ifndef LIST_INCLUDED
  #include <OList.hpp>
#endif

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef LOSTRING_INCLUDED
  #include <lOString.hpp>
#endif

typedef class OSysInfoVIO *pOSysInfoVIO;

class __CPP_EXPORT__ OSysInfoVIO
  : public OCLObject
{
 public:
    lOString          SysInfoList;
    OString           SysInfoVar;

    OSysInfoVIO       ();

    virtual
       ~OSysInfoVIO   ();

    virtual
       PSZ isOfType   () const;

    BOOL
       getDrives      (),               // get all local nonremovable drives (and drive labels)
       getAllDrives   (),               // get all drives (and drive labels)
       getEnv         (PCSZ env),       // get an environment variable
       getBootDrive   (),               // get the system boot drive
       getCfgEnv      (PSZ env),        // get a system setting from CONFIG.SYS
       getOSVer       (),               // get the OS/2 version number as string in SysInfoVar
       getOSVer       (double& version),// get OS/2 version number as double in passed reference
       findPathFile   (PCSZ file),      // find a file in path
       checkRemovable (PCSZ Drive),     // check if drive is a nonremovable local drive
       clearRDOnly    (PCSZ FileName);  // reset readonly flag of a file
};




typedef class OSysInfo *pOSysInfo;

class __CPP_EXPORT__ OSysInfo 
  : public OSysInfoVIO
{
 public:
    OSysInfo         ();

    virtual
       ~OSysInfo     ();

    virtual
       PSZ isOfType  () const;

    BOOL getDesktop  ();               // get the Desktop directory
};


#endif  // OSYSINFO_INCLUDED



// end of source
