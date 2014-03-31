// OCL Sample 
// Procstat.hpp

#define OINCL_OSTRING
#define OINCL_OXAPP
#define OINCL_OFRAME
#define OINCL_OCONTAINER
#define OINCL_OPMEXCEPTION
#define OINCL_OPROCSTAT

#include <ocl.hpp>


#include "..\Source\procstat.h"


class PContainer
  : public OContainer<MINIRECORDCORE, MINIRECORDCORE>,
    public OProcStat
{
 private:
   HPOINTER hptr;

 public:
   PContainer(pOFrame Parent);
   virtual ~PContainer();

   virtual PSZ isOfType() const { return("PContainer"); }

   BOOL setupDetails();
   BOOL setupItems();
   BOOL insertChilds(PMINIRECORDCORE parentRecord, ULONG ulParent);
};




typedef class Procstat *pProcstat;

class Procstat 
  : public OFrame
{
 private:
   OXApp      app;
   PContainer *cnr;

 public:

   Procstat();
   ~Procstat();

   virtual PSZ isOfType() const { return("Procstat"); }

   void init();
   BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
