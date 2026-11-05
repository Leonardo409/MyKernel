#include "string.h"
#include "vga.h"


int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return *s1 - *s2;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}


//read hexadecimal
void terminal_writehex(uint8_t value)
{
    char hex[] = "0123456789ABCDEF";

    terminal_putchar('0');
    terminal_putchar('x');

    terminal_putchar(hex[(value >> 4) & 0x0F]);
    terminal_putchar(hex[value & 0x0F]);
}
