#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"
#include "vga.h"
#include "io.h"
// #include "io.h"

//read hexadecimal

void terminal_writehex(uint8_t value)
{
    char hex[] = "0123456789ABCDEF";

    terminal_putchar('0');
    terminal_putchar('x');

    terminal_putchar(hex[(value >> 4) & 0x0F]);
    terminal_putchar(hex[value & 0x0F]);
}

void kernel_main(uint32_t magic, uint32_t mbi_addr) 
{

	terminal_initialize();


	// if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    // {
    //     for (;;);
    // }

    // struct multiboot_info* mbi =
    //     (struct multiboot_info*)mbi_addr;

    // if (mbi->flags & (1 << 6))

	print("leoOs$>");
	
	while(1){

		char c = keyboard_getchar();
		uint8_t scancode = inb(0x60);

		if (scancode == 0x1C){
			terminal_initialize();
			print("leoOs$>");
			continue;	
		}

		if (scancode == 0x0E){
			delete_carac();
			continue;
		}
			
		// terminal_writehex(scancode);

		if (c != 0)
			terminal_putchar(c);

	}

}



