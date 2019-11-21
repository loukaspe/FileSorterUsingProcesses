/* File for the Record struct you have in verify.c */

#ifndef LOUKASPETEINARIS_PRJ2_RECORD_H
#define LOUKASPETEINARIS_PRJ2_RECORD_H

#define SIZE_OF_BUFF 20
#define SSIZE_OF_BUFF 6

typedef struct{
    long  	custid;
    char 	FirstName[SIZE_OF_BUFF];
    char 	LastName[SIZE_OF_BUFF];
    char	Street[SIZE_OF_BUFF];
    int 	HouseID;
    char	City[SIZE_OF_BUFF];
    char	postcode[SSIZE_OF_BUFF];
    float  	amount;
} MyRecord;

#endif //LOUKASPETEINARIS_PRJ2_RECORD_H
