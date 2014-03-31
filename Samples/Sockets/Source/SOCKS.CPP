// OCL - OS/2 Class Library (Samples)
// (c) Cubus 1996
// (c) 1982, 1985, 1986 Regents of the University of California.
// (c) Raoul Gema 1996
// All Rights Reserved
// SOCKS.CPP

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

// $Header: W:/Projects/OCL/Samples/Sockets/Source/rcs/SOCKS.CPP 1.50 1996/08/11 23:48:54 B.STEIN Release $

#include <ocl.hpp>
#include <OIP_Server.hpp>
#include <OMessage.hpp>
#include <OXcptVio.hpp>

#define LOGO		"CT.NET++ Mini-Server"
#define FILENAME	"DEMO.TXT"


class SystemHandler
  : public OXcptVio
{
 public:
     SystemHandler   ();

   virtual
     ~SystemHandler  ();

   virtual  
      PSZ isOfType   () const; 
   BOOL killTrace    ();
   BOOL trapTrace    ();
};



int main(int argc, char* argv[])
{
 OXCPTRECORD   exceptionRecord;
 SystemHandler except;
 OIP_Server    server;
 int           ok;

 cout << LOGO
      << endl
      << OIP::Version().getText()
      << endl;


 if (argc != 2)
  {
   cout << "Usage: SOCKS Portnummer" << endl;
   exit(1);
  }

 except.setHandler(exceptionRecord); // set system exception handler

 try
  {
   server.init((USHORT)atoi(argv[1]));

   for (;;)
    {
     server.waitForClient().connectMsg();

     try
      {
       char data[1024];
       sprintf(data, "%s\n%s", LOGO, OIP::Version().getText());
       server.send(data, strlen(data) + 1);  // Logo senden
       server.recv(data, sizeof(data));      // empfangen
       cout << "Received: "
            << data
            << endl; 

       switch (data[0]) {
         case '+': {
           ofstream file(FILENAME,	ios::out | ios::ate);
           if (file) {
             file << (char*)(data + 2) << endl;
             strcpy(data, "OK"); }
           else
             strcpy(data, "Internal error saving data.");
          file.close();
          break; }

        case '=': {
          ifstream file(FILENAME, ios::in | ios::nocreate);
          if (!file)
            sprintf(data, "No information available.");
          else
            file.get(data, sizeof(data), '\0');
          file.close();
          break; }

        case '?': {
          ifstream file(FILENAME, ios::in | ios::nocreate);
          if (!file)
            sprintf(data, "No information available.");
          else {
            char line[256];
            int found = 0;
            while (!found) {
              file.get(line, sizeof(line), '\n');
              if (file.eof()) break;
              file.get();
              if (!strcmp(data + 2, line))
              found++; }
            strcpy(data, (found) ?	"OK" : "Requested string not found."); }
		file.close();
          break; }

        default:
         sprintf(data, "Unknown command."); }

       server.send(data, strlen(data) + 1);	//* Antwort senden
       cout << "Sent    : " 
            << data
            << endl; 
       server.disconnect().disconnectMsg();
      }

     catch (OException& e)
      {
       e.viewError();
      }

     ok = 0;
    }
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

 except.unsetHandler();           // release system exception handler

 return ok;
}



SystemHandler::SystemHandler()
 : OXcptVio(FALSE)
 {}

SystemHandler::~SystemHandler()
 {}

PSZ SystemHandler::isOfType   () const 
{
 return("SystemHandler");
}

BOOL SystemHandler::killTrace()
{
 cout << endl << "Terminating " << LOGO << endl;
 return(FALSE); 
}


BOOL SystemHandler::trapTrace()
{
 return(FALSE);  // show exception message and abort
}

// end of source
