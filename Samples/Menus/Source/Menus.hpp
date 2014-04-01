// OCL Sample 
// Menus.hpp


#include <ocl.hpp>
#include <oxapp.hpp>
#include <omenu.hpp>

#include "..\Source\Menus.h"


typedef class MenuSample *pMenuSample;

class MenuSample 
   : public OFrame
{
 protected:
   OXApp    app;

 public:
   pOMenu menu;

   MenuSample();
   ~MenuSample(); 
   
   virtual PSZ isOfType() const { return("MenuSample"); }   
   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
