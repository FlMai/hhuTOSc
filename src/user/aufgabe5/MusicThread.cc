#include "user/aufgabe5/MusicThread.h"
#include "kernel/Globals.h"

void MusicThread::run () {
   while (true) {
      pcspk.tetris();
   }
}