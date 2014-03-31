// ITTest.cpp

// $Header: W:/Projects/OCL/Samples/Iterators/Source/rcs/ITTest.cpp 1.50 1996/08/11 23:48:27 B.STEIN Release $

#define __OCL_RESOLVE_TEMPLATES__

#define OINCL_BASE
#include <ocl.hpp>

#include <lOString.hpp>
#include <OConstIterator.hpp>
#include <OIterator.hpp>

#if defined(__EMX__)
  template class OConstIterator<OString>;
  template class OIterator<OString>;
#endif


class printableList 
  : public lOString
{
 private:

   class _printer
     : public OConstIterator<OString>   
   {
    public:
      void applyToElement(const OString* elem) const;
   }; 

   class _editor
     : public OIterator<OString>   
   {
    public:
      void applyToElement(OString* elem);
   }; 

   _printer            printTool;
   _editor             editTool;

 public:
       printableList   () {}

   virtual
      ~printableList   () {}

   inline void
      print            () { allElementsDo(printTool); }

   inline void
      edit             () { allElementsDo(editTool); }
};



void main(void)
{
 OString       a("A"),
               b("B"),
               c("C"),
               d("D"),
               e("E");

 printableList list;

 list << a;
 list << b;
 list << c;
 list << d;
 list << e;
 
 list.print();
 list.edit();
 list.print();

 _exit(0);
} 



void printableList::_printer::applyToElement(const OString* elem) const
{
 if (elem)
   cout << elem->getText() << endl;
}

void printableList::_editor::applyToElement(OString* elem)
{
 if (elem)
   *elem + *elem;
}


// end of source
