/* This is the class that will do the Quick Sorting. It is a sorter for strings,
 * which will be used for whatever column is given of a MyRecord after it's
 * turned into string */

#ifndef LOUKASPETEINARIS_PRJ2_QUICKSORTER_H
#define LOUKASPETEINARIS_PRJ2_QUICKSORTER_H

#include <iostream>
#include <cstring>
#include "Helper.h"

using namespace std;

class QuickSorter {
    public:
        static void quickSort(MyRecord*, int, int, int);
        static void printArray(MyRecord*, int, int);
    private:
        static int partition(MyRecord*, int, int, int);
};


#endif //LOUKASPETEINARIS_PRJ2_QUICKSORTER_H
