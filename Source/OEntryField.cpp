// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OEntryField.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OEntryField.cpp 1.50 1996/08/11 23:49:15 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OEntryField.hpp>



OEntryField::OEntryField(const ULONG id,
                         const HWND Parent,
                         const ULONG Style,
                         const ULONG Limit)
  : OWindow(id, 0, 0),
    limit(Limit)
{
 parent = Parent;
 owner = Parent;
 style = Style;
}



OEntryField::OEntryField(const ULONG id,
                         const OFrame& Parent,
                         const ULONG Style,
                         const ULONG Limit)
  : OWindow(id, 0, 0),
    limit(Limit)
{
 parent = Parent.hwnd;
 owner = Parent.hwnd;
 style = Style;
}



OEntryField::OEntryField(const ULONG id,
                         const pOFrame Parent,
                         const ULONG Style,
                         const ULONG Limit)
  : OWindow(id, 0, 0),
    limit(Limit)
{
 parent = Parent->hwnd;
 owner = Parent->hwnd;
 style = Style;
}



OEntryField::~OEntryField()
  {}


PSZ OEntryField::isOfType() const
{ 
 return("OEntryField"); 
}



OEntryField& OEntryField::createEntryField(const ULONG x, const ULONG y, 
                                           const ULONG cx, const ULONG cy)
{
 if ((hwnd = WinCreateWindow(parent, WC_ENTRYFIELD, "",
                             style | WS_VISIBLE,
                             x, y, cx, cy, owner, HWND_TOP,
                             res, NULL, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(158), 0);
 
 setTextLimit(limit);
 return(*this);
}



OWindow& OEntryField::inherit(const HWND hwndDlg)
{
 OWindow::inherit(hwndDlg);
 setTextLimit(limit);
 return(*this);
}

BOOL  OEntryField::getText(OString& Buffer)
{
 OString temp(limit+1);
 ULONG   charsRead;

 if ((charsRead = (ULONG) WinQueryWindowText(hwnd, limit+1, temp)) != 0)
   Buffer << temp;
 else
   Buffer << (PSZ) NULL;
 return(charsRead != 0);
}



BOOL  OEntryField::setText(PCSZ text)
{
 if (text)
   return(WinSetWindowText(hwnd, (PSZ)text));
 else
   return(WinSetWindowText(hwnd, ""));
}



BOOL  OEntryField::cutText()
{
 return((BOOL)WinSendMsg(hwnd, EM_CUT, NULL, NULL));
}


BOOL  OEntryField::copyText()
{
 return((BOOL)WinSendMsg(hwnd, EM_COPY, NULL, NULL));
}


BOOL  OEntryField::pasteText()
{
 return((BOOL)WinSendMsg(hwnd, EM_PASTE, NULL, NULL));
}


BOOL  OEntryField::clearText()
{
 return((BOOL)WinSendMsg(hwnd, EM_CLEAR, NULL, NULL));
}


BOOL  OEntryField::queryChanged()
{
 return((BOOL)WinSendMsg(hwnd, EM_QUERYCHANGED, NULL, NULL));
}


ULONG OEntryField::queryFirstChar()
{
 return((ULONG)WinSendMsg(hwnd, EM_QUERYFIRSTCHAR, NULL, NULL));
}



BOOL  OEntryField::queryRDOnly()
{
 return((BOOL)WinSendMsg(hwnd, EM_QUERYREADONLY, NULL, NULL));
}


BOOL  OEntryField::querySelection(USHORT& firstChar, USHORT& lastChar)
{
 MRESULT temp = WinSendMsg(hwnd, EM_QUERYSEL, NULL, NULL);

 return((temp != NULL) &&
        ((firstChar = SHORT1FROMMP(temp)) != 0) &&
        ((lastChar = SHORT2FROMMP(temp)) != 0));
}



BOOL  OEntryField::setFirstChar(const USHORT first)
{
 return((BOOL)WinSendMsg(hwnd, EM_SETFIRSTCHAR, MPFROMSHORT(first), NULL));
}


BOOL  OEntryField::setInsertMode(const BOOL insert)
{
 return((BOOL)WinSendMsg(hwnd, EM_SETINSERTMODE, MPFROMSHORT(insert), NULL));
}


BOOL  OEntryField::setRDOnly(const BOOL readOnly)
{
 return((BOOL)WinSendMsg(hwnd, EM_SETREADONLY, MPFROMSHORT(readOnly), NULL));
}


BOOL  OEntryField::setSelection(const USHORT firstChar, const USHORT lastChar)
{
 return((BOOL)WinSendMsg(hwnd, EM_SETSEL, MPFROM2SHORT(firstChar, lastChar), NULL));
}


BOOL  OEntryField::setTextLimit(const USHORT limit)
{
 return((BOOL)WinSendMsg(hwnd, EM_SETTEXTLIMIT, MPFROMSHORT(limit), NULL));
}


// end of source
