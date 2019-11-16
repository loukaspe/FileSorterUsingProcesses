/* This class will represent the Coordinator of the Project. I chose to implement
 * the Coordinator, Coach, and QuickSorter as classes with a function doAction() that
 * will do the things each class is supposed to do. The coordinator will create
 * the pipes and the coaches. */

#ifndef LOUKASPETEINARIS_PRJ2_COORDINATOR_H
#define LOUKASPETEINARIS_PRJ2_COORDINATOR_H

#include "RecordReader.h"
#include "PipeReader.h"
#include "PipeWriter.h"
#include "CoachFactory.h"

class Coordinator {
public:
    Coordinator(char*, MyRecord*, long, int);
    void doAction();
private:
    char* filename;
    MyRecord* records;
    int numberOfCoaches;
    long bufferSize;
    PipeReader** pipeReaders;
    PipeWriter** pipeWriters;
    static const char* pipeNames[];
    void createPipeReaders();
    void createPipeWriters();
};


#endif //LOUKASPETEINARIS_PRJ2_COORDINATOR_H
