// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OProfile.cpp

// Profile Actions (INI-Handling)


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

// $Header: W:/Projects/OCL/Source/rcs/OProfile.cpp 1.50 1996/08/11 23:49:29 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OApp.hpp>
#include <OProfile.hpp>


// members of OProfile


OProfile::OProfile() 
  : hini(NULLHANDLE)
  {}


OProfile::OProfile(const HINI iniHandle)
  : hini(iniHandle)
  {}


OProfile::OProfile(PSZ iniName)
{
 hini = PrfOpenProfile(OApp::current().anchor(), iniName);
}


BOOL OProfile::open(PSZ iniName)
{
 hini = PrfOpenProfile(OApp::current().anchor(), (PSZ) iniName);
 return(hini != NULLHANDLE);
}


OProfile::~OProfile()
{
 list.reset();
 PrfCloseProfile(hini);
}


PSZ OProfile::isOfType() const
{ 
 return("OProfile"); 
}


void OProfile::close()
{
 PrfCloseProfile(hini);
}


BOOL OProfile::write(PSZ App, PSZ Key, PVOID Value, ULONG len)
{
 return(PrfWriteProfileData(hini, (PSZ) App, (PSZ) Key, Value, len));
}


BOOL OProfile::deleteApp(PSZ App)
{
 return(PrfWriteProfileData(hini, App, NULL, NULL, 0));
}


BOOL OProfile::deleteKey(PSZ App, PSZ Key)
{
 return(PrfWriteProfileData(hini, App, Key, NULL, 0));
}

BOOL OProfile::getApps()
{
 return(getKeys(NULL));
}


BOOL OProfile::getKeys(PSZ App)
{
 UCHAR  *DatTemp;
 ULONG  Size = 0x0000ffffL;

 if (DosAllocMem((PPVOID) &DatTemp,  0x0000ffffL, PAG_READ | PAG_WRITE | PAG_COMMIT))
   return(FALSE);

 if (getData(App, NULL, DatTemp, &Size))
  return(setupList(DatTemp));
 else
  return(FALSE);
}


BOOL OProfile::getStr(PSZ App, PSZ Key)
{
 UCHAR  *DatTemp;
 ULONG  Size = 0x0000ffffL;

 if (DosAllocMem((PPVOID) &DatTemp,  0x0000ffffL, PAG_READ | PAG_WRITE | PAG_COMMIT))
   return(FALSE);

 if (!getData(App, Key, DatTemp, &Size))
   return(FALSE);
 else
   val << (PSZ) DatTemp;

 DosFreeMem(DatTemp);
 return(TRUE);
}


BOOL OProfile::getData(PSZ App, PSZ Key, PVOID Buffer, PULONG Size)
{
 return(PrfQueryProfileData(hini, App, Key, Buffer, Size));
}


BOOL OProfile::setupList(UCHAR *DatTemp)
{
 ULONG x, len;
 UCHAR *Buffer;

 if (DosAllocMem((PPVOID) &Buffer,  0x0000ffffL, PAG_READ | PAG_WRITE | PAG_COMMIT))
   return(FALSE);

 list.reset();

 x = 0;
 do
   {
    len = 0;
    while (DatTemp[x+len] != '\0')
      {
       Buffer[len] = DatTemp[x+len];
       ++len;
      }
    Buffer[len] = '\0';
    if (len != 0)
      {
       list << (PSZ) Buffer;
       x += (len+1);
      }
   }
   while (DatTemp[x] != '\0');

 DosFreeMem(Buffer);
 DosFreeMem(DatTemp);
 return(TRUE);
}


BOOL OProfile::insert(const HWND hwnd, const ULONG id)
{
 OListItem<OString> *tmp = list.first();

 while((tmp) && (tmp->item) && (tmp->item->getText()))
  {
   if (LIT_MEMERROR == (LONG)WinSendDlgItemMsg(hwnd, id, LM_INSERTITEM,
                            MPFROM2SHORT(LIT_SORTASCENDING, 0),
                            MPFROMP(tmp->item->getText())))
     return(FALSE);
   tmp = tmp->next;
  }

 tmp = list.first();
 if ((tmp) && (tmp->item) && (tmp->item->getText()))
    WinSetDlgItemText(hwnd, id, tmp->item->getText());
 return(TRUE);
}


// end of source
