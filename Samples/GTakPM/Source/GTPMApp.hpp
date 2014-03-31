// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMApp.hpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMApp.hpp 1.50 1996/08/11 23:48:07 B.STEIN Release $

#ifndef GTPMAPP_HPP_INCLUDED
  #define GTPMAPP_HPP_INCLUDED


#ifndef GTAKPM_HPP_INCLUDED
  #include "..\Source\GTakPM.hpp"
#endif


class GTPMApp : public OXApp
{
 private:
   OThread<GTPMApp> waitThread;

 public:

   GTPMApp          (const ULONG num,
                     CHAR *parms[]);   
   virtual
     ~GTPMApp       ();

   virtual  
      PSZ isOfType  () const 
      { return("GTPMApp"); }

   void
     initArgs       (PCSZ argStr),
     wait           ();

   BOOL
     TasklistKill   (),    // trap task list kills
     ShutdownPosted ();    // trap shutdown message
 
// static

   static pGTPMApp GTakPM;
};



#endif // GTPMAPP_HPP_INCLUDED

// end of source
