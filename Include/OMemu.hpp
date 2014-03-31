// OCL - OS/2 Class Library
// (c) Cubus 1995
// (c) Glenn Brew, Cook, Benjamin Stein 1995
// All Rights Reserved
// OMemu.hpp


// This class uses OS20MEMU.DLL
// written by Glenn Brew and Ross Cook (IBM EWS).
// If this library or its device driver OS20MEMU.SYS
// are not available the constructor of OMemu will fail.


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
 
// $Header: W:/Projects/OCL/Include/rcs/OMemu.hpp 1.50 1996/08/11 23:47:21 B.STEIN Release $

#ifndef OMEMU_INCLUDED
  #define OMEMU_INCLUDED


#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef ODYNAMICLIB_INCLUDED
  #include <ODynamicLib.hpp>
#endif

#ifndef OLIST_INCLUDED
  #include <OList.hpp>
#endif

#ifndef OMEMU_H_INCLUDED
  #include <OMemu.h>
#endif



class __CPP_EXPORT__ OMemu
 : public os20memu_general_info,
   public OList<gi_process_data_s>

{
 private:
   ODynamicLib         *memu_library;
   PMEMU_GGI           EP_get_general_info;
   PMEMU_GPI           EP_get_process_info;   

 public:
   OMemu               ();

   virtual
      ~OMemu           ();

   virtual
      PSZ isOfType     () const; 

   BOOL
      querySystem      (),    // query general info and process list
      queryGeneralInfo ();    // query only general info

   static ULONG
     makeKByte         (ULONG pages);
};


#endif // OMEMU_INCLUDED


// end of source
