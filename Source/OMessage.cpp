// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMessage.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OMessage.cpp 1.50 1996/08/11 23:49:23 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OMessage.hpp>



OMessage::OMessage()
   : message(OCL_MAXMESSAGE),
     msglen(0) 
   {}



OMessage::OMessage(ULONG msgId,
                   PSZ   msgFileName,
                   PSZ   textInsert1,
                   PSZ   textInsert2,
                   PSZ   textInsert3,
                   PSZ   textInsert4,
                   PSZ   textInsert5,
                   PSZ   textInsert6,
                   PSZ   textInsert7,
                   PSZ   textInsert8,
                   PSZ   textInsert9)
   : message(OCL_MAXMESSAGE),
     msglen(0) 
{
 retrieve(msgId, msgFileName,
          textInsert1, textInsert2, textInsert3, textInsert4, textInsert5,
          textInsert6, textInsert7, textInsert8, textInsert9);
};


OMessage& OMessage::retrieve(ULONG msgId,
                    PSZ   msgFileName,
                    PSZ   textInsert1,
                    PSZ   textInsert2,
                    PSZ   textInsert3,
                    PSZ   textInsert4,
                    PSZ   textInsert5,
                    PSZ   textInsert6,
                    PSZ   textInsert7,
                    PSZ   textInsert8,
                    PSZ   textInsert9)
{
 APIRET rc = 0;
 ULONG  count = 0;
 PSZ    insertTable[9] = { 0 };

 if (!msgFileName)
   throw OVioException("No message file specified.", OException::unrecoverable);

 if (textInsert1)
  {
   count++;
   insertTable[0] = (PSZ)textInsert1;
   if (textInsert2)
    {
     count++;
     insertTable[1] = (PSZ)textInsert2;
     if (textInsert3)
      {
       count++;
       insertTable[2] = (PSZ)textInsert3;
       if (textInsert4)
        {
         count++;
         insertTable[3] = (PSZ)textInsert4;
         if (textInsert5)
          {
           count++;
           insertTable[4] = (PSZ)textInsert5;
           if (textInsert6)
            {
             count++;
             insertTable[5] = (PSZ)textInsert6;
             if (textInsert7)
              {
               count++;
               insertTable[6] = (PSZ)textInsert7;
               if (textInsert8)
                {
                 count++;
                 insertTable[7] = (PSZ)textInsert8;
                 if (textInsert9)
                  {
                   count++;
                   insertTable[8] = (PSZ)textInsert9;
                  }
                }
              }
            }
          }
        }
      }
    }
  }


 rc = DosGetMessage(insertTable,
                    count,
                    message.getText(),
                    OCL_MAXMESSAGE,
                    msgId,
                    (PSZ)msgFileName,
                    &msglen);

 if (rc != 0)
   throw OVioException("Cannot load message.\n", rc, OException::unrecoverable);
 
 message.getText()[msglen] = '\0';
 message.replace("\r\n", "\n");
 return(*this);
}


OMessage::~OMessage()
 {}



PSZ OMessage::isOfType() const
{
 return("OMessage");
}



PSZ OMessage::getText()
{
 return(message.getText());
}



ULONG OMessage::getLen()
{
 return(msglen);
}



PSZ OMessage::getMessage(ULONG msgId,
                         PSZ   msgFileName,
                         PSZ   textInsert1,
                         PSZ   textInsert2,
                         PSZ   textInsert3,
                         PSZ   textInsert4,
                         PSZ   textInsert5,
                         PSZ   textInsert6,
                         PSZ   textInsert7,
                         PSZ   textInsert8,
                         PSZ   textInsert9)
{
 retrieve(msgId, msgFileName,
          textInsert1, textInsert2, textInsert3, textInsert4, textInsert5,
          textInsert6, textInsert7, textInsert8, textInsert9);
 return(message.getText());
};



ostream& operator <<   (ostream& out, pOMessage s)
{
 if (s)
   out << s->getText();
 return(out);
}


// end of source
