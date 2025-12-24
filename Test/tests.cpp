#include <iostream>
#include "Doubles/LCDScreenSpy.hpp"
#include "../Displayer.cpp"
#include <vector>

using namespace std;

void assertTrue(bool condition, string message)
{
    if (condition == true)
    {
        return;
    }
    throw std::runtime_error(message);
}

int main(int argc, char* argv[]) {
    LCDScreenSpy spy;
    Displayer sut(spy);

    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "test message";
    char* sutargv[] = { arg0, arg1, arg2 };
    sut.Run(2, sutargv);


    vector<LCDCall> expectedCalls = 
        { LCDCall::DisplayScroll, LCDCall::MoveToSecondLine, LCDCall::DisplayScroll };
    vector<string> expectedMsgs = 
        { "test message", "test message" };
    spy.shouldCallInOrder(expectedCalls, expectedMsgs);

    cout << "\033[32m" << "✓ All tests passed" << "\033[0m" << endl;
    return 0;
}
