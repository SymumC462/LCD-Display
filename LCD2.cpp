#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include "Services/LCDScreen.hpp"
using namespace std;

int main() {
    LCDScreen lcd;
    lcd.clear();
    lcd.displayScroll("Symum");
    lcd.clear();
    lcd.moveToSecondLine();
    lcd.displayScroll("Symum");
    return 0;
}



    
   

