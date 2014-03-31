// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OContainerBase.hpp

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

// $Header: E:/Projects/OCL/Include/rcs/OContainerBase.hpp 1.12 1996/01/16 10:12:17 B.STEIN Release B.STEIN $

#ifndef OCONTAINERBASE_INCLUDED
  #define OCONTAINERBASE_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <oframe.hpp>
#endif

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


typedef class OContainerBase *pOContainerBase;

class __CPP_EXPORT__ OContainerBase
  : public OWindow
{
 public:

   CNRINFO              cnri;

   OContainerBase      (const ULONG id,             // id of the container (must be unique!)
                        const HWND Parent,          // becomes parent AND owner of the container
                        const ULONG cnrStyle,       // container style
                        const ULONG initViewStyle); // default view style

   OContainerBase      (const ULONG id,             // id of the container (must be unique!)
                        const OFrame& Parent,       // becomes parent AND owner of the container
                        const ULONG cnrStyle,       // container style
                        const ULONG initViewStyle); // default view style

   OContainerBase      (const ULONG id,             // id of the container (must be unique!)
                        const pOFrame Parent,       // becomes parent AND owner of the container
                        const ULONG cnrStyle,       // container style
                        const ULONG initViewStyle); // default view style

   virtual
      ~OContainerBase  ();

   virtual
      PSZ isOfType     () const;

   virtual BOOL
     setupDetails      () = 0,           // sets up details view colums
     setupItems        () = 0;           // inserts all records

   OContainerBase&
     createContainer   ();               // creates the container and calls setupDetails()
                                         // and setupItems()

   OWindow&
     inherit           (const HWND       hwndDlg);

   BOOL
     insertDetailInfo  (PFIELDINFO       info, 
                        PFIELDINFOINSERT insert) const,
     insertRecord      (PVOID            rootRecord,
                        PRECORDINSERT    insert) const,
     freeDetails       (),               // frees details fieldinfo
     freeItems         (),               // removes all items
     freeContainer     (),               // calls freeDetails() and freeItems()
     freeDetailInfo    (PFIELDINFO       rootRecord, ULONG count) const,
     freeRecord        (PVOID            rootRecord, ULONG count) const,
     eraseRecord       (PVOID            record) const,
     removeDetailInfo  (PFIELDINFO       rootRecord,
                        ULONG            count,
                        ULONG            flag = CMA_FREE | CMA_INVALIDATE) const,
     removeRecord      (PVOID            rootRecord,
                        ULONG            count, 
                        ULONG            flag = CMA_FREE | CMA_INVALIDATE) const,
     queryCnrInfo      () const,
     setView           (ULONG            viewStyle),
     setTitle          (PSZ              title),
     setCnrInfo        (ULONG            attributeFlag = CMA_FLWINDOWATTR) const,
     setEmphasis       (PVOID            record,
                        ULONG            emphasis = CRA_SELECTED,
                        BOOL             set = TRUE) const,
     arrangeRecords    () const,
     collapseTree      (PVOID            rootRecord = NULL) const,
     expandTree        (PVOID            rootRecord = NULL) const,
     openEdit          (PCNREDITDATA     editData) const,
     closeEdit         () const,
     invalidateDetails () const,
     invalidateRecord  (PVOID            rootRecord = NULL,
                        ULONG            flag = CMA_REPOSITION,
                        ULONG            count = 0) const,   // invalidate all
     filter            (PFN              function, 
                        PVOID            storage) const;     // not yet implemented

   PRECORDCORE
     _allocRecords     (ULONG            additional, ULONG records) const,
     _queryRecord      (PVOID            rootRecord,
                        ULONG            flag   = CMA_FIRST,
                        ULONG            order  = CMA_ITEMORDER) const,
     _queryEmphasis    (PVOID            record = (PVOID)CMA_FIRST,
                        ULONG            flag   = CRA_SELECTED) const;

   PFIELDINFO
     allocDetailFields (ULONG            fields) const,
     queryDetailInfo   (PFIELDINFO       rootRecord,
                        ULONG            flag = CMA_FIRST) const;
};


#endif // OCONTAINERBASE_INCLUDED

// end of source
