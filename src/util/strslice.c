#include <string.h>
#include "strslice.h"

void strslice(const char *source, char *result, size_t start, size_t end) {
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        result[j++] = source[i];
    }
    result[j] = 0;
}
