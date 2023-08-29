#ifndef __scrollthread_include__
#define __scrollthread_include__

#include "kernel/threads/Thread.h"

class ScrollThread : public Thread {
    
private:
    ScrollThread (const ScrollThread &copy); // Verhindere Kopieren
    uint8_t *shared_mem;
public:
    ScrollThread (uint8_t *shared_mem) {
        this->shared_mem = shared_mem;
    }
    void run ();
};

#endif