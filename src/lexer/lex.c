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
        offset += t->read_len;

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
        printf("%d - %d characters at %p\n\t'", tok->type, tok->data_len, tok->data);
        for (unsigned int i = 0; i < tok->data_len; i++) {
            printf("%c", ((char*)tok->data)[i]);
        }
        printf("'\n");
        tok = tok->next_token;
    }
}

struct lexer_token lex_get_token(char *input, unsigned int offset) {
    char c = 0xA;  /* Char to track the current character */
    unsigned int cursor = offset;  /* Track the current position in the input */
    unsigned int accum_offset = 0;  /* Track the current position in the accumulator */
    int all_nums = 1;  /* Track if all of the characters are numbers */

    /* Create the accumulator to hold all of the data we want */
    char *accum = malloc(strlen(input));
    bzero(accum, strlen(input));

    /* Construct the basics of the token */
    struct lexer_token tok;
    tok.next_token = NULL;
    tok.data = accum;
    tok.type = LT_UNKNOWN;
    tok.data_len = 0;
    tok.read_len = 0;

    /* Print message */
    printf(MSG_INFO "Lexer: looking for token starting at position %d.\n", offset);

    /* Loop over each character and start searching for a token */
    while (c) {
        /* Update the current char */
        c = input[cursor];
            
        /* Update token */
        tok.read_len++;

        char next_char = input[cursor + 1];  /* Peek at the next character */
        
        /* Update the all_nums flag */
        for (unsigned int i = 0; i < strlen(accum); i++) {
            all_nums = all_nums && accum[i] >= '0' && accum[i] <= '9';
        }

        /* Check for a numerical literal */
        if ((lex_char_is_whitespace(c) || c == ';' || c == '\n')
            && all_nums && strlen(accum) > 0) {
            tok.type = LT_LIT_NUM;
            tok.read_len--;
            break;
        }

        /* Skip whitespace */
        if (lex_char_is_whitespace(c)) {
            cursor++;
            continue;
        }

        /* Add the current char to the accumulator */
        accum[accum_offset] = c;
        accum_offset++;

        /* Detect single char tokens */
        if (c == '+') {
            tok.type = LT_ADD;
            break;
        }
        if (c == '-') {
            tok.type = LT_SUB;
            break;
        }
        if (c == '*') {
            tok.type = LT_MULT;
            break;
        }
        if (c == '/') {
            tok.type = LT_DIV;
            break;
        }
        if (c == ';') {
            tok.type = LT_SEMICOLON;
            break;
        }
 
        cursor++;
    }

    /* Load the size of the data */
    tok.data_len = strlen(accum);

    /* Check for ignore tokens */
    if (tok.type == LT_UNKNOWN && tok.data_len == 0) {
        tok.type = LT_IGNORE;
    }

    /* Return the token */
    return tok;
}

int lex_char_is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
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

int lex_is_reserved_name(char *name, char *str) {
    return strcmp(name, str) == 0;
}
