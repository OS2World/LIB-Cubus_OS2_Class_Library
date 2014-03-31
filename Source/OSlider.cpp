// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 Matthias StÅbner
// All Rights Reserved
// OSlider.cpp


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

// $Header: W:/Projects/OCL/Source/rcs/OSlider.cpp 1.50 1996/08/11 23:49:30 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OSlider.hpp>


OSlider::OSlider(const ULONG id,
                 const HWND  Parent,  // becomes parent and owner of the slider
                 const ULONG scale1,
                 const ULONG space1,
                 const ULONG scale2,
                 const ULONG space2,
                 const ULONG Style)
  : OWindow(id, 0, 0),
    Scale1(scale1),
    Space1(space1),
    Scale2(scale2),
    Space2(space2)
{
 parent = Parent;
 owner  = Parent;
 style  = Style;
}


OSlider::OSlider(const ULONG id,
                 const OFrame& Parent,
                 const ULONG scale1,
                 const ULONG space1,
                 const ULONG scale2,
                 const ULONG space2,
                 const ULONG Style)
  : OWindow(id, 0, 0),
    Scale1(scale1),
    Space1(space1),
    Scale2(scale2),
    Space2(space2)
{
 parent = Parent.hwnd;
 owner  = Parent.hwnd;
 style  = Style;
}


OSlider::OSlider(const ULONG id,
                 const pOFrame Parent,
                 const ULONG scale1,
                 const ULONG space1,
                 const ULONG scale2,
                 const ULONG space2,
                 const ULONG Style)
 : OWindow(id, 0, 0),
   Scale1(scale1),
   Space1(space1),
   Scale2(scale2),
   Space2(space2)
{
 parent = Parent->hwnd;
 owner  = Parent->hwnd;
 style  = Style;
}


// dtor
OSlider::~OSlider()
  {}


PSZ OSlider::isOfType() const
{ 
 return("OSlider"); 
}


OSlider& OSlider::createSlider(const SHORT x, const SHORT y, 
                           const SHORT cx, const SHORT cy)
{
 ctlData.cbSize = sizeof(SLDCDATA);
 ctlData.usScale1Increments = Scale1;
 ctlData.usScale1Spacing = Space1;
 ctlData.usScale2Increments = Scale2;
 ctlData.usScale2Spacing = Space2;

 if ((hwnd = WinCreateWindow(parent, WC_SLIDER, NULL,
                             style | WS_VISIBLE,
                             x, y, cx, cy,
                             owner, HWND_TOP, 0,
                             (PVOID)&ctlData, NULL)) == NULLHANDLE)
   throw OPMException(OCL::error(170), 0);

 return (*this);
}


OWindow& OSlider::inherit(const HWND Parent)
{
 OWindow::inherit(Parent);
 return(createSlider());
}


OSlider& OSlider::setSliderStyles(const ULONG Style)
{
 style = Style;
 return(*this); 
}


OSlider& OSlider::setSliderSize(const ULONG x, const ULONG y, 
                            const ULONG cx, const ULONG cy)
{
 sizepos.x = x;
 sizepos.y = y;
 sizepos.cx = cx;
 sizepos.cy = cy;
 WinSetWindowPos(hwnd, HWND_TOP, x, y, cx, cy, SWP_SIZE);
 return(*this);
}


OSlider& OSlider::setSliderArmSize(ULONG x, ULONG y)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
                       MPFROMSHORT (SMA_SLIDERARMDIMENSIONS),
                       MPFROM2SHORT (x,y)))
   throw OPMException(OCL::error(171), 0);
   
 return(*this);
}

OSlider& OSlider::setSliderArmPos(SHORT pos)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
                       MPFROM2SHORT(SMA_SLIDERARMPOSITION,SMA_INCREMENTVALUE),
                       MPFROMSHORT(pos)))
   throw OPMException(OCL::error(172), 0);

 return(*this);
}

OSlider& OSlider::setSliderShaftPos(SHORT x, SHORT y)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
                       MPFROMSHORT (SMA_SHAFTPOSITION),
                       MPFROM2SHORT (x, y)))
   throw OPMException(OCL::error(173), 0);

 return(*this);
}


OSlider& OSlider::setSliderShaftDim(SHORT dim)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
                       MPFROMSHORT (SMA_SHAFTDIMENSIONS),
                       MPFROMSHORT (dim)))
   throw OPMException(OCL::error(174), 0);

 return(*this);
}

