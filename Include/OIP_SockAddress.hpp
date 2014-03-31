// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_SockAddress.hpp

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


// $Header: W:/Projects/OCL/Include/rcs/OIP_SockAddress.hpp 1.50 1996/08/11 23:47:17 B.STEIN Release $



#ifndef OIP_SOCKADDRESS_INCLUDED
   #define OIP_SOCKADDRESS_INCLUDED

#ifndef OIP_INCLUDED
   #include <OIP.hpp>
#endif



typedef class OIP_SockAddress* pOIP_SockAddress;

class __CPP_EXPORT__ OIP_SockAddress
  : public OCLObject
{
 protected:
    sockaddr_in             data;

 public:
    OIP_SockAddress         ();

    virtual
      ~OIP_SockAddress      ();

    virtual
      PSZ isOfType          () const;

    operator sockaddr_in    ();
    operator psockaddr_in   ();

    USHORT
      Setin_port            (USHORT port),
      Getin_port            ();

    ULONG
      Set_sin_addr          (ULONG addr = INADDR_ANY),
      Set_sin_addr          (PSZ target),
      Get_sin_addr          ();

    PSZ
      Get_in_addr           ();

    short
      Set_sin_family        (short family = AF_INET),
      Get_sin_family        ();

    void
      Get_inet_addr         (PSZ adress);

    psockaddr_in
      Get_sockaddr_in       ();
};


#endif	// OIP_SOCKADDRESS_INCLUDED

