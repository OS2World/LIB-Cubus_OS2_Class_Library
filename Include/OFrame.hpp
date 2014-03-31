// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OFrame.hpp

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

// $Header: E:/Projects/OCL/Include/rcs/OFrame.hpp 1.12 1996/01/16 10:12:19 B.STEIN Release B.STEIN $

#ifndef OFRAME_INCLUDED
  #define OFRAME_INCLUDED

#ifndef OWINDOW_INCLUDED
  #include <OWindow.hpp>
#endif

#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif

typedef class OFrame *pOFrame;


class __CPP_EXPORT__ OFrame
  : public OWindow
{
 public:
   HWND                 frame;
   HWND                 client;

// ctor/dtor

   OFrame              (const ULONG id,
                        const ULONG Style = FCF_STANDARD,
                        const ULONG winbits = CS_SAVEBITS | CS_SIZEREDRAW);

   virtual
      ~OFrame          ();

   virtual
      PSZ isOfType     () const;

   OFrame&
      createFrame      (PSZ className);

   virtual OFrame
      &setSizePosFrame (const HWND behind,
                        SWP dimensions,
                        const ULONG flag),
      &trackFrame      (), 
      &showFrame       (),
      &hideFrame       (),
      &centerFrame     ();

   OFrame
      &postQuit        (),
      &destroyFrame    (),
      &setWindowText   (PCSZ text);


// CommandHandler
// this default handler handles font and color configuration by drag and drop

   virtual 
      BOOL OCommand   (ULONG msg, MPARAM mp1, MPARAM mp2);
};


#endif // OFRAME_INCLUDED

// end of source
