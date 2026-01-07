#include <iostream>
#include <unistd.h>
#include <string>
#include <curl/curl.h>
#include "Interfaces/LCDScreen.hpp"
#include <nlohmann/json.hpp>
#include "Services/CurlWeatherClient.hpp"
using namespace std;

class Displayer
{
    private:
        LCDScreen& lcd;
        ostream& out;
    public:
        Displayer(LCDScreen& lcd, ostream& outparam) : lcd(lcd), out(outparam){}
        int Run(int argc, char* argv[]);
};


int Displayer::Run(int argc, char* argv[])
{
    string mode = argv[1];
    
    if (argc <= 2 && mode == "Print")
    {
        out << "Error: Both Mode and Argument must be provided" << endl;
        return 1;
    }
    if (mode == "Print" && strlen(argv[2]) < 17) 
    {
        lcd.clear();
        lcd.displayScroll(argv[2]); // argv[2] is the message to be printed
        lcd.clear();
        lcd.moveToSecondLine();
        lcd.displayScroll(argv[2]);
    }
    else if (mode == "Print" && strlen(argv[2]) >= 17)
    {
        out << "Error: Message too long to be displayed" << endl;
    }
    else if (mode == "Weather")
    {
        double tempFahrenheit;
        CurlWeatherClient weather;
        tempFahrenheit = weather.GetTempFahrenheit();
        // Let's assume a day never comes where we experience a temperature under 0 degrees Fahrenheit
        if (tempFahrenheit == -1) // signal that the key didn't get set
        {
            out << "Key didn't get set." << endl;
        }
        else if (tempFahrenheit == -2) // signal that initialization failed
        {
            out << "Curl nitialization failed." << endl;
        }
        else if (tempFahrenheit == -3) // signal that Weather API is Down
        {
            out << "Weather API is Down." << endl;
        }
        else
        {
            lcd.displayStatic("Temp: ");
            lcd.displayStatic((to_string(tempFahrenheit)).substr(0,5));
            lcd.displayStatic(" F");
        }
        
    }
    else 
    {
        out << "Mode must be Print or Weather" << endl;
        return 1;
    }
    
    return 0;
}
