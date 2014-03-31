// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OOrderedCollection.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OOrderedCollection.cpp 1.50 1996/08/11 23:49:25 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OOrderedCollection.hpp>

OOrderedCollection::OOrderedCollection(BOOL copyElements) 
  : OCollection(copyElements),
    collectionSem((PSZ)NULL),
    sortAscending(TRUE), 
    collectionCursor(0) 
  {}

OOrderedCollection::~OOrderedCollection()
{
 collectionSem.requestMuxSem();
 collectionSem.releaseMuxSem();
}

PSZ OOrderedCollection::isOfType() const
{ 
 return("OOrderedCollection"); 
}

void OOrderedCollection::setAscending(BOOL ascending)
{
 sortAscending = ascending;
}

void OOrderedCollection::addSorted(PVOID elem)
{
 if (!first) {
   addFirst(elem);
   return; }

 if (sortAscending)
   addSortAscending(elem);
 else
   addSortDescending(elem);
}

void OOrderedCollection::addSortAscending(PVOID elem)
{
 ULONG   step = 2, i;
 PPVITEM tmp;

 if (_isLess(elem, first->item))
  {
   addFirst(elem);
   return; 
  }

 if (_isLess(last->item, elem))
  {
   addLast(elem);
   return; 
  }

 collectionSem.requestMuxSem();
 collectionCursor = items/step;

 tmp = _getNextListItem(_getItem(collectionCursor));

 while(TRUE)
  {
   step = 2*step;
   collectionCursor = items/step;
   if (collectionCursor > 2)
     {
      if (_isLess(elem, tmp->item))
        {
         for(i = 0; i < collectionCursor; i+=2)
            tmp = tmp->prev->prev; 
        }
      else 
        {
         for(i = 0; i < collectionCursor; i+=2)
            tmp = tmp->next->next; 
        }
     }
   else break;
 }

 while (_isLess(elem, tmp->item))
    tmp = tmp->prev;
 while(_isLess(tmp->item, elem))
    tmp = tmp->next;
 addAfter(tmp->prev, elem);
 collectionSem.releaseMuxSem();
}

void OOrderedCollection::addSortDescending(PVOID elem)
{
 ULONG    step = 2, i;
 PPVITEM  tmp;

 if (_isLess(first->item, elem))
  {
   addFirst(elem);
   return; 
  }

 if (_isLess(elem, last->item))
  {
   addLast(elem);
   return; 
  }

 collectionSem.requestMuxSem();
 collectionCursor = items/step;

 tmp = _getNextListItem(_getItem(collectionCursor));

 while(TRUE)
  {
   step = 2*step;
   collectionCursor = items/step;
   if (collectionCursor > 2)
     {
      if (_isLess(tmp->item, elem))
        {
         for(i = 0; i < collectionCursor; i+=2)
            tmp = tmp->prev->prev; 
        }
      else 
        {
         for(i = 0; i < collectionCursor; i+=2)
            tmp = tmp->next->next; 
        }
     }
   else break;
 }

 while (_isLess(tmp->item, elem))
    tmp = tmp->prev;
 while(_isLess(elem, tmp->item))
    tmp = tmp->next;
 addAfter(tmp->prev, elem);
 collectionCursor = 0;
 collectionSem.releaseMuxSem();
}


// end of source
