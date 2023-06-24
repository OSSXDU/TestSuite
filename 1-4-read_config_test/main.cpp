#include <iostream>

#include "TestConfiguration.h"

int main() {
    TestConfiguration t;
    t.run();
    long nFail = t.report();
    if (nFail == 0) {
        std::cout << "TestConfiguration passed" << std::endl;
    } else {
        std::cout << "TestConfiguration failed" << std::endl;
    }
    return 0;
}
