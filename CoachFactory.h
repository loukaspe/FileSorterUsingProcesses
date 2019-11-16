/* This class will have a static function that will be called from the
 * coordinator and will create the coaches processes */

#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

#ifndef LOUKASPETEINARIS_PRJ2_COACHFACTORY_H
#define LOUKASPETEINARIS_PRJ2_COACHFACTORY_H

class CoachFactory {
public:
    static void getCoaches(int, char*, char**);
private:
    static const char* FORK_ERROR;
};


#endif //LOUKASPETEINARIS_PRJ2_COACHFACTORY_H
