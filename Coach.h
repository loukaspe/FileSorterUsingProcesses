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
    Coach(char*, char*, int, int, long, SorterType*);
    void doAction();
private:
    char* recordFilename;
    int numberOfRecords;
    int coachNumber;
    long bufferSize;
    SorterType* type;
    char* pipeNameFromCoordinator;
    int numberOfSortersToBeCreated;
    void getSortersToBeCreatedNumberFromCoachNumber();
    PipeReader** pipeReadersFromSorters;
    PipeWriter* pipeWriterToCoordinator;
    static char* pipeNamesForSorters[][8];
    void createPipeReadersFromSorters();
    void createPipeWritersToCoordinator();
    static const int NUMBER_OF_CHARS_IN_OUTPUT_FILENAME;
    static const char* OUTPUT_FILENAME;
    static const char* OUTPUT_FILE_STARTING_TEXT;
    static const char* FOPEN_WRITING_MODE;
    static const char* ERROR_OPENING_FILE;
};

#endif //LOUKASPETEINARIS_PRJ2_COACH_H
