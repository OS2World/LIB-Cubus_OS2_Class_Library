// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OCollection.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OCollection.cpp 1.50 1996/08/11 23:49:11 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OCollection.hpp>

#if defined (__EMX__)
  template class OListItem<void>;
#endif


OCollection::OCollection(BOOL copyElements) 
  : copyFlag(copyElements),
    items(0), 
    actual(NULL), 
    first(NULL), 
    last(NULL) 
  {}


OCollection::~OCollection()
{
 if (copyFlag)
   reset();
 else
   init();
#ifdef __IBMCPP__ 
   _heapmin();  // return all unused memory to OS/2
#endif
}


PSZ OCollection::isOfType() const
{ 
 return("OListBase"); 
}


BOOL OCollection::isCopyCollection() const
{
 return(copyFlag);
}


ULONG OCollection::numberOfElements() const
{
 return(items);
}


BOOL OCollection::isEmpty() const
{
 return(first == NULL);
}


void OCollection::rewind()
{
 actual = first;
}


void OCollection::init()
{
 if (first)
  {
   PPVITEM tmp = last->prev;
   while(tmp)
    {
     delete tmp->next;
     tmp = tmp->prev;
    }
   delete first;
  }
 items = 0;
 actual = first = last = NULL;
}


void OCollection::reset()
{
 if (first)
  {
   PPVITEM tmp = last->prev;

   while(tmp)
    {
     freeItem(tmp->next->item);
     delete tmp->next;
     tmp = tmp->prev;
    }
   freeItem(first->item);
   delete first;
  }
 items = 0;
 actual = first = last = NULL;
}



void OCollection::addFirst(PVOID elem)
{
 PPVITEM aNew;

 if (!elem) return;
 
 aNew = new PVITEM;
 aNew->next = first;
 aNew->item = elem;

 if (first)
   first->prev = aNew;
 else
   last = aNew;

 first = aNew;
 items++;
}


void OCollection::addLast(PVOID elem)
{
 PPVITEM aNew;

 if (!elem) return;
 
 aNew = new PVITEM;

 if (!first)
  {
   aNew->item = elem;
   first = actual = aNew;
  }
 else
  {
   aNew->item = elem;
   aNew->prev = last;
   last->next = aNew;
  }
 last = aNew;
 items++;
}



void OCollection::addAfter(PVOID previous, PVOID elem)
{
 PPVITEM tmp = first;

 if (!elem) return;

 if ((!previous) || (!first))
  {
   addFirst(elem);
   return;
  }

 while((tmp) && (tmp->item != previous))
   tmp = tmp->next;

 if (tmp)
   addAfter(tmp, elem);
 else
   addLast(elem);
}


void OCollection::addAfter(PPVITEM previous, PVOID elem)
{
 PPVITEM aNew;

 if (!elem) return;

 if (!previous)
  {
   addFirst(elem);
   return;
  }

 if (!previous->next)
  {
   addLast(elem);
   return;
  }

 aNew = new PVITEM;

 aNew->next = previous->next;
 aNew->prev = previous;
 aNew->item = elem;

 previous->next->prev = aNew;
 previous->next = aNew;

 items++;
}



PVOID OCollection::_getFirst()
{
 if (first)
  {
   rewind();
   return(first->item);
  }
 return(NULL);
}



PVOID OCollection::_getLast()
{
 if (first)
  {
   actual = last;
   return(last->item);
  }
 return(NULL);
}



PVOID OCollection::_getNext()
{
 if (!first)
   return(NULL);
 else if (actual->next)
  {
   actual = actual->next;
   if (actual)
     return(actual->item);
   else
     return(NULL);
  }
 else
   return(NULL);
}




PVOID OCollection::_getPrev()
{
 if (!first)
   return(NULL);
 else if (actual->prev)
  {
   actual = actual->prev;
   if (actual)
     return(actual->item);
   else
     return(NULL);
  }
 else
   return(NULL);
}


PVOID OCollection::_getItem(ULONG itemNum)
{
 ULONG i;
 PVOID tmp;

 if ((!first) || (itemNum < 1))
   return(NULL);
 if (itemNum == 1)
   return(first->item);
 tmp = _getFirst();
 for (i=2; ((i <= itemNum) && (tmp)); i++)
   tmp = _getNext();
 return(tmp);
}


PVOID OCollection::_getNext(PVOID elem)
{
 PPVITEM tmp = first;

 if (!elem) return(NULL);

 while((tmp) && (tmp->item != elem))
   tmp = tmp->next;

 if (!tmp)
   return(NULL);
 else
   return(tmp->item);
}



PVOID OCollection::_getPrev(PVOID elem)
{
 PPVITEM tmp = last;

 if (!elem) return(NULL);

 while((tmp) && (tmp->item != elem))
    tmp = tmp->prev;

 if (!tmp)
   return(NULL);
 else
   return(tmp->item);
}



PPVITEM OCollection::_getPrevListItem(PVOID elem)
{
 PPVITEM tmp = last;

 if (!elem) return(NULL);

 while((tmp) && (tmp->item != elem))
   tmp = tmp->prev;

 return(tmp);
}


PPVITEM OCollection::_getNextListItem(PVOID elem)
{
 PPVITEM tmp = first;

 if (!elem) return(NULL);

 while((tmp) && (tmp->item != elem))
   tmp = tmp->next;

 return(tmp);
}


void OCollection::remove(PVOID elem)
{
 PPVITEM tmp = first;

 if (!elem) return;

 while(tmp)
  {
   if ((tmp->item) && (tmp->item == elem))
    {
     if (tmp->prev)
       tmp->prev->next = tmp->next;
     else
       first = tmp->next;
     if (tmp->next)
       tmp->next->prev = tmp->prev;
     else
       last = tmp->prev;
     if (tmp == actual)
      {
       if (tmp->prev)
         actual = tmp->prev;
       else if (tmp->next)
         actual = tmp->next;
      }
     --items;
     tmp->item = NULL;
     if ((!tmp->prev) && (!tmp->next))
       init();
     else
      {
       delete tmp;
       tmp = NULL;
       return;
      }
    }
   tmp = tmp->next;
  }
}


void OCollection::del(PVOID elem)
{
 if ((first) && (elem))
  {
   remove(elem);
   freeItem(elem);
  }
}

// end of source
