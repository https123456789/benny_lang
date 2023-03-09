#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "../lexer/lexer.h"
#include "../blc.h"

void parse(struct lexer_token *tokens_head, struct ast_node *ast_root) {
    /* Clear the root */
    bzero(ast_root, sizeof(struct ast_node));
    
    struct lexer_token *current_token = tokens_head;
    int lexer_tokens_index = 0;
    struct ast_node *parent_node = ast_root;
    
    printf(MSG_INFO "Parser: Generating AST tree.\n");

    /* Clean off the root node */
    ast_root->type = AST_NTYPE_PROGRAM;
    struct ast_program_node_info root_info = { 0 };
    ast_root->node_info = (void*) &root_info;

    /* Compose an array of the tokens for simplified access */
    int total_tokens = count_lexer_tokens(tokens_head);
    printf("total tokens: %d\n", total_tokens);
    struct lexer_token **tokens = malloc(sizeof(struct lexer_token) * total_tokens);
    bzero((char*) tokens, sizeof(struct lexer_token) * total_tokens);

    /* Load each token into the array */
    while (current_token) {
        tokens[lexer_tokens_index] = current_token;
        lexer_tokens_index++;
        current_token = current_token->next_token;
    }

    /* Iterate over all of the tokens and try to construct the AST */
    lexer_tokens_index = 0;
    while (lexer_tokens_index < total_tokens) {
        current_token = tokens[lexer_tokens_index];
        printf("Current Token: %d.\n", current_token->type);

        /* Check for fundamental math operators */
        if (lexer_tokens_index - 1 >= 0 && lexer_tokens_index + 1 <= total_tokens &&
            (current_token->type == LT_ADD || current_token->type == LT_SUB ||
             current_token->type == LT_MULT || current_token->type == LT_DIV)) {
            /* Check for invalid right or left tokens */
            if (tokens[lexer_tokens_index - 1]->type != LT_LIT_NUM) {
                fprintf(stderr, MSG_ERROR "Expected left hand value to be a numerical literal. Got '\x1b[95m%s\x1b[0m'.\n", lex_token_to_string(tokens[lexer_tokens_index - 1]));
                exit(1);
            }
            if (tokens[lexer_tokens_index + 1]->type != LT_LIT_NUM) {
                fprintf(stderr, MSG_ERROR "Expected right hand value to be a numerical literal. Got '\x1b[95m%s\x1b[0m'.\n", lex_token_to_string(tokens[lexer_tokens_index + 1]));
                exit(1);
            }
            
            /* Construct the AST nodes for the expression */
            struct ast_node *node = malloc(sizeof(struct ast_node));
            struct ast_node *left = malloc(sizeof(struct ast_node));
            struct ast_node *right = malloc(sizeof(struct ast_node));
            struct ast_lit_num_node_info *left_info = malloc(sizeof(struct ast_lit_num_node_info));
            struct ast_lit_num_node_info *right_info = malloc(sizeof(struct ast_lit_num_node_info));
            bzero(node, sizeof(struct ast_node));
            
            /* Fill in the nodes */
            switch (current_token->type) {
                case LT_SUB:
                    node->type = AST_NTYPE_SUBTRACTION;
                    break;
                case LT_MULT:
                    node->type = AST_NTYPE_MULTIPLICATION;
                    break;
                case LT_DIV:
                    node->type = AST_NTYPE_DIVISION;
                    break;
                case LT_ADD:
                default:
                    node->type = AST_NTYPE_ADDITION;
                    break;
            }
            construct_ast_lit_num_node(left, tokens[lexer_tokens_index - 1], left_info);
            construct_ast_lit_num_node(right, tokens[lexer_tokens_index + 1], right_info);
            
            /* Connect the nodes */
            node->children = left;
            left->next = right;
            right->next = NULL;
            ast_add_to_node_children(parent_node, node);

            char symbol = '+';
            switch (current_token->type) {
                case LT_SUB:
                    symbol = '-';
                    break;
                case LT_MULT:
                    symbol = '*';
                    break;
                case LT_DIV:
                    symbol = '/';
                    break;
                default:
                    break;
            }

            printf("%d --> %d %c %d\n", lexer_tokens_index, ((struct ast_lit_num_node_info*) left->node_info)->value, symbol, ((struct ast_lit_num_node_info*) right->node_info)->value);

        }

        /* Check for function definitions */
        if (current_token->type == LT_FN && lexer_tokens_index + 1 <= total_tokens) {
            if (tokens[lexer_tokens_index + 1]->type != LT_IDENT) {
                fprintf(stderr, MSG_ERROR "Expected an indetifier after keyword '\x1b[95mfn\x1b[0m'. Got '\x1b[95m%s\x1b[0m'.\n", lex_token_to_string(tokens[lexer_tokens_index + 1]));
                exit(1);
            }
            char *fn_name = lex_token_to_string(tokens[lexer_tokens_index + 1]);
            printf("fn %s\n", fn_name);

            /* Construct the AST node */
            struct ast_node *node = malloc(sizeof(struct ast_node));
            struct ast_fn_node_info *node_info = malloc(sizeof(struct ast_fn_node_info));
            bzero((char*) node, sizeof(struct ast_node));
            bzero((char*) node_info, sizeof(struct ast_fn_node_info));

            /* Build the node's info */
            node_info->name = fn_name;

            /* Search for arguments */
            if (tokens[lexer_tokens_index + 2]->type != LT_LPAREN) {
                fprintf(stderr, MSG_ERROR "Expected '(' after function name but got '\x1b[95m%s\x1b[0m'.\n", lex_token_to_string(tokens[lexer_tokens_index + 2]));
                exit(1);
            }
            
            int i = lexer_tokens_index + 3;
            struct lexer_token *t = tokens[i];
            int on_ident = 1;
            int on_name = 1;
            while (i < total_tokens) {
                printf("%d -- %s\n", t->type, lex_token_to_string(t));
                if (t->type == LT_RPAREN) {
                    if (on_ident || !on_name) {
                        fprintf(stderr, MSG_ERROR "Unexpected end to arguments list.\n");
                        exit(1);
                    }
                    break;
                }
                if (on_ident) {
                    if (t->type != LT_IDENT && t->type != LT_LIT_TYPENAME) {
                        fprintf(stderr, MSG_ERROR "Expected an identifier. Got '\x1b[95m%s\x1b[0m' type %d.\n", lex_token_to_string(t), t->type);
                        exit(1);
                    }
                    if (on_name) {
                        char *arg_name = lex_token_to_string(t);
                        printf("ARG NAME: %s\n", arg_name);
                        on_name = 0;
                    } else {
                        on_name = 1;
                    }
                    on_ident = 0;
                } else {
                    on_ident = 1;
                }
                i++;
                t = tokens[i];
            }
            
            node->type = AST_NTYPE_FN;
            node->node_info = (void*) node_info;

            /* Connect the node */
            ast_add_to_node_children(parent_node, node);
        }

        lexer_tokens_index++;
    }

    /* Print the tree using preorder traversal*/
    printf("--------------\n");
    /*ast_print_tree(ast_root, 0);*/
    {
        char *str;
        str = ast_to_str(ast_root, NULL, 0);
        printf("%s\n", str);
        free(str);
        str = NULL;
    }

    printf(MSG_INFO "Parser: Generated AST tree.\n");
}

