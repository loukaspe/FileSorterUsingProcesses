#ifndef LOUKASPETEINARIS_PRJ2_QUICKSORTER_H
#define LOUKASPETEINARIS_PRJ2_QUICKSORTER_H

#include <iostream>
#include "Helper.h"

using namespace std;

class QuickSorter {
    public:
        static void quickSort(int[], int, int);
        static void printArray(int[], int);
    private:
        static int partition(int[], int, int);
};


#endif //LOUKASPETEINARIS_PRJ2_QUICKSORTER_H
