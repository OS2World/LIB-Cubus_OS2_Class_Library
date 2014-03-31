// language.hpp

#include <ocl.hpp>
#include <OXApp.hpp>
#include <ODialog.hpp>
#include <ODynamicLib.hpp>
#include <OListBox.hpp>
#include <OPMException.hpp>
#include <OMessage.hpp>

#include "..\Source\res.h"


class Language
   : public OXApp 
{
 protected:
   ODynamicLib     *reslib;

 public:

      enum lang
       {
        english = 0,
        german  = 1
       };
   

      Language     ();

 virtual
      ~Language    ();

 virtual
   PSZ  isOfType   () const { return("Language"); }


 Language
       &selectLang (),
       &showDialog ();

 static
   Language::lang  language;  
};


class SelectDlg
   : public ODialog 
{
 protected:
   OListBox        box;

 public:
   
      SelectDlg    ();   

 virtual
      ~SelectDlg   () {}

 virtual
   PSZ  isOfType   () const { return("SelectDlg"); }

   BOOL OCommand   (ULONG msg, MPARAM mp1, MPARAM mp2); 
};



class LanguageDlg
   : public ODialog 
{
 public:
   
      LanguageDlg     (HMODULE mod);   

 virtual
      ~LanguageDlg    () {}

 virtual
   PSZ  isOfType      () const { return("LanguageDlg"); }

   BOOL OCommand      (ULONG msg, MPARAM mp1, MPARAM mp2); 
};


// end of source
