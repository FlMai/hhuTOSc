#include "lib/Queue.h"
#include "kernel/Globals.h"

/*****************************************************************************
*                                                                           *
*                              Q U E U E                                    *
*                                                                           *
*---------------------------------------------------------------------------*
* Beschreibung:    Implementierung einer einfach verketteten Liste von      *
*                  Chain Objekten. Die Implementierung ist etwas trickreich *
*                  'tail' verweist naemlich nicht, wie oft ueblich, auf das *
*                  letzte Element der Liste, sondern auf den 'next' Zeiger  *
*                  des letzten Elements, bzw., solange die Liste noch leer  *
*                  ist, auf den 'head' Zeiger der Liste. Dadurch muss beim  *
*                  Anfuegen eines Elements an die Liste nicht ueberprueft   *
*                  werden, ob bereits Elemente in ihr enthalten sind. Beim  *
*                  Entfernen von Elementen kann auf die Fallunterscheidung  *
*                  allerdings nicht verzichtet werden.                      *
*                                                                           *
* Autor:           Olaf Spinczyk, TU Dortmund                               *
*****************************************************************************/

void Queue::remove(Chain *item) {
    Chain *ptr = this->head;
    if (ptr == 0x0) {
        return;
    }
    
    while (ptr->next != 0x0) {
        if (ptr->next == item) {
            ptr->next = item->next;
        }
        ptr = ptr->next;
    }
}

void Queue::enqueue(Chain *item) {
    *(this->tail) = item;       
    this->tail = &(item->next);
}

Chain* Queue::dequeue() {
    if (this->head == 0x0) {
        kout << "OS PANIC: dequeing from empty readQue!" << endl;
        cpu.die();
    }
    if (this->head->next == 0x0) {
        Chain *tmp = this->head;
        this->head = 0x0;
        this->tail = &this->head;
        tmp->next = 0x0;
        return tmp; 
    } else {
        Chain *tmp = this->head;
        this->head = this->head->next;
        tmp->next = 0x0;
        return tmp;
    }
    kout << "OS PANIC: dequeing in ambigous state of readyQue!" << endl;
    cpu.die();
}