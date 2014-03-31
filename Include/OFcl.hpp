// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFcl.hpp

// file collector

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

// $Header: E:/Projects/OCL/Include/rcs/OFcl.hpp 1.12 1996/01/16 10:12:18 B.STEIN Release B.STEIN $

#ifndef FCL_INCLUDED
  #define FCL_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef LIST_INCLUDED
  #include <OList.hpp>
#endif

#ifndef LOSTRING_INCLUDED
  #include <lOString.hpp>
#endif

typedef class OFcl *pOFcl;

class __CPP_EXPORT__ OFcl
  : public OCLObject
{
 protected:
     BOOL            stopASAP;

 private:
     PFILEFINDBUF3   pffb;
     OString         filespec;
     OString         ext;
     PBYTE           tmp;
     ULONG           ulMaxFiles;
     ULONG           bufSize;
     APIRET          rc;
     BOOL            recurse;
     BOOL            checkDate;
     BOOL            checkTime;

     void
        setupFilebuf (),                        // allocate space for the buffer
        finddirs     (PSZ  dir),                // find dirs in case of recursion
        finddrives   (PCSZ spec),               // find all non removable drives
        findfiles    (OListItem<OString> *tmp), // find all files
        addfiles     (),                        // set all found file into List this->files
        adddirs      (PCSZ dir),                // set all found dirs into List this->dirs
        copy         ();                        // copy all batches into out

     BOOL
        hasDate      (PFILEFINDBUF3 buf),
        hasTime      (PFILEFINDBUF3 buf);

 public:

     lOString        dirs,                      // List of found dirs
                     files;                     // List of found files
     ULONG           AttrMask,                  // attribute mask (default FILE_NORMAL)
                     space,                     // amount of space used by all found files
                     found;                     // count of found files
     DATETIME        *DateTime;

     OFcl();                                    // constructor

     virtual
        ~OFcl();                                // destructor

     virtual
        PSZ isOfType () const; 

     void
        fclinit      (),                       // delete all Lists
        setCheck     (BOOL date, BOOL time),
        collect      (PCSZ spec,               // collect files with this mask
                      BOOL rec,                // recursive or not
                      BOOL local),             // all local drives?
        fclstop      ();                       // stops the scanner immediatly
};




typedef class OScanFcl *pOScanFcl;

class __CPP_EXPORT__ OScanFcl
   : public OFcl
{
 private:
    PSZ             Buffer;
    OString         ToScan;

 public:
    lOString        good;
    ifstream        file;


    OScanFcl        ();
    virtual
       ~OScanFcl    ();

    virtual
       PSZ isOfType () const; 

    BOOL init       (PCSZ FileName, PCSZ toScan);
    void init       (PCSZ FileName);
    void release    ();
    BOOL check      (PCSZ string);
    void checkFiles (PCSZ text);
};




#endif // FCL_INCLUDED

// end of source
