/*****************************************************************************
 *                                                                           *
 *                       C O R O U T I N E L O O P                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Loop ist eine Koroutine, die nichts weiter tut als einen *
 *                  Zaehler hochzuzaehlen und diesen auf dem Bildschirm      *
 *                  anzuzeigen und dann auf die naechste Korotuine umzu-     *
 *                  schalten.				 	 	 	           			 *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "user/aufgabe4/CoroutineLoop.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         CoroutineLoop::run                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion der Koroutine.                         *
 *****************************************************************************/
void CoroutineLoop::run () {

   /* Hier muss Code eingefuegt werden */
   while (true) {
      kout.setpos(20*this->id,12);
      kout << "[" << this->id << "] : " << this->counter << endl;
      this->counter = this->counter + 1;
      this->switch2next();
   }
}
