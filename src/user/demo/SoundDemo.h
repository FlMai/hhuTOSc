#ifndef __sounddemo_include__
#define __sounddemo_include__

#include "kernel/threads/Thread.h"

class SoundDemo : public Thread {
    
private:
    SoundDemo (const SoundDemo &copy); // Verhindere Kopieren
    
public:
    SoundDemo () {}
    void run ();
};

#endif
