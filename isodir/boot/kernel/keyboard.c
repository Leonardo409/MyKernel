#include <stdint.h>
#include "io.h"


uint8_t keyboard_read(void)
{
    while (!(inb(0x64) & 1))
    {
        // Esperar hasta que haya datos disponibles
    }

    return inb(0x60);
}

// char keyboard_translate(uint8_t scancode)
// {
//     if (scancode & 0x80)
//         return 0;

//     if (scancode >= 128)
//         return 0;

//     return scancode_map[scancode];
// }

char keyboard_getchar(void)
{
    uint8_t scancode = keyboard_read();
    if (scancode & 0x80)
        return 0;

    return scancode_map[scancode];
}

