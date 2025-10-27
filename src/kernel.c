
#include "mem.h"
#include "cpu.h"
#include "io.h"
#include "task.h"
#include "syscall.h"
#include "timer.h"
#include "isr.h"
#include "shell.h"


void print(const char *str, int row) {
    char *vidptr = (char*)0xb8000 + row * 160;
    unsigned int i = 0;
    while(str[i]) {
        vidptr[i*2] = str[i];
        vidptr[i*2+1] = 0x07;
        i++;
    }
}

void print_hex(unsigned int val, int row) {
    char *vidptr = (char*)0xb8000 + row * 160;
    for (int i = 0; i < 8; i++) {
        int shift = (7-i)*4;
        char c = ((val >> shift) & 0xF);
        c = c < 10 ? '0'+c : 'A'+(c-10);
        vidptr[i*2] = c;
        vidptr[i*2+1] = 0x0A;
    }
}


void demo_task() {
    for (int i = 0; i < 10; i++) {
        print("Task running", 12);
        for (volatile int d = 0; d < 1000000; d++); 
        print("Task yield", 12);
        for (volatile int d = 0; d < 1000000; d++); 
        task_schedule();
    }
    print("Task done", 12);
    while(1) {}
}

void kernel_main(void) {
    isr_install();
    timer_init(100);
    mem_init(0x100000, 0x10000);
    syscall_init();
    print("runko-kernel: Memory/CPU/IO demo", 0);
    print("Total mem:", 2); print_hex(get_total_memory(), 2);
    print("Free mem:", 3); print_hex(get_free_memory(), 3);
    char vendor[13]; cpu_get_vendor(vendor);
    print("CPU vendor:", 4);
    for (int i = 0; i < 12; i++) {
        char *vidptr = (char*)0xb8000 + 4*160 + 20 + i*2;
        vidptr[0] = vendor[i]; vidptr[1] = 0x0B;
    }
    print("I/O port 0x60:", 5);
    unsigned char val = inb(0x60);
    char hex[3] = {0};
    hex[0] = ((val >> 4) < 10 ? '0'+((val>>4)&0xF) : 'A'+((val>>4)&0xF)-10);
    hex[1] = ((val & 0xF) < 10 ? '0'+(val&0xF) : 'A'+(val&0xF)-10);
    char *vidptr = (char*)0xb8000 + 5*160 + 18;
    vidptr[0] = hex[0]; vidptr[1] = 0x0C;
    vidptr[2] = hex[1]; vidptr[3] = 0x0C;
    void *p = kmalloc(32);
    print("Allocated 32 bytes", 7);
    print("Free mem:", 8); print_hex(get_free_memory(), 8);
    kfree(p);
    print("Freed 32 bytes", 9);
    print("Free mem:", 10); print_hex(get_free_memory(), 10);


        shell_run();
}
