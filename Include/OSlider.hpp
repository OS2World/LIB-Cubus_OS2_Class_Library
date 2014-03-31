// OCL - OS/2 Class Library
// (c) Cubus 1995
// (c) 1994 Matthias StÅbner
// (c) Benjamin Stein 1994
// All Rights Reserved
// OSlider.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OSlider.hpp 1.50 1996/08/11 23:47:29 B.STEIN Release $

#ifndef OSLIDER_INCLUDED
  #define OSLIDER_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


/* Possible styles for slider are:

- SLS_HORIZONTAL    - Slider is horicontical
- SLS_VERTICAL      - Slider is vertical
- SLS_CENTER        -
- SLS_BOTTOM        -
- SLS_TOP           -
- SLS_LEFT          -
- SLS_RIGHT         -

- SLS_PRIMARYSCALE1 - Slider with scale above
- SLS_PRIMARYSCALE2 - Slider with scale beneath
    (if both parameters are used the systems assumes a scale beneath

- SLS_HOMELEFT      - starting point left (horicontal slider only)
- SLS_HOMERIGHT     - starting point right (horicontal slider only)
- SLS_HOMEBOTTOM    - starting point at bottom (vertical slider only)
- SLS_HOMETOP       - starting point at top (vertical slider only)
- SLS_BUTTONSLEFT   - control buttons left (horicontal slider only)  
- SLS_BUTTONSRIGHT  - control buttons right (horicontal slider only)
- SLS_BUTTONSBOTTOM - control buttons at bottom (vertical slider only)
- SLS_BUTTONSTOP    - control buttons at top (vertical slider only)
- SLS_SNAPTOINCREMENT    - marker always jumps to next whole number
- SLS_READONLY      - removes slider and control buttons (e.g. progress indicator)
- SLS_RIBBONSTRIP   - fills slider between beginning and end of range with color
- SLS_OWNERDRAW     - if you have to do it by yourself ;-))

*/

typedef class OSlider *pOSlider;

class __CPP_EXPORT__ OSlider
  : public OWindow
{
 protected:
    ULONG                   Scale1;
    ULONG                   Space1;
    ULONG                   Scale2;
    ULONG                   Space2;
    SLDCDATA                ctlData;

 public:

// ctors
    OSlider                (const ULONG id,
                            const HWND  Parent,  // becomes parent and owner of the slider
                            const ULONG scale1,
                            const ULONG space1,
                            const ULONG scale2,
                            const ULONG space2,
                            const ULONG Style);

    OSlider                (const ULONG id,
                            const OFrame& Parent,
                            const ULONG scale1,
                            const ULONG space1,
                            const ULONG scale2,
                            const ULONG space2,
                            const ULONG Style);

    OSlider                (const ULONG id,
                            const pOFrame Parent,
                            const ULONG scale1,
                            const ULONG space1,
                            const ULONG scale2,
                            const ULONG space2,
                            const ULONG Style);

// dtor
    virtual
       ~OSlider            ();
 
    virtual
       PSZ isOfType        () const;


    OSlider
       &createSlider       (const SHORT x  = 0,
                           const SHORT y  = 0,
                           const SHORT cx = 0, 
                           const SHORT cy = 0),
       &setSliderArmPos    (SHORT pos),
       &setSliderArmSize   (ULONG x, ULONG y),
       &setSliderShaftPos  (SHORT x, SHORT y),
       &setSliderShaftDim  (SHORT dim),
       &incSliderArm       (SHORT delta = 1),
       &decSliderArm       (SHORT delta = 1),
       &setSliderScaleText (PCSZ Text, USHORT pos),
       &setTickSize        (ULONG size = 10, ULONG num = SMA_SETALLTICKS),
       &setSliderStyles    (const ULONG Style),
       &setSliderSize      (const ULONG x, 
                           const ULONG y, 
                           const ULONG cx, 
                           const ULONG cy),
       &getSliderShaftDim  (SHORT *lenght, SHORT *height),
       &getSliderShaftPos  (SHORT *x, SHORT *y),
       &getSliderArmSize   (SHORT *x, SHORT *y),
       &drawSliderElement  (POWNERITEM  item, COLOR color);

    OWindow&
       inherit             (const HWND Parent);

    ULONG
       addDetent           (SHORT pos),
       getDetentPos        (ULONG id),
       getSliderArmPos     (),
       getTickSize         (SHORT pos);

    PSZ
       getScaleText        (SHORT loc, PSZ buf,SHORT len);
};


#endif // OSLIDER_INCLUDED
