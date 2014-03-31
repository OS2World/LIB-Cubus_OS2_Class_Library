// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OHelpPopup.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OHelpPopup.hpp 1.50 1996/08/11 23:47:14 B.STEIN Release $

#ifndef OHPOPUP_INCLUDED
  #define OHPOPUP_INCLUDED

#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif

#ifndef STATUSLINE_INCLUDED
  #include <OStatusLine.hpp>
#endif



// These timers should not affect your application.
// The library has to be recompiled if these macros
// are changed.


#define OHELP_POPUP_SHOWTIMER   TID_USERMAX - 40
#define OHELP_POPUP_CLOSETIMER  TID_USERMAX - 41


typedef class OHelpPopup *pOHelpPopup;

class __CPP_EXPORT__ OHelpPopup
  : public OStatusLine
{
 protected:
    ULONG                 showTime;
    OString               textToShow;

 public:

    OHelpPopup            ();

    virtual
       ~OHelpPopup        ();

    virtual
       PSZ isOfType       () const;

    OStatusLine&
       createStatusLine   ();

    ULONG showTimeout     () const;   

    OHelpPopup
       &setPopupTimeout   (ULONG timeout),
       &startPopupTimer   (),
       &stopPopupTimer    (),
       &timePopup         (PCSZ helpText),
       &showPopup         (PCSZ helpText),
       &hidePopup         ();

    virtual
       BOOL OCommand      (ULONG msg, MPARAM mp1, MPARAM mp2); 
};

#endif // OHPOPUP_INCLUDED


// end of source
