#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"
#include "string.h"
#include "vga.h"
#include "io.h"
#include "pmm.h"


void kernel_main(uint32_t magic, uint32_t mbi_addr, uint32_t stack_initial_addrs) {
	
	//initialize the phisical memory 0xFF for all the empty spaces
	pmm_init();

	//print 10 spaces
	// pmm_test();

	//getting the multiboot struct info
	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        for (;;);
    }
	struct multiboot_info* mbi = (struct multiboot_info*)mbi_addr;

	struct multiboot_mmap_entry *entry=(struct multiboot_mmap_entry *) (mbi->mmap_addr);


	//printing the terminal sign
	terminal_initialize();
	
	if (mbi->flags & (1 << 6)){
		terminal_initialize();
		print("memory map avialable: ");
		while(1){

			char c = keyboard_getchar();
			uint8_t scancode = inb(0x60);
			

			if (scancode == 0x1C){
				terminal_initialize();
				print("$");		
				continue;			
			}
		
			if (scancode == 0x0E){
				delete_carac();
				continue;
			}	

			if (c != 0){
				terminal_putchar(c);
			}
		}	
	}
}




//clear the screen 
// if (scancode == 0x1C){
// 			for(int i = 0; i <= 4; i++){
// 				text[i] = terminal_buffer[i+1] & 0xFF; 
// 			}

// 			if(strcmp(text, "clear") == 0){
// 				terminal_initialize();
// 				print("$");	
// 			}
// 			continue;			
// 		}



	

  
