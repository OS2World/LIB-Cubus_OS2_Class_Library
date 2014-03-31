// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OList.inl

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

// $Header: W:/Projects/OCL/Include/rcs/OList.inl 1.50 1996/08/11 23:47:19 B.STEIN Release $


#ifndef OLIST_INLINED
  #define OLIST_INLINED


template <class T>
OList<T>::OList(BOOL copyElements)
  : OCollection(copyElements)
  {}

template <class T>
OList<T>::OList(OList<T>& list, BOOL copyElements)
  : OCollection(copyElements)
{
 T* temp = list.getFirst();

 while (temp) {
   add((T*)temp);
   temp = list.getNext(); }
}

template <class T>
OList<T>::~OList()
  {}

template <class T>
PSZ OList<T>::isOfType() const
{ 
 return("OList<T>"); 
}

template <class T>
void OList<T>::freeItem(PVOID elem)
{ 
 delete (T*) elem; 
}

template <class T>
T* OList<T>::getFirst()
{ 
 return((T*) OCollection::_getFirst()); 
}

template <class T>
T* OList<T>::getLast()
{ 
 return((T*) OCollection::_getLast()); 
}

template <class T>
T* OList<T>::get()
{ 
 return((T*) OCollection::_getNext()); 
}

template <class T>
T* OList<T>::getNext()         
{ 
 return((T*) OCollection::_getNext()); 
}

template <class T>
T* OList<T>::getNext(T *elem)
{ 
 return((T*) OCollection::_getNext(elem)); 
}

template <class T>
T* OList<T>::getPrev()          
{ 
 return((T*) OCollection::_getPrev()); 
}

template <class T>
T* OList<T>::getPrev(T *elem)
{ 
 return((T*) OCollection::_getPrev(elem)); 
}

template <class T>
T* OList<T>::getItem(ULONG itemNum)
{ 
 return((T*) OCollection::_getItem(itemNum)); 
}


template <class T>
OListItem<T>* OList<T>::first() const
{
 return((OListItem<T>*)OCollection::first);
}

template <class T>
OListItem<T>* OList<T>::actual() const
{
 return((OListItem<T>*)OCollection::actual);
}

template <class T>
OListItem<T>* OList<T>::last() const
{
 return((OListItem<T>*)OCollection::last);
}

template <class T>
OListItem<T>* OList<T>::getNextListItem(T *elem)
{ 
 return((OListItem<T>*) OCollection::_getNextListItem(elem)); 
}

template <class T>
OListItem<T>* OList<T>::getPrevListItem(T *elem)
{ 
 return((OListItem<T>*) OCollection::_getPrevListItem(elem)); 
}

template <class T>
void OList<T>::add(T& elem)
{ 
 isCopyCollection() ? addLast(new T(elem)) : addLast(&elem);
}

template <class T>
void OList<T>::add(T* elem)
{ 
 isCopyCollection() ? addLast(new T(*elem)) : addLast((T*)elem);
}

template <class T>
OList<T>& OList<T>::operator << (T* elem)
{
 if (elem) add(elem);
 return(*this);
}

template <class T>
OList<T>& OList<T>::operator << (T& elem)
{
 add(&elem);
 return(*this);
}

template <class T>
OList<T>& OList<T>::operator >> (T& elem)
{
 T* temp = getNext();
 
 if (temp)
   elem = *temp;

 return(*this);
}

template <class T>
OList<T>& OList<T>::operator >> (T* elem)
{
 elem = getNext();
 return(*this);
}


template <class T>
void OList<T>::allElementsDo(void (*function)(const T* elem)) const
{
 OListItem<T> *temp = first();

 while(temp) {
   if (temp->item)
     function(temp->item);
   temp = temp->next; }
}

template <class T>
void OList<T>::allElementsDo(OConstIterator<T>& iter) const
{
 OListItem<T> *temp = first();

 while(temp) {
   if (temp->item)
     iter.applyToElement(temp->item);
   temp = temp->next; }
}


template <class T>
void OList<T>::allElementsDo(void (*function)(T* elem))
{
 T *temp = getFirst();

 while(temp) {
   function(temp);
   temp = getNext(); }
}

template <class T>
void OList<T>::allElementsDo(OIterator<T>& iter)
{
 T *temp = getFirst();

 while(temp) {
   iter.applyToElement(temp);
   temp = getNext(); }
}


#endif // OLIST_INLINED

// end of source
