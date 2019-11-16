/* Source: Your given file verify.c */

#ifndef LOUKASPETEINARIS_PRJ2_RECORDREADER_H
#define LOUKASPETEINARIS_PRJ2_RECORDREADER_H

#define SIZE_OF_BUFF 20
#define SSIZE_OF_BUFF 6

#include <cstdio>
#include <cerrno>
#include "Helper.h"

typedef struct{
    long  	custid;
    char 	FirstName[SIZE_OF_BUFF];
    char 	LastName[SIZE_OF_BUFF];
    char	Street[SIZE_OF_BUFF];
    int 	HouseID;
    char	City[SIZE_OF_BUFF];
    char	postcode[SSIZE_OF_BUFF];
    float  	amount;
} MyRecord;

class RecordReader {
public:
    RecordReader(char*);
    MyRecord* fetchAllRecords();
    int getRecordsNumber();
private:
    const char* filename;
    int recordsNumber;
    static const char* READING_MODE;
    static const char* NO_INPUT_FILE_ERROR;
    static const char* ERROR_OPENING_FILE_MESSAGE;
};


#endif //LOUKASPETEINARIS_PRJ2_RECORDREADER_H
