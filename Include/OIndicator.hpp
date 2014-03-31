// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OIndicator.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OIndicator.hpp 1.50 1996/08/11 23:47:18 B.STEIN Release $

#ifndef OINDICATOR_INCLUDED
  #define OINDICATOR_INCLUDED


#ifndef OSLIDER_INCLUDED
  #include <OSlider.hpp>
#endif

#define OINDICATOR_STYLE SLS_HORIZONTAL | SLS_BOTTOM | SLS_HOMELEFT | SLS_OWNERDRAW | \
                         SLS_SNAPTOINCREMENT | SLS_RIBBONSTRIP | SLS_READONLY


typedef class OIndicator *pOIndicator;

class __CPP_EXPORT__ OIndicator
  : public OSlider
{
 public:

// ctors
    OIndicator         (const ULONG id,
                        const HWND  Parent, 
                        const ULONG Style = OINDICATOR_STYLE);

    OIndicator         (const ULONG id,
                        const OFrame& Parent, 
                        const ULONG Style = OINDICATOR_STYLE);

    OIndicator         (const ULONG id,
                        const pOFrame Parent, 
                        const ULONG Style = OINDICATOR_STYLE);

// dtor
    virtual
       ~OIndicator     ();

    virtual
       PSZ isOfType    () const; 

    OIndicator&
       createIndicator (const SHORT x  = 0,
                        const SHORT y  = 0,
                        const SHORT cx = 0,
                        const SHORT cy = 0);

    OWindow&
       inherit         (const HWND Parent);
};


#endif // OSLIDER_INCLUDED
