/* Sources for implementing QuickSort and HeapSort:
 * https://www.geeksforgeeks.org/quick-sort/
 * https://www.geeksforgeeks.org/heap-sort/ */

#include "Sorter.h"

void Sorter::quickSort(int numberToBeSorted[], int startIndex, int endIndex) {
    if (startIndex < endIndex)
    {
        int pi = partition(numberToBeSorted, startIndex, endIndex);

        quickSort(numberToBeSorted, startIndex, pi - 1);
        quickSort(numberToBeSorted, pi + 1, endIndex);
    }
}

void Sorter::heapSort() {

}