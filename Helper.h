#ifndef LOUKASPETEINARIS_PRJ2_HELPER_H
#define LOUKASPETEINARIS_PRJ2_HELPER_H

/* Helper Class contains various function that should not technically be
 * part of other classes and have more general usage */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>


class Helper {
public:
    static char* copyString(char*);
    static void handleError(const char*);
    static bool inArray(char*, char**, int);
    static char* removeNewLineCharacterFromString(char*);
    static void swapNumbers(int*, int*);
private:
    static const char* STRING_COPY_ERROR;
    static const char* STRING_CONCAT_ERROR;
    static bool hasStringNewLineCharacterInTheEnd(char*);
};

#endif //LOUKASPETEINARIS_PRJ2_HELPER_H
