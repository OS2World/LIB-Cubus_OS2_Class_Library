// OCL Sample 
// Critics.cpp

#define __OCL_RESOLVE_TEMPLATES__
#include "..\Source\critics.hpp"

#if defined(__EMX__)
  template class OThread<Thread>;
#endif

USHORT         row;

void main(void)
{
 USHORT         col;   
 Thread         first  ("First   :", 1);
 Thread         second ("Second  :", 2);
 Thread         third  ("Third   :", 3);
 CriticalThread master (4);

 cout << "\n\n\n" << endl;
 VioGetCurPos(&row, &col, 0);
 row -= 4;

 try 
   {
    first.paint.run();
    DosSleep(1000); 
    second.paint.run();
    DosSleep(1000); 
    third.paint.run();
    DosSleep(1000); 
    master.paint.run();

    // wait for all threads
    master.paint.waitFor();
    first.paint.waitFor();
    second.paint.waitFor();
    third.paint.waitFor();
   }
 catch(OVioException& err)
   {
    err.viewError();
   }
 _exit(0);
}


// class implementation Thread

Thread::Thread(PSZ name, USHORT threadRow)
  : paint(this, &Thread::paintfunc, USHRT_MAX, FALSE),
    threadName(name),
    line(threadRow),   
    count(0)
  {}

Thread::~Thread()
  {}
  
PSZ Thread::isOfType() const
{
 return("Thread");
}

void Thread::paintfunc()
{
 for(ULONG i = 0; i < 11; i++)
  {
   CHAR  str[40];
 
   sprintf(str, "%s %ld ticks.", threadName, i);
   VioWrtCharStr(str, strlen(str), row + line, 0, 0);
   DosSleep(1000);
  }
}


// class implementation CriticalThread

CriticalThread::CriticalThread(USHORT threadRow)
  : Thread("Critical:", threadRow) 
  {}

CriticalThread::~CriticalThread()
  {}
   
PSZ CriticalThread::isOfType() const
{
 return("CriticalThread");
}

void CriticalThread::paintfunc()
{
 critical.enter();
 Thread::paintfunc();
 critical.exit();
}


// end of source 
