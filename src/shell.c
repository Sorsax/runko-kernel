#include "shell.h"
#include "io.h"
#include <stddef.h>

#define SHELL_INPUT_MAX 32

static char input_buf[SHELL_INPUT_MAX];
static int input_len = 0;

void shell_print(const char *str, int row) {
    char *vidptr = (char*)0xb8000 + row * 160;
    int i = 0;
    while(str[i]) {
        vidptr[i*2] = str[i];
        vidptr[i*2+1] = 0x0F;
        i++;
    }
}

void shell_prompt() {
    shell_print("runko> ", 20);
}

void shell_handle_command() {
    if (input_len == 0) return;
    if (input_buf[0] == 'h' && input_buf[1] == 'e' && input_buf[2] == 'l' && input_buf[3] == 'p') {
        shell_print("help: show this message", 21);
    } else if (input_buf[0] == 'e' && input_buf[1] == 'c' && input_buf[2] == 'h' && input_buf[3] == 'o') {
        shell_print(input_buf+5, 21);
    } else {
        shell_print("Unknown command", 21);
    }
    input_len = 0;
    for (int i = 0; i < SHELL_INPUT_MAX; i++) input_buf[i] = 0;
}

void shell_run() {
    shell_prompt();
    while (1) {
        unsigned char sc = inb(0x60);
        if (sc & 0x80) continue; 
        char c = 0;
        if (sc == 0x1C) { 
            shell_handle_command();
            shell_prompt();
        } else if (sc == 0x0E) { 
            if (input_len > 0) input_len--;
        } else if (sc >= 0x02 && sc <= 0x0B) { 
            c = "1234567890"[sc-0x02];
        } else if (sc >= 0x10 && sc <= 0x19) { 
            c = "qwertyuiop"[sc-0x10];
        } else if (sc >= 0x1E && sc <= 0x26) { 
            c = "asdfghjkl"[sc-0x1E];
        } else if (sc >= 0x2C && sc <= 0x32) { 
            c = "zxcvbnm"[sc-0x2C];
        } else if (sc == 0x39) { 
            c = ' ';
        }
        if (c && input_len < SHELL_INPUT_MAX-1) {
            input_buf[input_len++] = c;
            char out[2] = {c, 0};
            shell_print(out, 20);
        }
    }
}
