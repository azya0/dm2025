#include "application/application.h"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Application(argc, argv);
    } catch (std::exception& error) {
        std::cout << error.what();
        return 1;
    };

    return 0;
}
