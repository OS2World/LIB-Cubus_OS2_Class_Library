// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OQueue.inl

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

// $Header: W:/Projects/OCL/Include/rcs/OQueue.inl 1.50 1996/08/11 23:47:28 B.STEIN Release $

#ifndef OQUEUE_INLINED
  #define OQUEUE_INLINED

template <class T>
OQueue<T>::OQueue(BOOL copyElements)
  : OList<T>(copyElements)
  {} 

template <class T>
OQueue<T>::OQueue(OQueue<T>& queue, BOOL copyElements)
  : OList<T>(queue, copyElements)
  {}


template <class T>
OQueue<T>::~OQueue()
 {}

template <class T>
PSZ OQueue<T>::isOfType() const
{
 return("OQueue<T>");
} 

template <class T>
void OQueue<T>::put(T& item)
{
 addLast(&item);
}

template <class T>
void OQueue<T>::put(T *item)
{
 addLast(item);
}

template <class T>
T* OQueue<T>::get()
{
 T* retVal = (T*) _getFirst();

 if (retVal)
   remove(retVal);

 return(retVal); 
}


#endif // OQUEUE_INLINED

// end of source
