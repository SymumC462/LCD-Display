#include <iostream>
#include "Doubles/LCDScreenSpy.hpp"
#include "../Displayer.cpp"
using namespace std;

int main(int argc, char* argv[]) {
    LCDScreenSpy spy;
    Displayer sut(spy);

    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "test message";
    char* sutargv[] = { arg0, arg1, arg2 };
    sut.Run(2, sutargv);

    if (spy.displayScrollCallCount != 2)
    {
        cout << "Test failed with displayScrollCallCount not being 2" << endl;
        return 1;
    }
    if (spy.moveToSecondLineCallCount != 1)
    {
        cerr << "\033[31m" << "Test failed with moveToSecondLineCallCount not being 1" << "\033[0m"  << endl;
        return 1;
    }

    cout << "\033[32m" << "✓ All tests passed" << "\033[0m" << endl;
    return 0;
}
