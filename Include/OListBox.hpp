// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OListBox.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OListBox.hpp 1.50 1996/08/11 23:47:19 B.STEIN Release $

#ifndef OLISTBOX_INCLUDED
  #define OLISTBOX_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif


// Note - the following styles are available

// LS_MULTIPLESEL             0x00000001L
// LS_OWNERDRAW               0x00000002L
// LS_NOADJUSTPOS             0x00000004L
// LS_HORZSCROLL              0x00000008L
// LS_EXTENDEDSEL             0x00000010L


typedef class OListBox *pOListBox;


class __CPP_EXPORT__ OListBox
  : public OWindow
{
 protected:
    BOOL                   autoScroll;

    void auto_scroll       ();

 public:

    OListBox               (const ULONG id,
                            const HWND Parent,
                            const ULONG Style = LS_NOADJUSTPOS | LS_EXTENDEDSEL,
                            BOOL autoScrolling = FALSE);

    OListBox               (const ULONG id,
                            const OFrame& Parent,
                            const ULONG Style = LS_NOADJUSTPOS | LS_EXTENDEDSEL,
                            BOOL autoScrolling = FALSE);

    OListBox               (const ULONG id,
                            const pOFrame Parent,
                            const ULONG Style = LS_NOADJUSTPOS | LS_EXTENDEDSEL,
                            BOOL autoScrolling = FALSE);

    virtual
       ~OListBox           ();

    virtual
       PSZ isOfType        () const; 

    OListBox
       &createListBox       (const ULONG x,  const ULONG y,
                            const ULONG cx, const ULONG cy),

       &setAutoScroll       (BOOL autoScrolling = TRUE);

    BOOL
       deleteAll           (),
       selectItem          (const ULONG itemIndex, const BOOL state = TRUE),
       setItemHandle       (const ULONG itemIndex, const ULONG handle),
       setItemHeight       (const ULONG newHeight),
       setItemText         (const ULONG itemIndex, PCSZ text),
       setToTop            (const ULONG itemIndex);

    ULONG
       deleteItem          (const ULONG itemIndex),
       insertItem          (PCSZ  text, const ULONG itemIndex = LIT_END),
       queryItemCount      (),
       queryItemHandle     (const ULONG itemIndex),
       queryItemText       (OString& Buffer, const ULONG itemIndex),
       queryItemTextLength (const ULONG itemIndex),
       querySelection      (const ULONG itemStart = LIT_FIRST),
       queryTopItem        (),
       searchString        (PCSZ  text,
                            const ULONG itemStart = LIT_FIRST, 
                            const ULONG command = LSS_CASESENSITIVE);
};


#endif // OLISTBOX_INCLUDED

// end of source
