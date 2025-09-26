#include "syscall.h"
#include "io.h"

uint32_t syscall_handler(uint32_t num, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
    switch(num) {
        case SYSCALL_PRINT:
            {
                char *vidptr = (char*)0xb8000 + arg2 * 160;
                vidptr[0] = (char)arg1;
                vidptr[1] = 0x0E;
            }
            return 0;
        case SYSCALL_EXIT:
            __asm__ __volatile__("cli; hlt");
            return 0;
        default:
            return (uint32_t)-1;
    }
}

void syscall_init() {
}
