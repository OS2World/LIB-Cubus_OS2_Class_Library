// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OButtonBar.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OButtonBar.cpp 1.50 1996/08/11 23:49:09 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OButtonBar.hpp>

#if defined(__EMX__)
  template class OList<OGraphicsButton>;
  template class OIterator<OGraphicsButton>;
#endif 


OButtonBar::OButtonBar(const ULONG id,
                       const HWND parentWindow,
                       const BOOL bubbleHelp)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW | CS_HITTEST),
    orientation(OButtonBar::left2right),
    drawStyle(OButtonBar::fillButton),
    currentButton(0),
    bubbleHelper(bubbleHelp)
{
 setParent(parentWindow);
 setOwner(parentWindow);
 initButtonBarDefaults();
}


OButtonBar::OButtonBar(const ULONG id,
                       const OFrame& parentWindow, 
                       const BOOL bubbleHelp)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW),
    orientation(OButtonBar::left2right),
    drawStyle(OButtonBar::fillButton),
    currentButton(0),
    bubbleHelper(bubbleHelp)
{
 setParent(parentWindow.hwnd);
 setOwner(parentWindow.hwnd);
 initButtonBarDefaults();
}

OButtonBar::OButtonBar(const ULONG id,
                       const pOFrame parentWindow, 
                       const BOOL bubbleHelp)
  : OFrame(id, FCF_NOBYTEALIGN, CS_SIZEREDRAW),
    orientation(OButtonBar::left2right),
    drawStyle(OButtonBar::fillButton),
    currentButton(0),
    bubbleHelper(bubbleHelp)
{
 setParent(parentWindow->hwnd);
 setOwner(parentWindow->hwnd);
 initButtonBarDefaults();
}



OButtonBar::~OButtonBar()
{
 buttons.init();
}


PSZ OButtonBar::isOfType() const
{ 
 return("OButtonBar"); 
}


OButtonBar& OButtonBar::initButtonBarDefaults()
{
 bHeight = 40;
 bWidth = 40;
 picSize = 32;
 pparms.Fore = SYSCLR_WINDOWTEXT;
 pparms.Back = SYSCLR_WINDOW;
 strcpy(pparms.Font, "8.Helv");
 return(*this);
}


OButtonBar& OButtonBar::createButtonBar()
{
 createFrame("OButtonBar");
 setupButtons();
 return(*this);
}


OButtonBar& OButtonBar::destroyButtons()
{
 buttons.allElementsDo(btn_destroy);
 return(*this);
}


OButtonBar& OButtonBar::enableButtons()
{
 buttons.allElementsDo(btn_enable);
 return(*this);
}

OButtonBar& OButtonBar::disableButtons()
{
 buttons.allElementsDo(btn_disable);
 return(*this);
}

PSZ OButtonBar::requestHelpText(const ULONG id, const BOOL isHandle)
{
 if (!buttons.isEmpty())
  {
   pOGraphicsButton pgrb = buttons.getFirst();

   while(pgrb)
   {
    if (((isHandle) && (pgrb->hwnd == id)) ||
       ((!isHandle) && (pgrb->res == id)))
        return(pgrb->helpText);
    pgrb = buttons.getNext();
   }
  }
 return(NULL);
}


PSZ OButtonBar::requestHelpText()
{
 return(requestHelpText(NULLHANDLE, TRUE));
}


OButtonBar& OButtonBar::setupButtons()
{
 ULONG i = 0,
       posx = 0,
       posy = 0;

 pOGraphicsButton pgrb = buttons.getFirst();

 hideFrame();

 while(pgrb) 
  {
   switch(orientation) {
     case up2down:
       posx = 0;
       posy = (buttons.numberOfElements() - i - 1)*bHeight;
       break;
     case left2right:
       posx = i*bWidth;
       posy = 0;
       break; }
   
   try
    {
     pgrb->parent     = hwnd;
     pgrb->owner      = hwnd;
     pgrb->sizepos.x  = posx;
     pgrb->sizepos.y  = posy;
     pgrb->sizepos.cx = bWidth;
     pgrb->sizepos.cy = bHeight;
     pgrb->createButton();
    }
   catch(OPMException ex) {}
   i++;
   pgrb = buttons.getNext();
  }
 showFrame();
 return(*this);
}



OButtonBar& OButtonBar::setButtonDimensions(const ULONG height, const ULONG width)
{
 bHeight = height;
 bWidth  = width; 
 return(*this);
}


OButtonBar& OButtonBar::setPicSize(const ULONG length)
{
 picSize = length;
 return(*this);
}


OButtonBar& OButtonBar::setOrientation(const ULONG type) 
{
 orientation = type; 
 return(*this);
}


OButtonBar& OButtonBar::setDrawStyle(const ULONG Style) 
{
 drawStyle = Style; 
 return(*this);
}


