#ifndef LOUKASPETEINARIS_PRJ2_SORTERTYPEFACTORY_H
#define LOUKASPETEINARIS_PRJ2_SORTERTYPEFACTORY_H

#include <cstdlib>

/* I have as flag for a Quick or Heap Sorter an int with value of 0 or 1 */
#define HEAP 0
#define QUICK 1

/* SorterType struct contains information about the type of the Sorter that the
* Coach will create. Specifically, it contains an int about the number of column
* to sort and another int (0 or 1) that will define if it's a Heap or Quick
* Sorter */

typedef struct SorterType {
    int sorterType;
    int columnNumber;
} SorterType;


/* The SorterTypeFactory will create an array of SorterTypes and will return it */
class SorterTypeFactory {
public:
    SorterTypeFactory();
    void add(int, int);
    SorterType* getSorterTypes();
    int getNumberOfSorterTypes();
private:
    SorterType* sorterTypes;
    int numberOfSorterTypes;
};


#endif //LOUKASPETEINARIS_PRJ2_SORTERTYPEFACTORY_H
