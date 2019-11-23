#include "QuickSorter.h"
#include "RecordReader.h"
#include "PipeWriter.h"

/* This and heapsort.cpp are the independent programs the Coach will call with SorterCaller
 * to do the sorting of records, as pointed out in https://piazza.com/class/k1631q2t5o11rj?cid=76
 * It makes uses of the QuickSorter class which is a Sorter using quick sort
 * method. */

/* Function for deallocating memory */
void deletePointers(MyRecord*, MyRecord*, RecordReader*, PipeWriter*);

int main(int argc, char* argv[]) {

    const int START_INDEX_OF_RECORD_ARRAY = 0;

    char* filenameOfRecords = argv[1];
    int startIndexOfSubsetOfRecords = atoi( argv[2] );
    int endIndexOfSubsetOfRecords = atoi( argv[3] );
    char* pipeName = argv[4];
    int column = atoi( argv[5] );

    int numberOfRecords = endIndexOfSubsetOfRecords - startIndexOfSubsetOfRecords + 1;

    RecordReader* recordReader = new RecordReader(filenameOfRecords);
    MyRecord* totalRecords = recordReader->fetchAllRecords();
    MyRecord* subsetOfRecords = Helper::createSubsetOfRecords(
        totalRecords,
        startIndexOfSubsetOfRecords,
        endIndexOfSubsetOfRecords
    );

    QuickSorter::quickSort(
        subsetOfRecords,
        START_INDEX_OF_RECORD_ARRAY,
        numberOfRecords,
        column
    );

    //QuickSorter::printArray(subsetOfRecords, numberOfRecords, column);

    int fd;
    int bufferSize = numberOfRecords * sizeof(MyRecord);
    PipeWriter* pipeWriterToCoach = new PipeWriter(fd, pipeName);
    /* Firstly we pass the total bufferSize needed for writing the Records to
     * the named pipe and then we pass the records */
    pipeWriterToCoach->writeNumber(bufferSize);
    pipeWriterToCoach->writeRecords(subsetOfRecords, bufferSize);

    deletePointers(
        totalRecords,
        subsetOfRecords,
        recordReader,
        pipeWriterToCoach
    );

    return 0;
};

void deletePointers(
    MyRecord* records,
    MyRecord* subsetOfRecords,
    RecordReader* recordReader,
    PipeWriter* pipeWriter
) {
    delete records;
    delete subsetOfRecords;
    delete recordReader;
    delete pipeWriter;
}
