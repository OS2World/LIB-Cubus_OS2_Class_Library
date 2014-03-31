// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_Client.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OIP_Client.hpp 1.50 1996/08/11 23:47:16 B.STEIN Release $


#ifndef OIP_CLIENT_INCLUDED
   #define OIP_CLIENT_INCLUDED

#ifndef OIP_CLISOCKET_INCLUDED
   #include <OIP_CliSocket.hpp>
#endif

#ifndef OIP_SRVSOCKET_INCLUDED
   #include <OIP_SrvSocket.hpp>
#endif


typedef class OIP_Client *pOIP_Client;


class __CPP_EXPORT__ OIP_Client
  : public OCLObject
{
 protected:
    BOOL                active;
    USHORT              port;
    OIP_CliSocket	client;
    OString             serveraddress;
    OString             servername;

 public:

       OIP_Client       ();
  
    virtual
       ~OIP_Client      ();

    virtual PSZ
       isOfType         () const; 

    OIP_Client
       &init            (),
       &terminate       (),  
       &connect         (PSZ name, USHORT _port),  
       &connectMsg      (),  
       &disconnect      (),
       &disconnectMsg   (),
       &send            (PVOID data, ULONG size),
       &sendSuccess     (),   
       &sendEnd         (),   
       &recv            (PVOID data, ULONG size);
};


#endif // OIP_CLIENT_INCLUDED

// end of source
