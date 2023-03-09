#include "../lexer/lexer.h"

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

enum ast_type {
    AST_NTYPE_PROGRAM,        /* 0  A Program node         */
    AST_NTYPE_ADDITION,       /* 1  An Addition node       */
    AST_NTYPE_SUBTRACTION,    /* 2  A subtraction node     */
    AST_NTYPE_MULTIPLICATION, /* 3  A multiplication node  */
    AST_NTYPE_DIVISION,       /* 4  A division node        */
    AST_NTYPE_LIT_NUM,        /* 5  A numerical literal    */
    AST_NTYPE_FN              /* 6  A function definition  */
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

/* Node info for the Function node */
struct ast_fn_node_info {
    /* Name of the function */
    char *name;

    /* Return type of the function as an identifier */
    char *return_type;

    /* A linked list of the function's arguments */
    struct ast_fn_arg_info *args;
};

/* A struct for holding information regarding the arguments to
   a function when they are represented in the AST tree */
struct ast_fn_arg_info {
    /* The name of the argument */
    char *name;

    /* The type of the argument */
    char *type;
};

/** parse
 * Parses the provided linked list of lexer tokens to an AST
 * @param tokens_head The head of the lexer tokens.
 * @param ast_root The root of the ast.
*/
void parse(struct lexer_token *tokens_head, struct ast_node *ast_root);

/** ast_to_str
 * Turns the provided AST tree into a C string.
 * The main use for this function is for generating AST files.
 * @param root The root node of the AST tree.
 * @param res The string into which the result will be written.
*/
char* ast_to_str(struct ast_node *root, char *res, int depth);

/** ast_node_to_str
 * Turns the provided AST node into a C string.
 * @param node The AST node.
 * @param res The buffer to hold the data. If NULL, a new buffer will be made. It is your responsibility to free.
 * @return The string.
*/
char *ast_node_to_str(struct ast_node *node, char *res);

/** construct_ast_lit_num_node
 * Constructs an AST node with the type LIT_NUM and fills it with all of the required data.
 * @param node The AST node.
 * @param token The lexer token containing the node's data.
 * @param node_info The struct to hold the node info.
*/
void construct_ast_lit_num_node(struct ast_node *node, struct lexer_token *token, struct ast_lit_num_node_info *node_info);

/** ast_add_to_node_children
 * Appends the given node to the given parent node's list of children
 * @param parent The parent node.
 * @param node The node to add.
*/
void ast_add_to_node_children(struct ast_node *parent, struct ast_node *node);

/** ast_type_to_str
 * Returns the matching string representation of the provided ast_type
 * @param type The type
 * @return The string representation of the type
*/
const char *ast_type_to_str(enum ast_type type);

#endif  /* PARSER_PARSER_H_ */
