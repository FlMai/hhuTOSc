/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/demo/HeapDemo.h"
#include "user/demo/MyObj.h"
#include "lib/Input.h"

void heap_demo() {
    
    int a = 0;
    while ( true ) {
        kout.clear();
        kout << "Heap allocation and free demo." << endl;
        MyObj *testObj1 = new MyObj();
        MyObj *testObj2 = new MyObj();
        MyObj *testObj3 = new MyObj();
        MyObj *testObj4 = new MyObj();
        MyObj *testObj5 = new MyObj();
        if (testObj1 == NULL || testObj2 == NULL || testObj3 == NULL || testObj4 == NULL || testObj5 == NULL) break;
        kout.setpos(60,5);
        kout << "#Allocations:" << a << endl;
        
        delete testObj2;
        delete testObj4;
        kout.setpos(0,3);
        allocator.dump_free_memory();
        
        while(true) {
            char k = getch();
            if (k == 'r') kb.reboot();
            if (k == '\n') break;
        }
        delete testObj3;
        allocator.dump_free_memory();
        
        a++;
        while(true) {
            char k = getch();
            if (k == 'r') kb.reboot();
            if (k == '\n') break;
        }    
    }
    while(true) {
        char k = getch();
        if (k == 'r') kb.reboot();
    } 
}
