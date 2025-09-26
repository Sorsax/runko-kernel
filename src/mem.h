#ifndef MEM_H
#define MEM_H

#include <stddef.h>

void mem_init(unsigned int heap_start, unsigned int heap_size);
void *kmalloc(size_t size);
void kfree(void *ptr);

unsigned int get_total_memory();
unsigned int get_free_memory();

#endif // MEM_H
