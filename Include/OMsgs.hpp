// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMsgs.hpp
// Message Boxes

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

// $Header: W:/Projects/OCL/Include/rcs/OMsgs.hpp 1.50 1996/08/11 23:47:22 B.STEIN Release $

#ifndef OMSGS_INCLUDED
  #define OMSGS_INCLUDED

#ifndef OAPP_INCLUDED
  #include <OApp.hpp>
#endif

typedef class OMsgs *pOMsgs;

class __CPP_EXPORT__ OMsgs
  : public OCLObject
{
 private:
   HWND            Parent;
   HWND            Owner;
 
 protected:
   HMODULE         handle;
   CHAR            Msg[2*CCHMAXPATH];
   CHAR            Title[60];

 public:

   OMsgs           (const HMODULE moduleHandle = NULLHANDLE,
                    const HWND parent          = HWND_DESKTOP,
                    const HWND owner           = HWND_DESKTOP);

   virtual
      ~OMsgs       ();

   virtual
      PSZ isOfType () const; 

   PSZ 
      message      (),
      title        ();

   void
      setResource  (const HMODULE moduleHandle = NULLHANDLE),
      info         (const ULONG msgID),
      info         (const ULONG titleID, const ULONG msgID),
      info         (PCSZ msg),
      info         (PCSZ title, PCSZ msg),
      error        (const ULONG msgID),
      error        (const ULONG titleID, const ULONG msgID),
      error        (PCSZ msg),
      error        (PCSZ title, PCSZ msg),
      beeper       ();

   BOOL
      ask          (const ULONG titleID, const ULONG msgID),
      ask          (PCSZ title, PCSZ msg),
      loadString   (const ULONG resID, const ULONG Size, PSZ str);

   inline operator
      HMODULE      () const { return(handle); }
};

#endif  // OMSGS_INCLUDED



// end of source
