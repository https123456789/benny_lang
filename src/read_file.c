#include <stdlib.h>
#include <stdio.h>
#include "./blc.h"

char *read_file(char *file_name) {
    char *data = malloc(256 * sizeof(char));
    int chars = 0;
    /*
        This is an int account for the fact that EOF (-1) will
        wrap on systems where the default signedness of a char is signed (like a raspberry pi)
    */
    int c = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Failed to open source file.\n");
        exit(-1);
    }

    while ((c = fgetc(file)) != EOF) {
        /* printf("%c", c); */
        chars++;
        /* Allocate room for a new character */
        void *realloc_p = realloc(data, chars);
        if (realloc_p == NULL) {
            fprintf(stderr, "Error: Failed to allocate room for the input.\n");
            exit(-1);
        }
        data = realloc_p;
        data[chars - 1] = c;
    }

    fclose(file);
    return data;
}
