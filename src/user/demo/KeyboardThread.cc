#include "user/demo/KeyboardThread.h"
#include "kernel/Globals.h"
#include "lib/Input.h"

void KeyboardThread::run () {
    while(true) {
        char k = getch();
        if( k == 'q' || k == 'e' || k == 'w' || k == 'a' || k == 's' || k == 'd') {
            *shared_mem = k;
        }
    }
}