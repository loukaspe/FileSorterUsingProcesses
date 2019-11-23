/* This class will have a static function that will be called from the
 * coordinator and will create the coaches processes */

#include <iostream>
#include "Coach.h"

using namespace std;

#ifndef LOUKASPETEINARIS_PRJ2_COACHFACTORY_H
#define LOUKASPETEINARIS_PRJ2_COACHFACTORY_H

class CoachFactory {
public:
    static void createCoachesAndDoAction(
        int,
        char*,
        char**,
        int,
        SorterType*
    );
private:
    static const char* FORK_ERROR;
    static char* MALLOC_FAIL_ERROR_MESSAGE;
};

#endif //LOUKASPETEINARIS_PRJ2_COACHFACTORY_H