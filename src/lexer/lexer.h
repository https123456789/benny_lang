#ifndef LEXER_LEXER_H_
#define LEXER_LEXER_H_

/* Token Types */
enum lexer_token_type {
    /* Literals */
    LT_LIT_NUM,         /* A numerical literal */
    LT_LIT_STR,         /* A string literal */
    LT_LIT_TYPENAME,    /* A typename literal */

    /* Keywords */
    LT_IF,              /* An if keyword */
    LT_ELSE,            /* An else keyword */
    LT_IMPORT,          /* An import keyword */
    LT_EXPORT,          /* An export keyword */
    LT_FN,              /* A fn keyword */
    LT_RETURN,          /* A return keyword */

    /* Math */
    LT_ADD,             /* An addition symbol */
    LT_SUB,             /* A subtraction symbol */
    LT_MULT,            /* A multiplication symbol */
    LT_DIV,             /* A division symbol */

    /* Misc */
    LT_UNKNOWN,         /* Unknown token */
    LT_WHITESPACE,      /* Whitespace */
    LT_IDENT,           /* An identifier */
    LT_LBRACE,          /* A left brace */
    LT_RBRACE,          /* A right brace */
    LT_SEMICOLON,       /* A semicolon */
    LT_LPAREN,          /* A left parenthesis */
    LT_RPAREN,          /* A right parenthesis */
    LT_LBRACK,          /* A left bracket */
    LT_RBRACK,          /* A right bracket */
    LT_PRODUCES         /* A produces symbol */
};

struct lexer_token {
    enum lexer_token_type type;
    void *data;
    unsigned int data_len;
    struct lexer_token *next_token;
};

/** lex
 * Run the specified string through lexical analysis
 * @param input The input string.
 * @param head A lexer_token that will be the head of a linked list
*/
void lex(char *input, struct lexer_token *head);

/** lex_get_token
 * Returns the next token in the specified input after the offset
 * @param input The input string
 * @param offset The offset to start the search at
 * @return A lexer token that is the next token in the string
*/
struct lexer_token lex_get_token(char *input, unsigned int offset);

/** count_lexer_tokens
 * Counts the total number of tokens in a provided linked list of tokens
 * @param head The first token in the linked list
 * @returns The total number of tokens
*/
int count_lexer_tokens(struct lexer_token *head);

#endif  // LEXER_LEXER_H_
