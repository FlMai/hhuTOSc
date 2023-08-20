/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe1/KeyboardDemo.h"
#include "user/aufgabe2/HeapDemo.h"
#include "user/aufgabe2/SoundDemo.h"
#include "user/aufgabe3/KeyIRQDemo.h"

extern "C" void init_interrupts();     // in 'interrupts.asm' 


void aufgabe03() {
   // Keyboard & Interrupts testen
   key_irq_demo();
}

void aufgabe01() { 
   text_demo();
   keyboard_demo();
}

void aufgabe02() {
   heap_demo();
   sound_demo();
}

int main() {
   //aufgabe01();
   //aufgabe02();
   kout.clear();
   // Heapverwaltung initialisieren
   allocator.init();
   // IDT & PIC initialisieren
   init_interrupts();     // in 'interrupts.asm' 

   // Tastatur-Unterbrechungsroutine 'einstoepseln'
   kb.plugin();
   // Interrupt-Verarbeitung durch CPU erlauben
   if (!cpu.disable_int()) {
      cpu.enable_int();
   }
   if (pic.status(1)) {
      kout << "KB enabled" << endl;
   }
   aufgabe03();

   while (1);
   return 0;
 }