OSlider& OSlider::setSliderScaleText(PCSZ Text, USHORT pos)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSCALETEXT,
                       MPFROMSHORT (pos),MPFROMP(Text)))
   throw OPMException(OCL::error(175), 0);

 return(*this);
}

OSlider& OSlider::setTickSize(ULONG size, ULONG num)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETTICKSIZE,
                       MPFROM2SHORT (num,size), NULL))
   throw OPMException(OCL::error(176), 0);

 return(*this);
}

ULONG OSlider::addDetent(SHORT pos)
{
 return((ULONG) WinSendMsg(hwnd, SLM_ADDDETENT, MPFROMSHORT (pos), 0));
}

ULONG OSlider::getDetentPos(ULONG id)
{
 return(LONGFROMMP(WinSendMsg(hwnd, SLM_QUERYDETENTPOS, MPFROMLONG(id), 0)));
}


PSZ OSlider::getScaleText(SHORT loc, PSZ buf,SHORT len)
{
 WinSendMsg(hwnd, SLM_QUERYSCALETEXT,
            MPFROM2SHORT(loc,len),MPFROMP(buf));
 return((PSZ)buf);
}

OSlider& OSlider::getSliderShaftDim(SHORT *lenght, SHORT *height)
{
 ULONG  tmp;

 tmp = LONGFROMMP(WinSendMsg(hwnd,SLM_QUERYSLIDERINFO,
                             MPFROM2SHORT(SMA_SHAFTDIMENSIONS,SMA_INCREMENTVALUE),0));
 *lenght = SHORT1FROMMP(tmp);
 *height = SHORT2FROMMP(tmp);

 return(*this);
}

OSlider& OSlider::getSliderShaftPos(SHORT *x, SHORT *y)
{
 ULONG   tmp;

 tmp = LONGFROMMP(WinSendMsg(hwnd,SLM_QUERYSLIDERINFO,
                             MPFROM2SHORT(SMA_SHAFTPOSITION,SMA_INCREMENTVALUE),0));
 *x = SHORT1FROMMP(tmp);
 *y = SHORT2FROMMP(tmp);

 return(*this);
}

OSlider& OSlider::getSliderArmSize(SHORT *x, SHORT *y)
{
 ULONG   tmp;

 tmp = LONGFROMMP(WinSendMsg(hwnd,SLM_QUERYSLIDERINFO,
                             MPFROM2SHORT(SMA_SLIDERARMDIMENSIONS,SMA_INCREMENTVALUE),0));
 *x = SHORT1FROMMP(tmp);
 *y = SHORT2FROMMP(tmp);

 return(*this);
}

ULONG OSlider::getSliderArmPos()
{
 return((ULONG)WinSendMsg(hwnd,SLM_QUERYSLIDERINFO,
                          MPFROM2SHORT(SMA_SLIDERARMPOSITION,SMA_INCREMENTVALUE),0));
}

ULONG OSlider::getTickSize(SHORT pos)
{
 return((ULONG)WinSendMsg(hwnd,SLM_QUERYTICKSIZE, MPFROMSHORT(pos), 0));
}


OSlider& OSlider::incSliderArm(SHORT delta)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
            MPFROM2SHORT(SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
            MPFROMSHORT((ULONG)WinSendMsg(hwnd, SLM_QUERYSLIDERINFO,
            MPFROM2SHORT(SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),NULL) + delta)))
   throw OPMException(OCL::error(177), 0);

 return(*this);
}


OSlider& OSlider::decSliderArm(SHORT delta)
{
 if (!(BOOL)WinSendMsg(hwnd, SLM_SETSLIDERINFO,
            MPFROM2SHORT (SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),
            MPFROMSHORT((ULONG)WinSendMsg(hwnd, SLM_QUERYSLIDERINFO,
            MPFROM2SHORT(SMA_SLIDERARMPOSITION, SMA_INCREMENTVALUE),NULL) - delta)))
   throw OPMException(OCL::error(178), 0);

 return(*this);
}



OSlider& OSlider::drawSliderElement(POWNERITEM  item, COLOR color)
{
 WinQueryWindowRect(item->hwnd, &item->rclItem);
 GpiSetColor(item->hps, color);
 GpiBox(item->hps, DRO_FILL, (PPOINTL) &item->rclItem.xRight, 0L, 0L);
 return(*this);
}

// end of source
