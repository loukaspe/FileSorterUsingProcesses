/* Sources for implementing QuickSort and HeapSort:
 * https://www.geeksforgeeks.org/quick-sort/ */

#include "QuickSorter.h"

void QuickSorter::quickSort(int numberToBeSorted[], int startIndex, int endIndex) {
    if (startIndex < endIndex)
    {
        int partitioningIndex = partition(
            numberToBeSorted,
            startIndex,
            endIndex
        );

        quickSort(numberToBeSorted, startIndex, partitioningIndex - 1);
        quickSort(numberToBeSorted, partitioningIndex + 1, endIndex);
    }
}

/* This function takes last element as pivot, places the pivot element at its
 * correct position in sorted array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right of pivot */
int QuickSorter::partition (int arrayOfNumbers[], int lowValue, int highValue)
{
    int pivot = arrayOfNumbers[highValue];
    int lowIndex = lowValue - 1;
    int highIndex = highValue - 1;

    for (int j = lowValue; j <= highIndex; j++)
    {
        // If current element is smaller than the pivot
        if (arrayOfNumbers[j] < pivot)
        {
            // increment index of smaller element
            lowIndex++;
            Helper::swapNumbers(
                &arrayOfNumbers[lowIndex],
                &arrayOfNumbers[j]
            );
        }
    }
    Helper::swapNumbers(
        &arrayOfNumbers[lowIndex + 1],
        &arrayOfNumbers[highValue]
    );

    return lowIndex + 1;
}

/* Function to print an array */
void QuickSorter::printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
