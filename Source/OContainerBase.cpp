// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OContainerBase.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OContainerBase.cpp 1.50 1996/08/11 23:49:12 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OContainer.hpp>


OContainerBase::OContainerBase(const ULONG id,
                               const HWND Parent,
                               const ULONG cnrStyle, 
                               const ULONG initViewStyle)
  : OWindow(id, cnrStyle, 0)
{
 parent = owner = Parent;
 cnri.flWindowAttr = initViewStyle;
 hwnd = NULLHANDLE;
}


OContainerBase::OContainerBase(const ULONG id,
                               const pOFrame Parent, 
                               const ULONG cnrStyle, 
                               const ULONG initViewStyle)
  : OWindow(id, cnrStyle, 0)
{
 parent = Parent->client;
 owner  = Parent->frame;
 cnri.flWindowAttr = initViewStyle;
 hwnd = NULLHANDLE;
}


OContainerBase::OContainerBase(const ULONG id,
                               const OFrame& Parent, 
                               const ULONG cnrStyle, 
                               const ULONG initViewStyle)
  : OWindow(id, cnrStyle, 0)
{ 
 parent = Parent.client;
 owner  = Parent.frame;
 cnri.flWindowAttr = initViewStyle;
 hwnd = NULLHANDLE;
} 
 


OContainerBase::~OContainerBase() 
  {}


PSZ OContainerBase::isOfType() const
{ 
 return("OContainerBase"); 
}


OContainerBase& OContainerBase::createContainer()
{
 if (!hwnd)
  {
   if ((hwnd = WinCreateWindow(parent, WC_CONTAINER, "",
                               style, 0, 0, 0, 0,
                               owner, HWND_TOP,
                               res, this, NULL)) == NULLHANDLE)
     throw OPMException(OCL::error(165), 0);
  }

 if ((!setupDetails()) || (!setupItems()))
   throw OPMException(OCL::error(166), 0);

 if (cnri.flWindowAttr & CA_CONTAINERTITLE)
   setTitle(winText);
 else
   setView(cnri.flWindowAttr);

 show();

 return(*this);
}


OWindow& OContainerBase::inherit(const HWND hwndDlg)
{
 OWindow::inherit(hwndDlg);
 createContainer();
 return(*this);
}


BOOL OContainerBase::freeDetails()
{
 if (!hwnd) return(FALSE);

 WinSendMsg(hwnd, CM_REMOVEDETAILFIELDINFO, NULL,
            MPFROM2SHORT(0, CMA_FREE | CMA_INVALIDATE));
 return(TRUE);
}


BOOL OContainerBase::freeItems()
{
 if (!hwnd) return(FALSE);

 WinSendMsg(hwnd, CM_REMOVERECORD, NULL,
            MPFROM2SHORT(0, CMA_FREE | CMA_INVALIDATE));
 return(TRUE);
}



BOOL OContainerBase::freeContainer()
{
 return(freeItems() && freeDetails());
}


BOOL OContainerBase::setTitle(PSZ title)
{
 if (title) {
   winText << title;
   cnri.pszCnrTitle = winText;
   return(setCnrInfo(CMA_FLWINDOWATTR | CMA_CNRTITLE) && invalidateDetails()); }
 return(FALSE);
}


BOOL OContainerBase::setView(ULONG viewStyle)
{
 cnri.flWindowAttr = viewStyle;
 return(setCnrInfo(CMA_FLWINDOWATTR) && invalidateDetails()); 
}


/***********************************************************************************************************/
/* Services                                                                                                */
/***********************************************************************************************************/


PFIELDINFO  OContainerBase::allocDetailFields(ULONG fields) const
{
 return((PFIELDINFO)WinSendMsg(hwnd, 
                               CM_ALLOCDETAILFIELDINFO, 
                               MPFROMSHORT(fields), 
                               NULL));
}


PRECORDCORE OContainerBase::_allocRecords(ULONG additional, ULONG records) const
{
 return((PRECORDCORE)WinSendMsg(hwnd, 
                                CM_ALLOCRECORD, 
                                MPFROMSHORT(additional), 
                                MPFROMSHORT(records)));
}


BOOL OContainerBase::arrangeRecords() const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_ARRANGE, 
                         NULL, 
                         NULL));
}



BOOL OContainerBase::collapseTree(PVOID rootRecord) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_COLLAPSETREE, 
                         MPFROMP(rootRecord), 
                         NULL));
}



