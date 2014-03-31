// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 B. Stein & M. StÅbner (!!!)
// OMenu.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OMenu.hpp 1.50 1996/08/11 23:47:21 B.STEIN Release $

//  valid messages
//  MM_DELETEMENU
//  MM_ENDMENUMODE
//  MM_INSERTITEM
//  MM_ISITEMVALID
//  MM_ITEMIDFROMPOSITION
//  MM_QUERYDEFAULTITEMID
//  MM_QUERYITEM
//  MM_QUERYITEMATTR
//  MM_QUERYITEMCOUNT
//  MM_QUERYITEMRECT
//  MM_QUERYITEMTEXT
//  MM_QUERYITEMTEXTLENGTH
//  MM_QUERYSELITEMID
//  MM_REMOVEITEM
//  MM_SELECTITEM
//  MM_SETDEFAULTITEMID
//  MM_SETITEM
//  MM_SETITEMATTR
//  MM_SETITEMHANDLE
//  MM_SETITEMTEXT
//  MM_STARTMENUMODE


#ifndef OMENU_INCLUDED
  #define OMENU_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif

#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif


#ifndef ODYNAMICLIB_INCLUDED
  #include <ODynamicLib.hpp>
#endif


#ifndef OMENUITEM_INCLUDED
  #include <OMenuItem.hpp>
#endif


typedef class OMenu *pOMenu;

typedef OList<OMenuItem> lOMenuItem;
typedef lOMenuItem *plOMenuItem;

typedef OList<ULONG> lUlong;
typedef lUlong *plUlong;

class __CPP_EXPORT__ OMenu
  : public OWindow
{
 private:
   HMODULE             OMenu_resLibrary;

 protected:
   OMenu&
      createOMenuObject ();   
 
 public:

   OMenu              (const ULONG id,
                       const HWND Parent,
                       const HWND Owner,
                       const pODynamicLib resLibrary);

   OMenu              (const ULONG id,
                       const HWND Parent,
                       const HWND Owner,
                       const HMODULE resLibrary);

   OMenu              (const ULONG id,
                       const OWindow& Parent,
                       const OWindow& Owner,
                       const pODynamicLib resLibrary);

   OMenu              (const ULONG id,
                       const OWindow& Parent,
                       const OWindow& Owner,
                       const HMODULE resLibrary);

   OMenu              (const ULONG id,
                       const pOWindow Parent,
                       const pOWindow Owner,
                       const pODynamicLib resLibrary);

   OMenu              (const ULONG id,
                       const pOWindow Parent,
                       const pOWindow Owner,
                       const HMODULE resLibrary);

   virtual
      ~OMenu          ();

   virtual
      PSZ isOfType    () const; 

   BOOL
      isEnabled       (const ULONG item),
      isChecked       (const ULONG item);

   OMenu
      &insertItem      (const ULONG insertAfter,
                        const pOMenuItem item),
      &insertItemList  (const ULONG insertAfter,
                        const plOMenuItem items),

      &removeItem      (const ULONG item),
      &removeItemList  (OList<ULONG>& items),
      &removeItemList  (const ULONG items[],
                        const ULONG elements),

      &enableItem      (const ULONG item,
                        BOOL state = TRUE),
      &enableItemList  (OList<ULONG>& items,
                        BOOL state = TRUE),
      &enableItemList  (const ULONG items[],
                        const ULONG elements,
                        BOOL state = TRUE),

      &checkItem       (const ULONG item,
                        BOOL state = TRUE),
      &checkItemList   (OList<ULONG>& items,
                        BOOL state = TRUE),
      &checkItemList   (const ULONG items[],
                        const ULONG elements,
                        BOOL state = TRUE), 

      &setItemText     (const ULONG item,
                        PCSZ text),
      &setItemText     (const ULONG item,
                        pOString text),
      &setItemText     (const ULONG item,
                        const ULONG resID);
};


#endif // OMENU_INCLUDED

// end of source
