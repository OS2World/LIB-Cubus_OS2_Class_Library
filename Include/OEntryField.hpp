// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OEntryField.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OEntryField.hpp 1.50 1996/08/11 23:47:13 B.STEIN Release $

#ifndef OEFIELD_INCLUDED
  #define OEFIELD_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


typedef class OEntryField *pOEntryField;

class __CPP_EXPORT__ OEntryField
  : public OWindow
{
 protected:
    ULONG  limit;

 public:

    OEntryField          (const ULONG id,
                          const HWND Parent,
                          const ULONG Style = ES_MARGIN | ES_AUTOSCROLL,
                          const ULONG Limit = CCHMAXPATH);

    OEntryField          (const ULONG id,
                          const OFrame& Parent,
                          const ULONG Style = ES_MARGIN | ES_AUTOSCROLL,
                          const ULONG Limit = CCHMAXPATH);

    OEntryField          (const ULONG id,
                          const pOFrame Parent,
                          const ULONG Style = ES_MARGIN | ES_AUTOSCROLL,
                          const ULONG Limit = CCHMAXPATH);

    virtual
       ~OEntryField      ();

    virtual
       PSZ isOfType      () const;

    OEntryField&
       createEntryField  (const ULONG x,
                          const ULONG y,
                          const ULONG cx,
                          const ULONG cy);

    OWindow&
       inherit           (const HWND hwndDlg);

    BOOL
       getText           (OString& Buffer),
       setText           (PCSZ text),
       cutText           (),
       copyText          (),
       pasteText         (),
       clearText         (),
       queryChanged      (),
       queryRDOnly       (),
       querySelection    (USHORT& firstChar, USHORT& lastChar),
       setFirstChar      (const USHORT first),
       setInsertMode     (const BOOL insert = TRUE),
       setRDOnly         (const BOOL readOnly = TRUE),
       setSelection      (const USHORT firstChar, const USHORT lastChar),
       setTextLimit      (const USHORT limit);

    ULONG
       queryFirstChar    ();
};


#endif // OEFIELD_INCLUDED

// end of source
