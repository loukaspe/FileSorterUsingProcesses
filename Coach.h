/* This class will represent the Coaches of the Project. The coaches will create
 * the pipes for Coordinator, the pipes for the Sorters and the Sorters themselves
 * through the SorterFactory class. */

#ifndef LOUKASPETEINARIS_PRJ2_COACH_H
#define LOUKASPETEINARIS_PRJ2_COACH_H

#include <iostream>
#include "SorterTypeFactory.h"
#include "SorterCaller.h"
#include "PipeReader.h"
#include "PipeWriter.h"
#include "RecordReader.h"

using namespace std;

class Coach {
public:
    Coach(char*, char*, MyRecord*, int, int, long, SorterType*);
    void doAction();
private:
    char* recordFilename;
    MyRecord* records;
    int numberOfRecords;
    int coachNumber;
    long bufferSize;
    SorterType* type;
    char* pipeNameFromCoordinator;
    int numberOfSortersToBeCreated;
    void getSortersToBeCreatedNumberFromCoachNumber();
    PipeReader** pipeReadersFromSorters;
    PipeWriter** pipeWritersToSorters;
    PipeReader* pipeReaderFromCoordinator;
    PipeWriter* pipeWriterToCoordinator;
    static char* pipeNamesForSorters[][8];
    void createPipeReaders();
    void createPipeWriters();
    void createPipeReadersFromSorters();
    void createPipeWritersToSorters();
    void createPipeReaderFromCoordinator();
    void createPipeWritersToCoordinator();
};

#endif //LOUKASPETEINARIS_PRJ2_COACH_H
