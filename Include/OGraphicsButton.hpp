// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OGraphicsButton.hpp


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


// $Header: W:/Projects/OCL/Include/rcs/OGraphicsButton.hpp 1.50 1996/08/11 23:47:14 B.STEIN Release $

#ifndef OGRBTN_INCLUDED
  #define OGRBTN_INCLUDED


#ifndef OUBTN_INCLUDED
  #include <OUserButton.hpp>
#endif

#ifndef OBITMAP_INCLUDED
  #include <OBitmap.hpp>
#endif

#ifndef OICON_INCLUDED
  #include <OIcon.hpp>
#endif


// messages

#define OBUTTONBAR_MOVEOVER      WM_MOUSEMOVE
#define OGRBTN_SETHILITE         BM_SETHILITE
#define OGRBTN_WINDOWENTER       WM_WINDOWENTER
#define OGRBTN_WINDOWLEAVE       WM_WINDOWLEAVE
#define OGRBTN_PRESPARAMCHANGED  WM_PRESPARAMCHANGED


// classes

// Objects of this class are used by OButtonBar.
// The member OGraphicsButton::helpText should
// be set for toolbar-buttons. This way fly-over-help
// is enabled automatically.

typedef class OGraphicsButton *pOGraphicsButton;

class __CPP_EXPORT__ OGraphicsButton
  : public OUserButton 
{
 private:
    PFNWP            PM_ButtonProc;
    BOOL             isEnabled;

 protected:
    enum  
      {
       useBitmap = 1,
       useIcon 
      };    

    BOOL             pushState;
    ULONG            imageType;
    
 public:

    pOIcon           pIco;
    pOBitmap         pBmp;
    OString          helpText;


    OGraphicsButton (ULONG    id,          // id for this control
                     HWND     Parent,      // parent window
                     pOIcon   ico,         // image to draw
                     PSZ      help = NULL, // help text for bubble help
                     ULONG    x  = 0,      // x-dimension within parent
                     ULONG    y  = 0,      // y-dimension within parent
                     ULONG    cx = 40,     // width within parent
                     ULONG    cy = 20);    // height within parent

    OGraphicsButton (ULONG    id,
                     HWND     Parent,
                     pOBitmap bmp,
                     PSZ      help = NULL,
                     ULONG    x  = 0,
                     ULONG    y  = 0,
                     ULONG    cx = 40,
                     ULONG    cy = 20);

    OGraphicsButton (ULONG    id,
                     OFrame&  Parent,
                     pOIcon   ico,    
                     PSZ      help = NULL,
                     ULONG    x  = 0,
                     ULONG    y  = 0,
                     ULONG    cx = 40,
                     ULONG    cy = 20);

    OGraphicsButton (ULONG    id,
                     OFrame&  Parent,
                     pOBitmap bmp,
                     PSZ      help = NULL,
                     ULONG    x  = 0,
                     ULONG    y  = 0,
                     ULONG    cx = 40,
                     ULONG    cy = 20);

    OGraphicsButton (ULONG    id,
                     pOFrame  Parent,
                     pOIcon   ico,    
                     PSZ      help = NULL,
                     ULONG    x  = 0,
                     ULONG    y  = 0,
                     ULONG    cx = 40,
                     ULONG    cy = 20);

    OGraphicsButton (ULONG    id,
                     pOFrame  Parent,
                     pOBitmap bmp,
                     PSZ      help = NULL,
                     ULONG    x  = 0,
                     ULONG    y  = 0,
                     ULONG    cx = 40,
                     ULONG    cy = 20);

    virtual
      ~OGraphicsButton    ();

    virtual
      PSZ isOfType        () const;


    MRESULT UBDefaultCall (ULONG  msg,  
                           MPARAM mp1,
                           MPARAM mp2);

    OButton&
       createButton       ();

    OGraphicsButton&
       drawButton         (HPS hPS);

    virtual BOOL 
       OCommand           (ULONG msg, MPARAM mp1, MPARAM mp2);
};

extern "C"
{
 MRESULT EXPENTRY OGraphicsButtonProc(HWND hwnd,
                                      ULONG msg,
                                      MPARAM mp1,
                                      MPARAM mp2);
}

#endif // OGRBTN_INCLUDED


// end of source
