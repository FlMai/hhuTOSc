#include "user/demo/ScrollThread.h"
#include "kernel/Globals.h"
#include "lib/Input.h"

void ScrollThread::run () {
    bool flip_flop = true;

    while(true) {   // all 500ms send signal to tetris thread
        uint64_t start = systime;
        while(true) {
            cpu.pause();
            uint64_t now = systime;
            if ((start + (75)) < now) break;
        }
        if (flip_flop) {
            *shared_mem = 'a';
            flip_flop = false;
        } else {
            *shared_mem = 'b';
            flip_flop = true;
        }
    }
}