#ifndef LCDSCREENSPY_H
#define LCDSCREENSPY_H
#include <string>
#include "../../Interfaces/LCDScreen.hpp"  // Include the interface

class LCDScreenSpy : public LCDScreen  // Inherit from LCDScreen
{
public:
    int displayScrollCallCount;
    int moveToSecondLineCallCount;
    LCDScreenSpy();
    ~LCDScreenSpy() override;  // Override keyword for clarity
    
    void displayStatic(std::string msg) override;
    void clear() override;
    void displayScroll(std::string msg) override;
    void moveToSecondLine() override;
};

#endif
