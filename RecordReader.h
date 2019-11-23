/* Class for reading the Records from the given Binary File and retrieving the
 * Records and their number
 * Source: Your given file verify.c */

#ifndef LOUKASPETEINARIS_PRJ2_RECORDREADER_H
#define LOUKASPETEINARIS_PRJ2_RECORDREADER_H

#include <cstdio>
#include <cerrno>
#include "Helper.h"

class RecordReader {
public:
    RecordReader(char*);
    MyRecord* fetchAllRecords();
    int getRecordsNumber();
private:
    const char* filename;
    int recordsNumber;
    static char* READING_MODE;
    static char* NO_INPUT_FILE_ERROR;
    static char* ERROR_OPENING_FILE_MESSAGE;
    static char* MALLOC_FAIL_ERROR_MESSAGE;
};


#endif //LOUKASPETEINARIS_PRJ2_RECORDREADER_H