BOOL OButtonBar::OCommand(ULONG msg, MPARAM mp1, MPARAM mp2)
{
 switch(msg)
   {
    case WM_PAINT:
    case WM_ERASEBACKGROUND:
     WinQueryWindowRect(hwnd, &rcl);
     if (orientation == up2down)
      {
       ULONG             newHeight = rcl.yTop - rcl.yBottom;
       ULONG             i = 1;
       pOGraphicsButton  btn = buttons.getFirst();

       while(btn)
        {
         WinSetWindowPos(btn->hwnd, HWND_TOP, 0, 
                         newHeight - i*bHeight,
                         bWidth, bHeight, SWP_MOVE | SWP_SHOW | SWP_SIZE);
         i++;
         btn = buttons.getNext();
        }
       } 
     if (drawStyle == OButtonBar::fillButton)
      {
       hps = WinBeginPaint(hwnd, 0, NULL);
       GpiCreateLogColorTable(hps, LCOL_RESET, LCOLF_RGB, 0L, 0L, NULL);
       WinFillRect(hps, &rcl, SYSCLR_BUTTONMIDDLE);
       if (orientation == left2right)
         fillBTN.drawButton(hps,
                            bWidth * buttons.numberOfElements(),
                            0,
                            rcl.xRight - rcl.xLeft - bWidth * buttons.numberOfElements(),  
                            bHeight);
       else
         fillBTN.drawButton(hps,
                            0,
                            0,
                            bWidth,
                            rcl.yTop - rcl.yBottom - bHeight * buttons.numberOfElements());  
       WinEndPaint(hps);
      } 
     break;

// the following two messages can be removed when using Warp with Fixpack 16 or up

    case WM_MOUSEMOVE:
      if (currentButton != 0)
       {
        currentButton = 0;
        WinSendMsg(parent, WM_CONTROL,
                 MPFROM2SHORT(OBUTTONBAR_MOVEOVER, 0),
                 MPFROMP((PSZ)""));       
       }
      return(FALSE);

    case WM_CONTROLPOINTER:
      if (SHORT1FROMMP(mp1) != currentButton)
       {
        pOGraphicsButton button = buttons.getFirst();

        currentButton = SHORT1FROMMP(mp1);
        while((button) && (button->res != currentButton))
          button = buttons.getNext();
        if (button)    
            WinSendMsg(parent, WM_CONTROL,
                 MPFROM2SHORT(OBUTTONBAR_MOVEOVER, currentButton),
                 MPFROMP(button->helpText.getText()));       
       }  
      return(FALSE);

// end of remove
 
    case WM_CONTROL:
     switch(SHORT1FROMMP(mp1))
      {
       case OGRBTN_WINDOWENTER:
         currentButton = SHORT2FROMMP(mp1);
         if (bubbleHelper)
           bubbleHelpWin.timePopup((PSZ)PVOIDFROMMP(mp2));
         WinSendMsg(parent, WM_CONTROL,
                    MPFROM2SHORT(OBUTTONBAR_MOVEOVER, SHORT2FROMMP(mp1)),
                    MPFROMP((PSZ)PVOIDFROMMP(mp2)));       
         break;

       case OGRBTN_WINDOWLEAVE:
         currentButton = 0;
         if (bubbleHelper)
           bubbleHelpWin.hidePopup();
         WinSendMsg(parent, WM_CONTROL,
                    MPFROM2SHORT(OBUTTONBAR_MOVEOVER, SHORT2FROMMP(mp1)),
                    MPFROMP((PSZ)PVOIDFROMMP(mp2)));       
         break;

       case OGRBTN_SETHILITE:
         if (bubbleHelper)
            bubbleHelpWin.hidePopup();
         break;        

       case OGRBTN_PRESPARAMCHANGED: {
         pOGraphicsButton button = (pOGraphicsButton)PVOIDFROMMP(mp2);
         if (button) {
           button->getFont();
           bubbleHelpWin.setFont(button->pparms.Font); }
         break; }
      }
     break;

    case WM_BUTTON1DOWN:
    case WM_BUTTON2DOWN:
    case WM_BUTTON3DOWN:
     {
      pOGraphicsButton button = buttons.getFirst();

      while((button) && (button->res != currentButton))
        button = buttons.getNext();
      if (bubbleHelper)
        bubbleHelpWin.hidePopup();
      if (button)
        WinSendMsg(parent, WM_CONTROL, MPFROM2SHORT(msg, button->res), mp1);
     } 
     break;        
    
    case WM_COMMAND:
     WinSendMsg(parent, msg, mp1, mp2);
     break;

    case WM_CLOSE:
    case WM_DESTROY:
     destroyButtons();
     break;

    default:
     return(OFrame::OCommand(msg, mp1, mp2));
   }
 return(TRUE);
}


void OButtonBar::_enable::applyToElement (OGraphicsButton* elem)
{
 elem->enable();
}

void OButtonBar::_disable::applyToElement (OGraphicsButton* elem)
{
 elem->disable();
}

void OButtonBar::_destroy::applyToElement (OGraphicsButton* elem)
{
 elem->destroy();
}

// end of source  
