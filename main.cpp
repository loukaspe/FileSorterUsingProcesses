#include <iostream>

const int RETURN_FAILURE = 1;
const int RETURN_SUCCESS = 0;

int main(int argc, char** argv) {

    if ( argc != 2 ) {
        printf("Correct syntax is: %s BinaryFile\n", argv[0]);
        return(RETURN_FAILURE);
    }

    return RETURN_SUCCESS;
}