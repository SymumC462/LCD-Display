#ifndef LCDSCREEN_H
#define LCDSCREEN_H
#include <string>

class LCDScreen
{
public:
    virtual ~LCDScreen() = default;  // Virtual destructor is important for interfaces
    
    virtual void displayStatic(std::string msg) = 0;
    virtual void clear() = 0;
    virtual void displayScroll(std::string msg) = 0;
    virtual void moveToSecondLine() = 0;
};

#endif
