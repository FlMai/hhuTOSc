
#ifndef __musicthread_include__
#define __musicthread_include__

#include "kernel/threads/Thread.h"

class MusicThread : public Thread {
    
private:
    int counter = 0;

    MusicThread (const MusicThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    MusicThread () {}

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif