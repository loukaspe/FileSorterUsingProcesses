#include "Helper.h"

char* Helper::NO_SUCH_RECORD_COLUMN_ERROR_MESSAGE = "ERROR: There is no column"
                                                    "with that number";

char* Helper::MALLOC_FAIL_ERROR_MESSAGE = "ERROR: malloc() failed to "
                                                "allocate memory";

void Helper::handleError(const char * errorMessage) {
    fprintf(
            stderr,
            "%s",
            errorMessage
    );
    exit(EXIT_FAILURE);
}

bool Helper::inArray(int needle, int haystack[], int haystackSize) {
    int i;
    for( i = 0; i < haystackSize; i++) {
        if( needle == haystack[i] ) {
            return true;
        }
    }

    return false;
}

/* Helper Function for swapping values between two integers */
void Helper::swapRecords(MyRecord* firstRecord, MyRecord* secondRecord) {
    MyRecord temp = *firstRecord;
    *firstRecord = *secondRecord;
    *secondRecord = temp;
}

/* This is a function that will be used in the Heap and Quick Sorters. These
 * sorters will take as argument for sorting a whole array of MyRecords and
 * through this function here will pass the MyRecords' column to be sorted to
 * the heapSort and quickSort function as string */
char* Helper::getRecordColumnAsString(MyRecord* record, int columnAsNumber) {

    char* temp = (char*) malloc(64 * sizeof(char) );
    if(temp == NULL) {
        Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
    }

    switch(columnAsNumber) {
        case 0:
            sprintf(temp, "%ld", record->custid);
            return temp;
        case 1:
            return record->FirstName;
        case 2:
            return record->LastName;
        case 3:
            return record->Street;
        case 4:
            sprintf(temp, "%d", record->HouseID);
            return temp;
        case 5:
            return record->City;
        case 6:
            return record->postcode;
        case 7:
            sprintf(temp, "%f", record->amount);
        default:
            Helper::handleError(Helper::NO_SUCH_RECORD_COLUMN_ERROR_MESSAGE);
    }
}

/* Function that given an array of Records and start, end indexes, it returns
 * a subset of that array from start index to end index */
MyRecord* Helper::createSubsetOfRecords(
    MyRecord* records,
    int startIndex,
    int endIndex
) {
    int subsetsSize = endIndex - startIndex + 1;

    MyRecord* subsetOfRecords = (MyRecord*) malloc (
        subsetsSize * sizeof(MyRecord)
    );
    if(subsetOfRecords == NULL) {
        Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
    }

    int j = 0;
    for(int i = startIndex; i <= endIndex; i++) {
        subsetOfRecords[j++] = records[i];
    }

    return subsetOfRecords;
}

/* Function used in coordinator.cpp to handle a given argument from command line.
 * Implemented in Helper.h in order to simplify and keep clean coordinator.cpp */
void Helper::handleGivenHeapCoachFromCommandLine(
        int* numberOfCoachesGivenInCommandLine,
        int columnArgument,
        int previousColumnArguments[],
        SorterTypeFactory* sorterTypeFactory,
        int maxNumberOfCoaches
) {
    if(
        *numberOfCoachesGivenInCommandLine >= maxNumberOfCoaches
        || Helper::inArray(
            columnArgument,
            previousColumnArguments,
            maxNumberOfCoaches
        )
    ) {
        return;
    }

    sorterTypeFactory->add(HEAP, columnArgument);

    previousColumnArguments[
            *numberOfCoachesGivenInCommandLine
    ] = columnArgument;

    (*numberOfCoachesGivenInCommandLine)++;
}

void Helper::handleGivenQuickCoachFromCommandLine(
        int* numberOfCoachesGivenInCommandLine,
        int columnArgument,
        int previousColumnArguments[],
        SorterTypeFactory* sorterTypeFactory,
        int maxNumberOfCoaches
) {
    if(
        *numberOfCoachesGivenInCommandLine >= maxNumberOfCoaches
        || Helper::inArray(
            columnArgument,
            previousColumnArguments,
            maxNumberOfCoaches
        )
    ) {
        return;
    }

    sorterTypeFactory->add(QUICK, columnArgument);

    previousColumnArguments[
            *numberOfCoachesGivenInCommandLine
    ] = columnArgument;

    (*numberOfCoachesGivenInCommandLine)++;
}

/* Function for finding max, min and average values in an array of doubles */
double Helper::findMaxInArrayOfDouble(double* numbers, int size) {
    double max = numbers[0];

    for(int i = 0; i < size; i++) {
        if(numbers[i] > max) {
            max = numbers[i];
        }
    }

    return max;
}

double Helper::findMinInArrayOfDouble(double* numbers, int size) {
    double min = numbers[0];

    for(int i = 0; i < size; i++) {
        if(numbers[i] < min) {
            min = numbers[i];
        }
    }

    return min;
}

double Helper::findAverageOfArrayOfDouble(double* numbers, int size) {
    double sum = 0.0;

    for(int i = 0; i < size; i++) {
        sum += numbers[i];
    }

    return (double) sum/ (double) size;
}
