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
#include "user/aufgabe2/HeapDemo.h"
#include "user/aufgabe2/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
// void waitForReturn() {

//     /* hier muss Code eingefuegt werden */
//     // while(1) {
//     //     char k = kb.key_hit().ascii();
//     //     if (k == '\n') break;
//     //     kout.print(&k, 1, 0x0f);
//     // }

// }


void heap_demo() {

    kout.clear();

    allocator.dump_free_memory();

    int a = 1;
    int counter = 0;
    while ( true ) {
        switch (counter)
        {
        case 0:
            kout.show(79,24, '|', 0x0f);
            break;
        case 1:
            kout.show(79,24, '/', 0x0f);

            break;   
        case 2:
            kout.show(79,24, '-', 0x0f);
            break;
        case 3:
            kout.show(79,24, '\\', 0x0f);
            counter = -1;
            break;          
        default:
            break;
        }
        counter++;
        MyObj *testObj1 = new MyObj();
        MyObj *testObj2 = new MyObj();
        MyObj *testObj3 = new MyObj();
        if (testObj1 == NULL || testObj2 == NULL || testObj3 == NULL) break;
        delete testObj2;
        kout.setpos(0,0);
        allocator.dump_free_memory();
        kout.setpos(60,0);
        kout << "#Allocations:" << a << endl;
        a++;
    }
    kout.setpos(30,10);
    allocator.dump_free_memory();
    allocator.init();
}
