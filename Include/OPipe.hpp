// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OPipe.hpp

// Unnamed streamable pipes

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

// $Header: W:/Projects/OCL/Include/rcs/OPipe.hpp 1.50 1996/08/11 23:47:25 B.STEIN Release $

#ifndef OPIPE_INCLUDED
 #define OPIPE_INCLUDED

#if ((!defined (__fstream_h)) && (!defined (__FSTREAM_H)))
  #include <fstream.h>
#endif


#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif


typedef class OPipe_streamable *pOPipe_streamable;
typedef OPipe_streamable OPipe;
typedef OPipe *pOPipe;

typedef class OPipe_istream *pOPipe_istream;
typedef OPipe_istream OIPipe;
typedef OIPipe *pOIPipe;

typedef class OPipe_ostream *pOPipe_ostream;
typedef OPipe_ostream OOPipe;
typedef OOPipe *pOOPipe;

typedef class OPipe_iostream *pOPipe_iostream;
typedef OPipe_iostream OIOPipe;
typedef OIOPipe *pOIOPipe;



class __CPP_EXPORT__ OPipe_streamable
  : public OCLObject
{
 private:
   BOOL                 wasCreator;

   void
     closePipe          ();

 public:
   HFILE                ifh;
   HFILE                ofh;

   OPipe_streamable     ();
   OPipe_streamable     (ULONG storage);
   OPipe_streamable     (pOPipe_streamable pipe);
   OPipe_streamable     (OPipe_streamable& pipe);
   OPipe_streamable     (HFILE in, HFILE out);

   virtual
      ~OPipe_streamable (); // the pipe is destroyed only when
                            // the object was created using 
                            // OPipe_streamable(ULONG storage)
   virtual
      PSZ isOfType      () const;
};


class __CPP_EXPORT__ OPipe_istream 
  : public OPipe_streamable, 
    public ifstream
{
 public:
   OPipe_istream     (ULONG storage = USHRT_MAX);
   OPipe_istream     (pOPipe_streamable pipe);
   OPipe_istream     (OPipe_streamable& pipe);
 
   virtual
      ~OPipe_istream (); // the pipe is destroyed only when
                         // the object was created using 
                         // OPipe_istream(ULONG storage)
   virtual 
      PSZ isOfType   () const;
};


class __CPP_EXPORT__ OPipe_ostream 
  : public OPipe_streamable, 
    public ofstream
{
 public:
   OPipe_ostream     (ULONG storage = USHRT_MAX);
   OPipe_ostream     (pOPipe_streamable pipe);
   OPipe_ostream     (OPipe_streamable& pipe);
 
   virtual
      ~OPipe_ostream (); // the pipe is destroyed only when
                         // the object was created using 
                         // OPipe_ostream(ULONG storage)
   virtual
      PSZ isOfType   () const;
};


#endif // OPIPE_INCLUDED

// end of source
