// OCL - OS/2 Class Library
// (c) Matthias Stuebner (matze@joker.berlinet.de)
// (c) Benno Stein
// (c) Cubus 1995
// All Rights Reserved
// ODragEntryField.hpp


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

// $Header: W:/Projects/OCL/Include/rcs/ODragEntryField.hpp 1.50 1996/08/11 23:47:13 B.STEIN Release $


#ifndef ODRAGENTRYFIELD_INCLUDED
  #define ODRAGENTRYFIELD_INCLUDED


#ifndef OEFIELD_INCLUDED
  #include <OEntryField.hpp>
#endif

#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif


typedef class ODragEntryField *pODragEntryField;

 
class __CPP_EXPORT__ ODragEntryField
  : public OEntryField
{
  private:

    PFNWP                PM_EntryFieldProc;

  public:

    ODragEntryField     (const ULONG     id,
                         const HWND      Parent,
                         const ULONG     Style = ES_MARGIN | ES_AUTOSCROLL,
                         const ULONG     Limit = CCHMAXPATH);

    ODragEntryField     (const ULONG     id,
                         const OFrame&   Parent,
                         const ULONG     Style = ES_MARGIN | ES_AUTOSCROLL,
                         const ULONG     Limit = CCHMAXPATH);

    ODragEntryField     (const ULONG     id,
                         const pOFrame   Parent,
                         const ULONG     Style = ES_MARGIN | ES_AUTOSCROLL,
                         const ULONG     Limit = CCHMAXPATH);

    virtual
      ~ODragEntryField  ();


    ODragEntryField&
      createEntryField  (const ULONG     x,
                         const ULONG     y,
                         const ULONG     cx,
                         const ULONG     cy);

    OWindow&
      inherit           (const HWND      hwndDlg);

    MRESULT
      EFDefaultCall     (ULONG  msg,  
                         MPARAM mp1,
                         MPARAM mp2);

    virtual
       PSZ isOfType     () const;

    virtual
       BOOL OCommand    (ULONG msg,
                         MPARAM mp1,
                         MPARAM mp2);

};

#ifdef __cplusplus
 extern "C" {
#endif

  MRESULT EXPENTRY
       ODragEntryFieldProc
                        (HWND hwnd,
                         ULONG msg,
                         MPARAM mp1,
                         MPARAM mp2);
#ifdef __cplusplus
 }
#endif


#endif // ODRAGENTRYFIELD_INCLUDED

// end of source
