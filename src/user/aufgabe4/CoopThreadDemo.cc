#include "kernel/Globals.h"
#include "user/aufgabe4/CoopThreadDemo.h"
#include "user/aufgabe4/LoopThread.h"


void CoopThreadDemo::run () {

    LoopThread *t1 = new LoopThread;
    LoopThread *t2 = new LoopThread;
    LoopThread *t3 = new LoopThread;

    scheduler.ready(t1);
    scheduler.ready(t2);
    scheduler.ready(t3);


    for (int i = 0; i < 1000; i++){
        scheduler.yield();
    }
    scheduler.kill(t2);
    scheduler.exit();

}
