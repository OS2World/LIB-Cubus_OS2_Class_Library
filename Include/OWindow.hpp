// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OWindow.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OWindow.hpp 1.50 1996/08/11 23:47:35 B.STEIN Release $


#ifndef OWINDOW_INCLUDED
   #define OWINDOW_INCLUDED


#ifndef OAPP_INCLUDED
  #include <OApp.hpp>
#endif


#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif


// messages

#define WM_WINDOWENTER  1054
#define WM_WINDOWLEAVE  1055

typedef struct _PresParms
{
 COLOR   Fore;
 COLOR   Back;
 CHAR    Font[80];
} PresParms, *pPresParms;


typedef class OWindow *pOWindow;

class __CPP_EXPORT__ OWindow
  : public OCommandHandler
{
 public:
   HWND                 parent;
   HWND                 owner;
   BOOL                 termFlag;
   ULONG                res;
   ULONG                style;
   ULONG                bits;
   OString              winText;
   HPS                  hps;
   RECTL                rcl;
   SWP                  sizepos;
   PresParms            pparms; 

   OWindow             (const ULONG id, 
                        const ULONG winstyle, 
                        const ULONG winbits);

   virtual
      ~OWindow         ();

   virtual
      PSZ isOfType     () const;

   OWindow
      &inherit         (const HWND hwndDlg),        // call this in WM_INITDLG when a dialog
      &initReplace     (const ULONG id, SWP& swp),  // the OWindow should replace window id
      &show            (),
      &hide            (),
      &enable          (),
      &disable         (),
      &activate        (),
      &destroy         (),
      &setFocus        (),
      &setParent       (const HWND handle),
      &setOwner        (const HWND handle),
      &cancelClose     (),
      &setForeColor    (COLOR color),
      &setBackColor    (COLOR color),
      &setFont         (PSZ fontnamesize),
      &setPresentation (pPresParms presentation),
      &getPresentation (pPresParms presentation);

   COLOR
      getForeColor     (),
      getBackColor     ();

   PSZ
      getFont          ();
};


#endif // OWINDOW_INCLUDED

// end of source
