/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"


/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {

     allocations = 0;
     next = (unsigned char *)Allocator::heap_start;

}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
     kout << "Number of allocations: " << allocations << endl;

     kout << "Heap pointer at: " << next << endl;

     kout << "Free Memory: " << (heap_end - (uint64_t)next) <<  " byte(s)." << endl << endl;
}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(uint64_t req_size) {

     /* Hier muess Code eingefuegt werden */

     if (uint64_t(next + req_size) <= heap_end) {
          unsigned char * ret = next;
          allocations = allocations + 1;
          next = next + req_size;
          return ret;
     }
     kout << "Requested memory for object is to large." << endl;
     return NULL;
}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (uint64_t)ptr << ", not supported" << endl;
}

