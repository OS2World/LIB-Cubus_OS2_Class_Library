// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OLogo.hpp


// program information logo

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

// $Header: W:/Projects/OCL/Include/rcs/OLogo.hpp 1.50 1996/08/11 23:47:20 B.STEIN Release $

#ifndef OLOGO_INCLUDED
  #define OLOGO_INCLUDED

#ifndef OSTRING_INCLUDED
  #include <OString.hpp>
#endif

#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif

#ifndef OBITMAP_INCLUDED
  #include <OBitmap.hpp>
#endif

#ifndef OPMEXCEPTION_INCLUDED
  #include <OPMException.hpp>
#endif

typedef class OLogo *pOLogo;


class __CPP_EXPORT__ OLogo
  : public OFrame 
{
 protected:
   OString          bmpfile;
   OBitmap          *bmp;
   HMODULE          mod;
   POINTL           dest;

 public:

   OLogo            (const HMODULE module,
                     const ULONG bitmapID, 
                     const ULONG cx, 
                     const ULONG cy);

   OLogo            (const PSZ filename,
                     const ULONG frameID,
                     const ULONG cx,
                     const ULONG cy);

   virtual
      ~OLogo        ();

   virtual
      PSZ isOfType  () const;

   OLogo&
      showLogo      (const ULONG timeout = 0);         // show until destruction

   virtual 
      BOOL OCommand (ULONG msg, MPARAM mp1, MPARAM mp2);
};
 

#endif // OLOGO_INCLUDED

// end of source
