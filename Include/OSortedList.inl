// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OSortedList.inl

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

// $Header: W:/Projects/OCL/Include/rcs/OSortedList.inl 1.50 1996/08/11 23:47:30 B.STEIN Release $

#ifndef SORTEDLIST_INLINED
  #define SORTEDLIST_INLINED

template <class T>
OSortedList<T>::OSortedList(BOOL copyElements)
  : OOrderedCollection(copyElements)
  {}

template <class T>
OSortedList<T>::OSortedList(OSortedList<T>& slist, BOOL copyElements)
  : OOrderedCollection(copyElements)
{
 T* temp = slist.getFirst();

 while (temp) {
   add((T*)temp);
   temp = slist.getNext(); }
}


template <class T>
OSortedList<T>::~OSortedList()
  {}

template <class T>
PSZ OSortedList<T>::isOfType() const
{ 
 return("OSortedList<T>"); 
}

template <class T>
void OSortedList<T>::freeItem(PVOID elem)
{ 
 delete (T*) elem; 
}

template <class T>
BOOL OSortedList<T>::_isLess(PVOID first, PVOID second)
{ 
 return(isLess((T*)first, (T*)second)); 
}

template <class T>
T* OSortedList<T>::getFirst()
{ 
 return((T*) OCollection::_getFirst()); 
}

template <class T>
T* OSortedList<T>::getLast()
{ 
 return((T*) OCollection::_getLast()); 
}

template <class T>
T* OSortedList<T>::get()
{ 
 return((T*) OCollection::_getNext()); 
}

template <class T>
T* OSortedList<T>::getNext()         
{ 
 return((T*) OCollection::_getNext()); 
}

template <class T>
T* OSortedList<T>::getNext(T *elem)
{ 
 return((T*) OCollection::_getNext(elem)); 
}

template <class T>
T* OSortedList<T>::getPrev()          
{ 
 return((T*) OCollection::_getPrev()); 
}

template <class T>
T* OSortedList<T>::getPrev(T *elem)
{ 
 return((T*) OCollection::_getPrev(elem)); 
}

template <class T>
T* OSortedList<T>::getItem(ULONG itemNum)
{ 
 return((T*) OCollection::_getItem(itemNum)); 
}


template <class T>
OListItem<T>* OSortedList<T>::first() const
{
 return((OListItem<T>*)OCollection::first);
}

template <class T>
OListItem<T>* OSortedList<T>::actual() const
{
 return((OListItem<T>*)OCollection::actual);
}

template <class T>
OListItem<T>* OSortedList<T>::last() const
{
 return((OListItem<T>*)OCollection::last);
}

template <class T>
OListItem<T>* OSortedList<T>::getNextListItem(T *elem)
{ 
 return((OListItem<T>*) OCollection::_getNextListItem(elem)); 
}

template <class T>
OListItem<T>* OSortedList<T>::getPrevListItem(T *elem)
{ 
 return((OListItem<T>*) OCollection::_getPrevListItem(elem)); 
}

template <class T>
void OSortedList<T>::add(T& elem)
{ 
 isCopyCollection() ? addSorted(new T(elem)) : addSorted(&elem);
}

template <class T>
void OSortedList<T>::add(T* elem)
{ 
 isCopyCollection() ? addSorted(new T(*elem)) : addSorted((T*)elem);
}

template <class T>
OSortedList<T>& OSortedList<T>::operator << (T* elem)
{
 if (elem) add(elem);
 return(*this);
}

template <class T>
OSortedList<T>& OSortedList<T>::operator << (T& elem)
{
 add(&elem);
 return(*this);
}

template <class T>
OSortedList<T>& OSortedList<T>::operator >> (T& elem)
{
 T* temp = getNext();
 
 if (temp)
   elem = *temp;

 return(*this);
}

template <class T>
OSortedList<T>& OSortedList<T>::operator >> (T* elem)
{
 elem = getNext();
 return(*this);
}


template <class T>
void OSortedList<T>::allElementsDo(void (*function)(const T* elem)) const
{
 OListItem<T> *temp = first();

 while(temp) {
   if (temp->item)
     function(temp->item);
   temp = temp->next; }
}

template <class T>
void OSortedList<T>::allElementsDo(OConstIterator<T>& iter) const
{
 OListItem<T> *temp = first();

 while(temp) {
   if (temp->item)
     iter.applyToElement(temp->item);
   temp = temp->next; }
}

template <class T>
void OSortedList<T>::allElementsDo(void (*function)(T* elem))
{
 T *temp = getFirst();

 while(temp) {
   function(temp);
   temp = getNext(); }
}

template <class T>
void OSortedList<T>::allElementsDo(OIterator<T>& iter)
{
 T *temp = getFirst();

 while(temp) {
   iter.applyToElement(temp);
   temp = getNext(); }
}


#endif // OSORTEDLIST_INLINED

// end of source
