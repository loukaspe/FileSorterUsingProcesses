#include "SorterTypeFactory.h"

SorterTypeFactory::SorterTypeFactory() {
    this->numberOfSorterTypes = 0;
}

void SorterTypeFactory::add(int sorterType, int columnNumber) {

    if(numberOfSorterTypes == 0) {
        this->sorterTypes = (SorterType*) malloc ( sizeof(SorterType) );
        sorterTypes[0].columnNumber = columnNumber;
        sorterTypes[0].sorterType = sorterType;
        return;
    }

    this->sorterTypes = (SorterType*) realloc(
        this->sorterTypes,
        sizeof(SorterType)
    );
    sorterTypes[this->numberOfSorterTypes].columnNumber = columnNumber;
    sorterTypes[this->numberOfSorterTypes].sorterType = sorterType;

    this->numberOfSorterTypes++;
}

SorterType* SorterTypeFactory::getSorterTypes() {
    return this->sorterTypes;
}

int SorterTypeFactory::getNumberOfSorterTypes() {
    return numberOfSorterTypes;
}

