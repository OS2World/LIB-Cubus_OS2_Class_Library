// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_Address.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OIP_Address.cpp 1.50 1996/08/11 23:49:18 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_Address.hpp>



OIP_Address::OIP_Address()
{
 addr_data.S_un.s_addr = 0;
}


OIP_Address::OIP_Address(UCHAR i1, UCHAR i2, UCHAR i3, UCHAR i4)
{
 Set_s_addr(i1, i2, i3, i4);
}


OIP_Address::OIP_Address(ULONG addr)
{
 addr_data.S_un.s_addr = lswap(addr);
}


OIP_Address::~OIP_Address()
{}


PSZ OIP_Address::isOfType () const
{
 return("OIP_Address");
}


ULONG OIP_Address::Set_s_addr(ULONG addr)
{
 return(addr_data.S_un.s_addr = addr);
}


ULONG OIP_Address::Get_s_addr()
{
 return(addr_data.S_un.s_addr);
}


OIP_Address::operator ULONG()
{
 return(addr_data.S_un.s_addr);
}



OIP_Address::operator = (ULONG addr)
{
 return(addr_data.S_un.s_addr = addr);
}


void OIP_Address::Set_s_addr(UCHAR i1, UCHAR i2, UCHAR i3, UCHAR i4)
{
 addr_data.S_un.s_addr = lswap((i1 << 24) | (i2 << 16) | (i3 << 8) | i4);
}



int OIP_Address::Set_s_addr(PSZ addrtext)
{
 UCHAR i1, i2, i3, i4, i;
 int ok = -1;

 if (sscanf(addrtext, "%u.%u.%u.%u%c", &i1, &i2, &i3, &i4, &i) == 4)
   {
    Set_s_addr(i1, i2, i3, i4);
    ok = 0;
   }
 return ok;
}


void OIP_Address::Get_inet_addr(PSZ adress)
{
 sprintf(adress, "%u.%u.%u.%u",
        (UINT)addr_data.S_un.S_un_b.s_b1, (UINT)addr_data.S_un.S_un_b.s_b2,
        (UINT)addr_data.S_un.S_un_b.s_b3, (UINT)addr_data.S_un.S_un_b.s_b4);
}


// end of source
