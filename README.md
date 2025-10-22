# runko-kernel

A small hobby project for learning C.  

## Features
- Basic memory management (heap, malloc/free)
- Process management (simple task scheduler, round-robin)
- I/O (port reading, screen output)
- Simple shell (command line, commands: help, echo)
- System call interface (syscall)

## Directory Structure
- `boot/` — Bootloader (GRUB multiboot)
- `src/` — Kernel source code (C and assembly)
- `build/` — Build output

## Build Requirements
- GCC cross-compiler for i386
- `make`
- QEMU for emulation
- `grub-mkrescue` (for creating a GRUB bootable ISO)

## Build & Run
```sh
make
make run
