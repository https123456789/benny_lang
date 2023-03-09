#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* ast_to_str(struct ast_node *root, char *res, int depth) {
    /* Allocate space for the string */
    if (res == NULL) {
        res = malloc(255 * sizeof(char));
        bzero(res, 255);
    } else {
        if (strlen(res) < 254) {
            void *nptr = realloc(res, 255);
            if (nptr == NULL) {
                perror("ast_to_str: realloc: ");
                exit(errno);
            }
            res = nptr;
        }
    }

    /* Construct a string for the indentation */
    char *indent = malloc((depth + 1) * sizeof(char));
    bzero(indent, depth + 1);
    memset(indent, ' ', depth);

    /* Make sure the root is not NULL */
    if (root == NULL) {
        return res;
    }
    
    /* Setup vars */
    struct ast_node *current_node = root;

    /* Print the current node */
    {
        /* Generate the string representation of the current node */
        char *str = ast_node_to_str(current_node, NULL);
        /* Calculate the new size of res (including a new line) */
        ssize_t new_size = strlen(res) + strlen(indent) + strlen(str) + 2;

        /* Resize the buffer to make room */
        char *tptr = realloc(res, new_size);
        if (tptr == NULL) {  /* Make sure it is valid */
            perror("ast_to_str: realloc: ");
            exit(errno);
        }

        /* Make the resize official*/
        res = tptr;
        tptr = NULL;

        /* Append the str onto the buffer */
        strcat(res, indent);
        strcat(res, str);
        strcat(res, "\n");

        /* Clean up */
        free(str);
        str = NULL;
    }

    /* Print the children */
    struct ast_node *current_child = current_node->children;
    int total_children = 0;
    while (current_child) {
        total_children++;
        {
            /* Generate the string representation of the current node */
            char *str = ast_to_str(current_child, NULL, depth + 1);
            /* Calculate the new size of res */
            ssize_t new_size = strlen(res) + strlen(indent) + strlen(str) + 1;

            /* Resize the buffer to make room */
            char *tptr = realloc(res, new_size);
            if (tptr == NULL) {  /* Make sure it is valid */
                perror("ast_to_str: realloc: ");
                exit(errno);
            }

            /* Make the resize official*/
            res = tptr;
            tptr = NULL;

            /* Append the str onto the buffer */
            strcat(res, indent);
            strcat(res, str);

            /* Clean up */
            free(str);
            str = NULL;
        }
        current_child = current_child->next;
    }

    free(indent);
    indent = NULL;

    return res;
}

char *ast_node_to_str(struct ast_node *node, char *res) {
    /* Format used to represent the node */
    const char *format = "%s(type=%d) %p";

    /* Determine how many bytes we need to hold the str */
    ssize_t blen = snprintf(
        NULL, 0, format,
        ast_type_to_str(node->type),
        node->type,
        (void*) node
    ) + 1;

    /* Allocate space for the string */
    if (res == NULL) {
        res = malloc(blen * sizeof(char));
    } else {
        void *nptr = realloc(res, blen);

        /* Make sure the pointer is valid */
        if (nptr == NULL) {
            perror("ast_node_to_str: realloc: ");
            exit(errno);
        }
        
        res = nptr;
    }

    /* Clear the provided buffer */
    bzero(res, blen);

    /* Actually print the node as a string */
    sprintf(
        res, format,
        ast_type_to_str(node->type),
        node->type,
        (void*) node
    );

    return res;
}
