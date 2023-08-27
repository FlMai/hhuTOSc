
#ifndef __coopthreaddemo_include__
#define __coopthreaddemo_include__


class CoopThreadDemo : public Thread {
    
private:
    CoopThreadDemo (const CoopThreadDemo &copy); // Verhindere Kopieren

public:
    CoopThreadDemo () { }

    void run ();

 };

#endif