#include <iostream>
#include "Doubles/LCDScreenSpy.hpp"
#include "../Displayer.cpp"
#include "Doubles/WeatherClientSpy.hpp"
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

void PrintMessage_DisplaysMessage(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "test message";
    char* sutargv[] = { arg0, arg1, arg2 };

    sut.Run(3, sutargv);

    vector<LCDCall> expectedCalls = 
        { LCDCall::DisplayScroll, LCDCall::MoveToSecondLine, LCDCall::DisplayScroll };
    vector<string> expectedMsgs = 
        { "test message", "test message" };
    lcdSpy.shouldCallInOrder(expectedCalls, expectedMsgs);
}

void PrintMessage_DisplaysAnotherMessage(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "Hi this is test";
    char* sutargv[] = { arg0, arg1, arg2 };

    sut.Run(3, sutargv);

    vector<LCDCall> expectedCalls = 
        { LCDCall::DisplayScroll, LCDCall::MoveToSecondLine, LCDCall::DisplayScroll };
    vector<string> expectedMsgs = 
        { "Hi this is test", "Hi this is test" };
    lcdSpy.shouldCallInOrder(expectedCalls, expectedMsgs);
}

void PrintMessage_MissingArgument_DisplaysNoMessageAndCoutError(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char* sutargv[] = { arg0, arg1 };

    sut.Run(2, sutargv);
    lcdSpy.ShouldHaveNoCalls();
    assertTrue(outSpy.str() == "Error: Both Mode and Argument must be provided\n", "Incorrect message printed");
}

void PrintMessage_MessageIsTooLong(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Print";
    char arg2[] = "test message that is too long";
    char* sutargv[] = { arg0, arg1, arg2 };

    sut.Run(3, sutargv);
    lcdSpy.ShouldHaveNoCalls();
    assertTrue(outSpy.str() == "Error: Message too long to be displayed\n", "Incorrect message printed");
}

void GetWeather_DisplaysWeather(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy, WeatherClientSpy&) {
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

void GetWeather_WeatherAPIIsDown(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "Weather";
    char* sutargv[] = { arg0, arg1 };

    sut.Run(2, sutargv);

    lcdSpy.ShouldHaveNoCalls();
    assertTrue(outSpy.str() == "Weather API is down.\n", "Incorrect message printed");
}

void ModeIsNotPrintOrWeather(Displayer& sut, LCDScreenSpy& lcdSpy, stringstream& outSpy)
{
    char arg0[] = "testcmd";
    char arg1[] = "PrinT";
    char* sutargv[] = { arg0, arg1 };

    sut.Run(2, sutargv);
    lcdSpy.ShouldHaveNoCalls();
    assertTrue(outSpy.str() == "Mode must be Print or Weather\n", "Incorrect message printed");
}

//// TEST END

int main(int argc, char* argv[]) {
    std::vector<std::function<void(Displayer&, LCDScreenSpy&, stringstream&)>> printTests = {
        PrintMessage_DisplaysMessage,
        PrintMessage_DisplaysAnotherMessage,
        PrintMessage_MissingArgument_DisplaysNoMessageAndCoutError,
        PrintMessage_MessageIsTooLong,
        ModeIsNotPrintOrWeather
    };

    std::vector<std::function<void(Displayer&, LCDScreenSpy&, stringstream&, WeatherClientSpy&)>> weatherTests = {
        GetWeather_DisplaysWeather
    };

    int i = 1;
    for (auto& test : printTests) {
        LCDScreenSpy lcdSpy;
        stringstream outSpy;
        WeatherClientSpy weatherSpy;
        Displayer sut(lcdSpy, outSpy, weatherSpy);
        test(sut, lcdSpy, outSpy);
        cout << "\033[32m" << "Test " + to_string(i++) + " passed" << "\033[0m" << endl;
    }
    for (auto&test : weatherTests)
    {
        LCDScreenSpy lcdSpy;
        stringstream outSpy;
        WeatherClientSpy weatherSpy;
        Displayer sut(lcdSpy, outSpy, weatherSpy);
        test(sut, lcdSpy, outSpy, weatherSpy);
        cout << "\033[32m" << "Test " + to_string(i++) + " passed" << "\033[0m" << endl;
    }

    cout << "\033[32m" << "✓ All tests passed" << "\033[0m" << endl;
    return 0;
}
