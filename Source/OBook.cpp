
// (c) Cubus 1995
// All Rights Reserved
// OBook.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OBook.cpp 1.50 1996/08/11 23:49:08 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMsgs.hpp>
#include <OBook.hpp>
#include <OMessage.hpp>

#if defined(__EMX__)
  template class OList<OBookPage>;
#endif


// definitions

#define TAB_WIDTH_MARGIN      10
#define TAB_HEIGHT_MARGIN     6
#define DEFAULT_NB_TAB_HEIGHT 16


OBook::OBook(const ULONG id, 
             const HWND Parent, 
             const ULONG frameStyle)
   : OFrame(id, frameStyle, CS_SIZEREDRAW),
     book(NULLHANDLE),
     bStyle(0),
     dimCX(0),
     dimCY(0)
{
 parent = Parent;
 owner  = Parent;
}

OBook::OBook(const ULONG id,
             const OFrame& Parent,
             const ULONG frameStyle)
   : OFrame(id, frameStyle, CS_SIZEREDRAW),
     book(NULLHANDLE),
     bStyle(0),
     dimCX(0),
     dimCY(0)
{
 parent = Parent.hwnd;
 owner  = Parent.hwnd;
}


OBook::OBook(const ULONG id,
             const pOFrame Parent,
             const ULONG frameStyle)
   : OFrame(id, frameStyle, CS_SIZEREDRAW),
     book(NULLHANDLE),
     bStyle(0),
     dimCX(0),
     dimCY(0)
{
 parent = Parent->hwnd;
 owner  = Parent->hwnd;
}


OBook::~OBook() {}


PSZ OBook::isOfType() const
{ 
 return("OBook"); 
}



OBook& OBook::createBook(PSZ Text,
                         const ULONG cx,
                         const ULONG cy,
                         const ULONG bookStyle)
{
 dimCX         = cx;
 dimCY         = cy;
 bStyle        = bookStyle;
 pOBookPage pP = Pages.getFirst();

 winText << (PSZ) Text;

 createFrame("OBook");

 if (!pP)
   throw OPMException(OCL::error(148), 0); 

 cNbk();

 if (!(BOOL) WinSendMsg(book, BKM_TURNTOPAGE,
             MPFROMLONG(pP->ulPageID), NULL))
   throw OPMException(OCL::error(141), 0); 

 return(setFramePos());
}



OBook& OBook::setFramePos()
{
 setSizePosFrame(HWND_TOP, sizepos, 0);
 return(*this);
}


// Set Frame of the Book Window

OBook& OBook::setSizePosFrame(const HWND behind, SWP dimensions, const ULONG flag)
{
 POINTL aptl[2];
 SWP    swpScreen;

 aptl[0].x = 0;
 aptl[0].y = 0;
 aptl[1].x = dimCX;
 aptl[1].y = dimCY;

 swpScreen.cx=WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
 swpScreen.cy=WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

 WinMapDlgPoints(HWND_DESKTOP, aptl, 2, TRUE);
 WinSetWindowPos(frame, behind, (swpScreen.cx-(aptl[1].x))/2,
                (swpScreen.cy-(aptl[1].y))/2, aptl[1].x, aptl[1].y,
                 SWP_SIZE | SWP_MOVE | SWP_RESTORE | SWP_ACTIVATE);

 return(*this);
#ifdef __BCPLUSPLUS__
  #pragma warn -par
#endif
}
#ifdef __BCPLUSPLUS__
  #pragma warn .par
#endif




// set dimensions of the tabs

OBook& OBook::setTabDimensions()
{
 FONTMETRICS  fm;
 INT          iSize, iLongestMajText = 0, iLongestMinText = 0;
 pOBookPage   pP = Pages.getFirst();
 BOOL         Majors=FALSE, Minors=FALSE;

 hps = WinGetPS(book);

 memset(&fm, 0, sizeof(FONTMETRICS));
 if(GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &fm))
    fm.lMaxBaselineExt += (TAB_HEIGHT_MARGIN * 2);
 else
    fm.lMaxBaselineExt = DEFAULT_NB_TAB_HEIGHT + (TAB_HEIGHT_MARGIN * 2);

 while(pP)
  {
   iSize = gSS(pP->szTabText);
   if(pP->usTabType == BKA_MAJOR)
    {
     Majors=TRUE;
     if(iSize > iLongestMajText)
       iLongestMajText = iSize;
    }
   else
    {
     Minors=TRUE;
     if(iSize > iLongestMinText)
       iLongestMinText = iSize;
    }
   pP = Pages.getNext();
  }

 WinReleasePS(hps);

 if(iLongestMajText)
   iLongestMajText += TAB_WIDTH_MARGIN;

 if(iLongestMinText)
   iLongestMinText += TAB_WIDTH_MARGIN;

 if (Majors)
   Majors = (BOOL) WinSendMsg(book, BKM_SETDIMENSIONS,
                              MPFROM2SHORT(iLongestMajText, (SHORT)fm.lMaxBaselineExt),
                              MPFROMSHORT(BKA_MAJORTAB));
 else Majors=TRUE;

 if (Minors)
   Minors =(BOOL) WinSendMsg(book, BKM_SETDIMENSIONS,
                             MPFROM2SHORT(iLongestMinText, (SHORT)fm.lMaxBaselineExt),
                             MPFROMSHORT(BKA_MINORTAB));
 else
   Minors=TRUE;

 if (!(Majors && Minors))
   throw OPMException(OCL::error(140), 0);

 return(*this);
}



