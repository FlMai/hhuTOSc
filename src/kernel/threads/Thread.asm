;*****************************************************************************
;*                                                                           *
;*                  C O R O U T I N E                                        *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerfunktionen zum Starten des ersten Koroutine und *
;*                  zum Umschalten zwischen Koroutinen.                      *
;*                                                                           *
;* Autor:           Michael, Schoettner, HHU, 15.05.2023                     *
;*****************************************************************************


; EXPORTIERTE FUNKTIONEN

[GLOBAL thread_start]
[GLOBAL thread_switch]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]
[BITS 64]


;
; Coroutine_start: Startet die erste Koroutine
;                  'now' zeigt auf den zuletzt belegten Eintrag des 
;                  prawparierten Stacks
;
; C Prototyp:      void _coroutine_start  (uint64_t *now);
;
thread_start:
    mov rsp, [rdi]
    popfq
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    sti
    ret


; Coroutine_switch: Coroutinenumschaltung. Der aktuelle Registersatz der 
;                   aktuellen Coroutine wird auf dem Stack 'now' gesichert
;                   und der Registersatz der neuen Coroutine wird vom Stack 
;                   'then' in den Prozessor geladen.
;
; C Prototyp:       void Coroutine_switch (uint64_t *now, uint64_t *then);
thread_switch:
    ; we already are at the stack position we need, dont load rsp from rdi

    cmp rdi, rsi    ; check if we switch to te same thread
    je  equal           ; if same thread

    push r8
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    pushfq
    mov [rdi], rsp          ; save new location of *now

    mov rsp, [rsi]          ; load new stack pointer
    popfq
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    sti
    ret

equal:
    sti
    ret