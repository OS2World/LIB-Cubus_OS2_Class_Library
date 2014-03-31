// OCL - OS/2 Class Library (Samples)
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// SOCKC.CPP

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

// $Header: W:/Projects/OCL/Samples/Sockets/Source/rcs/SOCKC.CPP 1.50 1996/08/11 23:48:53 B.STEIN Release $


#include <ocl.hpp>
#include <OIP_Client.hpp>
#include <OMessage.hpp>

#define LOGO	"CT.NET++ Mini-Client"


void usage()
{
 cout <<   "Usage: SOCKC hostname port kommando [text]" << endl 
      << "Command: '='       - show text"               << endl
      << "         '+' text  - add text"                << endl
      << "         '?' text  - search in text"          << endl;
 _exit(1);
}

int main(int argc, char *argv[])
{
 OIP_Client  client;
 int         ok;

 cout << LOGO
      << endl
      << OIP::Version().getText()
      << endl;


 if (argc < 4)
   usage();

 char command = argv[3][0];
 char* pcommandtext = "";

 switch (command)
  {
   case '=':
     break;
   case '+':
   case '?':
    {
     if (argc > 4) {
       pcommandtext = argv[4];
       break; }
    }
   default:
     usage();
  }

 try
  {
   OString  data(CCHMAXPATH);

   client.init();
   client.connect(argv[1], (USHORT)atoi(argv[2])).connectMsg();

   client.recv(data, CCHMAXPATH);
   cout << "Received: "
        << data.getText()
        << endl; 
   sprintf(data, "%c %s", command, pcommandtext);
   client.send(data.getText(), data.length() + 1);
   cout << "Sent    : "
        << data.getText()
        << endl;
   client.recv(data, CCHMAXPATH);
   cout << "Received: "
        << data.getText()
        << endl; 
   ok = 0;
  }

 catch (OException& e)
  {
   e.viewError(); 
   ok = -1;
  }

 catch (...)
  {
   printf(OIP::error(9));
   ok = -1;
  }

 return ok;
}

// end of source
