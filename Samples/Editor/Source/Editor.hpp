// OCL Sample 

// Editor.hpp

#include <ocl.hpp>
#include <OFrame.hpp>
#include <OEditor.hpp>
#include <OPMException.hpp>

#include "..\Source\Editor.h"

typedef class Editor *pEditor;

class Editor 
  : public OApp, 
    public OFrame
{
 public:
   OEditor    *textfield; 

   Editor();
   ~Editor(); 

   virtual PSZ isOfType() const;

   BOOL TasklistKill();

   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};



// end of source
