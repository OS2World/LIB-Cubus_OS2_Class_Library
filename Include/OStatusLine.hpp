// OCL - OS/2 Class Library
// (c) Cubus 1995
// All Rights Reserved
// OStatusLine.hpp

// frame window status line

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

// $Header: W:/Projects/OCL/Include/rcs/OStatusLine.hpp 1.50 1996/08/11 23:47:31 B.STEIN Release $

#ifndef STATUSLINE_INCLUDED
  #define STATUSLINE_INCLUDED


#ifndef OFRAME_INCLUDED
  #include <OFrame.hpp>
#endif

typedef class OStatusLine *pOStatusLine;

class __CPP_EXPORT__ OStatusLine
   : public OFrame
{
 protected:
    OStatusLine&
       initStatlineDefaults ();

 private:
    OString              statlineText;
    BOOL                 readOnly;
    BOOL                 ddStyle;
    ULONG                orientation;

 public:

    OStatusLine         (const ULONG id,
                         const HWND Parent,
                         const BOOL DDStyle = FALSE); // 3D-Look

    OStatusLine         (const ULONG id,
                         const OFrame& Parent,
                         const BOOL DDStyle = FALSE); // 3D-Look

    OStatusLine         (const ULONG id,
                         const pOFrame Parent,
                         const BOOL DDStyle = FALSE); // 3D-Look
 
    virtual
       ~OStatusLine     ();

    virtual
       PSZ isOfType     () const;

    OStatusLine&
       createStatusLine ();

    ULONG
       getHeight        (),
       getWidth         ();

    OStatusLine
       &refreshText     (),
       &setText         (PCSZ text),
       &setOrientation  (const ULONG Orientation),
       &setRDOnly       (BOOL readonly);

    virtual BOOL
       OCommand         (ULONG msg, MPARAM mp1, MPARAM m2);
};



#endif // STATUSLINE_INCLUDED


// end of source
