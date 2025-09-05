CC = i686-elf-gcc
CWARNING = -Wall -Wextra -Werror
CFLAGS = -m32 -ffreestanding -O2 -Iinclude -ggdb -fno-stack-protector -fno-builtin $(CWARNING)

AS = nasm
ASFLAG = -f elf32

LD = i686-elf-ld
LDFLAGS = -T linker.ld 
SRC = src
BIN = bin
OBJ = obj
ASM = asm

TARGET = $(BIN)/os.bin
OBJECTS = $(OBJ)/kernel.o $(OBJ)/boot.o $(OBJ)/vga.o $(OBJ)/gdt_asm.o $(OBJ)/gdt_c.o $(OBJ)/idt_asm.o $(OBJ)/idt_c.o $(OBJ)/memory.o $(OBJ)/io.o

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJ)/kernel.o: $(SRC)/kernel.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/boot.o: $(ASM)/boot.asm | $(OBJ)
	$(AS) $(ASFLAG) $< -o $@

$(OBJ)/gdt_asm.o: $(ASM)/gdt.asm | $(OBJ)
	$(AS) $(ASFLAG) $< -o $@
	
$(OBJ)/idt_asm.o: $(ASM)/idt.asm | $(OBJ)
	$(AS) $(ASFLAG) $< -o $@
	
$(OBJ)/vga.o: $(SRC)/vga.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/gdt_c.o: $(SRC)/gdt.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/idt_c.o: $(SRC)/idt.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/memory.o: $(SRC)/memory.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(OBJ)/io.o: $(SRC)/io.c | $(OBJ)
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
	qemu-system-i386 -cdrom os.iso -d int
clean:
	rm -rf $(OBJ)/ $(BIN)/ iso/ os.iso
.PHONY: all run clean
