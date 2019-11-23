/* This class will contain the function to be used for reading from Named Pipes in
 * the Project.
 * Source for Named Pipes and implementing them in my processes your given:
 * http://cgi.di.uoa.gr/~ad/k22/Rec2-ProcsIPC.pdf
 * and http://cgi.di.uoa.gr/~ad/k22/named-pipes.pdf */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Helper.h"

#ifndef LOUKASPETEINARIS_PRJ2_PIPEREADER_H
#define LOUKASPETEINARIS_PRJ2_PIPEREADER_H

class PipeReader {
    public:
        PipeReader(int, const char*);
        int readNumber();
        double readDoubleNumber();
        MyRecord* readRecords(long);
    private:
        int fd;
        const char* filename;
        static const int FIFO_MODE;
        static const int OPEN_MODE;
        static const char* MKFIFO_ERROR;
        static const char* OPEN_PIPE_ERROR;
        static const char* READING_ERROR;
        void handlePipeError(const char*);
};


#endif //LOUKASPETEINARIS_PRJ2_PIPEREADER_H
