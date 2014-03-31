// OCL Sample OValueSet


#define OINCL_OSTRING
#define OINCL_OAPP
#define OINCL_ODIALOG
#define OINCL_OMSGS
#define OINCL_OVALUESET
#define OINCL_OLOGO
#define OINCL_OPMEXCEPTION

#include <ocl.hpp>
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
