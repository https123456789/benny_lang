#ifndef UTIL_COMPARE_H_
#define UTIL_COMPARE_H_

/** partial_string_compare
 * Compares a full C string to a partial C string
 * @param str1 A full C string
 * @param str2 A partial C string
 * @param str2_len The length of the partial C string
 * @return 0 The parial string matches the full string
 *         -1 The partial string doesn't match the full string
*/
int partial_string_compare(char *str1, char *str2, int str2_len);

#endif  // UTIL_COMPARE_H_
