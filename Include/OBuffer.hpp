// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OBuffer.hpp


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


// $Header: W:/Projects/OCL/INCLUDE/rcs/OBuffer.hpp 1.1 1996/08/12 00:01:10 B.STEIN Release $

#ifndef OBUFFER_INCLUDED
  #define OBUFFER_INCLUDED


#ifndef OCLOBJECT_INCLUDED
  #include <OCLObject.hpp>
#endif

#ifndef OVIOEXCEPTION_INCLUDED
  #include <OVioException.hpp>
#endif


typedef class OBuffer *pOBuffer;


class __CPP_EXPORT__ OBuffer
  : public OCLObject
{
 protected:

     PBYTE       memPtr;
     ULONG       memSize;
     ULONG       allocSize;

 public:

     enum MemoryFlags
       {
        ALLOC    = PAG_READ | PAG_WRITE | PAG_COMMIT,
        DEFAULT  = PAG_DEFAULT,
        READ     = PAG_READ,
        WRITE    = PAG_WRITE,
        COMMIT   = PAG_COMMIT,
        DECOMMIT = PAG_DECOMMIT,
        GUARD    = PAG_GUARD,
        EXECUTE  = PAG_EXECUTE,
        TILED    = OBJ_TILE
       };
     
     enum MemorySizes
       {
        PAGESIZE = 4096,
        MAXPATH  = CCHMAXPATH,
        MOSTFIT  = 262144,
        TILESIZE = 65536     
       };

     OBuffer      (const ULONG sizeInBytes,
                   const ULONG flags = OBuffer::ALLOC);
   virtual
     ~OBuffer     ();

   virtual
     PSZ isOfType () const; 

   void
     commit       (const ULONG sizeInBytes),
     decommit     (const ULONG sizeInBytes),
     freeBuffer   ();

   ULONG
     allocated    (),
     committed    ();

   PBYTE
     getPtr       ();
 
   inline operator PBYTE () const { return(memPtr); }
};



#endif // OBUFFER_INCLUDED


// end of source
