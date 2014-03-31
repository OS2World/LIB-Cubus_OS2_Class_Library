// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMLE.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OMLE.hpp 1.50 1996/08/11 23:47:20 B.STEIN Release $

#ifndef OMLE_INCLUDED
  #define OMLE_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <oframe.hpp>
#endif

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OTHREAD_INCLUDED
  #include <OThread.hpp>
#endif


typedef class OMLE *pOMLE;


class __CPP_EXPORT__ OMLE
  : public OWindow
{
 protected:
   PVOID              imex;
   ULONG              imexLen;
   IPT                imexOffset;

 public:
   OThread<OMLE>      insertLargeThr;
   OString            openedFile;

// enums

   enum              {
                      text   = MLFIE_CFTEXT,
                      binary = MLFIE_NOTRANS,
                      winmle = MLFIE_WINFMT
                     };

   enum              {
                      border  = MLS_BORDER,
                      rdonly  = MLS_READONLY,
                      wrap    = MLS_WORDWRAP,
                      hscroll = MLS_HSCROLL,
                      vscroll = MLS_VSCROLL,
                      notab   = MLS_IGNORETAB,
                      noundo  = MLS_DISABLEUNDO
                     };

   OMLE              (const ULONG id,
                      const HWND Parent,
                      const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   OMLE              (const ULONG id,
                      const OFrame& Parent,
                      const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   OMLE              (const ULONG id,
                      const pOFrame Parent,
                      const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   virtual
      ~OMLE          ();

   virtual
      PSZ isOfType   () const;

   virtual ULONG
      getText        (PVOID out, ULONG len),
      getText        (OString& Buffer),
      setText        (PVOID in, ULONG len),
      setText        (PSZ text);

   virtual BOOL
      insertText     (PSZ text);

   BOOL
      createMLE      (const ULONG x  = 0,
                      const ULONG y  = 0,
                      const ULONG cx = 0,
                      const ULONG cy = 0),
      copy           (),
      cut            (),
      paste          (),
      copy2Clip      (),
      cut2Clip       (),
      pasteFromClip  (),
      clear          (),
      undo           (),
      changed        (),
      deleteText     (ULONG beginPoint, ULONG count),
      deleteAll      (),
      insertFile     (PCSZ fileName);

// services

   ULONG
      length         (),
      lines          (),
      setFormat      (const ULONG format);

   void
      disableRefresh (),
      enableRefresh  (),
      insertLarge    ();
};


#endif // OMLE_INCLUDED

// end of source
