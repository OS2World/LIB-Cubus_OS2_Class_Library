// dragsamp.hpp

// $Header: W:/Projects/OCL/Samples/DragSamp/Source/rcs/dragsamp.hpp 1.50 1996/08/11 23:47:58 B.STEIN Release $

#include <ocl.hpp>
#include <OApp.hpp>
#include <ODialog.hpp>
#include <ODragEntryField.hpp>

#include "..\Source\dragsamp.h"


extern "C" void main(void);


class DragSamp
  : virtual public OApp,
    virtual public ODialog
{
 private:
    ODragEntryField odf_a;
    ODragEntryField odf_b;
    ODragEntryField odf_c;

 public:
    DragSamp();
    virtual ~DragSamp();

    BOOL OCommand(ULONG msg, MPARAM mp1, MPARAM mp2);
};


// end of source
