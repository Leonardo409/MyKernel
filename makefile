bootsrc=isodir/boot/kernel
build=isodir/boot/build

all: build linker bootstrap kernel clean always



build: bootstrap kernel linker
	grub-mkrescue -o myos.iso isodir

linker: bootstrap kernel
	i686-elf-gcc -T $(bootsrc)/linker.ld -o $(build)/myos -ffreestanding -O2 -nostdlib $(build)/boot.o $(build)/kernel.o $(build)/vga.o  $(build)/keyboard.o -lgcc

bootstrap:
	i686-elf-as $(bootsrc)/boot.s -o $(build)/boot.o

kernel:
	i686-elf-gcc -c $(bootsrc)/kernel.c -o $(build)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(bootsrc)/vga.c -o $(build)/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c $(bootsrc)/keyboard.c -o $(build)/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

always:
	mkdir -p $(build)

clean:
	rm -rf $(build)/*


