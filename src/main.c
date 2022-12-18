#include <stdio.h>
#include "blc.h"

int main(int argc, char **argv) {
		if (argc != 2) {
				fprintf(stderr, "Error: Invalid arguments. Usage:\nblc file\n");
				return -1;
		}
		printf("blc 0.0.1-dev\n");
		printf("Reading input file %s...\n", argv[1]);
		char *input = read_file(argv[1]);
		printf("%s", input);
		return 0;
}
