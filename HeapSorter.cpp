/* Sources for implementing QuickSort and HeapSort:
 * https://www.geeksforgeeks.org/heap-sort/ */

#include "HeapSorter.h"
#include "RecordReader.h"

void HeapSorter::heapSort(MyRecord* records, int size, int column) {
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(records, size, i, column);
    }

    // One by one extract an element from heap
    for (int i = size - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(records[0], records[i]);

        // callSorter max heapify on the reduced heap
        heapify(records, i, 0, column);
    }
}

/* Function to print an array */
void HeapSorter::printArray(MyRecord* records, int size, int column)
{
    int i;
    for (i = 0; i < size; i++)
        cout << Helper::getRecordColumnAsString( &records[i], column ) << endl;
    cout << endl;
}

void HeapSorter::heapify(
        MyRecord* records,
        int sizeOfHeap,
        int indexOfRootOfSubtreeToBeHeapified,
        int column
) {
    int largestIndex = indexOfRootOfSubtreeToBeHeapified;
    int leftChild = 2 * indexOfRootOfSubtreeToBeHeapified + 1;
    int rightChild = 2 * indexOfRootOfSubtreeToBeHeapified + 2;

    // If leftChild child is larger than root
    if (
        leftChild < sizeOfHeap
        && strcmp(
            Helper::getRecordColumnAsString( &records[leftChild], column),
            Helper::getRecordColumnAsString( &records[largestIndex], column)
        ) > 0
    ) {
        largestIndex = leftChild;
    }

    // If rightChild child is larger than largestIndex so far
    if (
        rightChild < sizeOfHeap
        && strcmp(
                Helper::getRecordColumnAsString( &records[rightChild], column),
                Helper::getRecordColumnAsString( &records[largestIndex], column)
        ) > 0
    ) {
        largestIndex = rightChild;
    }

    // If largestIndex is not root
    if (largestIndex != indexOfRootOfSubtreeToBeHeapified)
    {
        Helper::swapRecords(
            &records[indexOfRootOfSubtreeToBeHeapified],
            &records[largestIndex]
        );

        // Recursively heapify the affected sub-tree
        heapify(records, sizeOfHeap, largestIndex, column);
    }
}