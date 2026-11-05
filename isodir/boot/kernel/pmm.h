#include "stdint.h"
#include "stddef.h"

#define PAGE_SIZE 4096
#define MAX_MEMORY (128 * 1024 * 1024)
#define MAX_PAGES (MAX_MEMORY / PAGE_SIZE)
#define BITMAP_SIZE (MAX_PAGES / 8)

#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

void pmm_set_used(uint32_t page);

void pmm_set_free(uint32_t page);

int pmm_is_used(uint32_t page);

void *memset(void *ptr, int value, size_t num);

void pmm_init(void);

void pmm_test(void);