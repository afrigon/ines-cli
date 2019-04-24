#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "ines.h"

int print_usage(char* name) {
    fprintf(stderr, "Usage: %s [-e] [file...]\n", name);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "e")) != -1) {
        switch (opt) {
        //case 'e': mode = EXTRACT_MODE; break;
        default: print_usage(argv[0]);
        }
    }

    if (optind >= argc) print_usage(argv[0]);

    int ret = 0;
    for (int i = optind; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == 0) {
            fprintf(stderr, "%s: failed to open %s (%d %s)\n",
                    argv[0],
                    argv[i],
                    errno,
                    strerror(errno));
            ret = EXIT_FAILURE;
            continue;
        }

        printf("File %d is %s", i, argv[i]);
        fclose(fp);
    }

    return ret;
}

