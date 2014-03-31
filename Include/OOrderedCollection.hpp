// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OOrderedCollection.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OOrderedCollection.hpp 1.50 1996/08/11 23:47:24 B.STEIN Release $

#ifndef OOCOLL_INCLUDED
  #define OOCOLL_INCLUDED


#ifndef OCOLLECTION_INCLUDED
  #include <OCollection.hpp>
#endif

#ifndef OMUXSEM_INCLUDED
  #include <OMuxSem.hpp>
#endif


class __CPP_EXPORT__ OOrderedCollection
  : public OCollection
{
 protected:
    OMuxSem                collectionSem;
    ULONG                  collectionCursor;
    BOOL                   sortAscending;  // FALSE means descending, default is ascending

    virtual void
       addSortAscending    (PVOID elem),
       addSortDescending   (PVOID elem),
       addSorted           (PVOID elem);

    virtual
       BOOL _isLess        (PVOID first, PVOID second) = 0;

 public:
    OOrderedCollection     (BOOL copyElements);

    virtual
       ~OOrderedCollection ();

    virtual
       PSZ isOfType        () const;

    void
       setAscending        (BOOL ascending);   // FALSE means descending
};


#endif // OOCOLL_INCLUDED

// end of source
