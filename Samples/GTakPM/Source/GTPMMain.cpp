// GTakPM
// (c) Benjamin Stein 1994
// All Rights Reserved
// GTPMMain.cpp

// $Header: W:/Projects/OCL/Samples/GTakPM/Source/rcs/GTPMMain.cpp 1.50 1996/08/11 23:48:08 B.STEIN Release $

#define __OCL_RESOLVE_TEMPLATES__

#include "..\Source\GTakPM.hpp"


#ifdef __EMX__
  template class OList<DirItem>;
  template class OContainer<DirInfo, RECORDCORE>;
  template class OContainer<FileInfo, MINIRECORDCORE>;
  template class OThread<FilesCnr>;
  template class OThread<DrivesCnr>;
  template class OThread<GTPMApp>;
  template class OThread<GTPMWin>;
#endif



void main(int argc, char *argv[])
{
 GTPMApp       *app;
 OXCPTRECORD   exceptionRecord;
 SystemHandler except;

 except.setHandler(exceptionRecord); // set system exception handler

 try
  {
   app = new GTPMApp(argc, argv); 
  }

 catch(OPMException ex)
  {
   except.unsetHandler();           // release system exception handler
   _exit(ex.rc); 
  }

 catch(...) 
  {
   except.unsetHandler();           // release system exception handler
   _exit(1); 
  }

 OApp::current().run();

 delete app;

 except.unsetHandler();             // release system exception handler

 _exit(0);
}

// end of source
