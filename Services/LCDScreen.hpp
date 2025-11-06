#ifndef LCDSCREEN_H
#define LCDSCREEN_H
#include <string>

class LCDScreen
{
    private: 
        int i2c_handle;
    public:
        void seti2c(int i2c);
        void displayStatic(std::string msg);
        void clear();
        void displayScroll(std::string msg, int times);
        void init();
};

#endif 