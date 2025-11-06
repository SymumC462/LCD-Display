#ifndef LCDSCREEN_H
#define LCDSCREEN_H
#include <string>

class LCDScreen
{
    private: 
        int i2c_handle;
        void init();
    public:
        LCDScreen();
        ~LCDScreen();
        void displayStatic(std::string msg);
        void clear();
        void displayScroll(std::string msg, int times);
        
};

#endif 