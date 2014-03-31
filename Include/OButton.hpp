// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OButton.hpp


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OButton.hpp 1.1 1996/08/12 00:01:10 B.STEIN Release $

#ifndef OBTN_INCLUDED
  #define OBTN_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


// classes


typedef class OButton *pOButton;

class __CPP_EXPORT__ OButton
  : public OWindow 
    
{
 public:
    OButton             (ULONG   id,
                         HWND    Parent,
                         ULONG   Style,
                         ULONG   x  = 0,
                         ULONG   y  = 0,
                         ULONG   cx = 0,
                         ULONG   cy = 0);

    OButton             (ULONG   id,
                         OFrame& Parent,
                         ULONG   Style,
                         ULONG   x  = 0,
                         ULONG   y  = 0,
                         ULONG   cx = 0,
                         ULONG   cy = 0);

    OButton             (ULONG   id,
                         pOFrame Parent,
                         ULONG   Style,
                         ULONG   x  = 0,
                         ULONG   y  = 0,
                         ULONG   cx = 0,
                         ULONG   cy = 0);

    virtual
      ~OButton          ();
 
    virtual
      PSZ isOfType      () const;

    virtual OButton&
      createButton      ();

    ULONG
      queryState        ();
  
    BOOL
      isChecked         (),
      isHilited         ();

    OButton
      &check            (),
      &uncheck          (),
      &setState         (ULONG state),
      &setDefault       (BOOL  displayDefault),
      &setHilite        (BOOL  hiliteState),
      &click            (BOOL  down);  
};


#endif // OBTN_INCLUDED


// end of source
