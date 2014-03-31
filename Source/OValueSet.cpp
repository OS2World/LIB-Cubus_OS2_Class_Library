// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) Matthias StÅbner 1994
// OValueSet.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OValueSet.cpp 1.50 1996/08/11 23:49:34 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OValueSet.hpp>


OValueSet::OValueSet(const ULONG id,
                     const HWND  Parent,      // becomes parent and owner of the set
                     const ULONG Rows,
                     const ULONG Columns,
                     const ULONG Margin,
                     const ULONG Style)
 : OWindow(id, 0, 0),
   rows(Rows),
   columns(Columns),
   margin(Margin)
{
 parent = Parent;
 owner  = Parent;
 style  = Style;
}


OValueSet::OValueSet(const ULONG id,
                     const OFrame& Parent,   // becomes parent and owner of the set
                     const ULONG Rows,
                     const ULONG Columns,
                     const ULONG Margin,
                     const ULONG Style)
 : OWindow(id, 0, 0),
   rows(Rows),
   columns(Columns),
   margin(Margin)
{
 parent = Parent.hwnd;
 owner  = Parent.hwnd;
 style  = Style;
}


OValueSet::OValueSet(const ULONG id,
                     const pOFrame Parent,   // becomes parent and owner of the set
                     const ULONG Rows,
                     const ULONG Columns,
                     const ULONG Margin,
                     const ULONG Style)
 : OWindow(id, 0, 0),
   rows(Rows),
   columns(Columns),
   margin(Margin)
{
 parent = Parent->hwnd;
 owner  = Parent->hwnd;
 style  = Style;
}


// dtor

OValueSet::~OValueSet()
  {}


PSZ OValueSet::isOfType() const
{
 return("OValueSet");
}


OValueSet& OValueSet::createValueSet(const SHORT x, const SHORT y,
                               const SHORT cx, const SHORT cy)
{
 ctlData.cbSize = sizeof(VSCDATA);
 ctlData.usRowCount = rows;
 ctlData.usColumnCount = columns;

 if ((hwnd = WinCreateWindow(parent, WC_VALUESET, NULL,
                             style | WS_VISIBLE,
                             x, y, cx, cy,
                             owner, HWND_TOP,
                             res, &ctlData, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(163), 0);

 return(*this);
}



BOOL OValueSet::queryItem(ULONG row, ULONG col)
{
 ULONG itemInfo = 0;

 memset(&selected, 0, sizeof(vsItem));

 switch(queryItemAttr(row, col))
  {
   case VIA_TEXT: {
     VSTEXT vstext;
     CHAR   Buffer[100];

     vstext.ulBufLen = 100;
     vstext.pszItemText = Buffer;
     WinSendMsg(hwnd, VM_QUERYITEM, MPFROM2SHORT(row, col), MPFROMP(&vstext));
     selected.text << Buffer;
     break; }

   case VIA_ICON:
     itemInfo = (ULONG) WinSendMsg(hwnd, VM_QUERYITEM, MPFROM2SHORT(row, col), NULL);
     selected.icon = (HPOINTER) itemInfo;
     break;

   case VIA_BITMAP:
     itemInfo = (ULONG) WinSendMsg(hwnd, VM_QUERYITEM, MPFROM2SHORT(row, col), NULL);
     selected.icon = (HBITMAP) itemInfo;
     break;

   case VIA_RGB:
     itemInfo = (ULONG) WinSendMsg(hwnd, VM_QUERYITEM, MPFROM2SHORT(row, col), NULL);
     selected.rgb.bRed = (BYTE) itemInfo / 65536;
     itemInfo %= 65536;
     selected.rgb.bGreen = (BYTE) itemInfo / 256;
     selected.rgb.bBlue = (BYTE) itemInfo % 256;
     break;
 
   case VIA_COLORINDEX:
     selected.colorIndex = itemInfo;
     break;
  }
 return(itemInfo != 0);
}



ULONG OValueSet::queryItemAttr(ULONG row, ULONG col)
{
 return((ULONG)WinSendMsg(hwnd, VM_QUERYITEMATTR, MPFROM2SHORT(row, col), NULL));
}



ULONG OValueSet::queryMetrics(ULONG fMetric)
{
 return((ULONG)WinSendMsg(hwnd, VM_QUERYMETRICS, MPFROMSHORT(fMetric), NULL));
}



BOOL  OValueSet::querySelected()
{
 MRESULT temp;

 temp = WinSendMsg(hwnd, VM_QUERYSELECTEDITEM, NULL, NULL);
 if (temp)
  {
   selected.row = SHORT1FROMMP(temp);
   selected.col = SHORT2FROMMP(temp);
   return(TRUE);
  }
 return(FALSE);
}



BOOL OValueSet::selectItem(ULONG row, ULONG col)
{
 return((BOOL)WinSendMsg(hwnd, VM_SELECTITEM, MPFROM2SHORT(row, col), NULL));
}


BOOL OValueSet::setItem(ULONG row, ULONG col, ULONG itemInfo)
{
 BOOL fSuccess = TRUE;

 if (row == 0)
  {
   for (ULONG rowCount = 1; ((rowCount <= rows) && (fSuccess)); rowCount++)
     fSuccess = setItem(rowCount, col, itemInfo);
   return(fSuccess);
  }

 if (col == 0)
  {
   for (ULONG colCount = 1; ((colCount <= columns) && (fSuccess)); colCount++)
     fSuccess = setItem(row, colCount, itemInfo);
   return(fSuccess);
  }

 return((BOOL)WinSendMsg(hwnd, VM_SETITEM, MPFROM2SHORT(row, col), MPFROMLONG(itemInfo)));
}



BOOL OValueSet::setItemAttr(ULONG row, ULONG col, ULONG attribute, BOOL set)
{
 BOOL fSuccess = TRUE;

 if (row == 0)
  {
   for (ULONG rowCount = 1; ((rowCount <= rows) && (fSuccess)); rowCount++)
     fSuccess = setItemAttr(rowCount, col, attribute, set);
   return(fSuccess);
  }

 if (col == 0)
  {
   for (ULONG colCount = 1; ((colCount <= columns) && (fSuccess)); colCount++)
     fSuccess = setItemAttr(row, colCount, attribute, set);
   return(fSuccess);
  }

 return((BOOL)WinSendMsg(hwnd, VM_SETITEMATTR,
                         MPFROM2SHORT(row, col), MPFROM2SHORT(attribute, set)));
}


BOOL OValueSet::setMetrics(ULONG fMetric, ULONG itemInfo)
{
 return((BOOL)WinSendMsg(hwnd, VM_SETMETRICS, MPFROMSHORT(fMetric), MPFROMSHORT(itemInfo)));
}


// end of source
