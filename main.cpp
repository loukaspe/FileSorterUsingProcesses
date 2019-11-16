#include <iostream>
#include "Coordinator.h"

void sorter(int sorterNumber, int coachNumber) {
    cout << "I am sorter no. " << sorterNumber + 1 << " of Coach no. " << coachNumber + 1 << endl;
}

void createSorters(int sortersToBeCreated, int coachNumber) {
    for(int i = 0; i < sortersToBeCreated; i++) {
        pid_t id = fork();

        if(id == 0){
            sorter(i, coachNumber);
            exit(0);
        }
        wait(NULL);
    }
}

void coach(int coachNumber) {
    int sortersToBeCreated = pow(2, coachNumber);
    createSorters(sortersToBeCreated, coachNumber);

}

int main(int argc, char** argv) {
    const long BUFFER_SIZE = 1024;
    char* filename = argv[1];
    int numberOfCoaches = 4;
    RecordReader* recordReader = new RecordReader(filename);
    MyRecord* records = recordReader->fetchAllRecords();

    Coordinator* coordinator = new Coordinator(
        filename,
        records,
        BUFFER_SIZE,
        numberOfCoaches
    );
    coordinator->doAction();

    return 0;
}