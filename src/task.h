#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task {
    uint32_t *stack_ptr;
    void (*entry)(void);
    int active;
} task_t;

void task_init();
void task_create(void (*entry)(void));
void task_schedule();

#endif // TASK_H
