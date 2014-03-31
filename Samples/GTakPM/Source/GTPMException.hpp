// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMException.hpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMException.hpp 1.50 1996/08/11 23:48:07 B.STEIN Release $

#ifndef GTPMEXCEPTION_HPP_INCLUDED
  #define GTPMEXCEPTION_HPP_INCLUDED


#ifndef GTAKPM_HPP_INCLUDED
  #include "..\Source\GTakPM.hpp"
#endif



class GTPMException : public OPMException
{
 public:
      GTPMException  (const ULONG errResource,
                      const ULONG severity = OException::recoverable);
   virtual
      ~GTPMException ();

   virtual  
      PSZ isOfType   () const 
      { return("GTPMException"); }
};

#define throwGTPM(x) (throw GTPMException(x))


class SystemHandler : public OXcptPM
{
 public:
     SystemHandler   ();

   virtual
     ~SystemHandler  ();

   virtual  
      PSZ isOfType   () const 
      { return("SystemHandler"); }

   BOOL killTrace    ();
   BOOL trapTrace    ();
};

#endif // GTPMEXCEPTION_HPP_INCLUDED

// end of source
