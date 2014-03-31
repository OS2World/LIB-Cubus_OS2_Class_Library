// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_SockAddress.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OIP_SockAddress.cpp 1.50 1996/08/11 23:49:20 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_SockAddress.hpp>


OIP_SockAddress::OIP_SockAddress()
{
 memset(&data, 0, sizeof(data));
 data.sin_family = AF_INET;
}

OIP_SockAddress::~OIP_SockAddress()
 {}

PSZ OIP_SockAddress::isOfType () const
{
 return("OIP_SockAddress");
}

OIP_SockAddress::operator sockaddr_in()
{
 return(data);
}

OIP_SockAddress::operator psockaddr_in()
{
 return(&data);
}


psockaddr_in OIP_SockAddress::Get_sockaddr_in()
{
 return(&data);
}


USHORT OIP_SockAddress::Setin_port(USHORT port)
{
 return(data.sin_port = htons(port));
}

USHORT OIP_SockAddress::Getin_port()
{
 return(ntohs(data.sin_port));
}


ULONG OIP_SockAddress::Set_sin_addr(ULONG addr)
{
 return(data.sin_addr.S_un.s_addr = addr);
}

ULONG OIP_SockAddress::Set_sin_addr(PSZ   target)
{
 return(data.sin_addr.S_un.s_addr = ::inet_addr(target));
}

ULONG OIP_SockAddress::Get_sin_addr()
{
 return(data.sin_addr.S_un.s_addr);
}

short OIP_SockAddress::Set_sin_family(short family)
{
 return(data.sin_family = family);
}

short OIP_SockAddress::Get_sin_family()
{
 return(data.sin_family);
}

void OIP_SockAddress::Get_inet_addr(PSZ   adress)
{
 sprintf(adress, "%u.%u.%u.%u",
        (UINT)data.sin_addr.S_un.S_un_b.s_b1, (UINT)data.sin_addr.S_un.S_un_b.s_b2,
        (UINT)data.sin_addr.S_un.S_un_b.s_b3, (UINT)data.sin_addr.S_un.S_un_b.s_b4);

}



// end of source
