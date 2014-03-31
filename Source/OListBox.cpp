// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OListBox.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OListBox.cpp 1.50 1996/08/11 23:49:21 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OListBox.hpp>



OListBox::OListBox(const ULONG id,
                   const HWND Parent,
                   const ULONG Style,
                   BOOL autoScrolling)
  : OWindow(id, 0, 0),
    autoScroll(autoScrolling)
{
 parent = Parent;
 owner = Parent;
 style = Style;
}



OListBox::OListBox(const ULONG id,
                   const OFrame& Parent,
                   const ULONG Style,
                   BOOL autoScrolling)
  : OWindow(id, 0, 0),
    autoScroll(autoScrolling)
{
 parent = Parent.hwnd;
 owner = Parent.hwnd;
 style = Style;
}



OListBox::OListBox(const ULONG id,
                   const pOFrame Parent,
                   const ULONG Style,
                   BOOL autoScrolling)
  : OWindow(id, 0, 0),
    autoScroll(autoScrolling)
{
 parent = Parent->hwnd;
 owner = Parent->hwnd;
 style = Style;
}



OListBox::~OListBox()
  {}


PSZ OListBox::isOfType() const
{ 
 return("OListBox"); 
}



OListBox& OListBox::createListBox(const ULONG x, const ULONG y,
                                  const ULONG cx, const ULONG cy)
{
 if ((hwnd = WinCreateWindow(parent, WC_LISTBOX, "",
                             style | WS_VISIBLE,
                             x, y, cx, cy, owner, HWND_TOP,
                             res, NULL, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(153), 0);
 
 return(*this);
}



BOOL OListBox::deleteAll()
{
 return((BOOL)WinSendMsg(hwnd, LM_DELETEALL, NULL, NULL));
}



ULONG OListBox::deleteItem(const ULONG itemIndex)
{
 return((ULONG)WinSendMsg(hwnd, LM_DELETEITEM, MPFROMSHORT(itemIndex), NULL));
}



ULONG OListBox::insertItem(PCSZ text, const ULONG itemIndex)
{
 ULONG ul = 0;

 if (text)
   ul = (ULONG)WinSendMsg(hwnd, LM_INSERTITEM, MPFROMSHORT(itemIndex), MPFROMP(text));
 if (autoScroll)
   auto_scroll();
 return(ul);
}


ULONG OListBox::queryItemCount()
{
 return((ULONG)WinSendMsg(hwnd, LM_QUERYITEMCOUNT, NULL, NULL));
}


ULONG OListBox::queryItemHandle(const ULONG itemIndex)
{
 return((ULONG)WinSendMsg(hwnd, LM_QUERYITEMHANDLE, MPFROMSHORT(itemIndex), NULL));
}


ULONG OListBox::queryItemText(OString& Buffer, const ULONG itemIndex)
{
 PSZ   tmp = new CHAR[2*CCHMAXPATH];
 ULONG ul;

 ul = (ULONG) WinSendMsg(hwnd, LM_QUERYITEMTEXT, MPFROM2SHORT(itemIndex, 2*CCHMAXPATH), MPFROMP(tmp));
 Buffer << tmp;
 delete[] tmp;
 return(ul);
}


ULONG OListBox::queryItemTextLength(const ULONG itemIndex)
{
 return((ULONG)WinSendMsg(hwnd, LM_QUERYITEMTEXTLENGTH, MPFROMSHORT(itemIndex), NULL));
}


ULONG OListBox::querySelection(const ULONG itemStart)
{
 return((ULONG)WinSendMsg(hwnd, LM_QUERYSELECTION, MPFROMSHORT(itemStart), NULL));
}


ULONG OListBox::queryTopItem()
{
 return((ULONG)WinSendMsg(hwnd, LM_QUERYTOPINDEX, NULL, NULL));
}



ULONG OListBox::searchString(PCSZ text, 
                             const ULONG itemStart,
                             const ULONG command)
{
 if (text)
   return((ULONG)WinSendMsg(hwnd, LM_SEARCHSTRING, MPFROM2SHORT(command, itemStart), MPFROMP(text)));
 return(0);
}



BOOL  OListBox::selectItem(const ULONG itemIndex, const BOOL state)
{
 return((BOOL)WinSendMsg(hwnd, LM_SELECTITEM, MPFROMSHORT(itemIndex), MPFROMSHORT(state)));
}


BOOL  OListBox::setItemHandle(const ULONG itemIndex, const ULONG handle)
{
 return((BOOL)WinSendMsg(hwnd, LM_SETITEMHANDLE, MPFROMSHORT(itemIndex), MPFROMSHORT(handle)));
}


BOOL  OListBox::setItemHeight(const ULONG newHeight)
{
 return((BOOL)WinSendMsg(hwnd, LM_SETITEMHEIGHT, MPFROMSHORT(newHeight), NULL));
}


BOOL OListBox::setItemText(const ULONG itemIndex, PCSZ text)
{
 if (text)
   return((BOOL)WinSendMsg(hwnd, LM_SETITEMTEXT, MPFROMSHORT(itemIndex), MPFROMP(text)));
 return(FALSE);
}


BOOL  OListBox::setToTop(const ULONG itemIndex)
{
 return((BOOL)WinSendMsg(hwnd, LM_SETTOPINDEX, MPFROMSHORT(itemIndex), NULL));
}


void OListBox::auto_scroll()
{
 FONTMETRICS FontMetrics;

 WinQueryWindowRect(hwnd, &rcl);
 hps = WinGetPS(hwnd);
 GpiQueryFontMetrics(hps, sizeof(FONTMETRICS), &FontMetrics);
 WinReleasePS(hps);
 if (queryItemCount() > ((rcl.yTop - rcl.yBottom) / FontMetrics.lMaxBaselineExt))
  {
   if ((rcl.yTop - rcl.yBottom) % FontMetrics.lMaxBaselineExt)
     setToTop(queryTopItem()+2); 
   else
     setToTop(queryTopItem()+1); 
  }
}

OListBox&  OListBox::setAutoScroll(BOOL autoScrolling)
{
 autoScroll = autoScrolling;
 return(*this);
}

// end of source
