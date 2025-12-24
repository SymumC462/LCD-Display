#include "LCDScreenSpy.hpp"
#include <string>
using namespace std;

LCDScreenSpy::LCDScreenSpy()
{
    displayScrollCallCount = 0;
    moveToSecondLineCallCount = 0;
}

LCDScreenSpy::~LCDScreenSpy()
{
}

void LCDScreenSpy::displayStatic(string msg)
{
}

void LCDScreenSpy::clear()
{
}

void LCDScreenSpy::moveToSecondLine()
{
    moveToSecondLineCallCount++;
}

void LCDScreenSpy::displayScroll(string msg)
{
    displayScrollCallCount++;
}
