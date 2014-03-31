// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OMessage.hpp


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


// $Header: W:/Projects/OCL/Include/rcs/OMessage.hpp 1.50 1996/08/11 23:47:22 B.STEIN Release $

#ifndef OMESSAGE_INCLUDED
  #define OMESSAGE_INCLUDED


#ifndef OMESSAGE_H_INCLUDED
  #include <OMessage.h>
#endif

#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif


#define OCL_MAXMESSAGE  512


// classes


typedef class OMessage *pOMessage;


class __CPP_EXPORT__ OMessage
  : public OCLObject
{
 private:
   OString          message;
   ULONG            msglen;

   OMessage&
      retrieve      (ULONG,
                     PSZ, PSZ, PSZ, PSZ, PSZ,
                     PSZ, PSZ, PSZ, PSZ, PSZ);
 public:

   OMessage            ();
 
   OMessage            (ULONG msgId,
                        PSZ   msgFileName = "OSO001.MSG",
                        PSZ   textInsert1 = NULL,
                        PSZ   textInsert2 = NULL,
                        PSZ   textInsert3 = NULL,
                        PSZ   textInsert4 = NULL,
                        PSZ   textInsert5 = NULL,
                        PSZ   textInsert6 = NULL,
                        PSZ   textInsert7 = NULL,
                        PSZ   textInsert8 = NULL,
                        PSZ   textInsert9 = NULL);


   virtual
      ~OMessage        ();

   virtual
      PSZ isOfType     () const; 


      ULONG getLen     ();
      PSZ   getText    ();
      PSZ   getMessage (ULONG msgId,
                        PSZ   msgFileName = "OSO001.MSG",
                        PSZ   textInsert1 = NULL,
                        PSZ   textInsert2 = NULL,
                        PSZ   textInsert3 = NULL,
                        PSZ   textInsert4 = NULL,
                        PSZ   textInsert5 = NULL,
                        PSZ   textInsert6 = NULL,
                        PSZ   textInsert7 = NULL,
                        PSZ   textInsert8 = NULL,
                        PSZ   textInsert9 = NULL);

   friend ostream
      &operator <<  (ostream& out, pOMessage s);

   inline
      operator PSZ     () const { return(message.getText()); }

};


#endif // OMESSAGE_INCLUDED


// end of source
