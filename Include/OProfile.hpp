// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPROFILE.HPP

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

// $Header: W:/Projects/OCL/Include/rcs/OProfile.hpp 1.50 1996/08/11 23:47:27 B.STEIN Release $

#ifndef OPROFILE_INCLUDED
  #define OPROFILE_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <ostring.hpp>
#endif

// object creator

typedef class OProfile *pOProfile;

class __CPP_EXPORT__ OProfile
  : public OCLObject
{
 public:
      HINI             hini;
      lOString         list;
      OString          val;

      OProfile         ();
      OProfile         (PSZ iniName);
      OProfile         (const HINI iniHandle);

      virtual
         ~OProfile     ();

      virtual
         PSZ isOfType  () const;

      BOOL
         open          (PSZ   iniName),
         setupList     (UCHAR *DatTemp),
         write         (PSZ   App, PSZ Key, PVOID Value, ULONG len),
         deleteApp     (PSZ   App),
         deleteKey     (PSZ   App, PSZ Key),
         getApps       (),
         getKeys       (PSZ   App),
         getStr        (PSZ   App, PSZ Key),
         getData       (PSZ   App, PSZ Key, PVOID Buffer, PULONG Size),
         insert        (const HWND hwnd, const ULONG id);

      void close();
};


#endif

// end of source
