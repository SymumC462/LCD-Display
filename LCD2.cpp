#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include "Services/LCDScreen.hpp"
using namespace std;

int main() {
    LCDScreen lcd;
    lcd.clear();
    lcd.displayScroll("Charlie", 16);
    return 0;
}



    
   

