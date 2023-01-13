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

        /* Check for the token sequence that identified an addition expression
         * Sequence: LT_LIT_NUM, LT_ADD, LT_LIT_NUM
        */
        if (lexer_tokens_index - 1 >= 0 && lexer_tokens_index + 1 <= total_tokens &&
            current_token->type == LT_ADD) {
            /* Construct the AST nodes for the expression */
            struct ast_node *node = malloc(sizeof(struct ast_node));
            struct ast_node *left = malloc(sizeof(struct ast_node));
            struct ast_node *right = malloc(sizeof(struct ast_node));
            struct ast_lit_num_node_info *left_info = malloc(sizeof(struct ast_lit_num_node_info));
            struct ast_lit_num_node_info *right_info = malloc(sizeof(struct ast_lit_num_node_info));
            bzero(node, sizeof(struct ast_node));
            bzero(left, sizeof(struct ast_node));
            bzero(right, sizeof(struct ast_node));
            
            /* Fill in the top node */
            node->type = AST_NTYPE_ADDITION;

            /* Fill out the left node */
            left->type = AST_NTYPE_LIT_NUM;
            size_t left_data_size = tokens[lexer_tokens_index - 1]->data_len + 1;
            char *left_data = malloc(left_data_size);
            bzero(left_data, left_data_size);
            strncpy(left_data, tokens[lexer_tokens_index - 1]->data, left_data_size);
            left_info->value = atoi(left_data);
            left->node_info = (void *) left_info;
            
            /* Fill out the right node */
            right->type = AST_NTYPE_LIT_NUM;
            size_t right_data_size = tokens[lexer_tokens_index + 1]->data_len + 1;
            char *right_data = malloc(right_data_size);
            bzero(right_data, right_data_size);
            strncpy(right_data, tokens[lexer_tokens_index + 1]->data, right_data_size);
            right_info->value = atoi(right_data);
            right->node_info = (void *) right_info;

            /* Connect the nodes */
            node->children = left;
            left->next = right;
            right->next = NULL;
            printf("%p %p\n", (void*) left, (void*) right);
            struct ast_node *tmp_node = parent_node->children;
            printf("Before %p\n", (void*) tmp_node);
            if (tmp_node == NULL) {
                tmp_node = node;
                parent_node->children = tmp_node;
            } else {
                while (tmp_node->next) {
                    tmp_node = tmp_node->next;
                }
                tmp_node->next = node;
            }
            printf("After %p\n", (void *)tmp_node);
            printf("After %p\n", (void*) parent_node->children);
            printf("%d - ADD(%d + %d)\n", lexer_tokens_index, ((struct ast_lit_num_node_info*) left->node_info)->value, ((struct ast_lit_num_node_info*) right->node_info)->value);
        }
        
        lexer_tokens_index++;
    }

    /* Print the tree using preorder traversal*/
    printf("--------------\n");
    ast_print_tree(ast_root, 0);
    
    printf(MSG_INFO "Parser: Generated AST tree.\n");
}

void ast_print_tree(struct ast_node *root, int depth) {
    char *indent = malloc(depth);
    for (int i = 0; i < depth; i++) {
        indent[i] = '\t';
    }
    indent[depth] = 0;
    printf("%s^^^^^^^^^^^\n", indent);
    if (root == NULL) {
        printf("NULL RETURN\n");
        return;
    }
    
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
    printf("%sVVVVVVVVVV\n", indent);
}
