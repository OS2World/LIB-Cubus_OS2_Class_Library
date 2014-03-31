// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_SrvSocket.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OIP_SrvSocket.cpp 1.50 1996/08/11 23:49:20 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_SrvSocket.hpp>


OIP_SrvSocket::OIP_SrvSocket()
  {}


OIP_SrvSocket::~OIP_SrvSocket()
  {}


PSZ OIP_SrvSocket::isOfType () const
{
 return("OIP_SrvSocket");
}


int OIP_SrvSocket::bind()
{
 int x = ::bind(s, Get_sockaddr(), SOCADDR_BINDSIZE);
 if (x)
   throw OIP_SocketException(OIP_SocketException::ebind, GetErrorCode());
 return(x);
}

int OIP_SrvSocket::bind(pOIP_CliSocket pclient)
{
 int x = ::bind(s, pclient->Get_sockaddr(), SOCADDR_BINDSIZE);
 if (x)
   throw OIP_SocketException(OIP_SocketException::ebind, GetErrorCode());
 return(x);
}

int OIP_SrvSocket::listen(int clients)
{
 int x = ::listen(s, clients);
 if (x) throw OIP_SocketException(OIP_SocketException::elisten, GetErrorCode());
 
 return(x);
}

int OIP_SrvSocket::accept()
{
 int len = SOCADDR_BINDSIZE;
 return(s = ::accept(s, (psockaddr)&sockadd, (PINT)&len));
}

int OIP_SrvSocket::accept(pOIP_CliSocket pclient)
{
 int len = SOCADDR_BINDSIZE;
 return(pclient->Set_socket(::accept(s,	pclient->Get_sockaddr(), (PINT)&len)));
}

// end of source

