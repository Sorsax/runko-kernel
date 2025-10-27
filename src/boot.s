# Kernel entry (multiboot)
.section .multiboot, "a"
.align 4
.long 0x1BADB002
.long 0x00000000
.long -(0x1BADB002 + 0x00000000)

.section .text
.global _start
.section .text
.global _start
_start:
    mov $0xb8000, %edi
    mov $'O', %al
    mov $0x0F, %ah
    movw %ax, (%edi)
.hang:
    hlt
    jmp .hang

.section .bss
.align 16
stack_bottom:
    .skip 16384
stack_top:
