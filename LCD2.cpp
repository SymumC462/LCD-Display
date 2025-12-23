#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include <curl/curl.h>
#include "Services/LCDScreen.hpp"
#include <nlohmann/json.hpp>
#include "Displayer.cpp"
using namespace std;



int main(int argc, char* argv[]) {
    LCDScreen lcd;
    Displayer displayer;
    displayer.Run(lcd, argc, argv);
}



    
   

