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

const int Coach::NUMBER_OF_CHARS_IN_OUTPUT_FILENAME = 32;

const char* Coach::OUTPUT_FILENAME = "fileOfSortedRecordsCoach%dColumn%d";
const char* Coach::OUTPUT_FILE_STARTING_TEXT = "Coach %d From Sorter %d on "
                                               "column %d\n";

const char* Coach::FOPEN_WRITING_MODE = "w";

const char* Coach::ERROR_OPENING_FILE = "ERROR: Coach could not open file for "
                                        "writing sorted Records.";

Coach::Coach(
    char* recordsFilename,
    char* pipeNameFromCoordinator,
    int numberOfRecords,
    int coachNumber,
    SorterType* type
) {
    this->recordFilename = recordsFilename;
    this->pipeNameFromCoordinator = pipeNameFromCoordinator,
    this->numberOfRecords = numberOfRecords;
    this->coachNumber = coachNumber;
    this->type = type;

    getSortersToBeCreatedNumberFromCoachNumber();
}

void Coach::doAction() {
    FILE* fileOfSortedRecords;
    int columnNumber = type->columnNumber;

    clock_t startTimeOfSorter;
    clock_t endTimeOfSorter;
    double* executionTimeOfSorters = (double*) malloc (
        numberOfSortersToBeCreated * sizeof(double)
    );

    /* We create a string with size of the word 'fileOfSortedRecordsCoach%dColumn%d'
     * (24 chars) plus two numbers (2 char), that show the number of Coach and
     * the number of column */
    char* filename = (char*) malloc (
        NUMBER_OF_CHARS_IN_OUTPUT_FILENAME * 2 * sizeof(char)
    );
    /* We add 1 to ColumnNumber so that count of column starts from 1 */
    sprintf(filename, OUTPUT_FILENAME, coachNumber, columnNumber + 1);

    fileOfSortedRecords = fopen(filename, FOPEN_WRITING_MODE);
    if( fileOfSortedRecords == NULL ) {
        Helper::handleError(ERROR_OPENING_FILE);
    }

    cout << "I am coach no. " << this->coachNumber + 1 << endl;

    /* Firstly we create our pipes for reading and writing */
    createPipeReadersFromSorters();
    createPipeWritersToCoordinator();

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
            pipeNamesForSorters[coachNumber][i]
        );

        startTimeOfSorter = clock();
        sorterCallers[i]->callSorter();
        endTimeOfSorter = clock();

        executionTimeOfSorters[i] = (double) (
            endTimeOfSorter - startTimeOfSorter
        ) / CLOCKS_PER_SEC;

        cout << "Sorter no. " << i << " run for " << executionTimeOfSorters[i] << endl;

        int retrievedRecordsBufferSize = pipeReadersFromSorters[i]->readNumber();
        int retrievedRecordsNumber = (
                retrievedRecordsBufferSize / sizeof(MyRecord)
        ) - 1;

        MyRecord* retrievedRecords;
        retrievedRecords = pipeReadersFromSorters[i]->readRecords(
            retrievedRecordsBufferSize
        );

        /* According to https://piazza.com/class/k1631q2t5o11rj?cid=47 the Coach
         * merges the Records the Sorters bring, in any way we want, with no need
         * to be sorted again */

        int sorterNumber = i;
        fprintf(
            fileOfSortedRecords,
            OUTPUT_FILE_STARTING_TEXT,
            coachNumber,
            sorterNumber,
            columnNumber
        );

        for(int j = 0; j < retrievedRecordsNumber; j++) {
            fprintf(
                fileOfSortedRecords,
                "%ld %s %s %s %d %s %s %-9.2f\n",
                retrievedRecords[j].custid,
                retrievedRecords[j].FirstName,
                retrievedRecords[j].LastName,
                retrievedRecords[j].Street,
                retrievedRecords[j].HouseID,
                retrievedRecords[j].City,
                retrievedRecords[j].postcode,
                retrievedRecords[j].amount
            );
        }
    }

    fclose(fileOfSortedRecords);

    for(int i = 0; i < numberOfSortersToBeCreated; i++) {
        pipeWriterToCoordinator->writeDoubleNumber(executionTimeOfSorters[i]);
    }

    // free records

}

void Coach::getSortersToBeCreatedNumberFromCoachNumber() {
    this->numberOfSortersToBeCreated = pow(2, this->coachNumber);
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
            Coach::pipeNamesForSorters[this->coachNumber][i]
        );
    }
}

void Coach::createPipeWritersToCoordinator() {
    int fd;
    pipeWriterToCoordinator = new PipeWriter(fd, pipeNameFromCoordinator);
}