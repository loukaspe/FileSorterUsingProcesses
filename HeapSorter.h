/* This is the class that will do the Heap Sorting */

#ifndef LOUKASPETEINARIS_PRJ2_HEAPSORTER_H
#define LOUKASPETEINARIS_PRJ2_HEAPSORTER_H

#include <iostream>
#include "Helper.h"

using namespace std;

class HeapSorter {
    public:
        static void heapSort(int[], int);
        static void printArray(int[], int);
    private:
        static void heapify(int[], int, int);
};

#endif //LOUKASPETEINARIS_PRJ2_HEAPSORTER_H
