#include <stddef.h>

#ifndef UTIL_STRSLICE_H_
#define UTIL_STRSLICE_H_

/** strslice
 * Returns a C string that is a slice of the source string.
 * @param source The source C string.
 * @param start The start position (inclusive).
 * @param end The end position (inclusive).
 * @return The C string slice of the source.
*/
void strslice(const char *source, char *result, size_t start, size_t end);

#endif  // UTIL_STRSLICE_H_
