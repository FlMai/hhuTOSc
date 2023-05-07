/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"

#define HEAP_MIN_FREE_BLOCK_SIZE 64         // min. Groesse eines freien Blocks


/*****************************************************************************
 * Methode:         LinkedListAllocator::init                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liste der Freispeicherbloecke intitialisieren.           *
 *                  Anker zeigt auf ein Dummy-Element. Danach folgt          *
 *                  ein Block der den gesamten freien Speicher umfasst.      *
 *                                                                           *
 *                  Wird automatisch aufgerufen, sobald eine Funktion der    *
 *                  Speicherverwaltung erstmalig gerufen wird.               *
 *****************************************************************************/
void LinkedListAllocator::init() {

     initialized = true;
     struct free_block *tmp = (struct free_block *) Allocator::heap_start;
     tmp->size = Allocator::heap_size;
     tmp->next = NULL;
     free_start = tmp;

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {

     if (!initialized) {
          init();
     }

     free_block *ptr = free_start;
     
     int number_of_blocks = 0;
     uint64_t free_memory = 0;

     kout << "Walking memory chain:" << endl;

     while (ptr != NULL) {
          kout << ptr->size << " bytes free at " << ptr << "                             " << endl;

          number_of_blocks++;
          free_memory += ptr->size;

          ptr = ptr->next;
     }

     kout << "Number of free blocks: " << number_of_blocks << ", total free memory: " << free_memory << "." << endl << endl; 


}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(uint64_t req_size) {

          if (!initialized) {
          init();
     }

     if (free_start == NULL) {
          int x,y;
          kout.getpos(x,y);
          kout.setpos(0,24);
          kout << "No memory to allocate, free some space or search for memory leaks.";
          kout.flush();
          kout.setpos(x,y);
          return NULL;
     }

     free_block *ptr = free_start;
     free_block *prv = NULL;
     while (ptr != NULL) { 
          if (ptr->size >= req_size + sizeof(uintptr_t)) {
               // Watchout for case new obj fits only if we use last block (no new free_block entry, set free_start = NULL wait for free)
               // Watch out for cases where we cant spawn a new block in gerenal (prev->next = ptr -> next)

               unsigned int free_mem = ptr->size;
               struct free_block *next_block = ptr->next;

               uintptr_t *ret_size = (uintptr_t *)ptr;
               *ret_size = req_size + sizeof(uintptr_t);
               unsigned char *ret_ptr = ((unsigned char *)ptr) + sizeof(uintptr_t);


               // Construct new block of free memory
               struct free_block *new_block = NULL;
               if (free_mem - req_size - sizeof(uintptr_t) > sizeof(free_block)) {
                    new_block = (struct free_block *)(((unsigned char *)ptr) + req_size + sizeof(uintptr_t));
                    new_block->next = next_block;
                    new_block->size = free_mem - req_size - sizeof(uintptr_t);   
               } 

               if (new_block != NULL && prv != NULL) {
                    prv->next = new_block;
               } else if (new_block == NULL && prv != NULL) {
                    prv->next = next_block;
               } else if (new_block == NULL && prv == NULL && next_block != NULL) {
                    free_start = next_block;
               } else if (new_block != NULL && prv == NULL){
                    free_start = new_block;
               } else  if (new_block == NULL && prv == NULL && next_block == NULL) {
                    free_start = NULL;
               } else {
                    int x,y;
                    kout.getpos(x,y);
                    kout.setpos(0,24);
                    kout << "KERNEL PANIC: Memory allocation error.";
                    kout.flush();
                    kout.setpos(x,y);
                    return NULL;
               }

               return ret_ptr;
          } else{
               prv = ptr;
               ptr = ptr->next;
          }
     }

     kout << "Not enough remaining memory in a single block." << endl;
     return NULL;   

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {

     if (!initialized) {
          kout << "Heap not initialized, there isnt anything to free, use alloc (new) first." << endl;
          init();
          return;
     }
     if (ptr > (uint8_t*)(Allocator::heap_start + Allocator::heap_end) || ptr < (uint8_t*)Allocator::heap_start) {
          kout << "Cant free whats not on the heap, you pointer is outside the heap range!" << endl;
          return;
     }

     uint64_t free_size = *(((uintptr_t *)ptr) - 1);

     struct free_block *s = free_start;

     struct free_block *new_block = (struct free_block *)((uint8_t*)ptr - sizeof(uintptr_t));
     new_block->next = NULL;
     new_block->size = free_size;

     if ( s == NULL ) {
          free_start = new_block;
     } else if (s > new_block) {
          new_block->next = s;
          free_start = new_block;   
     } else {
          while (true) {
               if (s->next > new_block || s->next == NULL) {
                    new_block->next = s->next;
                    s->next = new_block;
                    break;
               }
               s = s->next;
          }
     }

     s = free_start;
     while (s != NULL) {
          bool cont = false;
          if ((uint8_t*)s + s->size == (uint8_t*)s->next) {
               s->size = s->size + s->next->size;
               s->next = s->next->next;
               cont = true;
          }
          if (!cont) s = s->next;
     }   
}

