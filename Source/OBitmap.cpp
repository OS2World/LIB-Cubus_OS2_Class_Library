// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OBitmap.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OBitmap.cpp 1.50 1996/08/11 23:49:07 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OBitmap.hpp>
#include <OPMException.hpp>
#include <OMessage.hpp>

OBitmap::OBitmap()
  : OPicture(0, 0),
    hbm(NULLHANDLE)
  {}



OBitmap::OBitmap(const HWND    bitmapOwner,
                 const ULONG   resID, 
                 const HMODULE module, 
                 const ULONG   CX, 
                 const ULONG   CY)
  : OPicture(CX, CY),
    hbm(NULLHANDLE)
{
 if ((hbm = GpiLoadBitmap(WinGetPS(bitmapOwner), 
                          module, resID, CX, CY)) == NULLHANDLE)
   throw OPMException(OCL::error(30), 0, OException::recoverable);
}



OBitmap::OBitmap(const HBITMAP hbmHandle)
  : OPicture(0, 0),
    hbm(hbmHandle)
{
 if(hbm == NULLHANDLE)
   throw OPMException(OCL::error(31), 0, OException::recoverable);
}



OBitmap::OBitmap(const HWND bitmapOwner, PCSZ fileName)
  : OPicture(0, 0),
    hbm(NULLHANDLE)
{
 APIRET              rc = 0;
 PBYTE               Buffer;
 FILESTATUS3         stat;
 fstream             bmpFile;
 PBITMAPFILEHEADER   pbmfh;

 if((!fileName) ||
   ((rc = DosQueryPathInfo(fileName, 1, &stat, sizeof(FILESTATUS3))) != 0) ||
   ((rc = DosAllocMem((PPVOID)&Buffer,  stat.cbFile,
                      PAG_READ | PAG_WRITE | PAG_COMMIT)) != 0))
   throw OPMException(OMessage(rc).getText(), rc, OException::recoverable);
 
#if defined(__EMX__) 
 bmpFile.open(fileName, ios::in);
#else
 bmpFile.open(fileName, ios::in | ios::binary);
#endif

 if((bmpFile.fail()) || (!bmpFile.read(Buffer, stat.cbFile))) {
   DosFreeMem(Buffer);
   throw OPMException(OMessage(ERROR_FILE_NOT_FOUND).getText(),
                      ERROR_FILE_NOT_FOUND, OException::recoverable); }

 bmpFile.close();

 pbmfh = (PBITMAPFILEHEADER)Buffer;
 if ((pbmfh) && (pbmfh->usType !=  BFT_BMAP)) {
   DosFreeMem(Buffer);  
   throw OPMException(OMessage(ERROR_BAD_FORMAT).getText(),
                      ERROR_BAD_FORMAT, OException::recoverable); }
 
 hbm = GpiCreateBitmap(WinGetPS(bitmapOwner), (PBITMAPINFOHEADER2) &pbmfh->bmp,
                      (ULONG) CBM_INIT,
                      (PBYTE) pbmfh + pbmfh->offBits,
                      (PBITMAPINFO2) &pbmfh->bmp);

 width  = pbmfh->bmp.cx;
 height = pbmfh->bmp.cy;

 DosFreeMem(Buffer);

 if (!hbm)
   throw OPMException(OCL::error(32), 0, OException::recoverable);
}


OBitmap::~OBitmap()
{
 if (hbm)
   GpiDeleteBitmap(hbm);
}


PSZ OBitmap::isOfType() const
{ 
 return("OBitmap"); 
}



// end of source
