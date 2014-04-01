// OCL Sample OValueSet


#include <ocl.hpp>
#include <OApp.hpp>
#include <ODialog.hpp>
#include <OMsgs.hpp>
#include <OValueSet.hpp>
#include <OLogo.hpp>
#include <OPMException.hpp>

#include "..\Source\Value.h"


typedef class ValueSample *pValueSample;

class ValueSample 
  : public OApp, 
    public ODialog
{
 private:
   OValueSet VSet;
   OLogo     logo;

 public:

   ValueSample();
   ~ValueSample();

   virtual PSZ isOfType() const;

   void init();

   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
