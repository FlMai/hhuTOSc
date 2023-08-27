
#ifndef __loopthread_include__
#define __loopthread_include__

#include "kernel/threads/Thread.h"

class LoopThread : public Thread {
    
private:
    int counter = 0;

    LoopThread (const LoopThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    LoopThread () {}

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif