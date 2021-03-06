// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_Address.hpp

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


// $Header: W:/Projects/OCL/Include/rcs/OIP_Address.hpp 1.50 1996/08/11 23:47:15 B.STEIN Release $


#ifndef OIP_ADDRESS_INCLUDED
   #define OIP_ADDRESS_INCLUDED


#ifndef OIP_INCLUDED
  #include <OIP.hpp>
#endif

typedef class OIP_Address *pOIP_Address;

class __CPP_EXPORT__ OIP_Address
  : public OCLObject
{
 public:

     OIP_Address         ();

     OIP_Address         (UCHAR i1,
                          UCHAR i2,
                          UCHAR i3,
                          UCHAR i4);

     OIP_Address         (ULONG addr);

     virtual
       ~OIP_Address      ();

     virtual
       PSZ isOfType      () const;
 

     void
       Set_s_addr        (UCHAR i1,
                          UCHAR i2,
                          UCHAR i3,
                          UCHAR i4);

     int
       Set_s_addr        (PSZ   addrtext);

     ULONG
       Set_s_addr        (ULONG addr),
       Get_s_addr        ();

     void
       Get_inet_addr     (PSZ adress);

     operator ULONG      ();
     operator =          (ULONG addr);


 protected:
     in_addr             addr_data;
 
};


#endif	// OIP_ADDRESS_INCLUDED

