#ifndef USERIO_HPP
#define USERIO_HPP

#include <iostream>

class UserIO {
public:

    static void outputError(int error, const char* description) {
        fprintf(stderr, "Error [%d]: %s\n", error, description);
    }

};

#endif
