#include "CoachFactory.h"

const char* CoachFactory::FORK_ERROR = "ERROR: fork() failed to create a new process";

void CoachFactory::createCoachesAndDoAction(
        int numberOfCoaches,
        char* recordsFilename,
        char** pipeNames,
        long bufferSize,
        int numberOfRecords,
        SorterType* sorterTypes
) {
    Coach** coaches = (Coach**) malloc (
        numberOfCoaches * sizeof( Coach* )
    );

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
                bufferSize,
                sorterTypes
            );

            coaches[i]->doAction();

            exit(0);
        }

        wait(NULL);
    }
}