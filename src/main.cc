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
#include "lib/Input.h"
#include "kernel/threads/IdleThread.h"
#include "user/demo/HeapDemo.h"
#include "user/demo/TextDemo.h"
#include "user/demo/SoundDemo.h"
#include "user/demo/RebootThread.h"

extern "C" void init_interrupts();     

int main() {
   kout.clear();
   allocator.init();
   init_interrupts();
   kb.plugin();   
   pit.plugin();

   if (!cpu.disable_int()) {
      cpu.enable_int();
   }

   kout << "hhuTOSc by Florian M." << endl << endl;
   kout << "Main Menu" << endl << "===========" << endl << endl;
   kout << "  [0] Heap Demo" << endl;
   kout << "  [1] Text + Keyboard Demo" << endl;
   kout << "  [2] Sound Demo" << endl;
   kout << "  [3] Preempt Multitask Demo" << endl;
   kout << "  [4] Tetris" << endl;

   while (true) {
      char k = getch();
      if (k == '0') {
         heap_demo();
      } else if (k == '1') {
         text_demo();
      } else if (k == '2') {
         SoundDemo *s = new SoundDemo();
         RebootThread *r = new RebootThread();

         scheduler.ready(s);
         scheduler.ready(r);
         scheduler.schedule();      
      }
      
   }
   while(1) {}
   return 0;
 }
