// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMLE.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMLE.cpp 1.50 1996/08/11 23:49:22 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMLE.hpp>

#if defined(__EMX__)
  template class OThread<OMLE>;
#endif


OMLE::OMLE(const ULONG id,
           const HWND Parent,
           const ULONG Style)
     : OWindow(id, 0, 0),
       imex(NULL),
       imexLen(0),
       imexOffset(0),
       insertLargeThr(this, &OMLE::insertLarge)
{
 parent = owner = Parent;
 style = Style;
}


OMLE::OMLE(const ULONG id,
           const OFrame& Parent,
           const ULONG Style)
     : OWindow(id, 0, 0),
       imex(NULL),
       imexLen(0),
       imexOffset(0),
       insertLargeThr(this, &OMLE::insertLarge)
{
 parent = owner = Parent.hwnd;
 style = Style;
}

OMLE::OMLE(const ULONG id,
           const pOFrame Parent,
           const ULONG Style)
     : OWindow(id, 0, 0),
       imex(NULL),
       imexLen(0),
       imexOffset(0),
       insertLargeThr(this, &OMLE::insertLarge)
{
 parent = owner = Parent->hwnd;
 style = Style;
}



OMLE::~OMLE()
  {}


PSZ OMLE::isOfType() const
{ 
 return("OMLE"); 
}


BOOL OMLE::createMLE(const ULONG x,
                     const ULONG y,
                     const ULONG cx,
                     const ULONG cy)
{
 hwnd = WinCreateWindow(parent, WC_MLE, NULL, style | WS_VISIBLE,
                        x, y, cx, cy,
                        owner, HWND_TOP, 0, NULL, NULL);
 return(hwnd != NULLHANDLE);
}



ULONG OMLE::getText(PVOID out, ULONG len)
{
 ULONG  exported;

 WinSendMsg(hwnd, MLM_SETIMPORTEXPORT, MPFROMP((PBYTE)out), MPFROMLONG(len));
 exported = (ULONG) WinSendMsg(hwnd, MLM_EXPORT, MPFROMP(&imexOffset), MPFROMP(&len));
 return(exported);
}


ULONG OMLE::getText(OString& Buffer)
{
 PSZ   temp = new CHAR[3*CCHMAXPATH];
 ULONG charsRead;

 if ((charsRead = (ULONG) WinQueryWindowText(hwnd, 3*CCHMAXPATH, temp)) != 0)
   Buffer << temp;
 else
   Buffer << (PSZ) NULL;
 delete[] temp;
 return(charsRead != 0);
}



ULONG OMLE::setText(PVOID in, ULONG len)
{
 ULONG  inserted = imexOffset;

 WinSendMsg(hwnd, MLM_SETIMPORTEXPORT, MPFROMP((PBYTE)in), MPFROMLONG(len));
 WinSendMsg(hwnd, MLM_IMPORT, MPFROMP(&imexOffset), MPFROMP(&len));

 inserted = imexOffset - inserted;
 return(inserted);
}


ULONG OMLE::setText(PSZ text)
{
 if (text)
   return(setText((PVOID)text, strlen(text)+1));
 return(0);
}



BOOL OMLE::insertText(PSZ text)
{
 if (text)
   return((BOOL)WinSendMsg(hwnd, MLM_INSERT, MPFROMP(text), NULL));
 return(FALSE);
}



BOOL OMLE::insertFile(PCSZ fileName)
{
 openedFile << (PSZ) fileName;
 insertLargeThr.run();
 return(TRUE);
}



BOOL OMLE::copy()
{
 return(FALSE);
}


BOOL OMLE::cut()
{
 return(FALSE);
}


BOOL OMLE::paste()
{
 return(FALSE);
}


BOOL OMLE::copy2Clip()
{
 return(FALSE);
}


BOOL OMLE::cut2Clip()
{
 return(FALSE);
}


BOOL OMLE::pasteFromClip()
{
 return(FALSE);
}


BOOL OMLE::clear()
{
 return(TRUE);
}




BOOL OMLE::undo()
{
 return(FALSE);
}




BOOL OMLE::deleteText(ULONG beginPoint, ULONG count)
{
 return(((ULONG)WinSendMsg(hwnd, MLM_DELETE,
                           MPFROMSHORT(beginPoint), MPFROMSHORT(count))) == count);
}

BOOL  OMLE::deleteAll()
{
 return(((ULONG)WinSendMsg(hwnd, MLM_DELETE, 
                           MPFROMSHORT(0), MPFROMSHORT(length()))) == length());
}


void OMLE::insertLarge()
{
 FILESTATUS fileStatus;
 PBYTE      rBuffer;
 HFILE      hf;
 ULONG      cbRead, ulAction;
 PBYTE      Buffer;
 ULONG      SIZE = 8192;

 DosOpen(openedFile, &hf, &ulAction, 0, FILE_NORMAL, FILE_OPEN | FILE_CREATE,
         OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL);
 DosQueryFileInfo(hf, 1, (PVOID)&fileStatus,  sizeof(FILESTATUS));
 DosAllocMem((PPVOID)&rBuffer, fileStatus.cbFile, PAG_READ | PAG_WRITE | PAG_COMMIT);
 memset(rBuffer, 0, fileStatus.cbFileAlloc);

 DosRead(hf, rBuffer, fileStatus.cbFile, &cbRead);
 DosClose(hf);

 if (!cbRead) {
   DosFreeMem(rBuffer);
   return; }

 if (cbRead > SIZE) {
   ULONG steps = cbRead / SIZE;
   ULONG rest = cbRead % SIZE;

   Buffer = rBuffer;
   for (ULONG i = 1; i <= steps; ++i) {
     setText(Buffer, SIZE);
     Buffer = Buffer+SIZE; }
   setText(Buffer, rest); }
 else
   setText(rBuffer, fileStatus.cbFile);

 DosFreeMem(rBuffer);
}



ULONG OMLE::length()
{
 return((ULONG)WinSendMsg(hwnd, MLM_QUERYFORMATTEXTLENGTH, MPFROMLONG(0), MPFROMLONG(-1)));
}


ULONG OMLE::lines()
{
 return((ULONG)WinSendMsg(hwnd, MLM_QUERYLINECOUNT, NULL, NULL));
}



BOOL OMLE::changed()
{
 return((BOOL)WinSendMsg(hwnd, MLM_QUERYCHANGED, NULL, NULL));
}


void OMLE::enableRefresh()
{
 WinSendMsg(hwnd, MLM_ENABLEREFRESH, NULL, NULL);
}


void OMLE::disableRefresh()
{
 WinSendMsg(hwnd, MLM_DISABLEREFRESH, NULL, NULL);
}


ULONG OMLE::setFormat(const ULONG format)
{
 return((ULONG)WinSendMsg(hwnd, MLM_FORMAT, MPFROMSHORT(format), NULL));
}



// end of source
