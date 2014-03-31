// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// All Rights Reserved
// OIP_Server.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OIP_Server.cpp 1.50 1996/08/11 23:49:19 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_Server.hpp>
#include <OMessage.hpp>


OIP_Server::OIP_Server()
  : port(0),
    active(FALSE)
  {}

  
OIP_Server::~OIP_Server()
{
 if (active)
    terminate();
}


PSZ OIP_Server::isOfType() const
{
 return("OIP_Server");
} 


OIP_Server& OIP_Server::init(USHORT _port)
{
 port = _port;
 server.sysinit(1 | (1 << 8));             // TCP/IP Init
 server.socket();                          // create Socket
 server.Setin_port(port); // set Port
 server.Set_sin_addr(INADDR_ANY);          // IP-Adresse
 server.bind();                            // binden
 server.listen();                          // Bereitschaft
 active = TRUE;
 return(*this);
}


OIP_Server& OIP_Server::terminate()
{
 client.close();
 server.close();
 server.sysfree();
 active = FALSE;
 return(*this);
}


OIP_Server& OIP_Server::waitForClient()
{
 server.accept(&client);

 if ((INT)client == -1)
   throw OVioException(OIP::error(17), 1);

 return(*this);
}
  

OIP_Server& OIP_Server::connectMsg()
{
 OString  clientadress(20);

 client.Get_inet_addr(clientadress);
 cout << OIP::error(18).getText()
      << " "
      << clientadress.getText()
      << " ";
 cout << OIP::error(19).getText()
      << " "
      << client.Getin_port()
      << " ["
      << (int)client
      << "]"
      << endl;  
 return(*this);
}

  
OIP_Server& OIP_Server::disconnect()
{
 client.close();
 return(*this);
}


OIP_Server& OIP_Server::disconnectMsg()
{
 OString  clientadress(20);

 client.Get_inet_addr(clientadress);
 cout << OIP::error(20).getText()
      << " "
      << clientadress.getText()
      << " ";
 cout << OIP::error(19).getText()
      << " "
      << client.Getin_port()
      << " ["
      << (int)client
      << "]"
      << endl;  
 return(*this);
}


OIP_Server& OIP_Server::send(PVOID data, ULONG size)
{
 client.send((PSZ)data, size);
 return(*this);
}


OIP_Server& OIP_Server::sendSuccess()
{
 return(send("OK", 3));
}
   


OIP_Server& OIP_Server::sendEnd()
{
 return(send("END", 4));
}


   
OIP_Server& OIP_Server::recv(PVOID data, ULONG size)
{
 client.recv((PSZ)data, size);
 return(*this);
}

// end of source
