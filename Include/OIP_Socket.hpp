// OCL - OS/2 Class Library
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// OIP_Socket.hpp

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


// $Header: W:/Projects/OCL/Include/rcs/OIP_Socket.hpp 1.50 1996/08/11 23:47:17 B.STEIN Release $


#ifndef OIP_SOCKET_INCLUDED
   #define OIP_SOCKET_INCLUDED

#ifndef OEXCEPTION_INCLUDED
   #include <OException.hpp>
#endif

#ifndef OIP_SOCKADDRESS_INCLUDED
   #include <OIP_SockAddress.hpp>
#endif

#ifndef OIP_HOST_INCLUDED
   #include <OIP_Host.hpp>
#endif


typedef class OIP_Socket* pOIP_Socket;


class __CPP_EXPORT__ OIP_Socket
  : public OCLObject
{
 protected:
     OIP_SockAddress  sockadd;
     OIP_Host         *phost;
     int              s;

 public:

    class OIP_SocketException
      : public OException
      {
       public:
         enum  excepttyp
          {
           esocket        = 10,
           elisten        = 11,
           ebind          = 12,
           esend          = 13,
           erecv          = 14,
           econnect       = 15,
           egethostbyname = 16,
           egethostbyaddr = 17
          };

         excepttyp etyp;
         int       value;

         OIP_SocketException     (excepttyp typ,
                                  int errorvalue);

         virtual 
            ~OIP_SocketException ();

         virtual
            PSZ isOfType         () const;

         virtual
            void viewError       ();

      };

   OIP_Socket        ();

   OIP_Socket        (phostent p);

   virtual
     ~OIP_Socket     ();

   virtual
     PSZ isOfType    () const;

   virtual int
     sysinit         (USHORT version),
     sysfree         ();

   int
     Set_socket      (int sock),
     Get_socket      (),
     close           (),
     Gethostname     (PSZ hostname, UINT size);


   pOIP_Host
     Gethostbyaddr   (PSZ hostaddress, int type = PF_INET),
     Gethostbyname   (PSZ hostname),
     Get_phost       (),
     Sethostent      (phostent phost);

   pservent
     Getservbyname   (PSZ, PSZ);

   USHORT
     Getin_port      ();

   void
     Setin_port      (USHORT port);

   ULONG
     Set_sin_addr    (),
     Set_sin_addr    (ULONG addr),
     Set_sin_addr    (PSZ target),
     Get_sin_addr    (),
     Getaddr_list    (UINT index = 0);

   BOOL
     Set_address     (USHORT port, PSZ target);

   short
     Set_sin_family  (short family = AF_INET),
     Get_sin_family  ();

   int
     socket          (int net = AF_INET, int typ = SOCK_STREAM, int x = 0),
     send            (PSZ buffer, int size, int options = 0),
     recv            (PSZ buffer, int size, int options = 0),
     GetErrorCode    (),
     setsockopt      (int, int, PSZ, int),
     recvfrom        (PSZ, int, int, psockaddr, PINT),
     sendto          (PSZ, int, int, psockaddr, int);

   void
     Get_inet_addr   (PSZ adress);

   psockaddr
     Get_sockaddr    ();

// operators

   operator =                (int handle);
   operator int              ();
   operator OIP_SockAddress  ();
   operator pOIP_SockAddress ();
};

#endif	// OIP_SOCKET

