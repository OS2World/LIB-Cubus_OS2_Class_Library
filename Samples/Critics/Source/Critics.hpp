// OCL Sample
// Critics.hpp

#define INCL_VIO

#include <ocl.hpp>
#include <OCriticalSec.hpp>
#include <OThread.hpp>


typedef class Thread *pThread;


class Thread 
  : virtual public OCLObject
{
 protected: 
   PSZ     threadName;
   ULONG   count;
   USHORT  line;

 public:
   OThread<Thread> paint;

   Thread(PSZ name, USHORT threadRow);
   virtual ~Thread();
   
   virtual PSZ isOfType() const;
   virtual void paintfunc();
};


typedef class CriticalThread *pCriticalThread;


class CriticalThread 
  : public Thread
{
 private:
   OCriticalSec critical;

 public:
   CriticalThread(USHORT threadRow);
   virtual ~CriticalThread();
   
   virtual PSZ isOfType() const;
   virtual void paintfunc();
};

// end of source 
