#include "user/aufgabe4/LoopThread.h"
#include "kernel/Globals.h"

void LoopThread::run () {
   while (true) {
      kout.setpos(15*this->tid,12);
      kout << "[" << this->tid << "] : " << this->counter << endl;
      this->counter = this->counter + 1;
      scheduler.yield();
   }
}