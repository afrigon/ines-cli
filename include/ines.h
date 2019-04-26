#ifndef INES_MAGIC_H
#define INES_MAGIC_H

#include <stdbool.h>

#define INES_MAGIC 0x1A53454E

typedef struct {
    uint32_t magic;
    uint8_t prg_size;
    uint8_t chr_size;
    uint8_t control1;
    uint8_t control2;
    uint8_t save_ram_size;
    char padding[7];
} ines_header;

int ines_process(FILE* fp, int mode, char* out_path);
char* yes_no_string(bool condition);
char* get_mapper(int value);
int extract(FILE* fp, ines_header* header, char* out_path);
void print_ines_header(ines_header* header);

#endif