BOOL OContainerBase::expandTree(PVOID rootRecord) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_EXPANDTREE, 
                         MPFROMP(rootRecord), 
                         NULL));
}



BOOL OContainerBase::openEdit(PCNREDITDATA editData) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_OPENEDIT, 
                         MPFROMP(editData), 
                         NULL));
}



BOOL OContainerBase::closeEdit() const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_CLOSEEDIT, 
                         NULL, 
                         NULL));
}



BOOL OContainerBase::eraseRecord(PVOID record) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_ERASERECORD, 
                         MPFROMP(record), 
                         NULL));
}


BOOL OContainerBase::freeDetailInfo(PFIELDINFO rootRecord, ULONG count) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_FREEDETAILFIELDINFO, 
                         MPFROMP(rootRecord), 
                         MPFROMSHORT(count)));
}


BOOL OContainerBase::freeRecord(PVOID rootRecord, ULONG count) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_FREERECORD, 
                         MPFROMP(rootRecord), 
                         MPFROMSHORT(count)));
}


BOOL OContainerBase::removeDetailInfo(PFIELDINFO rootRecord, ULONG count, ULONG flag) const
{
 return((BOOL)WinSendMsg(hwnd,
                         CM_REMOVEDETAILFIELDINFO,
                         MPFROMP(rootRecord),
                         MPFROM2SHORT(count, flag)));
}


BOOL OContainerBase::removeRecord(PVOID rootRecord, ULONG count, ULONG flag) const
{
 return((BOOL)WinSendMsg(hwnd,
                         CM_REMOVERECORD,
                         MPFROMP(rootRecord),
                         MPFROM2SHORT(count, flag)));
}


BOOL OContainerBase::filter(PFN function, PVOID storage) const
{
 return(FALSE);
}


BOOL OContainerBase::insertDetailInfo(PFIELDINFO info, PFIELDINFOINSERT insert) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_INSERTDETAILFIELDINFO, 
                         MPFROMP(info), 
                         MPFROMP(insert)));
}


BOOL OContainerBase::insertRecord(PVOID rootRecord, PRECORDINSERT insert) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_INSERTRECORD, 
                         MPFROMP(rootRecord), 
                         MPFROMP(insert)));
}



BOOL OContainerBase::invalidateDetails() const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_INVALIDATEDETAILFIELDINFO, 
                         NULL, NULL));
}


BOOL OContainerBase::invalidateRecord(PVOID rootRecord, ULONG flag, ULONG count) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_INVALIDATERECORD, 
                         MPFROMP(rootRecord), 
                         MPFROM2SHORT(count, flag)));
}


ULONG OContainerBase::queryCnrInfo() const
{
 return((ULONG)WinSendMsg(hwnd, 
                          CM_QUERYCNRINFO, 
                          MPFROMP(&cnri), 
                          MPFROMSHORT(sizeof(CNRINFO))));
}


PFIELDINFO OContainerBase::queryDetailInfo(PFIELDINFO rootRecord, ULONG flag) const
{
 return((PFIELDINFO)WinSendMsg(hwnd, 
                               CM_QUERYDETAILFIELDINFO, 
                               MPFROMP(rootRecord),
                               MPFROMSHORT(flag)));
}


PRECORDCORE OContainerBase::_queryRecord(PVOID rootRecord, ULONG flag, ULONG order) const
{
 return((PRECORDCORE)WinSendMsg(hwnd, 
                                CM_QUERYRECORD, 
                                MPFROMP(rootRecord), 
                                MPFROM2SHORT(flag, order)));
}


PRECORDCORE OContainerBase::_queryEmphasis(PVOID record, ULONG flag) const
{
 return((PRECORDCORE)WinSendMsg(hwnd, 
                                CM_QUERYRECORDEMPHASIS, 
                                MPFROMP(record), 
                                MPFROMSHORT(flag)));
}



BOOL OContainerBase::setCnrInfo(ULONG attributeFlag) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_SETCNRINFO, 
                         MPFROMP(&cnri), 
                         MPFROMSHORT(attributeFlag)));
}



BOOL OContainerBase::setEmphasis(PVOID record, ULONG emphasis, BOOL set) const
{
 return((BOOL)WinSendMsg(hwnd, 
                         CM_SETRECORDEMPHASIS, 
                         MPFROMP(record),
                         MPFROM2SHORT(set, emphasis)));
}


// end of source
