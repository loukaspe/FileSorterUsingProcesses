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

    readFromPipesAndPrintStatistics();
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

void Coordinator::readFromPipesAndPrintStatistics() {

    double* executionTimeOfCoaches = (double*) malloc (
            numberOfCoaches * sizeof(double)
    );

    double** executionTimeOfSortersOfCoaches = (double**) malloc(
            numberOfCoaches * sizeof(double*)
    );

    for(int i = 0; i < numberOfCoaches; i++) {

        int sortersToBeCreated = pow(2, i);

        executionTimeOfSortersOfCoaches[i] = (double*) malloc(
            sortersToBeCreated * sizeof(double)
        );

        for(int j = 0; j < pow(2, i); j++) {
            executionTimeOfSortersOfCoaches[i][j] = pipeReaders[i]->readDoubleNumber();
        }

        double maxExecutionTimeOfSortersOfCoaches = Helper::findMaxInArrayOfDouble(
            executionTimeOfSortersOfCoaches[i],
            sortersToBeCreated
        );
        double minExecutionTimeOfSortersOfCoaches = Helper::findMinInArrayOfDouble(
            executionTimeOfSortersOfCoaches[i],
            sortersToBeCreated
        );
        double averageExecutionTimeOfSortersOfCoaches = Helper::findAverageOfArrayOfDouble(
            executionTimeOfSortersOfCoaches[i],
            sortersToBeCreated
        );
        cout << "Execution of Sorters of Coach no. " << i << endl;
        cout << "\tMAX: " << maxExecutionTimeOfSortersOfCoaches << endl;
        cout << "\tMIN: " << minExecutionTimeOfSortersOfCoaches << endl;
        cout << "\tAVERAGE: " << averageExecutionTimeOfSortersOfCoaches << endl;

        executionTimeOfCoaches[i] = pipeReaders[i]->readDoubleNumber();
    }

    double maxExecutionTimeOfCoaches = Helper::findMaxInArrayOfDouble(
        executionTimeOfCoaches,
        numberOfCoaches
    );
    double minExecutionTimeOfCoaches = Helper::findMinInArrayOfDouble(
        executionTimeOfCoaches,
        numberOfCoaches
    );
    double averageExecutionTimeOfCoaches = Helper::findAverageOfArrayOfDouble(
        executionTimeOfCoaches,
        numberOfCoaches
    );

    cout << "Execution Of Coaches:" << endl;
    cout << "\tMAX: " << maxExecutionTimeOfCoaches << endl;
    cout << "\tMIN: " << minExecutionTimeOfCoaches << endl;
    cout << "\tAverage: " << averageExecutionTimeOfCoaches << endl;
}

