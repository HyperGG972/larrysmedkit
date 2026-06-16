; Multiboot header constants required by GRUB
MODULEALIGN equ  1 << 0
MEMINFO     equ  1 << 1
FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .text
global _start
extern kernel_main      ; This tells the assembler that 'kernel_main' exists in another file (C)

_start:
    cli                 ; Disable hardware interrupts
    mov esp, stack_top  ; Set up a stack pointer pointer for C variables
    call kernel_main    ; JUMP DIRECTLY INTO YOUR C CODE!
    
.hang:
    hlt                 ; Halt the CPU if C code ever finishes executing
    jmp .hang

section .bss
align 16
stack_bottom:
resb 16384              ; Reserve 16KB of RAM space for the C call stack
stack_top:
