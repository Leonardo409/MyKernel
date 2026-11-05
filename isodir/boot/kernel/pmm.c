#include "multiboot.h"
#include "pmm.h"
#include "stdint.h"
#include "string.h"


static uint8_t memory_bitmap[BITMAP_SIZE];

void pmm_set_used(uint32_t page){
    memory_bitmap[page / 8] |= (1 << (page % 8));
}

void pmm_set_free(uint32_t page){
    memory_bitmap[page / 8] &= ~(1 << (page % 8));
}

int pmm_is_used(uint32_t page){
    return memory_bitmap[page / 8] & (1 << (page % 8));
}

void *memset(void *ptr, int value, size_t num){
    uint8_t *p = (uint8_t *)ptr;

    for (size_t i = 0; i < num; i++){
        p[i] =(uint8_t) value;
    }
}

void pmm_init(void){
    memset(memory_bitmap, 0xFF, sizeof(memory_bitmap));
}

void pmm_test(void){
    for (int i = 0; i < 10; i++){
        terminal_writehex(memory_bitmap[i]);
    }
}