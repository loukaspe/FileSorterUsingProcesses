#include "Coach.h"

/* This is a 2D array of Strings to store the names of CoachSorter Pipes to be
 * created. Since we know the constant number of Sorters to be created for each
 * Coach, there is no need for the array himself to be dynamic. For each Coach we
 * set only the names of the Sorters that it needs. For example, the first Coach
 * will only have one Sorter, the second two Sorters etc */
char* Coach::pipeNamesForSorters[][8] = {
        {
            "pipeCoach1Sorter1", "", "", "", "", "", "", ""
        },
        {
            "pipeCoach2Sorter1", "pipeCoach2Sorter2", "", "", "", "", "", ""
        },
        {
            "pipeCoach3Sorter1", "pipeCoach3Sorter2", "pipeCoach3Sorter3",
            "pipeCoach3Sorter4", "", "", "", ""
        },
        {
            "pipeCoach4Sorter1", "pipeCoach4Sorter2", "pipeCoach4Sorter3",
            "pipeCoach4Sorter4", "pipeCoach4Sorter5", "pipeCoach4Sorter6",
            "pipeCoach4Sorter7", "pipeCoach4Sorter8"
        }
};

Coach::Coach(
    char* recordsFilename,
    char* pipeNameFromCoordinator,
    MyRecord* records,
    int numberOfRecords,
    int coachNumber,
    long bufferSize,
    SorterType* type
) {
    this->recordFilename = recordsFilename;
    this->pipeNameFromCoordinator = pipeNameFromCoordinator,
    this->records = records;
    this->numberOfRecords = numberOfRecords;
    this->coachNumber = coachNumber;
    this->bufferSize = bufferSize;
    this->type = type;

    getSortersToBeCreatedNumberFromCoachNumber();
}

void Coach::doAction() {
    cout << "I am coach no. " << this->coachNumber + 1 << endl;

    /* Firstly we create our pipes for reading and writing */
    createPipeReaders();
    createPipeWriters();

    // create sorters

    // read from coordinator
    // write to sorters
    // read from sorters
    // write to coordinator

    /* And then we run the Sorter Processes through the SorterCaller */
    SorterCaller** sorterCallers = (SorterCaller**) malloc(
        numberOfSortersToBeCreated * sizeof( SorterCaller* )
    );

    for(int i = 0; i < numberOfSortersToBeCreated; i++) {
        sorterCallers[i] = new SorterCaller(
            i,
            type->sorterType,
            numberOfRecords,
            type->columnNumber,
            recordFilename,
            coachNumber,
            pipeNamesForSorters[coachNumber][i],
            bufferSize
        );

        sorterCallers[i]->callSorter();
    }
}

void Coach::getSortersToBeCreatedNumberFromCoachNumber() {
    this->numberOfSortersToBeCreated = pow(2, this->coachNumber);
}

void Coach::createPipeReaders() {
    createPipeReaderFromCoordinator();
    createPipeReadersFromSorters();
}

void Coach::createPipeWriters() {
    createPipeWritersToCoordinator();
    createPipeWritersToSorters();
}

void Coach::createPipeReadersFromSorters() {

    /* We want a pipe for each sorter to be connected with the coach. So we
     * create an array of 'pipes' */
    int fd[this->numberOfSortersToBeCreated];

    pipeReadersFromSorters = (PipeReader**) malloc(
            this->numberOfSortersToBeCreated * sizeof(PipeReader)
    );

    for(int i = 0; i < this->numberOfSortersToBeCreated; i++) {
        pipeReadersFromSorters[i] = new PipeReader(
            fd[i],
            Coach::pipeNamesForSorters[this->coachNumber][i],
            18
        );
    }
}

void Coach::createPipeWritersToSorters() {

    int fd[this->numberOfSortersToBeCreated];

    pipeWritersToSorters = (PipeWriter**) malloc(
            this->numberOfSortersToBeCreated * sizeof(PipeWriter)
    );

    for(int i = 0; i < this->numberOfSortersToBeCreated; i++) {
        pipeWritersToSorters[i] = new PipeWriter(
            fd[i],
            Coach::pipeNamesForSorters[this->coachNumber][i],
            18
        );
    }
}

void Coach::createPipeReaderFromCoordinator() {
    int fd;
    pipeReaderFromCoordinator = new PipeReader(fd, pipeNameFromCoordinator, 18);
}

void Coach::createPipeWritersToCoordinator() {
    int fd;
    pipeWriterToCoordinator = new PipeWriter(fd, pipeNameFromCoordinator, 18);
}