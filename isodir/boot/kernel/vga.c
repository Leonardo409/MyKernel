#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "multiboot.h"
#include "vga.h"

//cursor
static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}


//delay
void delay(uint32_t count)
{
    for (volatile uint32_t i = 0; i < count; i++)
    {
        __asm__ volatile ("nop");
    }
}


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}


void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	vga_set_cursor(terminal_row ,terminal_column);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void print(const char* data) 
{
	terminal_write(data, strlen(data));
}


//same as termminal terminal_initialize

// void clear_terminal(void)
// {
// 	for(int i=0;i< VGA_WIDTH * VGA_HEIGHT; i++){
// 		terminal_buffer[i] = vga_entry(' ', terminal_color);
// 	}
// 	terminal_row = 0;
// 	terminal_column = 0;
// 	vga_set_cursor(terminal_row ,terminal_column);

// }


void delete_carac(void){
	if(terminal_column >= 2){
		terminal_column--;
	} 
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
	terminal_buffer[terminal_row * VGA_WIDTH + terminal_column] = vga_entry(' ', terminal_color);
	vga_set_cursor(terminal_row ,terminal_column);
}




void vga_set_cursor(uint16_t row, uint16_t column)
{
    uint16_t position = row * VGA_WIDTH + column;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)(position >> 8));
}

