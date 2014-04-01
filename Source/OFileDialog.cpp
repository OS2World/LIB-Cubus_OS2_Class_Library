// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFileDialog.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/ODialog.cpp 1.50 1996/08/11 23:49:13 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OFileDialog.hpp>


OFileDialog::OFileDialog(HWND hParent, HWND hOwner)
  : OStdDialog(hParent, hOwner)
{
 memset(&fileDialog, 0, sizeof(FILEDLG));
 fileDialog.cbSize = sizeof(FILEDLG);
}

OFileDialog::~OFileDialog()
  {}

PSZ OFileDialog::isOfType() const
{
 return("OFileDialog");
}


PSZ OFileDialog::open(PSZ title,
                      PSZ initialPath,
                      PSZ fileMask,
                      OFileDialog::styles style)
{
 if (lastPath)
   strcpy(fileDialog.szFullFile, lastPath);

 if (initialPath)
   strcpy(fileDialog.szFullFile, initialPath);

 if (fileMask) {
   strcat(fileDialog.szFullFile, "\\");
   strcat(fileDialog.szFullFile, fileMask); }

 fileDialog.fl          = FDS_OPEN_DIALOG | style;
 fileDialog.pszTitle    = title;
 fileDialog.pszOKButton = "~OK";

 if (!WinFileDlg(parent, owner, (PFILEDLG)&fileDialog))
   throw OPMException(OCL::error(OCL_OFILEDLG_SHOW), 0);

 if (fileDialog.lReturn == DID_OK)
  {
   lastFile << fileDialog.szFullFile;
   lastPath << fileDialog.szFullFile;
   lastPath.rightCut('\\');
   return(lastFile);
  }
 else
  return(NULL);
}


PSZ OFileDialog::saveAs(PSZ title,
                        PSZ initialPath,
                        PSZ initialFileName,
                        OFileDialog::styles style)
{
 if (lastPath)
   strcpy(fileDialog.szFullFile, lastPath);

 if (initialPath)
   strcpy(fileDialog.szFullFile, initialPath);

 strcat(fileDialog.szFullFile, "\\");
 if (initialFileName)
   strcat(fileDialog.szFullFile, initialFileName);

 fileDialog.fl          = FDS_SAVEAS_DIALOG | style;
 fileDialog.pszTitle    = title;

 if (!WinFileDlg(parent, owner, (PFILEDLG)&fileDialog))
   throw OPMException(OCL::error(OCL_OFILEDLG_SHOW), 0);

 if (fileDialog.lReturn == DID_OK)
  {
   lastFile << fileDialog.szFullFile;
   lastPath << fileDialog.szFullFile;
   lastPath.rightCut('\\');
   return(lastFile);
  }
 else
  return(NULL);
}


// end of source
