// OCL Sample 

// Listbox.hpp

#include <ocl.hpp>
#include <OApp.hpp>
#include <OFrame.hpp>
#include <OListbox.hpp>
#include <OPMException.hpp>

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
