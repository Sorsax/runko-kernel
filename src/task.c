#include "task.h"
#include <stddef.h>

#define MAX_TASKS 2
#define STACK_SIZE 4096

static task_t tasks[MAX_TASKS];
static int current_task = 0;

static uint32_t stacks[MAX_TASKS][STACK_SIZE/sizeof(uint32_t)];

void task_init() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].stack_ptr = NULL;
        tasks[i].entry = NULL;
        tasks[i].active = 0;
    }
    current_task = 0;
}

void task_create(void (*entry)(void)) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (!tasks[i].active) {
            tasks[i].entry = entry;
            tasks[i].active = 1;
            uint32_t *sp = &stacks[i][STACK_SIZE/sizeof(uint32_t)-1];
            *(--sp) = (uint32_t)entry;
            tasks[i].stack_ptr = sp;
            break;
        }
    }
}

void task_schedule() {
    int next = (current_task + 1) % MAX_TASKS;
    if (tasks[next].active) {
        asm volatile ("movl %%esp, %0" : "=m"(tasks[current_task].stack_ptr));
        asm volatile ("movl %0, %%esp" : : "m"(tasks[next].stack_ptr));
        current_task = next;
    }
}
