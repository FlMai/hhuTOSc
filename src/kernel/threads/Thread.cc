#include "kernel/Globals.h"
#include "kernel/threads/Thread.h"

extern "C"
{
    void thread_start  (uint64_t *now);
    void thread_switch (uint64_t *now, uint64_t *then);
}

void Thread_prepare_stack (uint64_t *stackptr, uint64_t *stack,
                     void (*kickoff)(Thread*), void* object) {
    
    uint64_t **sp = (uint64_t**)stack;

    // Stack initialisieren. Es soll so aussehen, als waere soeben die
    // eine Funktion aufgerufen worden, die als Parameter den Zeiger
    // "object" erhalten hat.
    // Da der Funktionsaufruf simuliert wird, kann fuer die Ruecksprung-
    // adresse nur ein unsinniger Wert eingetragen werden. Die aufgerufene
    // Funktion muss daher dafuer sorgen, dass diese Adresse nie benoetigt
    // wird, sie darf also nicht terminieren, sonst kracht's.
    *(--sp) = (uint64_t *)0x131155; // Ruecksprungadresse
    
    // Nun legen wir noch die Adresse der Funktion "kickoff" ganz oben auf
    // den Stack. Wenn dann bei der ersten Aktivierung dieser Koroutine der
    // Stackpointer so initialisiert wird, dass er auf diesen Eintrag
    // verweist, genuegt ein ret, um die Funktion kickoff zu starten.
    // Genauso sollen auch alle spaeteren Coroutinen-Wechsel ablaufen.
    
    *(--sp) = (uint64_t *)kickoff;  // Adresse

    // Nun sichern wir noch alle relevanten Register auf dem Stack 
    //implizite return adresse when switching
    *(--sp) = (uint64_t *)0;    	// r8
    *(--sp) = (uint64_t *)0;   		// r9
    *(--sp) = (uint64_t *)0;   		// r10
    *(--sp) = (uint64_t *)0;   		// r11
    *(--sp) = (uint64_t *)0;   		// r12
    *(--sp) = (uint64_t *)0;   		// r13
    *(--sp) = (uint64_t *)0;   		// r14
    *(--sp) = (uint64_t *)0;   		// r15
    *(--sp) = (uint64_t *)0;   		// rax
    *(--sp) = (uint64_t *)0;   		// rbx
    *(--sp) = (uint64_t *)0;   		// rcx
    *(--sp) = (uint64_t *)0;   		// rdx

    *(--sp) = (uint64_t *)0;   		// rsi
    *(--sp) = (uint64_t *)object; 	// rdi -> 1. Param fuer 'kickoff'
    *(--sp) = (uint64_t *)0;   		// rbp
    *(--sp) = (uint64_t *)cpu.getflags(); // flags

    // Zum Schluss speichern wir den Zeiger auf den zuletzt belegten
    // Eintrag auf dem Stack in 'stackptr'. Daruber gelangen wir in 
    // Coroutine_start an die noetigen Register     
    *stackptr = (uint64_t)sp;		// aktuellen Stack-Zeiger speichern
}

void kickoff (Thread* object) {
    object->run();    
    // object->run() kehrt hoffentlich nie hierher zurueck
    for (;;) {}
}

Thread::Thread () {
   stack = new uint64_t[1024];
   tid = threadId;
   threadId++;
   Thread_prepare_stack (&context, stack+1023, kickoff, this);
 }

void Thread::switchTo (Thread &next) {
    thread_switch(&context,  &(next.context));
}

void Thread::start () {
    thread_start(&context);
}

Thread::~Thread() {
    delete(stack);
}