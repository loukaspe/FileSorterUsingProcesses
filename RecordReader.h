/* Source: Your given file verify.c */

#ifndef LOUKASPETEINARIS_PRJ2_RECORDREADER_H
#define LOUKASPETEINARIS_PRJ2_RECORDREADER_H

#define SIZE_OF_BUFF 20
#define SSIZE_OF_BUFF 6

#include <cstdio>

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
private:
    const char* READING_MODE;
};


#endif //LOUKASPETEINARIS_PRJ2_RECORDREADER_H
