/* This class will represent the Coordinator of the Project. I chose to implement
 * the Coordinator, Coach, and QuickSorter as classes with a function doAction() that
 * will do the things each class is supposed to do. The coordinator will create
 * the pipes and the coaches. */

#ifndef LOUKASPETEINARIS_PRJ2_COORDINATOR_H
#define LOUKASPETEINARIS_PRJ2_COORDINATOR_H

#include "CoachFactory.h"
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>

class Coordinator {
public:
    Coordinator(char*, MyRecord*, int, long, int, SorterType*);
    void doAction();
private:
    char* recordsFilename;
    MyRecord* records;
    int numberOfRecords;
    int numberOfCoaches;
    long bufferSize;
    SorterType* sorterTypes;
    PipeReader** pipeReaders;
    PipeWriter** pipeWriters;
    static const char* pipeNames[];
    void createPipeReaders();
    void createPipeWriters();
};


#endif //LOUKASPETEINARIS_PRJ2_COORDINATOR_H
