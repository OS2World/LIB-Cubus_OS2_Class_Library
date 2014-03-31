// OCL - OS/2 Class Library
// (c) Matthias Stuebner (matze@joker.berlinet.de)
// (c) Benno Stein
// (c) Cubus 1995
// All Rights Reserved
// ODragEntryField.cpp


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


// $Header: W:/Projects/OCL/Source/rcs/ODragEntryField.cpp 1.50 1996/08/11 23:49:13 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <ODragEntryField.hpp>
#include <OMessage.hpp>


ODragEntryField::ODragEntryField( 
                        const ULONG     _id,
                        const HWND      _Parent,
                        const ULONG     _Style,
                        const ULONG     _Limit)

 : OEntryField(_id, _Parent, _Style, _Limit)
 {}

ODragEntryField::ODragEntryField( 
                        const ULONG     _id,
                        const OFrame&   _Parent,
                        const ULONG     _Style,
                        const ULONG     _Limit)

 : OEntryField(_id, _Parent, _Style, _Limit)
 {}

ODragEntryField::ODragEntryField( 
                        const ULONG     _id,
                        const pOFrame   _Parent,
                        const ULONG     _Style,
                        const ULONG     _Limit)

  : OEntryField(_id, _Parent, _Style, _Limit)
  {}


ODragEntryField::~ODragEntryField()
  {}


PSZ ODragEntryField::isOfType() const
{
 return("ODragEntryField");
}


ODragEntryField& ODragEntryField::createEntryField(
                          const ULONG x,
                          const ULONG y,
                          const ULONG cx,
                          const ULONG cy)
{
 CLASSINFO clsi ;
   
 WinQueryClassInfo(OApp::current().anchor(),
                   WC_ENTRYFIELD, &clsi);

 PM_EntryFieldProc = clsi.pfnWindowProc;

 if (!WinRegisterClass(OApp::current().anchor(),
                       "ODragEntryField",
                       (PFNWP) ODragEntryFieldProc,
                       0,
                       clsi.cbWindowData + sizeof (PVOID)))
   throw OPMException(OCL::error(45), 0, OException::fatal);


 if ((hwnd = WinCreateWindow(parent, "ODragEntryField", "",
                             style | WS_VISIBLE,
                             x, y, cx, cy, owner, HWND_TOP,
                             res, this, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(46), 0, OException::fatal);
 
 return(*this);
}



OWindow& ODragEntryField::inherit(const HWND hwndDlg)
{
 OWindow::inherit(hwndDlg);
 
 if (!WinQueryWindowPos(WinWindowFromID(hwndDlg, res), &sizepos))
   throw OPMException(OCL::error(47), 0, OException::fatal);
 
 WinDestroyWindow(WinWindowFromID(hwndDlg, res));

 return(createEntryField(sizepos.x, sizepos.y, sizepos.cx, sizepos.cy));
}


MRESULT ODragEntryField::EFDefaultCall(ULONG  msg,  
                                       MPARAM mp1,
                                       MPARAM mp2)
{
 return((MRESULT)PM_EntryFieldProc(hwnd, msg, mp1, mp2));
}



BOOL ODragEntryField::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 return(FALSE);
}



// The following function is strictly for internal use only!


MRESULT EXPENTRY ODragEntryFieldProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
 pODragEntryField odf_current = (pODragEntryField) WinQueryWindowPtr(hwnd, QWL_USER);

 if (odf_current)
   odf_current->hwnd = hwnd;

 switch(msg)
  {
   case WM_CREATE:
     if (!mp1)
       return(MRESULT(TRUE));
     odf_current = (pODragEntryField) mp1;
     WinSetWindowPtr(hwnd, QWL_USER, odf_current);
     odf_current->hwnd = hwnd;
     odf_current->EFDefaultCall(msg, mp1, mp2);
     odf_current->OCommand(msg, mp1, mp2);
     WinPostMsg(hwnd, EM_SETTEXTLIMIT, MPFROMSHORT (CCHMAXPATH), 0) ;
     break ;

   case WM_DESTROY:
     WinSetWindowPtr(hwnd, QWL_USER, NULL);
     if(odf_current) {
       odf_current->OCommand(msg, mp1, mp2); 
       return(odf_current->EFDefaultCall(msg, mp1, mp2)); }
     break;

   case DM_DRAGOVER:
    {
     PDRAGINFO  pdinfo = (PDRAGINFO) mp1;
     PDRAGITEM  pditem = NULL;

     DrgAccessDraginfo(pdinfo);
     pditem = DrgQueryDragitemPtr(pdinfo, 0);
     if (DrgVerifyRMF(pditem, "DRM_OS2FILE", NULL))
       {
        DrgFreeDraginfo (pdinfo) ;
        return(MRFROM2SHORT(DOR_DROP, DO_COPY));
       }
     else
       {
        DrgFreeDraginfo (pdinfo) ;
        return(MRFROM2SHORT(DOR_NEVERDROP, 0));
       }
    }

   case DM_DROP:
    {
     OString    Buffer1(CCHMAXPATH);
     OString    Buffer2(CCHMAXPATH);
     PDRAGINFO  pdinfo = (PDRAGINFO) mp1;
     PDRAGITEM  pditem = NULL;

     DrgAccessDraginfo(pdinfo);
     pditem = DrgQueryDragitemPtr(pdinfo, 0) ;
     DrgQueryStrName (pditem->hstrContainerName, CCHMAXPATH, Buffer1);
     DrgQueryStrName (pditem->hstrSourceName, CCHMAXPATH, Buffer2);
     Buffer1 + Buffer2;
     WinSetWindowText(hwnd, Buffer1);
     DrgFreeDraginfo (pdinfo) ;
     break;
    }
 
   default:
     if ((odf_current) &&
        (!odf_current->OCommand(msg, mp1, mp2)))
       return(odf_current->EFDefaultCall(msg, mp1, mp2));
     break;
  }
 return((MRESULT)FALSE);
}


// end of source
