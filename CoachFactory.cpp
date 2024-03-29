#include "CoachFactory.h"

const char* CoachFactory::FORK_ERROR = "ERROR: fork() failed to create a new process";
char* CoachFactory::MALLOC_FAIL_ERROR_MESSAGE = "ERROR: malloc() failed to "
                                                "allocate memory";

void CoachFactory::createCoachesAndDoAction(
        int numberOfCoaches,
        char* recordsFilename,
        char** pipeNames,
        int numberOfRecords,
        SorterType* sorterTypes
) {
    Coach** coaches = (Coach**) malloc (
        numberOfCoaches * sizeof( Coach* )
    );
    if(coaches == NULL) {
        Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
    }

    int fd[numberOfCoaches];
    PipeWriter** pipeWriters = (PipeWriter**) malloc(
        numberOfCoaches * sizeof(PipeWriter*)
    );
    if(pipeWriters == NULL) {
        Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
    }

    double executionTimeOfCoach;

    clock_t startTimeOfCoach;
    clock_t endTimeOfCoach;

    for(int i = 0; i < numberOfCoaches; i++) {
        int coachNumber = i;

        pid_t id = fork();

        if ( id == -1 ) {
            perror(FORK_ERROR);
            exit(1);
        }

        if( id == 0 ){

            coaches[i] = (Coach*) malloc( sizeof(Coach) );
            coaches[i] = new Coach(
                recordsFilename,
                pipeNames[i],
                numberOfRecords,
                coachNumber,
                &sorterTypes[i]
            );

            // We count the time before and after we call doAction() on the Coaches
            // and we pass this time to the Coordinator
            startTimeOfCoach = clock();
            coaches[i]->doAction();
            endTimeOfCoach = clock();

            executionTimeOfCoach = (double) (
                endTimeOfCoach - startTimeOfCoach
            ) / CLOCKS_PER_SEC;

            pipeWriters[i] = new PipeWriter(
                fd[i],
                pipeNames[i]
            );
            pipeWriters[i]->writeDoubleNumber(executionTimeOfCoach);

            delete pipeWriters[i];
            delete(coaches[i]);
            exit(0);
        }

        wait(NULL);
    }

    delete coaches;
    delete pipeWriters;
}