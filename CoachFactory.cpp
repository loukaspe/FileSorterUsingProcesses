#include "CoachFactory.h"

const char* CoachFactory::FORK_ERROR = "ERROR: fork() failed to create a new process";

void CoachFactory::getCoaches(
        int numberOfCoaches,
        char* filename,
        char** pipeNames
) {
    for(int i = 0; i < numberOfCoaches; i++) {

        pid_t id = fork();

        if ( id == -1 ) {
            perror(FORK_ERROR);
            exit(1);
        }

        if( id == 0 ){
            cout << "I am coach no. " << i + 1 << endl;
            cout << "Creating Sorters ..." << endl;
            exit(0);
        }

        wait(NULL);
    }
}