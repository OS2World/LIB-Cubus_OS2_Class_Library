// OCL - OS/2 Class Library
// (c) Cubus 1996
// All Rights Reserved
// OIP.cpp

// this is the OIP Version Logo

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

// $Header: W:/Projects/OCL/Source/rcs/OIP.cpp 1.50 1996/08/11 23:49:17 B.STEIN Release $


#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <oip.hpp>
#include <OMessage.hpp>


OString OIP::transport;
OString OIP::MSGFILE("OIP0001.MSG");


OString& OIP::Version()
{
 return(OIP::Version(OIP::transport));
}


OString& OIP::Version(OString& str)
{
 OMessage copyright(OIP_COPYRIGHT, "OIP0001.MSG");

#ifdef __BCPLUSPLUS__
   OMessage compiler(OIP_BORLAND, "OIP0001.MSG");
#elif __WATCOM_CPLUSPLUS__
   OMessage compiler(OIP_WATCOM, "OIP0001.MSG");
#elif ((__IBMCPP__) && (__IBMCPP__ == 300))
   OMessage compiler(OIP_VA, "OIP0001.MSG");
#elif __IBMCPP__
   OMessage compiler(OIP_CSET, "OIP0001.MSG");
#elif __HIGHC__
   OMessage compiler(OIP_METAWARE, "OIP0001.MSG");
#elif __EMX__
   OMessage compiler(OIP_EMX, "OIP0001.MSG");
#endif  
 
 str << OMessage(OIP_VER_MSG, "OIP0001.MSG", compiler, copyright).getText();
 return(str);
}


OString& OIP::error(ULONG x)
{
 return(OIP::transport << OMessage(x, "OIP0001.MSG").getText());
}


OString& OIP::apierror(ULONG x, APIRET rc)
{
 OString apimessage(OMessage((ULONG)rc).getText());
 
 return(OIP::transport << OMessage(x, "OIP0001.MSG", apimessage.getText()).getText());
}


// end of source
