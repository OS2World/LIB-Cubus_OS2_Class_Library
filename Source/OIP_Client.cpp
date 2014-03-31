// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// All Rights Reserved
// OIP_Client.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OIP_Client.cpp 1.50 1996/08/11 23:49:18 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_Client.hpp>
#include <OMessage.hpp>


OIP_Client::OIP_Client()
  : port(0),
    active(FALSE)
  {}  


OIP_Client::~OIP_Client()
{
 if (active)
   terminate();
}

PSZ OIP_Client::isOfType() const
{
 return("OIP_Client");
} 


OIP_Client& OIP_Client::init()
{
 client.sysinit(1 | (1 << 8));
 client.socket();
 return(*this);
}


OIP_Client& OIP_Client::terminate()
{
 client.close();
 client.sysfree();
 return(*this);
}  


OIP_Client& OIP_Client::connect(PSZ name, USHORT _port)
{
 BOOL      nameIsIP = FALSE;
 OString   address(20); 
 OString   hname(CCHMAXPATH);
 
 port = _port;
 
 try  // assume name to be a host name
  { 
   client.Gethostbyname(name);
   client.Set_sin_addr();
   client.Setin_port(port);
   client.Get_inet_addr(address);
   servername    << name;
   serveraddress << address;   
  }
 catch(OIP_Socket::OIP_SocketException ex)
  {
   if (ex.etyp == OIP_Socket::OIP_SocketException::egethostbyname)
     nameIsIP = TRUE;
   else
     throw ex;
  }

 if (nameIsIP) // assume name to be IP address
  {
   try
    {
     client.Set_sin_addr(name);
     client.Setin_port(port);
     client.Gethostname(hname.getText(), CCHMAXPATH); 
     servername    << hname;
     serveraddress << name;   
    }
   catch(OIP_Socket::OIP_SocketException ex)
    {
     ex.etyp = OIP_Socket::OIP_SocketException::egethostbyaddr;
     throw ex;
    }
  }
  
 client.connect();
 active = TRUE;
 return(*this);
}
  
OIP_Client& OIP_Client::connectMsg()
{
 cout << OIP::error(21).getText();
 cout << " "
      << servername.getText()
      << " "
      << serveraddress.getText()
      << " Port: "
      << client.Getin_port()
      << endl;
 return(*this);
}


OIP_Client& OIP_Client::disconnect()
{
 return(terminate());
}


OIP_Client& OIP_Client::disconnectMsg()
{
 cout << OIP::error(23).getText();
 cout << " "
      << servername.getText()
      << " "
      << serveraddress.getText()
      << endl;

 return(*this);
}


OIP_Client& OIP_Client::send(PVOID data, ULONG size)
{
 client.send((PSZ)data, size);
 return(*this);
}

OIP_Client& OIP_Client::sendSuccess()
{
 return(send("OK", 3));
}

   
OIP_Client& OIP_Client::sendEnd()
{
 return(send("END", 4));
}
   

OIP_Client& OIP_Client::recv(PVOID data, ULONG size)
{
 client.recv((PSZ)data, size);
 return(*this);
}


// end of source
 