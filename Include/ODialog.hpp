// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// ODialog.hpp

// class definitions for ODialog

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

// $Header: E:/Projects/OCL/Include/rcs/ODialog.hpp 1.12 1996/01/16 10:12:18 B.STEIN Release B.STEIN $

#ifndef ODIALOG_INCLUDED
  #define ODIALOG_INCLUDED


#ifndef OWINDOW_INCLUDED
  #include <OWindow.hpp>
#endif


#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif


#define CENTER_ONSCREEN 0
#define CENTER_ONPARENT 1

typedef class ODialog *pODialog;

class __CPP_EXPORT__ ODialog
  : public OWindow
{
 public:
   HMODULE            module;

 public:
    ODialog          (const ULONG idDlg);

    ODialog          (const HWND Parent,
                      const HWND Owner,
                      const ULONG idDlg);

    ODialog          (const HWND Parent,
                      const HWND Owner,
                      const HMODULE resource, 
                      const ULONG idDlg);

    virtual
       ~ODialog      ();

    virtual
       PSZ isOfType  () const;

    ODialog
       &createDlg    (),
       &showDlg      (),
       &dismissDlg   (BOOL success = TRUE),
       &hideDlg      (),
       &destroyDlg   (),
       &centerDlg    (const ULONG parentWindow = CENTER_ONSCREEN);

    BOOL showDlgModal();
};




#endif // ODIALOG_INCLUDED

// end of source
