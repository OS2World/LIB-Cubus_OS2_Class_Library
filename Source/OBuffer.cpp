// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OBuffer.cpp

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

// $Header: W:/Projects/OCL/Source/rcs/OBuffer.cpp 1.50 1996/08/11 23:49:08 B.STEIN Release $

#define __OCL_SOURCE__

#define OINCL_OSTRING
#define OINCL_BASE

#include <ocl.hpp>
#include <OBuffer.hpp>
#include <OMessage.hpp>

OBuffer::OBuffer(const ULONG sizeInBytes,
                 const ULONG flags)
  : memPtr    (NULL),
    memSize   (sizeInBytes),
    allocSize (0)
{
 APIRET rc;

 if ((flags & OBuffer::TILED) &&
     (sizeInBytes > OBuffer::TILESIZE))
   throw OVioException(OCL::error(20), 0);

 if (memSize < OBuffer::PAGESIZE)
   throw OVioException(OCL::error(21), 0);

 if (flags & OBuffer::COMMIT)
   allocSize = memSize;
 
 rc = DosAllocMem((PPVOID) &memPtr,
                  memSize,
                  flags);
 if (rc != 0) 
   throw OVioException(OMessage(rc, "OSO001.MSG", OCL::error(22)), rc);
}


OBuffer::~OBuffer()
{
 freeBuffer();
}


void OBuffer::commit(const ULONG sizeInBytes)
{
 APIRET rc = 0;

 if (!memPtr)
   throw OVioException("OBuffer, invalid object.", 0, OException::fatal);

 if (sizeInBytes < OBuffer::PAGESIZE)
   throw OVioException("At least OBuffer::PAGESIZE must be requested.", 0);

 if ((sizeInBytes + allocSize) > memSize)
   throw OVioException("OBuffer is smaller than requested commit.", 0);

 rc = DosSetMem(memPtr, sizeInBytes, OBuffer::COMMIT | OBuffer::DEFAULT);

 if (rc != 0) 
   throw OVioException("DosSetMem failed.", rc);

 allocSize += sizeInBytes;
}



void OBuffer::decommit(const ULONG sizeInBytes)
{
 APIRET rc = 0;

 if (!memPtr)
   throw OVioException("OBuffer, invalid object.", 0, OException::fatal);

 if (sizeInBytes < OBuffer::PAGESIZE)
   throw OVioException("At least OBuffer::PAGESIZE must be requested.", 0);

 if (sizeInBytes > allocSize)
   throw OVioException("OBuffer is smaller than requested decommit.", 0);

 rc = DosSetMem(memPtr, sizeInBytes, OBuffer::DECOMMIT);

 if (rc != 0) 
   throw OVioException("DosSetMem failed.", rc);

 allocSize -= sizeInBytes;
}


void OBuffer::freeBuffer()
{
 APIRET rc = 0;

 if (memPtr != NULL)
   rc = DosFreeMem(memPtr);

 if (rc != 0)
   throw OVioException("DosFreeMem failed.", rc);
}
  

ULONG OBuffer::allocated()
{
 return(memSize);
}


ULONG OBuffer::committed()
{
 return(allocSize);
}


PBYTE OBuffer::getPtr()
{
 return(memPtr);
}


PSZ OBuffer::isOfType() const 
{
 return("OBuffer");
}


// end of source
