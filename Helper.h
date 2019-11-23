#ifndef LOUKASPETEINARIS_PRJ2_HELPER_H
#define LOUKASPETEINARIS_PRJ2_HELPER_H

/* Helper Class contains various function that should not technically be
 * part of other classes and have more general usage */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "Record.h"
#include "SorterTypeFactory.h"

class Helper {
public:
    static void handleError(const char*);
    static bool inArray(int, int[], int);
    static void swapRecords(MyRecord*, MyRecord*);
    static char* getRecordColumnAsString(MyRecord*, int);
    static MyRecord* createSubsetOfRecords(MyRecord*, int, int);
    static void handleGivenHeapCoachFromCommandLine(
        int*, int, int[], SorterTypeFactory*, int
    );
    static void handleGivenQuickCoachFromCommandLine(
        int*, int, int[], SorterTypeFactory*, int
    );
private:
    static char* NO_SUCH_RECORD_COLUMN_ERROR_MESSAGE;
};

#endif //LOUKASPETEINARIS_PRJ2_HELPER_H
