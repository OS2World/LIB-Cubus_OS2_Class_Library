// OCL Sample 

// Listbox.hpp

#define OINCL_OSTRING
#define OINCL_OAPP
#define OINCL_OFRAME
#define OINCL_OLISTBOX
#define OINCL_OPMEXCEPTION

#include <ocl.hpp>


#include "..\Source\Listbox.h"


typedef class BoxSample *pBoxSample;

class BoxSample 
   : public OApp, 
     public OFrame
{
 private:
   OListBox *box;

 public:

   BoxSample();
   ~BoxSample();

   virtual PSZ isOfType() const { return("BoxSample"); }
   void init();
   void run();

   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


typedef class LBException *pLBException;

class LBException 
   : public OException
{
 public:
   LBException();
   ~LBException();

   virtual PSZ isOfType() const { return("LBException"); }
   void viewError();
};


// end of source
