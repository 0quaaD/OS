CC = i686-elf-gcc
CWARNING = -Wall -Wextra -Werror
CFLAGS = -m32 -ffreestanding -O2 -Iinclude $(CWARNING)

AS = nasm
ASFLAG = -f elf32

LD = i686-elf-ld
LDFLAGS = -T linker.ld 
SRC = src
BIN = bin
OBJ = obj
ASM = asm

TARGET = $(BIN)/os.bin
OBJECTS = $(OBJ)/kernel.o $(OBJ)/boot.o $(OBJ)/vga.o

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ)/kernel.o: $(SRC)/kernel.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/boot.o: $(ASM)/boot.asm | $(OBJ)
	$(AS) $(ASFLAG) $< -o $@

$(OBJ)/vga.o: $(SRC)/vga.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN):
	mkdir -p $@
$(OBJ):
	mkdir -p $@

run: $(TARGET)
	mkdir -p iso/boot/grub
	cp $(TARGET) iso/boot
	cp grub.cfg iso/boot/grub
	grub-mkrescue -o os.iso iso/
	qemu-system-i386 -cdrom os.iso -monitor stdio
clean:
	rm -rf $(OBJ)/ $(BIN)/ iso/ os.iso
.PHONY: all run clean
