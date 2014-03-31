// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSortedList.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OSortedList.hpp 1.50 1996/08/11 23:47:29 B.STEIN Release $

#ifndef SORTEDLIST_INCLUDED
  #define SORTEDLIST_INCLUDED


#ifndef LIST_INCLUDED
  #include <OList.hpp>
#endif

#ifndef OOCOLL_INCLUDED
  #include <OOrderedCollection.hpp>
#endif


template <class T>
class OSortedList 
  : public OOrderedCollection
{
 protected:
    virtual
       BOOL _isLess       (PVOID first, PVOID second);

    virtual
       void freeItem      (PVOID elem);

 public:

    OSortedList           (BOOL copyElements = FALSE);

    OSortedList           (OSortedList<T>& slist,
                           BOOL copyElements = FALSE);

    virtual
       ~OSortedList       ();

    virtual
       PSZ isOfType       () const;


    virtual T
       *getFirst          (),
       *getLast           (),
       *get               (),
       *getNext           (),
       *getNext           (T *elem),
       *getPrev           (),
       *getPrev           (T *elem),
       *getItem           (ULONG itemNum);

    virtual OListItem<T>
      *first              () const,
      *actual             () const,
      *last               () const,
      *getNextListItem    (T *elem),
      *getPrevListItem    (T *elem);


    virtual OSortedList<T>
      &operator <<        (T* elem),
      &operator <<        (T& elem),
      &operator >>        (T& elem),
      &operator >>        (T* elem);

    virtual void
      add                 (T& elem),
      add                 (T* elem),
      allElementsDo       (void (*function)(const T* elem)) const,
      allElementsDo       (OConstIterator<T>& iter) const,
      allElementsDo       (void (*function)(T* elem)),
      allElementsDo       (OIterator<T>& iter);

// pure virtual

    virtual BOOL isLess   (const T* first, const T* second) = 0;
};


#ifdef __OCL_RESOLVE_TEMPLATES__
  #include <OSortedList.inl>
#endif


#endif // SORTEDLIST_INCLUDED

// end of source
