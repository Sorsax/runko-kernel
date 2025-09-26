#include "timer.h"
#include "io.h"

static unsigned int tick = 0;

void timer_handler() {
    tick++;
}

void timer_init(unsigned int frequency) {
    unsigned int divisor = 1193180 / frequency;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}
