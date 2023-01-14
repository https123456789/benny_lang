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

        /* Check for fundamental math operators */
        if (lexer_tokens_index - 1 >= 0 && lexer_tokens_index + 1 <= total_tokens &&
            (current_token->type == LT_ADD || current_token->type == LT_SUB ||
             current_token->type == LT_MULT || current_token->type == LT_DIV)) {
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

        lexer_tokens_index++;
    }

    /* Print the tree using preorder traversal*/
    printf("--------------\n");
    ast_print_tree(ast_root, 0);
    
    printf(MSG_INFO "Parser: Generated AST tree.\n");
}

void ast_print_tree(struct ast_node *root, int depth) {
    /* Construct a string for the indentation */
    char *indent = malloc(depth);
    for (int i = 0; i < depth; i++) {
        indent[i] = '\t';
    }
    indent[depth] = 0;

    /* Make sure the root is not NULL */
    if (root == NULL) {
        printf("NULL RETURN\n");
        return;
    }
    
    /* Setup vars */
    struct ast_node *current_node = root;

    /* Print the current node */
    printf("%s%d\n", indent, current_node->type);
    printf("%s|\n", indent);

    /* Print the children */
    struct ast_node *current_child = current_node->children;
    int total_children = 0;
    while (current_child) {
        printf("%s%p\n", indent, (void*) current_child);
        total_children++;
        ast_print_tree(current_child, depth + 1);
        current_child = current_child->next;
    }
    printf("%sTotal Children: %d\n", indent, total_children);
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
    char *node_data = malloc(node_data_size);
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
