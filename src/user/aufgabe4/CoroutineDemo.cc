/*****************************************************************************
 *                                                                           *
 *                      C O R O U T I N E D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstieg in eine Anwendung.                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe4/CoroutineDemo.h"
#include "user/aufgabe4/CoroutineLoop.h"

/*****************************************************************************
 * Methode:         CoroutineDemo::main                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    main-Methode der Anwendung.                              *
 *****************************************************************************/
void CoroutineDemo::main () {

    /* 
     * Hier muss Code eingefuegt werden 
     *
     * Die 3 Koroutinen einrichten, verketten und die 1. starten
     *
     */
    CoroutineLoop *c1 = new CoroutineLoop(1);
    CoroutineLoop *c2 = new CoroutineLoop(2);
    CoroutineLoop *c3 = new CoroutineLoop(3);
    c1->setNext(c2);
    c2->setNext(c3);
    c3->setNext(c1);
    c1->start();

}
