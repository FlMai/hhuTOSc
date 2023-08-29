#include "user/demo/LoopThread.h"
#include "kernel/Globals.h"

void LoopThread::run () {
   while (true) {
      cpu.disable_int();
      kout.setpos(15*this->tid,15);
      kout << "[" << this->tid << "] : " << this->counter << endl;
      cpu.enable_int();
      this->counter = this->counter + 1;
   }
}