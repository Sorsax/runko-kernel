ISO_NAME = runko.iso
BUILD = build
SRC = src
BOOT = boot

CC = i386-elf-gcc
LD = i386-elf-ld

CFLAGS = -ffreestanding -fno-pic -fno-pie -fno-stack-protector -nostdlib -nostartfiles -mno-stack-arg-probe -m32
LDFLAGS = -T linker.ld

SRC_C = kernel.c mem.c cpu.c io.c task.c syscall.c shell.c timer.c isr.c
SRC_ASM = boot.s

SRC_OBJS = $(SRC)/boot.o $(addprefix $(SRC)/,$(SRC_C:.c=.o))

all: $(BUILD)/$(ISO_NAME)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC)/boot.o: $(SRC)/boot.s
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(ISO_NAME): $(BUILD)/kernel.elf $(BOOT)/grub.cfg
	mkdir -p $(BUILD)/iso/boot/grub
	cp $(BUILD)/kernel.elf $(BUILD)/iso/boot/kernel.elf
	cp $(BOOT)/grub.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BUILD)/iso

run: $(BUILD)/$(ISO_NAME)
	qemu-system-i386 -cdrom $< -serial stdio -m 512 -display gtk

direct: $(BUILD)/kernel.bin

	qemu-system-i386 -kernel $< -m 512 -display gtk

$(BUILD)/kernel.elf: $(SRC_OBJS)
	mkdir -p $(BUILD)
	$(LD) $(LDFLAGS) -n -e _start -o $@ $(SRC_OBJS)

elf: $(BUILD)/kernel.elf
	qemu-system-i386 -kernel $< -m 512 -display gtk

clean:
	rm -rf $(BUILD)/*.o $(SRC)/*.o $(BUILD)/*.bin $(BUILD)/iso $(BUILD)/*.iso

.PHONY: all run clean
