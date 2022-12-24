#include "./strip.h"  /* NOLINT */

char *strip_raw_data(char *data, unsigned int len) {
    char *c = data;
    unsigned int dist = 0;
    while (dist < len && (*c == ' ' || *c == '\t')) {
        c++;
        dist++;
    }
    return c;
}
