/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __Globals_include__
#define __Globals_include__

#include "kernel/CPU.h"
#include "devices/CGA_Stream.h"
#include "devices/PCSPK.h"
#include "devices/Keyboard.h"
#include "kernel/allocator/BumpAllocator.h"
#include "kernel/allocator/LinkedListAllocator.h"
#include "kernel/interrupts/PIC.h"
#include "kernel/interrupts/IntDispatcher.h"

extern CPU                      cpu;        // CPU-spezifische Funktionen
extern CGA_Stream               kout;       // Ausgabe-Strom fuer Kernel
extern PCSPK                    pcspk;      // PC-Lautsprecher
extern Keyboard                 kb;         // Tastatur
extern uint64_t                 total_mem;  // RAM total
//extern BumpAllocator          allocator;       
extern LinkedListAllocator      allocator;
extern IntDispatcher            intdis;     // Unterbrechungsverteilung
extern PIC                      pic;        // Interrupt-Controller
#endif
