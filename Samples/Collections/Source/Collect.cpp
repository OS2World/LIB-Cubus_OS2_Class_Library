#define INCL_BASE
#define __OCL_RESOLVE_TEMPLATES__

#include <ocl.hpp>
#include <OString.hpp>
#include <OStack.hpp>
#include <OQueue.hpp>

#if defined(__EMX__)
  template class OStack<OString>;
  template class OQueue<OString>;
#endif


void main(void)
{
 OStack<OString> strStack;
 OQueue<OString> strQueue;
 OString         a("First");
 OString         b("Second");
 OString         c("Third");
 OString         d("Fourth");
 pOString        temp = NULL;

 cout << "Sample Collect"
      << endl
      << (PSZ) OCL::Version()
      << endl;

 strQueue.put(a);
 strQueue.put(b);
 strQueue.put(c);
 strQueue.put(d);

 cout << strQueue.numberOfElements();
 cout << " elements in queue.";
 cout << endl;

 while((temp = strQueue.get()) != NULL)
  {
   cout << temp->getText();
   cout << endl; 
   strStack.push(temp);
  }

 cout << strStack.numberOfElements();
 cout << " elements on stack.";
 cout << endl;

 while((temp = strStack.pop()) != NULL)
  {
   cout << temp->getText();
   cout << endl; 
  }

 cout << strStack.numberOfElements();
 cout << " elements on stack.";
 cout << endl;
 cout << strQueue.numberOfElements();
 cout << " elements in queue.";
 cout << endl;

 _exit(0);
} 