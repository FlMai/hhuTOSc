#include "user/demo/SoundDemo.h"
#include "kernel/Globals.h"

void SoundDemo::run () {
   while (true) {
      pcspk.tetris();
   }
}