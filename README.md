
# runko-kernel

Pienoinen vapaa-ajan harrasteprojekti C:n oppimiseen
Tietysti assyäkin tulee opittua mutta lähinnä stackoverflow pohjaisesti sillä osastolla

## Ominaisuudet
- Perus muistinhallinta (heap, malloc/free)
- Prosessinhallinta (yksinkertainen tehtävienhallinta, round-robin)
- I/O (porttiluku, ruudulle tulostus)
- Yksinkertainen shell (komentorivi, komennot: help, echo)
- System call -rajapinta (syscall)

## Tiedostorakenne
- `boot/` — Bootloader (GRUB multiboot)
- `src/` — Kernelin lähdekoodi (C ja assembly)
- `build/` — Buildin ulostulo

## Build vaatimukset
- GCC cross-compiler i386:lle
- `make`
- QEMU emulointiin
- grub-mkrescue (GRUB bootloaderin ISO:n tekoon)

## Rakenna & Aja
```sh
make
make run
```

## Tiedostot
- `Makefile` — Käännösjärjestelmä
- `linker.ld` — Linkkeri
- `boot/grub.cfg` — GRUB config
- `src/boot.s` — Kernel entry (assembly)
- `src/kernel.c` — Kernelin pääohjelma (C)
- `src/mem.c`/`mem.h` — Muistinhallinta
- `src/task.c`/`task.h` — Prosessinhallinta
- `src/io.c`/`io.h` — I/O
- `src/syscall.c`/`syscall.h` — System call -rajapinta
- `src/shell.c`/`shell.h` — Yksinkertainen shell
