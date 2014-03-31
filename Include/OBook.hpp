// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OBook.hpp  - Notebooks


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OBook.hpp 1.1 1996/08/12 00:01:09 B.STEIN Release $

#ifndef OBOOK_INCLUDED
  #define OBOOK_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif

#ifndef LIST_INCLUDED
  #include <OList.hpp>
#endif


#ifndef OBOOKPAGE_INCLUDED
  #include <OBookPage.hpp>
#endif

// definitions and macros

// this is a standard style configuration
// use your own if you want

#define NB_STANDARD  (BKS_BACKPAGESBR | BKS_MAJORTABRIGHT | BKS_ROUNDEDTABS | BKS_STATUSTEXTLEFT | \
                      BKS_SPIRALBIND | BKS_TABTEXTLEFT | WS_GROUP | WS_TABSTOP | WS_VISIBLE)

#define NB_STANDARD_FRAME (FCF_TASKLIST | FCF_TITLEBAR | FCF_SYSMENU | \
                           FCF_MINBUTTON | FCF_SIZEBORDER | FCF_ICON)

typedef OList<OBookPage> pageList;
typedef pageList *ppageList;

typedef class OBook *pOBook;

class __CPP_EXPORT__ OBook
  : public OFrame
{
 private:  // these private members are strictly for internal use only !!!

   HWND     Assoc       (pOBookPage pnbp, PPAGESELECTNOTIFY ppsn);
   ULONG    gSS         (PCSZ szString);

   OBook
      &NBError     (PCH msg),
      &sNBP        (PPAGESELECTNOTIFY ppsn),
      &cNbk        (),
      &sP          (pOBookPage pP);

 public:
   HWND                 book;      // notebook window handle
   pageList             Pages;     // the pages setups in a List of pages
   ULONG                bStyle;    // Notebook Style
   ULONG                dimCX;     // cx-dimension
   ULONG                dimCY;     // cy-dimension

// ctors

   OBook                (const ULONG id, 
                         const HWND  Parent = HWND_DESKTOP,
                         const ULONG frameStyle = NB_STANDARD_FRAME);

   OBook                (const ULONG id,
                         const OFrame& Parent, 
                         const ULONG frameStyle = NB_STANDARD_FRAME);

   OBook                (const ULONG id,
                         const pOFrame Parent, 
                         const ULONG frameStyle = NB_STANDARD_FRAME);

   virtual
      ~OBook();

   virtual
      PSZ isOfType      () const; 

   OBook
     &createBook        (PSZ Text,
                         const ULONG cx, 
                         const ULONG cy, 
                         const ULONG bookStyle),

     &setFramePos       (),

     &setSizePosFrame   (const HWND behind, 
                         SWP dimensions, 
                         const ULONG flags),

     &addPages          (ppageList pagesList),

     &setTabDimensions  ();


// command Handlers
   virtual
      BOOL OCommand     (ULONG msg, MPARAM mp1, MPARAM mp2);
};


#endif // OBOOK_INCLUDED

// end of source
