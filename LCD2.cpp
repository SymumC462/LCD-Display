#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include "Services/LCDScreen.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    LCDScreen lcd;
    if (argc <= 2)
    {
        cout << "Error: Both Mode and Argument must be provided" << endl;
        return 1;
    }

    string mode = argv[1];
    if (mode == "Print") // argv[1] represents Mode
    {
        lcd.clear();
        lcd.displayScroll(argv[2]); // argv[2] is the string to be printed
        lcd.clear();
        lcd.moveToSecondLine();
        lcd.displayScroll(argv[2]);
    }
    else 
    {
        cout << "Mode must be Print" << endl;
        return 1;
    }
    
    return 0;
}



    
   

