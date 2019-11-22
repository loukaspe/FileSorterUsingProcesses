#include "PipeReader.h"

const int PipeReader::FIFO_MODE = 0666;
const int PipeReader::OPEN_MODE = O_RDONLY | O_NONBLOCK;
const char* PipeReader::MKFIFO_ERROR = "ERROR: mkfifo() failed to create a new named pipe";
const char* PipeReader::OPEN_PIPE_ERROR = "ERROR: open() failed to open a named pipe";
const char* PipeReader::READING_ERROR = "ERROR: read() failed to read from a named pipe";

PipeReader::PipeReader(int fd, const char* filename) {
    this->fd = fd;
    this->filename = filename;

    if(
        ( mkfifo(filename, FIFO_MODE) == -1 )
        && errno != EEXIST
    ) {
        handlePipeError(MKFIFO_ERROR);
    }

    if(
        ( this->fd = open(this->filename, OPEN_MODE) ) == -1
    ) {
        handlePipeError(OPEN_PIPE_ERROR);
    }
}


int PipeReader::readNumber() {
    int* number = (int*) malloc( sizeof(int) );
    int bufferSize = sizeof(int);

    if(
        ::read( this->fd, number, bufferSize ) < 0
    ) {
        handlePipeError(READING_ERROR);
    }

    return *number;
}

MyRecord* PipeReader::readRecords(long bufferSize) {
    MyRecord* records = (MyRecord*) malloc ( bufferSize );

    if(
        ::read( this->fd, records, bufferSize ) < 0
    ) {
        handlePipeError(READING_ERROR);
    }

    return records;
}

void PipeReader::handlePipeError(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}