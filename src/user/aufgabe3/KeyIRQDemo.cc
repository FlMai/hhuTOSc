/*****************************************************************************
 *                                                                           *
 *                         K E Y I R Q D E M O                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo zu Interrupts.                                      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void key_irq_demo() {

   /* Hier muss Code eingefuegt werden */
   kout.clear();
   while(1){
      kout.setpos(10,10);
      kout << "0" << endl;
      kout.setpos(10,11);
      kout << "1" << endl;
      kout.setpos(10,12);
      kout << "2" << endl;
      kout.setpos(10,13);
      kout << "3" << endl;
      kout.setpos(10,14);
      kout << "4" << endl;
      kout.setpos(10,15);
      kout << "5" << endl;
      kout.setpos(10,16);
      kout << "6" << endl;
      kout.setpos(10,17);
      kout << "7" << endl;
      kout.setpos(10,18);
      kout << "8" << endl;
      kout.setpos(10,19);
      kout << "9" << endl;
   }
}