void construct_ast_lit_num_node(struct ast_node *node,
                                struct lexer_token *token,
                                struct ast_lit_num_node_info *node_info) {
    /* Clear out any existing data in the node */
    bzero((char*) node, sizeof(struct ast_node));
    bzero((char*) node_info, sizeof(struct ast_lit_num_node_info));

    /* Set the node type */
    node->type = AST_NTYPE_LIT_NUM;

    /* Coerce the raw token data into a valid C string and then turn it into an int */
    size_t node_data_size = token->data_len + 1;
    char *node_data = malloc(node_data_size);  /* skipcq: CXX-S1006 */
    bzero(node_data, node_data_size);
    strncpy(node_data, token->data, node_data_size);

    /* Load the value and info into the node */
    node_info->value = atoi(node_data);
    node->node_info = (void*) node_info;
}

void ast_add_to_node_children(struct ast_node *parent, struct ast_node *node) {
    struct ast_node *tmp_node = parent->children;
    if (tmp_node == NULL) {
        tmp_node = node;
        parent->children = tmp_node;
    } else {
        while (tmp_node->next) {
            tmp_node = tmp_node->next;
        }
        tmp_node->next = node;
    }
}

const char *ast_type_to_str(enum ast_type type) {
    const char *ast_type_strs[] = {
        "Program",
        "Addition",
        "Subtraction",
        "Multiplication",
        "Division",
        "Numerical Literal",
        "Function"
    };
    return ast_type_strs[type];
}
