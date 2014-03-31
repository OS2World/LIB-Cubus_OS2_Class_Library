// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OTimer.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OTimer.hpp 1.50 1996/08/11 23:47:33 B.STEIN Release $

#ifndef OTIMER_INCLUDED
  #define OTIMER_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


class __CPP_EXPORT__ OTimer
{
 private:
    ULONG           _id;
    ULONG           _timeout;
    HWND            notifyHwnd;
    BOOL            isStarted;

 public:
    OTimer          (HWND    notifyWin,
                     ULONG   id,
                     ULONG   timeout);

    OTimer          (OFrame& notifyWin,
                     ULONG   id,
                     ULONG   timeout);

    OTimer          (pOFrame notifyWin,
                     ULONG   id,
                     ULONG   timeout);

    virtual
       ~OTimer      ();

    virtual
       PSZ isOfType () const; 

    OTimer
       &start       (),
       &start       (ULONG   timeout),
       &stop        (),

       &setId       (ULONG   id), 
       &setTimeout  (ULONG   timeout),
       &setNotify   (HWND    notifyWin),
       &setNotify   (OFrame& notifyWin),
       &setNotify   (pOFrame notifyWin);
};



#endif // OTIMER_INCLUDED

// end of source
