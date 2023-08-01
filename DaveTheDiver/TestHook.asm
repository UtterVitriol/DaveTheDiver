global test_hook         ; Tells NASM that this can be used outside of this file
extern hOnStartMeleeAttack
%define MY_AMMO 99 ; Preprocessor directive that makes the code easier to read, similar to a C/C++ #define


section .text         ; Tells NASM that the following section is code


test_hook:
    push rbp        ; Stack alignment stuff, don't worry if you don't know what that means
    mov rbp, rsp

    push rcx
    mov rcx, rbx
    call hOnStartMeleeAttack
    pop rcx

    ; Stolen bytes
    ; Need to increment stack offests by 0x10 (16) to account for out stack alignment

    mov rdi,[rbx+0x00000118]
    mov rdx,[rax+0x000000B8]
    mov esi,[rdx+0x000000F4]

    leave    ; Short for mov rsp, rbp + pop rbp, returns the stack registers to how they were pre-alignment
    ret