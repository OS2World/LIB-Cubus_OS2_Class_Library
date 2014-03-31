// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OValueSet.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OValueSet.hpp 1.50 1996/08/11 23:47:34 B.STEIN Release $

#ifndef OVALUE_INCLUDED
  #define OVALUE_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

// possible styles for value sets
// VS_ITEMBORDER
// VS_BORDER
// VS_TEXT
// VS_ICON
// VS_BITMAP
// VS_RGB
// VS_COLORINDEX
// VS_RIGHTTOLEFT
// VS_SCALEBITMAPS
// VS_OWNERDRAW


typedef struct vsItem *pvsItem;

struct vsItem
{
 USHORT   row;
 USHORT   col;
 USHORT   colorIndex;
 OString  text;
 HPOINTER icon;
 HBITMAP  bitmap;
 RGB      rgb;
};


typedef class OValueSet *pOValueSet;


class __CPP_EXPORT__ OValueSet
  : public OWindow
{
 private:
   VSCDATA             ctlData;
   ULONG               rows;
   ULONG               columns;
   ULONG               margin;

 public:
   vsItem              selected;

// ctors
   OValueSet          (const ULONG id,
                       const HWND  Parent,     // becomes parent and owner of the set
                       const ULONG Rows    = 2,
                       const ULONG Columns = 2,
                       const ULONG Margin  = 0,
                       const ULONG Style   = VS_ITEMBORDER | VS_BORDER | VS_ICON);

   OValueSet          (const ULONG id,
                       const OFrame& Parent,   // becomes parent and owner of the set
                       const ULONG Rows    = 2,
                       const ULONG Columns = 2,
                       const ULONG Margin  = 0,
                       const ULONG Style   = VS_ITEMBORDER | VS_BORDER | VS_ICON);

   OValueSet          (const ULONG id,
                       const pOFrame Parent,   // becomes parent and owner of the set
                       const ULONG Rows    = 2,
                       const ULONG Columns = 2,
                       const ULONG Margin  = 0,
                       const ULONG Style   = VS_ITEMBORDER | VS_BORDER | VS_ICON);

// dtor
    virtual
       ~OValueSet     ();

    virtual
       PSZ isOfType   () const;

    OValueSet&
       createValueSet (const SHORT x,
                       const SHORT y,
                       const SHORT cx,
                       const SHORT cy);

    BOOL
       querySelected  (),
       queryItem      (ULONG row = 1,
                       ULONG col = 1),
       selectItem     (ULONG row = 1,
                       ULONG col = 1),
       setItem        (ULONG row,
                       ULONG col,
                       ULONG itemInfo),
       setItemAttr    (ULONG row = 1,
                       ULONG col = 1,
                       ULONG attribute = VS_ICON, BOOL set = TRUE),
       setMetrics     (ULONG fMetric,
                       ULONG itemInfo);

    ULONG // return value is also placed in OValueSet::selected
       queryItemAttr  (ULONG row = 1,
                       ULONG col = 1),
       queryMetrics   (ULONG fMetric = VMA_ITEMSIZE);

};


#endif // OVALUE_INCLUDED


// end of source
