// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_Socket.cpp

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


// $Header: W:/Projects/OCL/Source/rcs/OIP_Socket.cpp 1.50 1996/08/11 23:49:20 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_Socket.hpp>
#include <OMessage.hpp>

OIP_Socket::OIP_Socket()
{
 phost = NULL;
 s     = 0;
}


OIP_Socket::OIP_Socket(phostent p)
{
 phost = new OIP_Host;
 phost->Set(p);
 s     = 0;
}


OIP_Socket::~OIP_Socket()
{
 close();
 if (phost) delete phost;
}


PSZ OIP_Socket::isOfType() const
{
 return("OIP_Socket");
}


int OIP_Socket::close()
{
 int ok;

 if (s)
  {
   ok = ::soclose(s);
   s = 0;
  }
 return(ok);
}


int OIP_Socket::sysinit(USHORT version)
{
 return(::sock_init());
}

int OIP_Socket::sysfree()
{
 return(0);
}

int OIP_Socket::Get_socket()
{
 return(s);
}

int OIP_Socket::Set_socket(int sock)
{
 return(s = sock);
}

pOIP_Host OIP_Socket::Get_phost()
{
 return(phost);
}

pOIP_Host OIP_Socket::Sethostent(phostent ph)
{
 if (phost)
   delete phost;

 phost = new OIP_Host;
 phost->Set(ph);

 return(phost);
}

int OIP_Socket::Gethostname(PSZ hostname, UINT size)
{
 return(::gethostname(hostname, size));
}

pOIP_Host OIP_Socket::Gethostbyname(PSZ hostname)
{
 phostent p = ::gethostbyname(hostname);

 if (!p)
   throw OIP_SocketException(OIP_SocketException::egethostbyname, GetErrorCode());
 return(Sethostent(p));
}

pOIP_Host OIP_Socket::Gethostbyaddr(PSZ hostaddress, int type)
{
 return(Sethostent(::gethostbyaddr(hostaddress, 4, type)));
}

pservent OIP_Socket::Getservbyname(PSZ name, PSZ proto)
{
 return(::getservbyname(name, proto));
}

void OIP_Socket::Setin_port(USHORT port)
{
 sockadd.Setin_port(port);
}

USHORT OIP_Socket::Getin_port()
{
 return(sockadd.Getin_port());
}

ULONG OIP_Socket::Set_sin_addr()
{
 return((phost) ? sockadd.Set_sin_addr(Getaddr_list()) : 0);
}

ULONG OIP_Socket::Set_sin_addr(ULONG addr)
{
 return(sockadd.Set_sin_addr(addr));
}

BOOL OIP_Socket::Set_address(USHORT port, PSZ target)
{
 if ((!Gethostbyname(target)) ||  (!Set_sin_addr()))
   return(TRUE);

 Setin_port(port);
 return(FALSE);
}


ULONG OIP_Socket::Set_sin_addr(PSZ target)
{
 return(sockadd.Set_sin_addr(target));
}

ULONG OIP_Socket::Get_sin_addr()
{
 return(sockadd.Get_sin_addr());
}

short OIP_Socket::Set_sin_family(short family)
{
 return(sockadd.Set_sin_family(family));
}

short OIP_Socket::Get_sin_family()
{
 return(sockadd.Get_sin_family());
}

ULONG OIP_Socket::Getaddr_list(UINT index)
{
 return(*((ULONG *)phost->h_data.h_addr_list[index]));
}

void OIP_Socket::Get_inet_addr(PSZ adress)
{
 sockadd.Get_inet_addr(adress);
}

int OIP_Socket::socket(int net, int typ, int y)
{
 int x = ::socket(net, typ, y);
 if (x == -1)
    throw OIP_SocketException(OIP_SocketException::esocket, GetErrorCode());
 return s = x;
}


OIP_Socket::operator =(int handle)
{
 return(s = handle);
}


OIP_Socket::operator int()
{
 return(s);
}


OIP_Socket::operator OIP_SockAddress()
{
 return(sockadd);
}

OIP_Socket::operator pOIP_SockAddress()
{
 return(&sockadd);
}

psockaddr OIP_Socket::Get_sockaddr()
{
 return((psockaddr) sockadd.Get_sockaddr_in());
}

int OIP_Socket::send(PSZ buffer, int size, int options)
{
 int x = ::send(s, buffer, size, options);
 if (!x)
    throw OIP_SocketException(OIP_SocketException::esend, GetErrorCode());
 return x;
}

int OIP_Socket::recv(PSZ buffer, int size, int options)
{
 int x = ::recv(s, buffer, size, options);
 if (!x)
   throw OIP_SocketException(OIP_SocketException::erecv, GetErrorCode());
 return x;
}

int OIP_Socket::GetErrorCode()
{
 return(::sock_errno());
}


OIP_Socket::OIP_SocketException::OIP_SocketException(excepttyp typ,
                                                     int errorvalue)
   : OException((PSZ)NULL, 0, OException::unrecoverable)
{
 etyp  = typ;
 value = errorvalue;
 rc    = value;  
 description << OIP::error(etyp);
}


OIP_Socket::OIP_SocketException::~OIP_SocketException()
  {}


PSZ OIP_Socket::OIP_SocketException::isOfType() const
{
 return("OIP_Socket::OIP_SocketException");
}


void OIP_Socket::OIP_SocketException::viewError()
{
 cout << description.getText() << "rc = " << rc << endl;
}


// end of source
