/*****************************************************************************
 *                                                                           *
 *                            A L L O C A T O R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung. 'new' und 'delete' werden   *
 *                  durch Ueberladen der entsprechenden Operatoren           *
 *                  realisiert.                                              *
 *                                                                           *
 *        Heap:                                                              *
 *                    0x400000:	Start-Adresse der Heap-Verwaltung            *
 *                    0x4FFFFF: Ende: Letzte Adresse des phys. Speichers     *
 *                                                                           *
 * Achtung:         Benötigt einen PC mit mindestens 5 MB RAM!               *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.5.2022                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"


#define MEM_SIZE_DEF        	 8*1024*1024 // Groesse des Speichers = 8 MB

#define HEAP_START           	 0x400000 	// Startadresse des Heaps
#define HEAP_SIZE	        	 2*1024*1024 	// Default-Groesse des Heaps, falls 
											// nicht über das BIOS ermittelbar 

/*****************************************************************************
 * Konstruktor:     Allocator::Allocator                                     *
 *****************************************************************************/
Allocator::Allocator() {
   // Groesse des Hauptspeichers (kann über das BIOS abgefragt werden,
   // aber sehr umstaendlich, daher hier fest eingetragen
   total_mem = MEM_SIZE_DEF;

   heap_start = HEAP_START;
   heap_end   = HEAP_START + HEAP_SIZE;
   heap_size  = HEAP_SIZE;
}


/*****************************************************************************
 * Nachfolgend sind die Operatoren von C++, die wir hier ueberschreiben      *
 * und entsprechend 'mm_alloc' und 'mm_free' aufrufen.                       *
 *****************************************************************************/
void* operator new ( size_t size ) {
    cpu.disable_int();
    void* ret = allocator.alloc(size);
    cpu.enable_int();
    return ret;
}

void operator delete ( void* ptr )  {
    cpu.enable_int();
    allocator.free(ptr);
    cpu.disable_int();
}

void* operator new[]( size_t count ) {
    cpu.enable_int();
    void *ret = allocator.alloc(count);
    cpu.disable_int();
    return ret; 
}

void operator delete[] ( void* ptr ) {
    cpu.disable_int();
    allocator.free(ptr);
    cpu.enable_int();
}

void operator delete(void*ptr, unsigned long) {
    cpu.disable_int();
    allocator.free(ptr);
    cpu.enable_int();
}
