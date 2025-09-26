
ISO_NAME = runko.iso
BUILD = build
SRC = src
BOOT = boot

all: $(BUILD)/$(ISO_NAME)




$(BUILD)/kernel.bin: $(SRC)/boot.o $(SRC)/kernel.o $(SRC)/mem.o $(SRC)/cpu.o $(SRC)/io.o $(SRC)/task.o $(SRC)/syscall.o $(SRC)/shell.o $(SRC)/timer.o $(SRC)/isr.o linker.ld
	ld -T linker.ld -o $@ $^

$(SRC)/timer.o: $(SRC)/timer.c
	gcc -m32 -ffreestanding -c $< -o $@
$(SRC)/isr.o: $(SRC)/isr.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/shell.o: $(SRC)/shell.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/syscall.o: $(SRC)/syscall.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/task.o: $(SRC)/task.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/boot.o: $(SRC)/boot.s
	gcc -m32 -c $< -o $@

$(SRC)/kernel.o: $(SRC)/kernel.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/mem.o: $(SRC)/mem.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/cpu.o: $(SRC)/cpu.c
	gcc -m32 -ffreestanding -c $< -o $@

$(SRC)/io.o: $(SRC)/io.c
	gcc -m32 -ffreestanding -c $< -o $@

$(BUILD)/$(ISO_NAME): $(BUILD)/kernel.bin $(BOOT)/grub.cfg
	mkdir -p $(BUILD)/iso/boot/grub
	cp $(BUILD)/kernel.bin $(BUILD)/iso/boot/kernel.bin
	cp $(BOOT)/grub.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BUILD)/iso

run: $(BUILD)/$(ISO_NAME)
	qemu-system-i386 -cdrom $<

clean:
	rm -rf $(BUILD)/*.o $(BUILD)/*.bin $(BUILD)/iso $(BUILD)/*.iso
