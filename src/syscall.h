#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void syscall_init();
uint32_t syscall_handler(uint32_t num, uint32_t arg1, uint32_t arg2, uint32_t arg3);

#define SYSCALL_PRINT 1
#define SYSCALL_EXIT  2

#endif // SYSCALL_H
