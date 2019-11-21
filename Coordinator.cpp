#include "Coordinator.h"

const char* Coordinator::pipeNames[] = {
        "pipeCoordinatorCoach1",
        "pipeCoordinatorCoach2",
        "pipeCoordinatorCoach3",
        "pipeCoordinatorCoach4"
};

Coordinator::Coordinator(
    char* filename,
    MyRecord* records,
    int numberOfRecords,
    long bufferSize,
    int numberOfCoaches,
    SorterType* sorterTypes
) {
    this->recordsFilename = filename;
    this->records = records;
    this->numberOfRecords = numberOfRecords;
    this->bufferSize = bufferSize;
    this->numberOfCoaches = numberOfCoaches;
    this->sorterTypes = sorterTypes;
}

void Coordinator::doAction() {

    cout << "I am the coordinator " << endl;

    /* Firstly we create our pipes for reading and writing */
    createPipeReaders();
    createPipeWriters();
    //TODO
    for(int i = 0; i < this->numberOfCoaches; i++) {
        char* temp;
        switch (i) {
            case 0:
                temp = "Coordinator to Coach 0";
                break;
            case 1:
                temp = "Coordinator to Coach 1";
                break;
            case 2:
                temp = "Coordinator to Coach 2";
                break;
            case 3:
                temp = "Coordinator to Coach 3";
                break;
            default:
                Helper::handleError("Error with test cases");
        }
        pipeWriters[i]->write(temp);
    }

    /* And then we create the Coach Processes through the CoachFactory */
    CoachFactory::createCoachesAndDoAction(
        this->numberOfCoaches,
        this->recordsFilename,
        const_cast<char **>(Coordinator::pipeNames),
        this->bufferSize,
        this->records,
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
            Coordinator::pipeNames[i],
            this->bufferSize
        );
    }
}

void Coordinator::createPipeWriters() {
    int fd[4];

    pipeWriters = (PipeWriter**) malloc(
            this->numberOfCoaches * sizeof(PipeWriter)
    );

    for(int i = 0; i < this->numberOfCoaches; i++) {
        pipeWriters[i] = new PipeWriter(
            fd[i],
            Coordinator::pipeNames[i],
            this->bufferSize
        );
    }
}
