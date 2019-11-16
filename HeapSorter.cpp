/* Sources for implementing QuickSort and HeapSort:
 * https://www.geeksforgeeks.org/heap-sort/ */

#include "HeapSorter.h"

void HeapSorter::heapSort(int arrayOfNumbers[], int size) {
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arrayOfNumbers, size, i);
    }

    // One by one extract an element from heap
    for (int i= size - 1; i >= 0; i--)
    {
        // Move current root to end
        swap(arrayOfNumbers[0], arrayOfNumbers[i]);

        // call max heapify on the reduced heap
        heapify(arrayOfNumbers, i, 0);
    }
}

/* Function to print an array */
void HeapSorter::printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void HeapSorter::heapify(
        int arrayOfNumbers[],
        int sizeOfHeap,
        int indexOfRootOfSubtreeToBeHeapified
) {
    int largestIndex = indexOfRootOfSubtreeToBeHeapified;
    int leftChild = 2 * indexOfRootOfSubtreeToBeHeapified + 1;
    int rightChild = 2 * indexOfRootOfSubtreeToBeHeapified + 2;

    // If leftChild child is larger than root
    if (leftChild < sizeOfHeap && arrayOfNumbers[leftChild] > arrayOfNumbers[largestIndex])
        largestIndex = leftChild;

    // If rightChild child is larger than largestIndex so far
    if (rightChild < sizeOfHeap && arrayOfNumbers[rightChild] > arrayOfNumbers[largestIndex])
        largestIndex = rightChild;

    // If largestIndex is not root
    if (largestIndex != indexOfRootOfSubtreeToBeHeapified)
    {
        swap(arrayOfNumbers[indexOfRootOfSubtreeToBeHeapified], arrayOfNumbers[largestIndex]);

        // Recursively heapify the affected sub-tree
        heapify(arrayOfNumbers, sizeOfHeap, largestIndex);
    }
}