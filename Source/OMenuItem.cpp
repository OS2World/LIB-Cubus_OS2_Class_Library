// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved

// OMenuItem.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OMenuItem.cpp 1.50 1996/08/11 23:49:23 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMenuItem.hpp>
#include <OMessage.hpp>

 
OMenuItem::OMenuItem(
                     const SHORT   _iPosition,    //  Position
                     const USHORT  _afStyle,      //  Style
                     const USHORT  _afAttribute,  //  Attribute
                     const USHORT  _id,           //  Identity
                     const HWND    _hwndSubMenu,  //  Submenu
                     const ULONG   _hItem         //  Item
                    ) 
{
 iPosition   = _iPosition;
 afStyle     = _afStyle;
 afAttribute = _afAttribute;
 id          = _id;
 hwndSubMenu = _hwndSubMenu;
 hItem       = _hItem;
}

OMenuItem::OMenuItem(const PMENUITEM itemData)
{
 if (!itemData)
   throw OPMException(OCL::apierror(99, ERROR_BAD_ARGUMENTS), 0);

 iPosition   = itemData->iPosition;
 afStyle     = itemData->afStyle;
 afAttribute = itemData->afAttribute;
 id          = itemData->id;
 hwndSubMenu = itemData->hwndSubMenu;
 hItem       = itemData->hItem; 
}


OMenuItem::OMenuItem(const MENUITEM& itemData)
{
 iPosition   = itemData.iPosition;
 afStyle     = itemData.afStyle;
 afAttribute = itemData.afAttribute;
 id          = itemData.id;
 hwndSubMenu = itemData.hwndSubMenu;
 hItem       = itemData.hItem; 
}


OMenuItem::~OMenuItem()
  {}


PSZ OMenuItem::isOfType() const
{ 
 return("OMenuItem"); 
}


// end of source
