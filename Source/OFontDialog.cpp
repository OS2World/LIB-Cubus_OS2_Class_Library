// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFontDialog.cpp

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
#include <OApp.hpp>
#include <OFontDialog.hpp>


OFontDialog::OFontDialog(HWND hParent, HWND hOwner)
  : OStdDialog(hParent, hOwner)
{
 if (!OApp::currentOApp)
   throw OPMException(OCL::error(OCL_OAPP_NO_OAPP), 0);
}

OFontDialog::~OFontDialog()
{
}

PSZ OFontDialog::isOfType() const
{
 return("OFontDialog");
}


PSZ OFontDialog::getFont(PSZ title, PSZ previewText)
{
 FONTDLG      fontDlg;
 FONTMETRICS  fontMetrics;
 OString      Buffer(100);
 OString      szFamily(FACESIZE);

 memset(&fontDlg, 0, sizeof(fontDlg));
 fontDlg.cbSize         = sizeof(FONTDLG);
 fontDlg.hpsScreen      = WinGetScreenPS(HWND_DESKTOP);
 fontDlg.pszTitle       = title;
 fontDlg.pszPreview     = previewText;
 fontDlg.pszFamilyname  = szFamily.getText();
 fontDlg.fl             = FNTS_BITMAPONLY | FNTS_CENTER;
 fontDlg.flFlags        = FNTF_NOVIEWPRINTERFONTS;
 fontDlg.clrFore        = CLR_BLACK;
 fontDlg.clrBack        = CLR_WHITE;
 fontDlg.usFamilyBufLen = FACESIZE;

 WinFontDlg(parent, owner, &fontDlg);
 WinReleasePS(fontDlg.hpsScreen);

 switch(fontDlg.lReturn)
  {
   case DID_CANCEL:
     WinReleasePS(fontDlg.hpsScreen);
     return(NULL); 

   case DID_OK:
     sprintf(Buffer.getText(), "%ld.%s",
             fontDlg.fxPointSize/65536,
             fontDlg.pszFamilyname);
     font << Buffer;
     return(font.getText());
  }
 
 return(NULL);  // we should never get here
}

// end of source
