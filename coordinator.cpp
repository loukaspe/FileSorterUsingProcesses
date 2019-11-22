#include "Coordinator.h"

const char* PROGRAM_OPTIONS = "h:q:";
const char* WRONG_PROGRAM_USAGE_ERROR = "ERROR: Wrong Program Call. Please give"
                                        " coaches and sorters options.";
const int MAX_NUMBER_OF_COACHES = 4;
const long BUFFER_SIZE = 1024;

int main(int argc, char** argv) {

    char* filename = argv[1];

    RecordReader* recordReader = new RecordReader(filename);
    MyRecord* records = recordReader->fetchAllRecords();
    int numberOfRecords = recordReader->getRecordsNumber();

    int numberOfCoaches = 0;

    /* Variables for the Program's Arguments */
    int opt;
    int columnArgument;

    /* This is a variable to keep how many Coaches the program is called to
     * create in the command line. It must not be greater than 4. */
    int numberOfCoachesGivenInCommandLine = 0;

    /* Array of integers to keep the columns that have already been called for
     * sorting in order to prevent from calling two or more sorters for the same
     * column (As told in https://piazza.com/class/k1631q2t5o11rj?cid=81 ). So
     * if a given column is already in this array, then the add() function of
     * SorterTypeFactory won't be called. The size of the array is static and
     * equal to 4 as the maximum of coaches is 4 */
    int previousColumnArguments[MAX_NUMBER_OF_COACHES];

    /* We keep the information of the Program Arguments to a SorterTypeArray
     * struct in order to give it to the Coach */
    SorterTypeFactory* sorterTypeFactory = new SorterTypeFactory();

    /* A SorterType is only added in the SorterTypeArray of SorterTypeFactory
     * if the numberOfCoachesGivenInCommandLine is less than 4, which is the
     * maximum of Coaches we can create and if the column given as argument is
     * not in the previousColumnsArguments array */
    while ( (opt = getopt(argc, argv, PROGRAM_OPTIONS)) != -1 ) {
        switch (opt) {
            case 'h':
                columnArgument = atoi(optarg);
                Helper::handleGivenHeapCoachFromCommandLine(
                    &numberOfCoaches,
                    &numberOfCoachesGivenInCommandLine,
                    columnArgument,
                    previousColumnArguments,
                    sorterTypeFactory,
                    MAX_NUMBER_OF_COACHES
                );
                break;
            case 'q':
                columnArgument = atoi(optarg);
                Helper::handleGivenQuickCoachFromCommandLine(
                    &numberOfCoaches,
                    &numberOfCoachesGivenInCommandLine,
                    columnArgument,
                    previousColumnArguments,
                    sorterTypeFactory,
                    MAX_NUMBER_OF_COACHES
                );
                break;
            default:
                Helper::handleError(WRONG_PROGRAM_USAGE_ERROR);
        }
    }

    SorterType* sorterTypes = sorterTypeFactory->getSorterTypes();

    Coordinator* coordinator = new Coordinator(
        filename,
        numberOfRecords,
        BUFFER_SIZE,
        numberOfCoaches,
        sorterTypes
    );
    coordinator->doAction();

    return 0;
}