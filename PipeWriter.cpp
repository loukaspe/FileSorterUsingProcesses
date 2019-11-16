#include "PipeWriter.h"

const int PipeWriter::FIFO_MODE = 0666;
const int PipeWriter::OPEN_MODE = O_WRONLY | O_NONBLOCK;
const char* PipeWriter::MKFIFO_ERROR = "ERROR: mkfifo() failed to create a new named pipe";
const char* PipeWriter::OPEN_PIPE_ERROR = "ERROR: open() failed to open a named pipe";
const char* PipeWriter::WRITING_ERROR = "ERROR: write() failed to write to a named pipe";

PipeWriter::PipeWriter(int fd, const char* filename, long bufferSize) {
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


char* PipeWriter::write() {
    char *stringReadByPipe = NULL;

    if(
        ( this->fd = open(this->filename, OPEN_MODE) ) < 0
    ) {
        handlePipeError(OPEN_PIPE_ERROR);
    }

    if(
            ::read( this->fd, stringReadByPipe, this->bufferSize ) < 0
    ) {
        handlePipeError(WRITING_ERROR);
    }

//    close to pipe

    return stringReadByPipe;
}

void PipeWriter::handlePipeError(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}