// add pages to the book

OBook& OBook::addPages(ppageList pagesList)
{
 pOBookPage pP = pagesList->getFirst();

 while(pP)
   {
    sP(pP);
    Pages.addLast(pP);
    pP = pagesList->getNext();
   }

 setTabDimensions();
 
 pP = Pages.getFirst();

 if (pP)
   WinSendMsg(book, BKM_TURNTOPAGE, MPFROMLONG(pP->ulPageID), NULL);

 return(*this);
}





BOOL OBook::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
    {
     case WM_SIZE:
       WinSetWindowPos(book, 0, 0, 0,
                       SHORT1FROMMP(mp2),
                       SHORT2FROMMP(mp2), SWP_SIZE | SWP_SHOW );
       break;

     case WM_CONTROL:
       if(SHORT1FROMMP(mp1) == FID_CLIENT)
        {
         switch(SHORT2FROMMP(mp1))
          {
           case BKN_PAGESELECTED:
             sNBP((PPAGESELECTNOTIFY) mp2);
             return(TRUE);
          }
        }
       break;

     case WM_DESTROY:
     case WM_CLOSE: {
       pOBookPage temp = Pages.getFirst();

       hideFrame();
       while(temp) {
         if ((temp->hwnd))
           WinSendMsg(temp->hwnd, msg, NULL, NULL);
         temp = Pages.getNext(); }
       break; }

     default:
       return(OFrame::OCommand(msg, mp1, mp2));
    }
 return(TRUE);
}


/*********************************************************************************************************/

// internals


// Create the Book

