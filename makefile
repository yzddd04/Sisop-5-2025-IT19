mkdir_bin:
	mkdir -p bin

prepare: mkdir_bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2800

bootloader:
	nasm -f bin src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img count=1 bs=512 conv=notrunc

stdlib:
	bcc -ansi -c -Iinclude src/std_lib.c -o bin/std_lib.o

shell:
	bcc -ansi -c -Iinclude src/shell.c -o bin/shell.o

kernel:
	nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
	bcc -ansi -c -Iinclude src/kernel.c -o bin/kernel.o

link:
	ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/shell.o bin/std_lib.o
	dd if=bin/kernel.bin of=bin/floppy.img seek=1 bs=512 conv=notrunc

build: prepare bootloader stdlib shell kernel link

run: build
	bochs -f bochsrc.txt

clean:
	rm -f bin/*.o bin/*.bin