#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../blc.h"
#include "./lexer.h"

void lex(char *input, struct lexer_token *head) {
    /* Pointer to track the current token */
    head = NULL;
    struct lexer_token *current_tok = head;

    /* Track the offset in the input */
    unsigned int offset = 0;

    /* Keep reading tokens till we've hit the end of the input */
    while (offset < strlen(input)) {
        /* Get the next token */
        struct lexer_token *t = malloc(sizeof(struct lexer_token));
        *t = lex_get_token(input, offset);

        /* Move the offset forward */
        offset += t->data_len;

        /* Add the token to the linked list */
        if (current_tok == NULL) {
            current_tok = t;
            current_tok->next_token = NULL;
            head = current_tok;
        } else {
            current_tok->next_token = t;
            current_tok = current_tok->next_token;
        }
    }

    /* Count the total number of tokens found */
    int total_tokens = count_lexer_tokens(head);
    printf(MSG_INFO "Lexer found %d tokens.\n", total_tokens);

    /* Print all of the tokens */
    printf("Tokens Found:\n");
    struct lexer_token *tok = head;
    while (tok) {
        printf("%d\n", tok->type);
        tok = tok->next_token;
    }
}

struct lexer_token lex_get_token(char *input, unsigned int offset) {
    char c;  /* Track the current character */
    unsigned int cursor = offset;  /* Tracks the position in the string */
    /* Create the accumulator to hold onto the current "read" text */
    char *accum = malloc(strlen(input));
    bzero(accum, strlen(input));  /* Make sure to clear it */

    /* Create a token fill in the basics */
    struct lexer_token tok;
    tok.next_token = NULL;
    tok.data = NULL;
    tok.type = LT_UNKNOWN;
    tok.data_len = 0;

    /* Print a nice message */
    printf(MSG_INFO "Lexer: Finding next token starting at %d.\n", offset);

    /* Do the actual finding */
    while (cursor < strlen(input)) {
        int accum_offset = cursor - offset;
        c = input[cursor];
        accum[accum_offset] = c;
        tok.data_len++;

        char next_char = accum[accum_offset + 1];
        int next_char_is_whitespace = (
            next_char == ' ' ||
            next_char == '\t' ||
            next_char == '\n');

        if (strcmp("fn", accum + accum_offset - 1) == 0 &&
            (cursor - offset <= 1 || input[cursor - 2] == ' ') &&
            (next_char == '\0' || next_char_is_whitespace)) {
            tok.type = LT_FN;
            tok.data = input + cursor;
            break;
        }

        cursor++;
    }

    /* Free the accumulator */
    free(accum);

    /* Return the token */
    return tok;
}

int count_lexer_tokens(struct lexer_token *head) {
    // Create a pointer to track the current token
    struct lexer_token *current = head;

    // Create a simple counter
    int count = 0;

    // Traverse the list
    while (current) {
        count++;
        current = current->next_token;
    }

    // Return the count
    return count;
}
