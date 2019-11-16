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
    long bufferSize,
    int numberOfCoaches
) {
    this->filename = filename;
    this->records = records;
    this->bufferSize = bufferSize;
    this->numberOfCoaches = numberOfCoaches;
}

void Coordinator::doAction() {

    cout << "I am the coordinator " << endl;

    /* Firstly we create our pipes for reading and writing */
    createPipeReaders();
    createPipeWriters();

    /* And then we create the Coach Processes through the CoachFactory */
    CoachFactory::getCoaches(
        this->numberOfCoaches,
        this->filename,
        const_cast<char **>(Coordinator::pipeNames)
    );
}

void Coordinator::createPipeReaders() {

    /* We want a pipe for each coach to be connected with the coordinator. So we
     * create an array of 'pipes' */
    int fd[4];

    pipeReaders = (PipeReader**) malloc(
            this->numberOfCoaches * sizeof(PipeReader)
    );

    for(int i = 0; i < this->numberOfCoaches; i++) {
        pipeReaders[i] = new PipeReader(fd[i], Coordinator::pipeNames[i], 18);
    }
}

void Coordinator::createPipeWriters() {
    int fd[4];

    pipeWriters = (PipeWriter**) malloc(
            this->numberOfCoaches * sizeof(PipeWriter)
    );

    for(int i = 0; i < this->numberOfCoaches; i++) {
        pipeWriters[i] = new PipeWriter(fd[i], Coordinator::pipeNames[i], 18);
    }
}
