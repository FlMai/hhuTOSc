#ifndef __rebootthread_include__
#define __rebootthread_include__

#include "kernel/threads/Thread.h"

class RebootThread : public Thread {
    
private:
    RebootThread (const RebootThread &copy); // Verhindere Kopieren
    
public:
    RebootThread () {}
    void run ();
};

#endif