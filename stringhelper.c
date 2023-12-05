#include "headers.h"


void removeChar(char *str, char target) {
    int i, j;
    int len = strlen(str);

    for (i = j = 0; i < len; i++) {
        if (str[i] != target) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0'; // Terminate the string at the new length
}
