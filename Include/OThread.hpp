// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OThread.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OThread.hpp 1.50 1996/08/11 23:47:33 B.STEIN Release $

#ifndef OTHREAD_INCLUDED
  #define OTHREAD_INCLUDED

#ifndef OTHREADBASE_INCLUDED
  #include <OThreadBase.hpp>
#endif


#ifdef __IBMCPP__
  typedef VOID (_Optlink OThread_mbrfn)(PVOID);
#elif __BCPLUSPLUS__
  typedef VOID (_USERENTRY OThread_mbrfn)(PVOID);
#elif __WATCOM_CPLUSPLUS__
  typedef VOID (OThread_mbrfn)(PVOID);
#elif __HIGHC__
  typedef VOID (OThread_mbrfn)(PVOID);
#elif __EMX__
  typedef VOID (OThread_mbrfn)(PVOID);
#endif


#ifdef __WATCOM_CPLUSPLUS__
  #define _WPPCAST_ __CPP_EXPORT__
#else
  #define _WPPCAST_
#endif 

  
#ifdef __IBMCPP__
  typedef void ( _Optlink *OptlinkFnPtr ) ( void * );
#endif


typedef OThread_mbrfn     *pOThread_mbrfn;
typedef class OThreadBase *pOThreadBase;


template <class T>
class OThread
  : public OThreadBase
{
 private:

   void             (_WPPCAST_ T::*member)();
   T*               object;
   PFNTHREAD        threadFunc;
   PVOID            pArgs;

 public:
   OThread         (T* obj,                      // pointer to object
                    void(_WPPCAST_ T::*mem)(),   // pointer to member-fn to detach
                    ULONG stackSize = USHRT_MAX, // stacksize for thread
                    BOOL  forPM = TRUE);         // initialize PM?

   OThread         (T& obj,                      // reference to object
                    void(_WPPCAST_ T::*mem)(),   // pointer to member-fn to detach
                    ULONG stackSize = USHRT_MAX, // stacksize for thread
                    BOOL  forPM     = TRUE);     // initialize PM?

   OThread         (PFNTHREAD aFunction,
                    ULONG stackSize = USHRT_MAX,
                    BOOL  forPM     = TRUE,
                    PVOID pvData    = NULL);

                    #ifdef __IBMCPP__
   OThread         (OptlinkFnPtr aFunction,
                    ULONG stackSize = USHRT_MAX,
                    BOOL  forPM     = TRUE,
                    PVOID pvData    = NULL);
                    #endif

   virtual
      ~OThread     ();

   virtual
      PSZ isOfType () const;

   void async      ();
};


#ifdef __OCL_RESOLVE_TEMPLATES__
  #include <OThread.inl>
#endif


#endif // OTHREAD_INCLUDED


// end of source
