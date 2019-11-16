/* This class will contain the function to be used for writing in Named Pipes in
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

#ifndef LOUKASPETEINARIS_PRJ2_PIPEWRITER_H
#define LOUKASPETEINARIS_PRJ2_PIPEWRITER_H


class PipeWriter {
    public:
        PipeWriter(int, const char*, long);
        char* write();
    private:
        int fd;
        long bufferSize;
        const char* filename;
        static const int FIFO_MODE;
        static const int OPEN_MODE;
        static const char* MKFIFO_ERROR;
        static const char* OPEN_PIPE_ERROR;
        static const char* WRITING_ERROR;
        void handlePipeError(const char*);
};


#endif //LOUKASPETEINARIS_PRJ2_PIPEWRITER_H