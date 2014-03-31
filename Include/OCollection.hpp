// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OCollection.hpp

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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OCollection.hpp 1.1 1996/08/12 00:01:12 B.STEIN Release $

#ifndef OCOLLECTION_INCLUDED
  #define OCOLLECTION_INCLUDED


#if (defined ( __IBMCPP__ ) && !defined ( OCL_HPP_INCLUDED ))  // in case of template generation
  #define INCL_DOS
  #define INCL_WIN
  #define INCL_PM
  #include <ocl.hpp>
#endif


template <class T>
class OListItem
{
 public:
   OListItem<T>        *next;  // next OListItem
   OListItem<T>        *prev;  // previous OListItem
   T                   *item;  // Data
   inline OListItem    () : next(NULL), prev(NULL), item(NULL)
                       {}
   inline ~OListItem   ()
                       {}
};

typedef OListItem<VOID> PVITEM;
typedef PVITEM *PPVITEM;

class __CPP_EXPORT__ OCollection
  : public OCLObject
{
 protected:
    BOOL                   copyFlag; // are elements copied to the collection?
    ULONG                  items;    // number of elements in list
    PPVITEM                actual;   // last accessed element
    PPVITEM                first;    // first element
    PPVITEM                last;     // last element

    virtual
       void freeItem       (PVOID elem) = 0;

    virtual PVOID
       _getFirst           (),
       _getLast            (),
       _getNext            (),       
       _getNext            (PVOID elem),
       _getPrev            (),
       _getPrev            (PVOID elem),
       _getItem            (ULONG itemNum);

    virtual PPVITEM
        _getNextListItem   (PVOID elem),
        _getPrevListItem   (PVOID elem);


 public:

    OCollection            (BOOL copyElements);
          
    virtual
       ~OCollection        (); 

    virtual
       PSZ isOfType        () const;

    BOOL
       isCopyCollection    () const,
       isEmpty             () const;

    ULONG numberOfElements () const;

    void
       rewind              (),
       init                ();

    virtual void 
       reset               (),
       addFirst            (PVOID elem),
       addLast             (PVOID elem),
       addAfter            (PVOID   previous, PVOID elem),
       addAfter            (PPVITEM previous, PVOID elem),
       remove              (PVOID elem),
       del                 (PVOID elem);
};


#endif // OCOLLECTION_INCLUDED



// end of source
