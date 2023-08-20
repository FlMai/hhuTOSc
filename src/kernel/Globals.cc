/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/

#include "kernel/Globals.h"


CPU                     cpu;        // CPU-spezifische Funktionen
CGA_Stream              kout;       // Ausgabe-Strom fuer Kernel
PCSPK                   pcspk;      // PC-Lautsprecher
Keyboard                kb;         // Tastatur
uint64_t                total_mem;  // RAM total
//BumpAllocator         allocator;       
LinkedListAllocator     allocator; 
IntDispatcher           intdis;     // Unterbrechungsverteilung
PIC                     pic;        // Interrupt-Controller

