#include "SorterTypeFactory.h"
#include "Helper.h"

char* SorterTypeFactory::MALLOC_FAIL_ERROR_MESSAGE = "ERROR: malloc() failed to "
                                                "allocate memory";

SorterTypeFactory::SorterTypeFactory() {
    this->numberOfSorterTypes = 0;
}

void SorterTypeFactory::add(int sorterType, int columnNumber) {

    if(numberOfSorterTypes == 0) {
        this->sorterTypes = (SorterType*) malloc ( sizeof(SorterType) );
        if(this->sorterTypes == NULL) {
            Helper::handleError(MALLOC_FAIL_ERROR_MESSAGE);
        }

        sorterTypes[0].columnNumber = columnNumber;
        sorterTypes[0].sorterType = sorterType;
        this->numberOfSorterTypes++;
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


