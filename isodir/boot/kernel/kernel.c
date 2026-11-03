#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"
#include "vga.h"
#include "io.h"
// #include "io.h"


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif




void kernel_main(uint32_t magic, uint32_t mbi_addr) 
{

	char row = 7;
	char column = 0;
	/* Initialize terminal interface */
	terminal_initialize();


	// if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    // {
    //     for (;;);
    // }

    // struct multiboot_info* mbi =
    //     (struct multiboot_info*)mbi_addr;

    // if (mbi->flags & (1 << 6))

	terminal_writestring("leoOs$>");

	while(1){
		
		vga_set_cursor(column, row);
		if (row == 80){
			column++;
			row = 0;
		}
		char c = keyboard_getchar();
	
		if (c != 0)
			terminal_putchar(c);

		

		row++;

	}

}



