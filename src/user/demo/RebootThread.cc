#include "user/demo/RebootThread.h"
#include "kernel/Globals.h"
#include "lib/Input.h"

void RebootThread::run () {
    while(true) {
        char k = getch();
        if( k == 'r') kb.reboot();
    }
}