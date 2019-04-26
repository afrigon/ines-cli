#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ines.h"

#pragma pack(1)

enum mode {
    MODE_PRINT = 0,
    MODE_EXTRACT = 1
};

int print_usage(char* name) {
    fprintf(stderr, "Usage: %s [-e output] [file...]\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int mode;
    char* out_path;

    int opt;
    while ((opt = getopt(argc, argv, "e:")) != -1) {
        switch (opt) {
        case 'e': 
            out_path = optarg;
            mode = MODE_EXTRACT;
            break;
        default: print_usage(argv[0]);
        }
    }

    if (optind >= argc) print_usage(argv[0]);

    int ret = 0;
    for (int i = optind; i < argc; ++i) {
        FILE* fp = fopen(argv[i], "r");
        if (fp == 0) {
            fprintf(stderr, "%s: failed to open %s (%d %s)\n",
                    argv[0],
                    argv[i],
                    errno,
                    strerror(errno));
            return EXIT_FAILURE;
        }

        ret = ines_process(fp, mode, out_path);
        if (ret) {
            fprintf(stderr, "%s: failed to process %s (%d %s)\n",
                    argv[0],
                    argv[i],
                    errno,
                    strerror(errno));
        }
        fclose(fp);
    }

    return ret;
}

