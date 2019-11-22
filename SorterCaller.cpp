#include "SorterCaller.h"

const char* SorterCaller::FORK_ERROR = "ERROR: fork() failed to create a new process";

SorterCaller::SorterCaller(
    int sorterNumber,
    int sorterType,
    int numberOfRecords,
    int column,
    char* recordFilename,
    int coachNumber,
    char* pipeName
) {
    this->sorterNumber = sorterNumber;
    this->sorterType = sorterType;
    this->numberOfRecords = numberOfRecords;
    this->column = column;
    this->recordFilename = recordFilename;
    this->coachNumber = coachNumber;
    this->pipeName = pipeName;

    setStartAndEndIndexesOfGivenRecordsDependingOnCoachNumberAndSorterNumber();
}

void SorterCaller::callSorter() {
    cout << "Sorter no. " << sorterNumber << " of Coach no. " << coachNumber << endl;

    pid_t id = fork();

    /* We turn integers to strings in order to pass them as argument in exec as
     * we callSorter the independent sorter programs */
    char startIndexAsString[64];
    sprintf(startIndexAsString, "%d", startIndexOfGivenRecords);
    char endIndexAsString[64];
    sprintf(endIndexAsString, "%d", endIndexOfGivenRecords);
    char columnAsString[64];
    sprintf(columnAsString, "%d", column);

    if ( id == -1 ) {
        perror(FORK_ERROR);
        exit(1);
    }

    if( id == 0 && sorterType == HEAP ) {
        execlp(
            "./heapsort",
            "./heapsort",
            recordFilename,
            startIndexAsString,
            endIndexAsString,
            pipeName,
            columnAsString,
            NULL
        );
        exit(0);
    }

    if( id == 0 && sorterType == QUICK ) {
        execlp(
            "./quicksort",
            "./quicksort",
            recordFilename,
            startIndexAsString,
            endIndexAsString,
            pipeName,
            columnAsString,
            NULL
        );
        exit(0);
    }

    wait(NULL);
}

/* Function to set the limits of records that this sorter will sort, as shown in
 * schema 1 of http://cgi.di.uoa.gr/~ad/k22/OS-F19-Prj2.pdf. Due to lack of time
 * I did not figure out another way of setting them other than hard-coded */
void SorterCaller::setStartAndEndIndexesOfGivenRecordsDependingOnCoachNumberAndSorterNumber() {
    if(coachNumber == 0 && sorterNumber == 0) {
        startIndexOfGivenRecords = 0;
        endIndexOfGivenRecords = numberOfRecords;
        return;
    }

    if(coachNumber == 1 && sorterNumber == 0) {
        startIndexOfGivenRecords = 0;
        endIndexOfGivenRecords = numberOfRecords/2 ;
        return;
    }

    if(coachNumber == 1 && sorterNumber == 1) {
        startIndexOfGivenRecords = numberOfRecords/2;
        endIndexOfGivenRecords = numberOfRecords;
        return;
    }

    if(coachNumber == 2 && sorterNumber == 0) {
        startIndexOfGivenRecords = 0;
        endIndexOfGivenRecords = numberOfRecords/8;
        return;
    }

    if(coachNumber == 2 && sorterNumber == 1) {
        startIndexOfGivenRecords = numberOfRecords/8;
        endIndexOfGivenRecords = numberOfRecords / 4;
        return;
    }

    if(coachNumber == 2 && sorterNumber == 2) {
        startIndexOfGivenRecords = numberOfRecords / 4;
        endIndexOfGivenRecords = numberOfRecords / 2;
        return;
    }

    if(coachNumber == 2 && sorterNumber == 3) {
        startIndexOfGivenRecords = numberOfRecords / 2;
        endIndexOfGivenRecords = numberOfRecords;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 0) {
        startIndexOfGivenRecords = 0;
        endIndexOfGivenRecords = numberOfRecords / 16;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 1) {
        startIndexOfGivenRecords = numberOfRecords / 16;
        endIndexOfGivenRecords = numberOfRecords / 8;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 2) {
        startIndexOfGivenRecords = numberOfRecords / 8;
        endIndexOfGivenRecords = 3 * numberOfRecords / 16;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 3) {
        startIndexOfGivenRecords = 3 * numberOfRecords / 16;
        endIndexOfGivenRecords = numberOfRecords / 4;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 4) {
        startIndexOfGivenRecords = numberOfRecords / 4;
        endIndexOfGivenRecords = 3 * numberOfRecords / 8;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 5) {
        startIndexOfGivenRecords = 3 * numberOfRecords / 8;
        endIndexOfGivenRecords = numberOfRecords / 2;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 6) {
        startIndexOfGivenRecords = numberOfRecords / 2;
        endIndexOfGivenRecords = 3 * numberOfRecords / 4;
        return;
    }

    if(coachNumber == 3 && sorterNumber == 7) {
        startIndexOfGivenRecords = 3 * numberOfRecords / 4;
        endIndexOfGivenRecords = numberOfRecords;
        return;
    }
}