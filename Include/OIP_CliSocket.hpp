// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_CliSocket.hpp

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

// $Header: W:/Projects/OCL/Include/rcs/OIP_CliSocket.hpp 1.50 1996/08/11 23:47:16 B.STEIN Release $


#ifndef OIP_CLISOCKET_INCLUDED
   #define OIP_CLISOCKET_INCLUDED

#ifndef OIP_SOCKET_INCLUDED
   #include <OIP_Socket.hpp>
#endif


typedef class OIP_CliSocket *pOIP_CliSocket;


class __CPP_EXPORT__ OIP_CliSocket
  : public OIP_Socket
{
public:

    OIP_CliSocket     ();

    virtual
       ~OIP_CliSocket ();

    virtual
       PSZ isOfType   () const;

    int 
       connect        (),
       connect        (pOIP_Socket server);

};

#endif	// OIP_CLISOCKET_INCLUDED

