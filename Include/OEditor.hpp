// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OEditor.hpp

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

// $Header: E:/Projects/OCL/Include/rcs/OEditor.hpp 1.12 1996/01/16 10:12:18 B.STEIN Release B.STEIN $

#ifndef OEDITOR_INCLUDED
  #define OEDITOR_INCLUDED


#ifndef OMLE_INCLUDED
  #include <omle.hpp>
#endif


#ifndef OTHREAD_INLCUDED
  #include <OThread.hpp>
#endif



typedef class OEditor *pOEditor;

typedef OThread<OEditor> EditorThread;

class __CPP_EXPORT__ OEditor
  : public OMLE
{
 public:
   EditorThread     loadFileThr;
   EditorThread     saveFileThr;
   EditorThread     saveFileAsThr;
   BOOL             clearFlag;

   OEditor         (const ULONG id, 
                    const HWND  Parent,
                    const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   OEditor         (const ULONG id,
                    const pOFrame Parent,
                    const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   OEditor         (const ULONG id,
                    const OFrame& Parent,
                    const ULONG Style = OMLE::hscroll | OMLE::vscroll | OMLE::border);

   virtual
      ~OEditor     ();

   virtual
      PSZ isOfType () const;

// threads
   void
     loadFile      (), 
     saveFile      (),
     saveFileAs    ();
};


#endif // OEDITOR_INCLUDED

// end of source
