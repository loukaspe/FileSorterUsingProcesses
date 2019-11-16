#include "PipeReader.h"

const int PipeReader::FIFO_MODE = 0666;
const int PipeReader::OPEN_MODE = O_RDONLY | O_NONBLOCK;
const char* PipeReader::MKFIFO_ERROR = "ERROR: mkfifo() failed to create a new named pipe";
const char* PipeReader::OPEN_PIPE_ERROR = "ERROR: open() failed to open a named pipe";
const char* PipeReader::READING_ERROR = "ERROR: read() failed to write to a named pipe";

PipeReader::PipeReader(int fd, const char* filename, long bufferSize) {
    this->fd = fd;
    this->bufferSize = bufferSize;
    this->filename = filename;

    if(
        ( mkfifo(filename, FIFO_MODE) == -1 )
        && errno != EEXIST
    ) {
        handlePipeError(MKFIFO_ERROR);
    }
}


char* PipeReader::read() {
    char *stringReadByPipe = NULL;

    if(
        ( this->fd = open(this->filename, OPEN_MODE) ) == -1
    ) {
        handlePipeError(OPEN_PIPE_ERROR);
    }

    if(
        ::read( this->fd, stringReadByPipe, this->bufferSize ) < 0
    ) {
        handlePipeError(READING_ERROR);
    }

    return stringReadByPipe;
}

void PipeReader::handlePipeError(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}