OBook& OBook::cNbk()
{
 pOBookPage pP = NULL;

 if ((book = WinCreateWindow(client, WC_NOTEBOOK, NULL,
                             bStyle, 0, 0, 0, 0,
                             frame, HWND_BOTTOM,
                             FID_CLIENT, NULL, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(142), 0);

 if(!WinSendMsg(book, BKM_SETNOTEBOOKCOLORS,
                MPFROMLONG(SYSCLR_FIELDBACKGROUND),
                MPFROMSHORT(BKA_BACKGROUNDPAGECOLORINDEX)))
   throw OPMException(OCL::error(143), 0);

 setTabDimensions();

 pP = Pages.getFirst();

 while(pP)
  {
   sP(pP);
   pP = Pages.getNext();
  }

 return(*this);
}


// Load a dialog and associate to a page

HWND OBook::Assoc(pOBookPage pnbp, PPAGESELECTNOTIFY ppsn)
{
 HWND hwndDlg = WinLoadDlg(book, book, OWinDefDlgProc,
                           NULLHANDLE, pnbp->idDlg, pnbp);

 if(hwndDlg)
    {
     if(!WinSendMsg(ppsn->hwndBook, BKM_SETPAGEWINDOWHWND,
                    MPFROMP(ppsn->ulPageIdNew), MPFROMLONG(hwndDlg)))
       {
        WinDestroyWindow(hwndDlg);
        hwndDlg = NULLHANDLE;
       }
    }
 else
    NBError("Error loading page dialog.");

 return(hwndDlg);
}


// get a string size

ULONG OBook::gSS(PCSZ szString)
{
 POINTL aptl[TXTBOX_COUNT];

 if(!GpiQueryTextBox(hps, strlen((PCH)szString), (PCH) szString, TXTBOX_COUNT, aptl))
   return 0;
 else
   return aptl[TXTBOX_CONCAT].x;
}


// setup a book page

OBook& OBook::sNBP(PPAGESELECTNOTIFY ppsn)
{
 HWND       hwndDlg = NULLHANDLE; 
 pOBookPage pnbp    = (pOBookPage) WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEDATA,
                                              MPFROMLONG(ppsn->ulPageIdNew), NULL);

 if (!pnbp)
   return(*this);

 if (pnbp == (pOBookPage) BOOKERR_INVALID_PARAMETERS)
   throw OPMException(OCL::error(149), 0);

 // If this is a BKA_MAJOR page and it is what this app terms a 'parent'
 // page, that means when the user selects this page we actually want to go
 // to its first MINOR page. So in effect the MAJOR page is just a dummy page
 // that has a tab that acts as a placeholder for its MINOR pages. If the
 // user is using the left arrow to scroll thru the pages and they hit this
 // dummy MAJOR page, that means they have already been to its MINOR pages in
 // reverse order. They would now expect to see the page before the dummy
 // MAJOR page, so we skip the dummy page. Otherwise the user is going the
 // other way and wants to see the first MINOR page associated with this
 // 'parent' page so we skip the dummy page and show its first MINOR page.

 if(pnbp->fParent)
  {
   ULONG ulPageFwd, ulPageNew;

   ulPageFwd = (ULONG) WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEID,
                                  MPFROMLONG(ppsn->ulPageIdNew),
                                  MPFROM2SHORT(BKA_NEXT, BKA_MINOR));

   // If this is true, the user is going in reverse order

   if((ulPageFwd == ppsn->ulPageIdCur) && (pnbp != Pages.getFirst()))
      ulPageNew = (ULONG) WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEID,
                                     MPFROMLONG(ppsn->ulPageIdNew),
                                     MPFROM2SHORT(BKA_PREV, BKA_MAJOR));
   else
      ulPageNew = ulPageFwd;

   if(ulPageNew == (ULONG) BOOKERR_INVALID_PARAMETERS)
      NBError("Invalid page specified");
   else if(ulPageNew)
      if(!WinSendMsg(ppsn->hwndBook, BKM_TURNTOPAGE,
                     MPFROMLONG(ulPageNew), NULL))
        NBError(OCL::error(10));
  }
 else
  {
   hwndDlg = (HWND) WinSendMsg(ppsn->hwndBook, BKM_QUERYPAGEWINDOWHWND,
                               MPFROMLONG(ppsn->ulPageIdNew), NULL);
   if(hwndDlg == (HWND) BOOKERR_INVALID_PARAMETERS )
    {
     hwndDlg = NULLHANDLE;
     NBError(OCL::error(11));
    }
   else if(!hwndDlg)
            // It is time to load this dialog because the user has flipped pages
            // to a page that hasn't yet had the dialog associated with it.
     hwndDlg = Assoc(pnbp, ppsn);
  }

    // Set focus to the first control in the dialog. This is not automatically
    // done by the notebook.

 if(!pnbp->fParent && hwndDlg)
   WinSetFocus(HWND_DESKTOP, WinWindowFromID(hwndDlg, pnbp->idFocus));

 return(*this);
}


// set up a particular page

OBook& OBook::sP(pOBookPage pP)
{
 ULONG ulPageId;

 if ((ulPageId = (ULONG) WinSendMsg(book, BKM_INSERTPAGE, NULL,
                         MPFROM2SHORT(pP->usTabType | BKA_STATUSTEXTON | BKA_AUTOPAGESIZE,
                         BKA_LAST))) == 0)
   throw OPMException(OCL::error(144), 0);

 pP->ulPageID = ulPageId;

 if (!(BOOL) WinSendMsg(book, BKM_SETPAGEDATA,
             MPFROMLONG(ulPageId),
             MPFROMP(pP)))
   throw OPMException(OCL::error(145), 0);

 if (!(BOOL) WinSendMsg(book, BKM_SETSTATUSLINETEXT,
             MPFROMP(ulPageId),
             MPFROMP(pP->szStatusLineText)))
   throw OPMException(OCL::error(146), 0);

 if (!(BOOL) WinSendMsg(book, BKM_SETTABTEXT,
             MPFROMP(ulPageId),
             MPFROMP(pP->szTabText)))
   throw OPMException(OCL::error(147), 0);

 return(*this);
}


OBook& OBook::NBError(PCH Msg)
{
 WinMessageBox(HWND_DESKTOP, HWND_DESKTOP, (PCH) Msg,
               OCL::error(12), 0,
               MB_OK | MB_APPLMODAL | MB_MOVEABLE | MB_CUAWARNING);
 return(*this);
}


/********************************************************************************************************/


// end of source
