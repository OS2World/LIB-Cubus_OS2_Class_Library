// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPicture.hpp


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


// $Header: W:/Projects/OCL/Include/rcs/OPicture.hpp 1.50 1996/08/11 23:47:25 B.STEIN Release $

#ifndef OPICTURE_INCLUDED
  #define OPICTURE_INCLUDED


typedef class OPicture *pOPicture;


class __CPP_EXPORT__ OPicture
  : public OCLObject
{
 public:
   ULONG          width;
   ULONG          height;

   OPicture       (ULONG CX,   // width
                   ULONG CY);  // height

   virtual
     ~OPicture    ();

   virtual
     PSZ isOfType () const; 

   void
     setDimension (ULONG Width, ULONG Height);  // required for OGraphicsButton using a bitmap 
};



#endif // OPICTURE_INCLUDED


// end of source
