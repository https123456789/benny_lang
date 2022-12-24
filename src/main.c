#include <stdio.h>
#include "./blc.h"
#include "lexer/lexer.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid arguments. Usage:\nblc file\n");
        return -1;
    }

    printf(MSG_INFO "blc 0.0.1-dev\n");

    /* Read the input from the file */
    printf(MSG_INFO "Reading input file %s...\n", argv[1]);
    char *input = read_file(argv[1]);

    /* Lexing */
    struct lexer_token lexer_tokens;
    lex(input, &lexer_tokens);
    return 0;
}
