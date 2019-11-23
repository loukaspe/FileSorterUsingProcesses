#include "Coordinator.h"

const char* Coordinator::pipeNames[] = {
        "pipeCoordinatorCoach1",
        "pipeCoordinatorCoach2",
        "pipeCoordinatorCoach3",
        "pipeCoordinatorCoach4"
};

Coordinator::Coordinator(
    char* filename,
    int numberOfRecords,
    int numberOfCoaches,
    SorterType* sorterTypes
) {
    this->recordsFilename = filename;
    this->numberOfRecords = numberOfRecords;
    this->numberOfCoaches = numberOfCoaches;
    this->sorterTypes = sorterTypes;
}

void Coordinator::doAction() {

    cout << "I am the coordinator " << endl;

    /* Firstly we create our pipes for reading from Coaches */
    createPipeReaders();

    /* And then we create the Coach Processes through the CoachFactory */
    CoachFactory::createCoachesAndDoAction(
        this->numberOfCoaches,
        this->recordsFilename,
        const_cast<char **>(Coordinator::pipeNames),
        this->numberOfRecords,
        this->sorterTypes
    );
}

void Coordinator::createPipeReaders() {

    /* We want a pipe for each coach to be connected with the coordinator. So we
     * create an array of 'pipes' */
    int fd[this->numberOfCoaches];

    pipeReaders = (PipeReader**) malloc(
            this->numberOfCoaches * sizeof(PipeReader)
    );

    for(int i = 0; i < this->numberOfCoaches; i++) {
        pipeReaders[i] = new PipeReader(
            fd[i],
            Coordinator::pipeNames[i]
        );
    }
}

