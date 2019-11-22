#include "PipeWriter.h"

const int PipeWriter::FIFO_MODE = 0666;
const int PipeWriter::OPEN_MODE = O_WRONLY | O_NONBLOCK;
const char* PipeWriter::MKFIFO_ERROR = "ERROR: mkfifo() failed to create a new named pipe";
const char* PipeWriter::OPEN_PIPE_ERROR = "ERROR: open() failed to open a named pipe";
const char* PipeWriter::WRITING_ERROR = "ERROR: write() failed to write to a named pipe";
const char* PipeWriter::NOT_ENOUGH_BUFFER_SIZE_ERROR = "ERROR: Given text's size bigger "
                                                       "pipe's buffer size";

PipeWriter::PipeWriter(int fd, const char* filename) {
    this->fd = fd;
    this->filename = filename;

    if(
        ( mkfifo(filename, FIFO_MODE) == -1 )
        && errno != EEXIST
    ) {
        handlePipeError(MKFIFO_ERROR);
    }

    if(
        ( this->fd = open(this->filename, OPEN_MODE) ) < 0
    ) {
        handlePipeError(OPEN_PIPE_ERROR);
    }
}

void PipeWriter::writeRecords(MyRecord* records, long bufferSize) {
    if(
        ::write( this->fd, records, bufferSize ) < 0
    ) {
        handlePipeError(WRITING_ERROR);
    }

//    close to pipe
}

void PipeWriter::handlePipeError(const char* errorMessage) {
    perror(errorMessage);
    exit(1);
}