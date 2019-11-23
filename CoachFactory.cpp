#include "CoachFactory.h"

const char* CoachFactory::FORK_ERROR = "ERROR: fork() failed to create a new process";

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

    int fd[numberOfCoaches];
    PipeWriter** pipeWriters = (PipeWriter**) malloc(
        numberOfCoaches * sizeof(PipeWriter*)
    );

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

            startTimeOfCoach = clock();
            coaches[i]->doAction();
            endTimeOfCoach = clock();

            executionTimeOfCoach = (double) (
                endTimeOfCoach - startTimeOfCoach
            ) / CLOCKS_PER_SEC;
            cout << "Coach no. " << i << " run for " << executionTimeOfCoach << endl;
            pipeWriters[i] = new PipeWriter(
                fd[i],
                pipeNames[i]
            );
            pipeWriters[i]->writeDoubleNumber(executionTimeOfCoach);

            exit(0);
        }

        wait(NULL);
    }
}