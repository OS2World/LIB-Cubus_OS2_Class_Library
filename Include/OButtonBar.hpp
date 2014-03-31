// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OButtonBar.hpp


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OButtonBar.hpp 1.1 1996/08/12 00:01:11 B.STEIN Release $

#ifndef OBUTTONBAR_INCLUDED
  #define OBUTTONBAR_INCLUDED


#ifndef OGRBTN_INCLUDED
  #include <OGraphicsButton.hpp>
#endif

#ifndef OFBTN_INCLUDED
  #include <OFillButton.hpp>
#endif
 
#ifndef OHPOPUP_INCLUDED
  #include <OHelpPopup.hpp>
#endif

/* 
  The OButtonBar sends a WM_CONTROL-Message to the parent window
  if the mouse pointer is moved over one of the buttons
  this message looks like
   
  WinSendMsg(parent, WM_CONTROL,
             MPFROM2SHORT(OBUTTONBAR_MOVEOVER, buttonID), MPARAM(helptext));

  Process this message if you want to display the helptext somewhere.
  When buttonID is set to 0 the mouse pointer has left the toolbar client area.
*/

/*
  The OButtonBar sends a WM_CONTROL-Message to the parent window
  if a mouse button is depressed on one of the buttons
  this message looks like

  WinSendMsg(parent, WM_CONTROL,
             MPFROM2SHORT(OBUTTONBAR_BUTTONxDOWN, buttonID), NULL);

  x means the depressed button. Process this message if you want to poupup a menu for example.
*/


#define OBUTTONBAR_BUTTON1DOWN  WM_BUTTON1DOWN
#define OBUTTONBAR_BUTTON2DOWN  WM_BUTTON2DOWN
#define OBUTTONBAR_BUTTON3DOWN  WM_BUTTON3DOWN


typedef class OButtonBar *pOButtonBar;


typedef OList<OGraphicsButton> buttonList;
typedef buttonList *pbuttonList;


class __CPP_EXPORT__ OButtonBar
  : public OFrame
{
 protected:
    BOOL                  bubbleHelper;
    OFillButton           fillBTN;

    class _enable : public OIterator<OGraphicsButton>
    {
     public: void applyToElement (OGraphicsButton* elem);
    };

    class _disable : public OIterator<OGraphicsButton>
    {
     public: void applyToElement (OGraphicsButton* elem);
    };

    class _destroy : public OIterator<OGraphicsButton>
    {
     public: void applyToElement (OGraphicsButton* elem);
    };

    OButtonBar&
      initButtonBarDefaults ();

 private:
    ULONG                    orientation,
                             bHeight,
                             bWidth,
                             picSize,
                             drawStyle,
                             currentButton;

    _enable                  btn_enable;
    _disable                 btn_disable;
    _destroy                 btn_destroy;
    
 public:
    OHelpPopup               bubbleHelpWin;
    buttonList               buttons; // linked list of buttoninfo


    enum
      {
       up2down = 1,       // default
       left2right, 
       fillButton         // paint button imitation into the free space
      };


    OButtonBar               (const ULONG id,
                              const HWND  parentWindow, 
                              const BOOL  bubbleHelp   = TRUE);

    OButtonBar               (const ULONG   id,
                              const OFrame& parentWindow, 
                              const BOOL    bubbleHelp = TRUE);

    OButtonBar               (const ULONG   id,
                              const pOFrame parentWindow, 
                              const BOOL    bubbleHelp = TRUE);

    virtual
       ~OButtonBar           ();

    virtual
       PSZ isOfType          () const;

    OButtonBar
       &createButtonBar      (),

       &setButtonDimensions  (const ULONG height = 32,
                              const ULONG width  = 32),
       &setOrientation       (const ULONG type),
       &setPicSize           (const ULONG length),
       &setDrawStyle         (const ULONG Style), 

       &setupButtons         (),
       &destroyButtons       (),
       &enableButtons        (),
       &disableButtons       ();

    PSZ
       requestHelpText       (const ULONG id, 
                              const BOOL isHandle),
       requestHelpText       ();

    inline ULONG
       getHeight             () const { return(bHeight); }

    inline ULONG
       getWidth              () const { return(bWidth);  }

    virtual
       BOOL OCommand         (ULONG msg, MPARAM mp1, MPARAM mp2);
};


#endif // OBUTTONBAR_INCLUDED

// end of source
