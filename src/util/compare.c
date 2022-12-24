#include "./compare.h"  /* NOLINT */

int partial_string_compare(char *str1, char *str2, int str2_len) {
    int index = 0;
    while (str1[index] == str2[index] && index <= str2_len) {
        printf("\n| %c -- %c |\n", str1[index], str2[index]);
        index++;
    }
    return (index == str2_len) - 1;
}
