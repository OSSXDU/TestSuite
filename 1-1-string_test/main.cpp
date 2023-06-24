// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
#include "TrimTest.h"

#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    TrimTest t;
    cout << "Running TrimTest:" << endl;
    t.run();
    return t.report();
    
    return 0;
}


