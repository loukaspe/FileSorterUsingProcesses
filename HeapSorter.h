/* This is the class that will do the Heap Sorting. It is a sorter for strings,
 * which will be used for whatever column is given of a MyRecord after it's
 * turned into string */

#ifndef LOUKASPETEINARIS_PRJ2_HEAPSORTER_H
#define LOUKASPETEINARIS_PRJ2_HEAPSORTER_H

#include <iostream>
#include <cstring>
#include "Helper.h"

using namespace std;

class HeapSorter {
    public:
        static void heapSort(MyRecord*, int, int);
        static void printArray(MyRecord*, int, int);
    private:
        static void heapify(MyRecord*, int, int, int);
};

#endif //LOUKASPETEINARIS_PRJ2_HEAPSORTER_H
