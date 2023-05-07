#ifndef __MyObj_include__
#define __MyObj_include__

#include "lib/Types.h"

class MyObj {
    public:
        int64_t number1;
        int64_t number2;

    MyObj() {
        number1 = 0;
        number2 = 0;
    }

    int64_t add();
};

#endif