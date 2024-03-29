/* This class will represent the Coordinator of the Project. I chose to implement
 * the Coordinator and the Coach as classes with a function doAction() that
 * will do the things each class is supposed to do. The coordinator will create
 * the pipes and the coaches and will print the Execution Times */

#ifndef LOUKASPETEINARIS_PRJ2_COORDINATOR_H
#define LOUKASPETEINARIS_PRJ2_COORDINATOR_H

#include "CoachFactory.h"
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>

class Coordinator {
public:
    Coordinator(char*, int, int, SorterType*);
    ~Coordinator();
    void doAction();
private:
    char* recordsFilename;
    int numberOfRecords;
    int numberOfCoaches;
    SorterType* sorterTypes;
    PipeReader** pipeReaders;
    static const char* pipeNames[];
    void createPipeReaders();
    void readFromPipesAndPrintStatistics();
    static char* MALLOC_FAIL_ERROR_MESSAGE;
};


#endif //LOUKASPETEINARIS_PRJ2_COORDINATOR_H
