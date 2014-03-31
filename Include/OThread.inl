// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OThread.inl

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

// $Header: W:/Projects/OCL/Include/rcs/OThread.inl 1.50 1996/08/11 23:47:33 B.STEIN Release $

#ifndef OTHREAD_INLINED
  #define OTHREAD_INLINED


#ifdef __IBMCPP__

template <class T>
OThread<T>::OThread(OptlinkFnPtr aFunction,
                    ULONG stackSize,
                    BOOL forPM,
                    PVOID pvData)
     : OThreadBase(stackSize, forPM),
       member(NULL),
       object((T*)NULL),
       threadFunc((PFNTHREAD)aFunction),
       pArgs(pvData)
{}

#endif // __IBMCPP__



template <class T>
OThread<T>::OThread(T* obj,                    // pointer to object
                    void(_WPPCAST_ T::*mem)(), // pointer to member-fn to detach
                    ULONG stackSize,           // stacksize for thread
                    BOOL  forPM)               // initialize PM?
     : OThreadBase(stackSize, forPM),
       member(mem),
       object(obj),
       threadFunc(NULL),
       pArgs(NULL)
{}


template <class T>
OThread<T>::OThread(T& obj,                    // reference to object
                    void(_WPPCAST_ T::*mem)(), // pointer to member-fn to detach
                    ULONG stackSize,           // stacksize for thread
                    BOOL  forPM)               // initialize PM?
     : OThreadBase(stackSize, forPM),
       member(mem),
       object(&obj),
       threadFunc(NULL),
       pArgs(NULL)
{}

template <class T>
OThread<T>::OThread(PFNTHREAD aFunction,
                    ULONG stackSize,
                    BOOL forPM,
                    PVOID pvData)
     : OThreadBase(stackSize, forPM),
#if defined(__EMX__)
       member( 0 ),
#else
       member( NULL),
#endif
       object((T*)NULL),
       threadFunc(aFunction),
       pArgs(pvData)
{}


template <class T>
OThread<T>::~OThread()
{}


template <class T>
PSZ OThread<T>::isOfType() const
{ 
 return("OThread<T>"); 
}


template <class T>
void OThread<T>::async() 
{
 if (threadFunc != NULL)
   threadFunc((ULONG)pArgs);
 else if (object)
   (object->*member)(); 
}


#endif // OTHREAD_INLINED

// end of source
