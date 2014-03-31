// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// (c) 1994 Matthias StÅbner
// (c) Benjamin Stein 1994
// OSPINBTN.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OSpinBtn.hpp 1.50 1996/08/11 23:47:30 B.STEIN Release $

#ifndef OSPINBTN_INCLUDED
  #define OSPINBTN_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif


/* Mîgliche Styles fÅr einen Spinbutton sind:

SPBS_MASTER         -   spin button with arrows
SPBS_SERVANT        -   spin button without arrows

SPBS_ALLCHARACTERS  -   all characteralle
SPBS_NUMERICONLY    -   only numbers
SPBS_READONLY       -   read only

SPBS_JUSTLEFT       -   content is left justified
SPBS_JUSTRIGHT      -   content is right justified
SPBS_JUSTCENTER     -   content is centered
SPBS_NOBORDER       -   without borders

SPBS_FASTSPIN       -   fast spin
SPBS_PADWITHZERO    -   pad with zeros
*/


typedef class OSpinBtn *pOSpinBtn;

class __CPP_EXPORT__ OSpinBtn
  : public OWindow
{
 public:

    OSpinBtn           (const ULONG ID,
                        const HWND  Parent,  // becomes parent and owner of the slider
                        const ULONG Style);

    OSpinBtn           (const ULONG id,
                        const OFrame& Parent, 
                        const ULONG Style);

    OSpinBtn           (const ULONG id,
                        const pOFrame Parent, 
                        const ULONG Style);

    virtual
       ~OSpinBtn       ();

    virtual
       PSZ isOfType    () const;
  
    BOOL
       createSpinBtn   (const SHORT x,  const SHORT y,
                        const SHORT cx, const SHORT cy),
       setArray        (PSZ array, ULONG num),
       setCurrent      (LONG index),
       setLimits       (LONG upper, LONG lower),
       setMaster       (HWND master),
       setTextLimit    (USHORT length),
       overrideLimits  (LONG upper, LONG lower),
       incSpin         (ULONG delta = 1),
       decSpin         (ULONG delta = 1),
       getLimits       (LONG *upper, LONG *lower),
       getCurrent      (PVOID addr, USHORT size, USHORT control = SPBQ_UPDATEIFVALID),
       jumptoEnd       (),
       jumptoStart     ();
};


#endif // OSPINBTN_INCLUDED
