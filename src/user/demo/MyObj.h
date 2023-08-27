#ifndef __MyObj_include__
#define __MyObj_include__

#include "lib/Types.h"

class MyObj {
    public:
        int64_t number1;
        int64_t number2;

    MyObj(int x = 0, int y = 0) {
        number1 = x;
        number2 = y;
    }

    int64_t add();
};

#endif