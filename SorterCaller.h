/* This class will be used the the Coach class and will be creating/calling the
 * sorter independent programs depending on if the option given is HEAP or QUICK.
 * Also, it will provide these sorters with the right (MyRecord) array to sort,
 * according to the column option and each's sorter's portion of data-file used.
 * It will also pass the the pipeName to the sorter. The independent programs to
 * be called are heapsorter.cpp or quicksorter.cpp, which make use of HeapSorter
 * and QuickSorter class accordingly. */

#ifndef LOUKASPETEINARIS_PRJ2_SORTERCALLER_H
#define LOUKASPETEINARIS_PRJ2_SORTERCALLER_H

#define HEAP 0
#define QUICK 1

#include <iostream>
#include "RecordReader.h"
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

class SorterCaller {
public:
    SorterCaller(int, int, int, int, char*, int, char*, int);
    void callSorter();
private:
    int sorterNumber;
    int sorterType;
    int numberOfRecords;
    int column;
    char* recordFilename;
    int coachNumber;
    char* pipeName;
    int bufferSize;
    int startIndexOfGivenRecords;
    int endIndexOfGivenRecords;
    void setStartAndEndIndexesOfGivenRecordsDependingOnCoachNumberAndSorterNumber();
    static const char* FORK_ERROR;

    double portion;
    double portionOfDataDependingOnCoachAndSorterNumber();
};


#endif //LOUKASPETEINARIS_PRJ2_SORTERCALLER_H
