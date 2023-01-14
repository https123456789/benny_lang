#include <stdio.h>
#include <stdlib.h>
#include "./blc.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

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
    lexer_tokens = *(lex(input, &lexer_tokens)); 
    
    /* Parse */
    struct ast_node *ast_root = malloc(sizeof(struct ast_node));
    parse(&lexer_tokens, ast_root);

    /* Free memory */
    free(input);
    /* TODO: FREE AST */

    return 0;
}
