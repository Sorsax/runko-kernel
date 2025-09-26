#include "mem.h"
#include <stdint.h>

#define HEAP_MAGIC 0xDEADBEEF

typedef struct heap_block {
    uint32_t magic;
    uint32_t size;
    struct heap_block *next;
    int free;
} heap_block_t;

static heap_block_t *heap_start = 0;
static unsigned int heap_total = 0;
static unsigned int heap_free = 0;

void mem_init(unsigned int heap_addr, unsigned int heap_size) {
    heap_start = (heap_block_t*)heap_addr;
    heap_start->magic = HEAP_MAGIC;
    heap_start->size = heap_size - sizeof(heap_block_t);
    heap_start->next = 0;
    heap_start->free = 1;
    heap_total = heap_start->size;
    heap_free = heap_total;
}

void *kmalloc(size_t size) {
    heap_block_t *curr = heap_start;
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(heap_block_t)) {
                heap_block_t *new_block = (heap_block_t*)((uint8_t*)curr + sizeof(heap_block_t) + size);
                new_block->magic = HEAP_MAGIC;
                new_block->size = curr->size - size - sizeof(heap_block_t);
                new_block->next = curr->next;
                new_block->free = 1;
                curr->next = new_block;
                curr->size = size;
            }
            curr->free = 0;
            heap_free -= curr->size;
            return (void*)((uint8_t*)curr + sizeof(heap_block_t));
        }
        curr = curr->next;
    }
    return 0;
}

void kfree(void *ptr) {
    if (!ptr) return;
    heap_block_t *block = (heap_block_t*)((uint8_t*)ptr - sizeof(heap_block_t));
    if (block->magic != HEAP_MAGIC) return;
    block->free = 1;
    heap_free += block->size;
    // Coalesce free blocks
    heap_block_t *curr = heap_start;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(heap_block_t) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

unsigned int get_total_memory() {
    return heap_total;
}

unsigned int get_free_memory() {
    return heap_free;
}
