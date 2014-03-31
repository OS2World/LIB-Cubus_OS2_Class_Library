// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 B. Stein


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OCircSlider.hpp 1.1 1996/08/12 00:01:12 B.STEIN Release $

#ifndef OCIRCSLIDER_INCLUDED
  #define OCIRCSLIDER_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


extern "C"
{
 BOOL EXPENTRY WinRegisterCircularSlider(VOID);
}                                 // requires SW.DLL from MMPM/2 :-(


#ifndef INCL_WINCIRCULARSLIDER    // this will be defined in the new Toolkit in pmstddlg.h
                                  // do not define the stuff more than once

 #define WC_CIRCULARSLIDER   ((PSZ)0xffff0041L)

 typedef struct _CSBITMAPDATA
  {
   HBITMAP hbmLeftUp;
   HBITMAP hbmLeftDown;
   HBITMAP hbmRightUp;
   HBITMAP hbmRightDown;
  } CSBITMAPDATA;
  typedef CSBITMAPDATA *PCSBITMAPDATA;

  // Messages

 #define CSM_QUERYRANGE      0x053D       // mp1: PSHORT pLow  mp2: PSHORT pHigh  
 #define CSM_SETRANGE        0x053E       // mp1: SHORT  Low   mp2: SHORT  High   
 #define CSM_QUERYVALUE      0x053F       // mp1: PSHORT pValue  mp2: NULL  
 #define CSM_SETVALUE        0x0540       // mp1: SHORT  Value   mp2: NULL  
 #define CSM_QUERYRADIUS     0x0541       // mp1: PUSHORT uRadius  
 #define CSM_SETINCREMENT    0x0542       // mp1: USHORT  ButtonIncr  mp2: USHORT TickIncr  
 #define CSM_QUERYINCREMENT  0x0543       // mp1: PUSHORT pButtonIncr mp2: PUSHORT pTickIncr  
 #define CSM_SETBITMAPDATA   0x0544       // mp1: PDIALBITMAPDATA  

 #define CSN_SETFOCUS        0x0548       // mp2: BOOL fSetFocus  
 #define CSN_CHANGED         0x0549       // mp2: SHORT Value  
 #define CSN_TRACKING        0x054A       // mp2: SHORT Value  
 #define CSN_QUERYBACKGROUNDCOLOR 0x054B  // mp2: NULL   return: CLR_  

 #define WS_NOBUTTON        0x1           // Style bits  
 #define WS_NOTEXT          0x2
 #define WS_NONUMBER        0x4
 #define WS_POINTSELECT     0x8
 #define WS_360            0x10
 #define WS_MIDPOINT       0x20

 #define CSS_NOBUTTON       WS_NOBUTTON   // Style bits  
 #define CSS_NOTEXT         WS_NOTEXT
 #define CSS_NONUMBER       WS_NONUMBER
 #define CSS_POINTSELECT    WS_POINTSELECT
 #define CSS_360            WS_360
 #define CSS_MIDPOINT       WS_MIDPOINT

 #define CSS_PROPORTIONALTICKS  0x40

#endif // !INCL_WINCIRCULARSLIDER


// Class definition


typedef class OCircSlider *pOCircSlider;


class __CPP_EXPORT__ OCircSlider
  : public OWindow
{
 protected:
    CSBITMAPDATA          ctlData;
    ULONG                 Scale;
    ULONG                 Space;

 public:

// ctors
    OCircSlider           (const ULONG ID,
                           const HWND  Parent,
                           const ULONG scale, 
                           const ULONG space,
                           const ULONG Style);

    OCircSlider           (const ULONG id,
                           const OFrame& Parent,
                           const ULONG scale, 
                           const ULONG space,
                           const ULONG Style);

    OCircSlider           (const ULONG id,
                           const pOFrame Parent,
                           const ULONG scale, 
                           const ULONG space,
                           const ULONG Style);

    virtual
       ~OCircSlider       ();

    virtual
       PSZ isOfType       () const; 

    OCircSlider&
       createCircSlider   (const SHORT x  = 0,
                           const SHORT y  = 0,
                           const SHORT cx = 0,
                           const SHORT cy = 0);

};


#endif // OCIRCSLIDER_INCLUDED
