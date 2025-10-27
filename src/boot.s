# Kernel entry (multiboot)
.section .multiboot
.align 4
.long 0x1BADB002
.long 0x00000000
.long 0xE4524FFB

.section .text
.global _start
_start:
    mov $0x03, %al
    mov $0x00, %ah
    int $0x10

    mov $stack_top, %esp
    call kernel_main
    cli
1:  hlt
    jmp 1b

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
