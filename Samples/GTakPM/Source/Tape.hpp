// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMApp.hpp

//  $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/Tape.hpp 1.50 1996/08/11 23:48:13 B.STEIN Release $

#ifndef TAPE_HPP_INCLUDED
  #define TAPE_HPP_INCLUDED


#ifndef GTAKPM_HPP_INCLUDED
  #include "..\Source\GTakPM.hpp"
#endif


typedef class Tape            *pTape;


class Tape 
{
 protected:
   pOPMPipeTool tool;

   ULONG        bsize;
   OString      device;

 public:
     Tape      (pOPMPipeTool currentTool, 
                PSZ TapeDescription,  
                ULONG tape_blocksize);

   virtual
     ~Tape();

   virtual  
      PSZ isOfType () const 
      { return("Tape"); }

   void
      prepare   (),
      blocksize (ULONG size = 0),
      status    (),
      load      (),
      unload    (),
      rewind    (),
      part      (OString& command), 
      format    (),
      erase     (),
      eraseq    (),
      lock      (),
      unlock    (),
      batch     (PSZ batchfile);
};

#endif // TAPE_HPP_INCLUDED

// end of source
