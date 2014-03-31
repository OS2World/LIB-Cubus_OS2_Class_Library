// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OIndicator.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OIndicator.cpp 1.50 1996/08/11 23:49:21 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIndicator.hpp>


OIndicator::OIndicator(const ULONG id,
                       const HWND  Parent,
                       const ULONG Style)
  : OSlider(id, Parent, 101, 0, 101, 0, Style)
  {}


OIndicator::OIndicator(const ULONG id,
                       const OFrame& Parent,
                       const ULONG Style)
  : OSlider(id, Parent, 101, 0, 101, 0, Style) 
  {}


OIndicator::OIndicator(const ULONG id,
                       const pOFrame Parent,
                       const ULONG Style)
  : OSlider(id, Parent, 101, 0, 101, 0, Style) 
  {}


OIndicator::~OIndicator()
  {}


PSZ OIndicator::isOfType() const
{ 
 return("OIndicator"); 
}



OIndicator& OIndicator::createIndicator(const SHORT x, const SHORT y,
                                        const SHORT cx, const SHORT cy)
{
 createSlider(x, y, cx, cy);

 setFont("8.Helv");

 setTickSize        (2).
 setTickSize        (5,   0).
 setTickSize        (5,  25).
 setTickSize        (5,  50).
 setTickSize        (5,  75).
 setTickSize        (5, 100).
 setSliderScaleText ("0",     0).
 setSliderScaleText ("25",   25).
 setSliderScaleText ("50",   50).
 setSliderScaleText ("75",   75).
 setSliderScaleText ("100", 100);
 
 return(*this);
}


OWindow& OIndicator::inherit(const HWND Parent)
{
 OWindow::inherit(Parent);
 return(createIndicator(0, 0, 0, 0));
}

// end of source
