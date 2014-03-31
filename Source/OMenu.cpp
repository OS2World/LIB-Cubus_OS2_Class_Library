// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMenu.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMenu.cpp 1.50 1996/08/11 23:49:23 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMenu.hpp>
#include <OMessage.hpp>

#if defined(__EMX__)
  template class OList<OMenuItem>;
#endif


// constructors

OMenu::OMenu(const ULONG id,
             const HWND Parent,
             const HWND Owner,
             const pODynamicLib resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!resLibrary) || 
     (!resLibrary->getLibHandle()) || 
     (!Parent) || 
     (!Owner))
   throw OPMException(OCL::apierror(80, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent;
 owner  = Owner;
 OMenu_resLibrary = resLibrary->getLibHandle(); 

 createOMenuObject();
}



OMenu::OMenu(const ULONG id,
             const HWND Parent,
             const HWND Owner,
             const HMODULE resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!Parent) || 
     (!Owner))
   throw OPMException(OCL::apierror(81, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent;
 owner  = Owner;

 OMenu_resLibrary = resLibrary; 

 createOMenuObject();
}


OMenu::OMenu(const ULONG id,
             const OWindow& Parent,
             const OWindow& Owner,
             const pODynamicLib resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!resLibrary) || 
     (!resLibrary->getLibHandle()) || 
     (!Parent.hwnd) || 
     (!Owner.hwnd))
   throw OPMException(OCL::apierror(82, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent.hwnd;
 owner  = Owner.hwnd;

 OMenu_resLibrary = resLibrary->getLibHandle(); 

 createOMenuObject();
}


OMenu::OMenu(const ULONG id,
             const OWindow& Parent,
             const OWindow& Owner,
             const HMODULE resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!Parent.hwnd) || 
     (!Owner.hwnd))
   throw OPMException(OCL::apierror(83, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent.hwnd;
 owner  = Owner.hwnd;

 OMenu_resLibrary = resLibrary; 

 createOMenuObject();
}


OMenu::OMenu(const ULONG id,
             const pOWindow Parent,
             const pOWindow Owner,
             const pODynamicLib resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!resLibrary) || 
     (!resLibrary->getLibHandle()) || 
     (!Parent) ||
     (!Parent->hwnd) ||
     (!Owner) || 
     (!Owner->hwnd))
   throw OPMException(OCL::apierror(84, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent->hwnd;
 owner  = Owner->hwnd;

 OMenu_resLibrary = resLibrary->getLibHandle(); 

 createOMenuObject();
}


OMenu::OMenu(const ULONG id,
             const pOWindow Parent,
             const pOWindow Owner,
             const HMODULE resLibrary)
  : OWindow(id, 0, 0)
{
 if ((!Parent) ||
     (!Parent->hwnd) ||
     (!Owner) || 
     (!Owner->hwnd))
   throw OPMException(OCL::apierror(85, ERROR_BAD_ARGUMENTS), 0);

 parent = Parent->hwnd;
 owner  = Owner->hwnd;

 OMenu_resLibrary = resLibrary; 

 createOMenuObject();
}


// destructor

OMenu::~OMenu()
  {}


PSZ OMenu::isOfType() const
{ 
 return("OMenu"); 
}


// members

OMenu& OMenu::createOMenuObject()
{
 hwnd = WinLoadMenu(parent, OMenu_resLibrary, res);

 if (!hwnd)
   throw OPMException(OCL::error(86), 0);

 setOwner(owner);
 return(*this);
}
   

BOOL OMenu::isEnabled(const ULONG item)
{
 return(((BOOL)WinSendMsg(hwnd, 
                          MM_QUERYITEMATTR, 
                          MPFROM2SHORT(item, TRUE), 
                          MPFROMSHORT(MIA_DISABLED)))!=TRUE);
}

BOOL OMenu::isChecked(const ULONG item)
{
 return((BOOL)WinSendMsg(hwnd, 
                         MM_QUERYITEMATTR, 
                         MPFROM2SHORT(item, TRUE), 
                         MPFROMSHORT(MIA_CHECKED)));
}


OMenu& OMenu::insertItem(const ULONG insertAfter, const pOMenuItem item)
{
 return(*this);
}

OMenu& OMenu::insertItemList(const ULONG insertAfter, const plOMenuItem items)
{
 return(*this);
}

OMenu& OMenu::removeItem(const ULONG item)
{
 return(*this);
}

OMenu& OMenu::removeItemList(OList<ULONG>& items)
{
 return(*this);
}

OMenu& OMenu::removeItemList(const ULONG items[], const ULONG elements)
{
 return(*this);
}


OMenu& OMenu::enableItem(const ULONG item, BOOL state)
{
 if (!(BOOL)WinSendMsg(hwnd, MM_SETITEMATTR, 
                       MPFROM2SHORT(item, TRUE), 
                       MPFROM2SHORT(MIA_DISABLED, state ? ~MIA_DISABLED : MIA_DISABLED)))
   throw OPMException(OCL::error(87), 0);
 return(*this);
}

OMenu& OMenu::enableItemList(OList<ULONG>& items, BOOL state)
{
 PULONG temp = items.getFirst();

 while(temp) {
   enableItem(*temp, state);
   temp = items.getNext(); }
 return(*this);
}

OMenu& OMenu::enableItemList(const ULONG items[], const ULONG elements, BOOL state)
{
 for(ULONG step = 0; step < elements; step++)
   enableItem(items[step], state);

 return(*this);
}


OMenu& OMenu::checkItem(const ULONG item, BOOL state)
{
 if (!(BOOL)WinSendMsg(hwnd, MM_SETITEMATTR, 
                       MPFROM2SHORT(item, TRUE), 
                       MPFROM2SHORT(MIA_CHECKED, state ? MIA_CHECKED : ~MIA_CHECKED)))
   throw OPMException(OCL::error(88), 0);
 return(*this);
}

OMenu& OMenu::checkItemList(OList<ULONG>& items, BOOL state)
{
 PULONG temp = items.getFirst();

 while(temp) {
   checkItem(*temp, state);
   temp = items.getNext(); }

 return(*this);
}


OMenu& OMenu::checkItemList(const ULONG items[], const ULONG elements, BOOL state)
{
 for(ULONG step = 0; step < elements; step++)
   checkItem(items[step], state);

 return(*this);
}


OMenu& OMenu::setItemText(const ULONG item, PCSZ text)
{
 if(!WinSendMsg(hwnd, MM_SETITEMTEXT, MPFROMSHORT(item), MPFROMP(text)))
   throw OPMException(OCL::error(89), 0);

 return(*this);
}



OMenu& OMenu::setItemText(const ULONG item, pOString text)
{
 if (!text)
   throw OPMException(OCL::apierror(89, ERROR_BAD_ARGUMENTS), 0);
 setItemText(item, text->getText());

 return(*this);
}


OMenu& OMenu::setItemText(const ULONG item, const ULONG resID)
{
 OString temp(CCHMAXPATH*2);

 if (!WinLoadString(OApp::current().anchor(),
                    OMenu_resLibrary, resID,
                    CCHMAXPATH*2, temp))
   throw OPMException(OCL::error(90), 0);

 return(setItemText(item, temp)); 
}



// end of source
