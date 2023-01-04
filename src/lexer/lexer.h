#ifndef LEXER_LEXER_H_
#define LEXER_LEXER_H_

#define RESERVED_NAME_ALIEN     "alien"
#define RESERVED_NAME_BREAK     "break"
#define RESERVED_NAME_CASE      "case"
#define RESERVED_NAME_CHAR      "char"
#define RESERVED_NAME_CLASS     "class"
#define RESERVED_NAME_CLOSURE   "closure"
#define RESERVED_NAME_CONST     "const"
#define RESERVED_NAME_CONTINUE  "continue"
#define RESERVED_NAME_DEFAULT   "default"
#define RESERVED_NAME_DO        "do"
#define RESERVED_NAME_DOUBLE    "double"
#define RESERVED_NAME_ELSE      "else"
#define RESERVED_NAME_ENUM      "enum"
#define RESERVED_NAME_EXPORT    "export"
#define RESERVED_NAME_FLOAT     "float"
#define RESERVED_NAME_FN        "fn"
#define RESERVED_NAME_FOR       "for"
#define RESERVED_NAME_IF        "if"
#define RESERVED_NAME_IMPORT    "import"
#define RESERVED_NAME_INT       "int"
#define RESERVED_NAME_INT8      "int8"
#define RESERVED_NAME_INT16     "int16"
#define RESERVED_NAME_INT64     "int64"
#define RESERVED_NAME_NEVER     "never"
#define RESERVED_NAME_THIS      "this"
#define RESERVED_NAME_RETURN    "return"
#define RESERVED_NAME_SIGNED    "signed"
#define RESERVED_NAME_SIZEOF    "sizeof"
#define RESERVED_NAME_STATIC    "static"
#define RESERVED_NAME_STRUCT    "struct"
#define RESERVED_NAME_SWITCH    "switch"
#define RESERVED_NAME_TYPEALIAS "typealias"
#define RESERVED_NAME_UNION     "union"
#define RESERVED_NAME_UNSIGNED  "unsigned"
#define RESERVED_NAME_WHILE     "while"

/* Token Types */
enum lexer_token_type {
    /* Literals */
    LT_LIT_NUM,         /* 0  A numerical literal */
    LT_LIT_STR,         /* 1  A string literal */
    LT_LIT_TYPENAME,    /* 2  A typename literal */

    /* Keywords */
    LT_IF,              /* 3  An if keyword */
    LT_ELSE,            /* 4  An else keyword */
    LT_IMPORT,          /* 5  An import keyword */
    LT_EXPORT,          /* 6  An export keyword */
    LT_FN,              /* 7  A fn keyword */
    LT_RETURN,          /* 8  A return keyword */

    /* Math */
    LT_ADD,             /* 9  An addition symbol */
    LT_SUB,             /* 10 A subtraction symbol */
    LT_MULT,            /* 11 A multiplication symbol */
    LT_DIV,             /* 12 A division symbol */

    /* Misc */
    LT_UNKNOWN,         /* 13 Unknown token */
    LT_IDENT,           /* 14 An identifier */
    LT_LBRACE,          /* 15 A left brace */
    LT_RBRACE,          /* 16 A right brace */
    LT_SEMICOLON,       /* 17 A semicolon */
    LT_LPAREN,          /* 18 A left parenthesis */
    LT_RPAREN,          /* 19 A right parenthesis */
    LT_LBRACK,          /* 20 A left bracket */
    LT_RBRACK,          /* 21 A right bracket */
    LT_PRODUCES,        /* 22 A produces symbol */
    LT_IGNORE           /* 23 Ignore */
};

struct lexer_token {
    enum lexer_token_type type;
    void *data;
    unsigned int data_len;
    unsigned int read_len;
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

/** lex_char_is_whitespace
 * Determines if the specified character is whitespace.
 * @param c The character.
 * @returns 1 is yes, 0 if no
*/
int lex_char_is_whitespace(char c);

/** count_lexer_tokens
 * Counts the total number of tokens in a provided linked list of tokens
 * @param head The first token in the linked list
 * @returns The total number of tokens
*/
int count_lexer_tokens(struct lexer_token *head);

/** lex_is_valid_ident
 * Determines if the identifier is valid from the perspective of the lexer.
 * @param str The string.
 * @returns 0 on an invalid identifier and 1 on a valid identifier.
*/
int lex_is_valid_ident(char *str);

/** lex_is_reserved_name
 * Determines if the specified string is a reserved name.
 * @param name The reserved name.
 * @param str The string.
 * @return 0 if false, 1 if true.
*/
int lex_is_reserved_name(char *name, char *str);

#endif  // LEXER_LEXER_H_
