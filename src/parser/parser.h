#include "../lexer/lexer.h"

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

enum ast_type {
    AST_NTYPE_PROGRAM,  /* 0  A Program node */
    AST_NTYPE_ADDITION, /* 1  An Addition node */
    AST_NTYPE_LIT_NUM   /* 2  A numerical literal */
};

struct ast_node {
    /* Store the `type` param that every node must have */
    enum ast_type type;

    /* Store a pointer to any struct that contains info
       specific to the node type */
    void *node_info;

    /* Store a reference to the head of a linked list
       of child nodes */
    struct ast_node *children;

    /* Store a reference to the next node in a children list
       this won't be used by the root node but all other nodes */
    struct ast_node *next;
};

/* Node info for the Program node */
struct ast_program_node_info {
    int ast_version;
};

/* Node info for the LIT_NUM node */
struct ast_lit_num_node_info {
    int value;
};

/** parse
 * Parses the provided linked list of lexer tokens to an AST
 * @param tokens_head The head of the lexer tokens.
 * @param ast_root The root of the ast.
*/
void parse(struct lexer_token *tokens_head, struct ast_node *ast_root);

void ast_print_tree(struct ast_node *root, int depth);

#endif  /* PARSER_PARSER_H_ */
