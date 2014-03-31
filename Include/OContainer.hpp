// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OContainer.hpp

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

// $Header: E:/Projects/OCL/Include/rcs/OContainer.hpp 1.14 1996/01/16 10:12:17 B.STEIN Release B.STEIN $

#ifndef OCONTAINER_INCLUDED
  #define OCONTAINER_INCLUDED


#ifndef OCONTAINERBASE_INCLUDED
  #include <OContainerBase.hpp>
#endif


// CID_LEFTCOLTITLEWND     column title (left)
// CID_RIGHTCOLTITLEWND    right column title
// CID_BLANKBOX            blank box at bottom right
// CID_HSCROLL             horizontal scroll bar
// CID_RIGHTHSCROLL        right horz scroll bar
// CID_CNRTITLEWND         Container title window
// CID_LEFTDVWND           Left Details View window
// CID_RIGHTDVWND          Right Details View window
// CID_VSCROLL             vertical scroll bar
// CID_MLE                 MLE window for direct edit
// CA_CONTAINERTITLE 
// CA_TITLESEPARATOR 
// CA_TITLELEFT 
// CA_TITLERIGHT 
// CA_TITLECENTER 
// CA_OWNERDRAW 
// CA_DETAILSVIEWTITLES 
// CA_ORDEREDTARGETEMPH 
// CA_MIXEDTARGETEMPH 
// CA_DRAWBITMAP 
// CA_DRAWICON 
// CA_TITLEREADONLY 
// CA_OWNERPAINTBACKGROUND 
// CA_TREELINE 
// CCS_EXTENDSEL 
// CCS_MULTIPLESEL 
// CCS_SINGLESEL 
// CCS_AUTOPOSITION 
// CCS_VERIFYPOINTERS 
// CCS_READONLY 
// CCS_MINIRECORDCORE 
// CV_TREE 
// CV_TEXT 
// CV_NAME 
// CV_ICON 
// CV_DETAIL 
// CV_FLOW 
// CV_MINI



// Template class T is your container record class
// OContainer<MyRecord> means that your container holds
// MyRecord objects instead of RECORDCORE structs

// Template class R is either RECORDCORE or MINIRECORDCORE
// depending on your cnrStyle

template <class T, class R>
class OContainer
  : public OContainerBase
{
 public:

   OContainer        (const ULONG id,             // id of the container (must be unique!)
                      const HWND Parent,          // becomes parent AND owner of the container
                      const ULONG cnrStyle,       // container style
                      const ULONG initViewStyle); // default view style

   OContainer        (const ULONG id,             // id of the container (must be unique!)
                      const OFrame& Parent,       // becomes parent AND owner of the container
                      const ULONG cnrStyle,       // container style
                      const ULONG initViewStyle); // default view style

   OContainer        (const ULONG id,             // id of the container (must be unique!)
                      const pOFrame Parent,       // becomes parent AND owner of the container
                      const ULONG cnrStyle,       // container style
                      const ULONG initViewStyle); // default view style

   virtual
      ~OContainer    ();

   virtual
      PSZ isOfType   () const;

   virtual BOOL
      setupDetails   () = 0,         // sets up details view colums
      setupItems     () = 0;         // inserts all records

   T
      *allocRecords  (ULONG records) const,
      *queryRecord   (T* root,
                      ULONG flag  = CMA_FIRST,
                      ULONG order = CMA_ITEMORDER) const,
      *queryEmphasis (T* record   = (T*)CMA_FIRST,
                      ULONG flag  = CRA_SELECTED) const,
      *querySelected (T* record   = (T*)CMA_FIRST) const;
};


#ifdef __OCL_RESOLVE_TEMPLATES__
  #include <OContainer.inl>
#endif


#endif // OCONTAINER_INCLUDED

// end of source
