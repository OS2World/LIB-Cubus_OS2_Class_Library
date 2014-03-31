// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OEditor.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OEditor.cpp 1.50 1996/08/11 23:49:14 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OEditor.hpp>
#include <OBuffer.hpp>

#if defined(__EMX__)
  template class OThread<OEditor>;
#endif


OEditor::OEditor(const ULONG id,
                 const HWND Parent, 
                 const ULONG Style)
  : OMLE(id, Parent, Style),
    clearFlag(FALSE),
    loadFileThr(this, &OEditor::loadFile),
    saveFileThr(this, &OEditor::saveFile),
    saveFileAsThr(this, &OEditor::saveFileAs)
 {}


OEditor::OEditor(const ULONG id,
                 const pOFrame Parent,
                 const ULONG Style)
  : OMLE(id, Parent, Style),
    clearFlag(FALSE),
    loadFileThr(this, &OEditor::loadFile),
    saveFileThr(this, &OEditor::saveFile),
    saveFileAsThr(this, &OEditor::saveFileAs)
 {}


OEditor::OEditor(const ULONG id,
                 const OFrame& Parent,
                 const ULONG Style)
  : OMLE(id, Parent, Style),
    clearFlag(FALSE),
    loadFileThr(this, &OEditor::loadFile),
    saveFileThr(this, &OEditor::saveFile),
    saveFileAsThr(this, &OEditor::saveFileAs)
 {}



OEditor::~OEditor() {}


PSZ OEditor::isOfType() const
{ 
 return("OEditor"); 
}


void OEditor::loadFile()
{
 FILEDLG  fdFileDlg;
 HWND     hwndFileDlg;

 memset(&fdFileDlg, 0, sizeof(FILEDLG));
 fdFileDlg.cbSize=sizeof(FILEDLG);
 fdFileDlg.fl=FDS_CENTER | FDS_OPEN_DIALOG;
 fdFileDlg.pszTitle="Editor";
 strcpy(fdFileDlg.szFullFile, "*");
 hwndFileDlg=WinFileDlg(HWND_DESKTOP, parent, &fdFileDlg);
 if (hwndFileDlg && (fdFileDlg.lReturn==DID_OK)) {
   deleteAll();
   insertFile(fdFileDlg.szFullFile); }
 openedFile << fdFileDlg.szFullFile;
}



void OEditor::saveFile()
{
 pOBuffer   Buffer;
 HFILE      hf;
 ULONG      cbWritten, ulAction;
 ULONG      SIZE = 8192;

 if (!openedFile)
  {
   saveFileAs();
   return;
  }

 DosOpen(openedFile, &hf, &ulAction, 0, 0,
         OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
         OPEN_SHARE_DENYWRITE | OPEN_ACCESS_WRITEONLY,
         NULL);

 Buffer = new OBuffer(SIZE+1, OBuffer::ALLOC);

 imexOffset = 0;

 while(TRUE)
  {
   if(((cbWritten = getText(Buffer->getPtr(), SIZE)) == 0) ||
       (DosWrite(hf, Buffer, cbWritten, &cbWritten)))
     break;
  }

 DosClose(hf);
 delete Buffer;
}



void OEditor::saveFileAs()
{
 FILEDLG  fdFileDlg;
 HWND     hwndFileDlg;

 memset(&fdFileDlg, 0, sizeof(FILEDLG));
 fdFileDlg.cbSize=sizeof(FILEDLG);
 fdFileDlg.fl=FDS_CENTER | FDS_SAVEAS_DIALOG;
 fdFileDlg.pszTitle="Editor";
 if (openedFile)
   strcpy(fdFileDlg.szFullFile, openedFile);
 hwndFileDlg=WinFileDlg(HWND_DESKTOP, parent, &fdFileDlg);
 if (hwndFileDlg && (fdFileDlg.lReturn==DID_OK))
  {
   openedFile << fdFileDlg.szFullFile;
   saveFileThr.run();
  }
}


// end of source
