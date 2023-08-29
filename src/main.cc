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
#include "user/demo/LoopThread.h"
#include "user/demo/KeyboardThread.h"
#include "user/demo/Tetris.h"
#include "user/demo/ScrollThread.h"

extern "C" void init_interrupts();     

int main() {
   kout.clear();
   kout.setpos(0,1);
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
         kout << endl << "Spawning Tetris song in thread." << endl;
         kout << "Press r to reboot." << endl;
         SoundDemo *s = new SoundDemo();
         RebootThread *r = new RebootThread();

         scheduler.ready(s);
         scheduler.ready(r);
         scheduler.schedule();      
      } else if (k == '3') {
         kout << endl << "Spawning 3 LoopCounter threads and a music thread." << endl;
         kout << "Press r to reboot." << endl;
         LoopThread *l1 = new LoopThread();
         LoopThread *l2 = new LoopThread();
         LoopThread *l3 = new LoopThread();
         SoundDemo *tetris = new SoundDemo();
         RebootThread *r = new RebootThread();

         scheduler.ready(l1);
         scheduler.ready(l2);
         scheduler.ready(l3);
         scheduler.ready(tetris);
         scheduler.ready(r);

         scheduler.schedule();
      } else if (k == '4') {
         uint8_t *shared_mem_kb = (uint8_t*) 0xC00000;
         *shared_mem_kb = 0;
         uint8_t *shared_mem_scroll_down = (uint8_t*) 0xC00008;
         *shared_mem_scroll_down = 0;
         Tetris *t = new Tetris(shared_mem_kb, shared_mem_scroll_down);

         scheduler.ready(t);
         scheduler.schedule();
      }
      
   }
   while(1) {}
   return 0;
 }
