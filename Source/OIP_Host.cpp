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

// $Header: W:/Projects/OCL/Source/rcs/OIP_Host.cpp 1.50 1996/08/11 23:49:19 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OIP_Host.hpp>


OIP_Host::OIP_Host()
 {}

OIP_Host::~OIP_Host()
 {}


PSZ OIP_Host::isOfType () const
{
 return("OIP_Host");
} 


OIP_Host::operator PSZ()
{
 return(h_data.h_name);
}


pOIP_Host OIP_Host::Set(phostent p)
{
 if (p)
  {
   h_data.h_name      = p->h_name;
   h_data.h_aliases   = p->h_aliases;
   h_data.h_addrtype  = p->h_addrtype;
   h_data.h_length    = p->h_length;
   h_data.h_addr_list = p->h_addr_list;
  }
 return(this);
}


pOIP_Host OIP_Host::gethostbyaddr(PSZ addr, int x, int net)
{
 return Set(::gethostbyaddr(addr, x, net));
}


pOIP_Host OIP_Host::gethostbyname(PSZ name)
{
 return Set(::gethostbyname(name));
}

// end of source
