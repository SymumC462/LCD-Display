#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include <curl/curl.h>
#include "Services/PiLCDScreen.hpp"
#include <nlohmann/json.hpp>
#include "Displayer.cpp"

int main(int argc, char* argv[]) {
    PiLCDScreen lcd;
    Displayer displayer(lcd, std::cout);
    displayer.Run(argc, argv);
}