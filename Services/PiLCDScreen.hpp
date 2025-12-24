#ifndef PILCDSCREEN_H
#define PILCDSCREEN_H
#include <string>
#include "LCDScreen.hpp"  // Include the interface

class PiLCDScreen : public LCDScreen  // Inherit from LCDScreen
{
private: 
    int i2c_handle;
    void init();
    
public:
    PiLCDScreen();
    ~PiLCDScreen() override;  // Override keyword for clarity
    
    void displayStatic(std::string msg) override;
    void clear() override;
    void displayScroll(std::string msg) override;
    void moveToSecondLine() override;
};

#endif