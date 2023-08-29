#ifndef __keyboardthread_include__
#define __keyboardthread_include__

#include "kernel/threads/Thread.h"

class KeyboardThread : public Thread {
    
private:
    KeyboardThread (const KeyboardThread &copy); // Verhindere Kopieren
    uint8_t *shared_mem;
public:
    KeyboardThread (uint8_t *shared_mem) {
        this->shared_mem = shared_mem;
    }
    void run ();
};

#endif