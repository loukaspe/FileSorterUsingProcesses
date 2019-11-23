#include "RecordReader.h"

char* RecordReader::NO_INPUT_FILE_ERROR = "ERROR: No Input File was found.\n";
char* RecordReader::READING_MODE = "rb";
char* RecordReader::ERROR_OPENING_FILE_MESSAGE = "Cannot open binary file\n";
char* RecordReader::MALLOC_FAIL_ERROR_MESSAGE = "ERROR: malloc() failed to "
                                                "allocate memory";

RecordReader::RecordReader(char* filename) {
    this->filename = filename;
    this->recordsNumber = 0;
}

MyRecord* RecordReader::fetchAllRecords() {
    if(filename == NULL) {
        Helper::handleError(NO_INPUT_FILE_ERROR);
    }

    FILE* inputFile;
    MyRecord* records;
    long lSize;
    errno = 0;

    inputFile = fopen(filename, READING_MODE );
    if (inputFile == NULL ) {
        printf("Error %d \n", errno);
        Helper::handleError(RecordReader::ERROR_OPENING_FILE_MESSAGE);
    }

    fseek (inputFile , 0 , SEEK_END);
    lSize = ftell(inputFile);
    rewind (inputFile);
    this->recordsNumber = (int) lSize / sizeof(MyRecord);

    records = (MyRecord*) malloc (this->recordsNumber * sizeof(MyRecord));
    if(records == NULL) {
        Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
    }

    for(int i = 0; i < this->recordsNumber; i++) {
        fread(records + i, sizeof(MyRecord), 1, inputFile);
    }

    fclose(inputFile);
    return records;
}

int RecordReader::getRecordsNumber() {
    return recordsNumber;
}