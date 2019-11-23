/* Sources for implementing QuickSort and HeapSort:
 * https://www.geeksforgeeks.org/quick-sort/ */

#include "QuickSorter.h"

void QuickSorter::quickSort(
    MyRecord* records,
    int startIndex,
    int endIndex,
    int column
) {
    if (startIndex < endIndex)
    {
        int partitioningIndex = partition(
            records,
            startIndex,
            endIndex,
            column
        );

        quickSort(records, startIndex, partitioningIndex - 1, column);
        quickSort(records, partitioningIndex + 1, endIndex, column);
    }
}

/* This function takes last element as pivot, places the pivot element at its
 * correct position in sorted array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right of pivot */
int QuickSorter::partition (
    MyRecord* records,
    int lowValue,
    int highValue,
    int column
) {
    char* pivot = Helper::getRecordColumnAsString(
        &records[highValue],
        column
    );

    int lowIndex = lowValue - 1;
    int highIndex = highValue - 1;

    for (int j = lowValue; j <= highIndex; j++)
    {
        // If current element is smaller than the pivot
        if (
            strcmp(
                Helper::getRecordColumnAsString( &records[j], column ),
                pivot
            ) < 0
        )
        {
            // increment index of smaller element
            lowIndex++;
            Helper::swapRecords(
                &records[lowIndex],
                &records[j]
            );
        }
    }
    Helper::swapRecords(
        &records[lowIndex + 1],
        &records[highValue]
    );

    return lowIndex + 1;
}

/* Function to print an array */
void QuickSorter::printArray(MyRecord* records, int size, int column)
{
    int i;
    for (i = 0; i < size; i++) {
        cout << Helper::getRecordColumnAsString( &records[i], column ) << " ";
    }

    cout << endl;
}
