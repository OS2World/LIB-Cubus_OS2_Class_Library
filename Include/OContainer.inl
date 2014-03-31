// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OContainer.inl

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

// $Header: E:/Projects/OCL/Include/rcs/OContainer.inl 1.2 1996/01/16 10:12:17 B.STEIN Release B.STEIN $

#ifndef OCONTAINER_INLINED
  #define OCONTAINER_INLINED


template <class T, class R>
OContainer<T,R>::OContainer(const ULONG id,
                            const HWND Parent,
                            const ULONG cnrStyle, 
                            const ULONG initViewStyle)
  : OContainerBase(id, Parent, cnrStyle, initViewStyle)
  {}


template <class T, class R>
OContainer<T,R>::OContainer(const ULONG id, 
                            const OFrame& Parent,
                            const ULONG cnrStyle,
                            const ULONG initViewStyle)
  : OContainerBase(id, Parent, cnrStyle, initViewStyle)
  {}


template <class T, class R>
OContainer<T,R>::OContainer(const ULONG id,
                            const pOFrame Parent,
                            const ULONG cnrStyle, 
                            const ULONG initViewStyle)
  : OContainerBase(id, Parent, cnrStyle, initViewStyle)
  {}


template <class T, class R>
OContainer<T,R>::~OContainer() {}


template <class T, class R>
PSZ OContainer<T,R>::isOfType() const
{ 
 return("OContainer<T,R>"); 
}


template <class T, class R>
T* OContainer<T,R>::allocRecords(ULONG records) const
{
 return((T*)OContainerBase::_allocRecords((sizeof(T) - sizeof(R)), records));
}



template <class T, class R>
T* OContainer<T,R>::queryRecord(T* root, ULONG flag, ULONG order) const
{
 return((T*)OContainerBase::_queryRecord(root, flag, order));
}


template <class T, class R>
T* OContainer<T,R>::queryEmphasis(T* record, ULONG flag) const
{
 return((T*)OContainerBase::_queryEmphasis(record, flag));
}


template <class T, class R>
T* OContainer<T,R>::querySelected(T* record) const
{
 return((T*)OContainerBase::_queryEmphasis(record, CRA_SELECTED));
}

#endif // OCONTAINER_INLINED


// end of source
