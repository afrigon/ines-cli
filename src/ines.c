#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "ines.h"
#include "color.h"

int ines_process(FILE* fp, int mode, char* out_path) {
    ines_header header;
    if (!fread(&header, sizeof(ines_header), 1, fp)) {
        puts("Could not read file");
        return -1;
    }

    if (header.magic != INES_MAGIC) {
        puts("The file is not an iNes file");
        return -1;
    }

    switch (mode) {
    case 0: print_ines_header(&header); return 0;
    case 1: return extract(fp, &header, out_path);
    default: return -1;
    }

    print_ines_header(&header);    
    return 0;
}

int extract(FILE* fp, ines_header* header, char* out_path) {
    int prg_size = header->prg_size * 16384;

    uint8_t data[prg_size];
    if (!fread(&data, prg_size, 1, fp)) {
        puts("Could not read program data");
        return -1;
    }

    FILE* output = fopen(out_path, "w");
    if (!fwrite(&data, prg_size, 1, output)) {
        puts("Could not write program data to output file");
        return -1;
    }
    fclose(output);
    return 0;
}

char* yes_no_string(bool condition) {
    return condition ?
        C_GREEN "yes" C_RESET :
        C_RED "no" C_RESET;
}

// TODO: Add more mapper
char* get_mapper(int value) {
    switch (value) {
        case 0: return "NROM";
        case 1: return "MMC1";
        case 2: return "UNROM";
        case 3: return "CNROM";
        case 4: return "MMC3";
        case 5: return "MMC5";
        default: return "unknown";
    }
}

void print_ines_header(ines_header* header) {
    printf("Program ROM size: %dKB\n", header->prg_size * 16);
    printf("Character ROM size: %dKB\n", header->chr_size * 8);

    uint8_t mapper = header->control1 >> 4 | (header->control2 & 0xF0);
    printf("Mapper: %s\n", get_mapper(mapper));

    printf("Mirroring: ");
    if (header->control1 & 8) printf("four screen\n");
    else if (header->control1 & 1) printf("vertical\n");
    else printf("horizontal\n");

    bool battery = header->control1 & 2;
    printf("Battery-backed Save RAM: %s", yes_no_string(battery));
    if (battery) 
        printf(", size: %dKB\n", (header->save_ram_size ? header->save_ram_size : 1) * 8);
    else printf("\n");

    printf("512 bytes Trainer: %s\n", yes_no_string(header->control1 & 4));
}
