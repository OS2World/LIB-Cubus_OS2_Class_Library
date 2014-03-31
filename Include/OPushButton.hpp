// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPushButton.hpp


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


// $Header: W:/Projects/OCL/Include/rcs/OPushButton.hpp 1.50 1996/08/11 23:47:28 B.STEIN Release $

#ifndef OPBTN_INCLUDED
  #define OPBTN_INCLUDED


#ifndef OBTN_INCLUDED
  #include <OButton.hpp>
#endif


// classes


typedef class OPushButton *pOPushButton;

class __CPP_EXPORT__ OPushButton
  : public OButton 
{
 public:
    OPushButton (ULONG   id,
                 HWND    Parent,
                 ULONG   x  = 0,
                 ULONG   y  = 0,
                 ULONG   cx = 40,
                 ULONG   cy = 20,
                 ULONG   extraStyle = WS_VISIBLE);

    OPushButton (ULONG   id,
                 OFrame& Parent,
                 ULONG   x  = 0,
                 ULONG   y  = 0,
                 ULONG   cx = 40,
                 ULONG   cy = 20,
                 ULONG   extraStyle = WS_VISIBLE);

    OPushButton (ULONG   id,
                 pOFrame Parent,
                 ULONG   x  = 0,
                 ULONG   y  = 0,
                 ULONG   cx = 40,
                 ULONG   cy = 20,
                 ULONG   extraStyle = WS_VISIBLE);

    virtual
      ~OPushButton  ();

    virtual
      PSZ isOfType  () const;
};


#endif // OPBTN_INCLUDED


// end of source
