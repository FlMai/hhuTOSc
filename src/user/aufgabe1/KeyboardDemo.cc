/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void keyboard_demo() {

    while(1) {
        char k = kb.key_hit().ascii();
        if (k == '\n') break;
        kout.print(&k, 1, 0x0f);
    }
}
