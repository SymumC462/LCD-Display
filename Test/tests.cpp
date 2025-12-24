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

//// TESTS

void PrintMessage_DisplaysMessage(Displayer& sut, LCDScreenSpy& lcdSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "test message";
    char* sutargv[] = { arg0, arg1, arg2 };

    sut.Run(2, sutargv);

    vector<LCDCall> expectedCalls = 
        { LCDCall::DisplayScroll, LCDCall::MoveToSecondLine, LCDCall::DisplayScroll };
    vector<string> expectedMsgs = 
        { "test message", "test message" };
    lcdSpy.shouldCallInOrder(expectedCalls, expectedMsgs);
}

void GetWeather_DisplaysWeather(Displayer& sut, LCDScreenSpy& lcdSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Weather";
    char* sutargv[] = { arg0, arg1 };

    sut.Run(2, sutargv);

    vector<LCDCall> expectedCalls = 
        { LCDCall::DisplayStatic, LCDCall::DisplayStatic, LCDCall::DisplayStatic };
    vector<string> expectedMsgs = 
        { "Temp: ", "%i", " F" };
    lcdSpy.shouldCallInOrder(expectedCalls, expectedMsgs);
}

//// TEST END

int main(int argc, char* argv[]) {
    std::vector<std::function<void(Displayer&, LCDScreenSpy&)>> tests = {
        PrintMessage_DisplaysMessage,
        GetWeather_DisplaysWeather
    };

    int i = 1;
    for (auto& test : tests) {
        LCDScreenSpy lcdSpy;
        Displayer sut(lcdSpy);
        test(sut, lcdSpy);
        cout << "\033[32m" << "Test " + to_string(i++) + " passed" << "\033[0m" << endl;
    }

    cout << "\033[32m" << "✓ All tests passed" << "\033[0m" << endl;
    return 0;
}
