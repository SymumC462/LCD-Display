#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include <curl/curl.h>
#include "Services/LCDScreen.hpp"
using namespace std;

/** Next Feature:
 * Epic: When I run the commmand displayWeather, I expect details about the weather (like temperature in 
 * Fahrenheit, percentange of rain, etc.) to show up on the LCD Screen.
 * **/
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
    else if (mode == "Weather")
    {
        CURL *curl;
        CURLcode res;
    
        curl = curl_easy_init();  // Initialize curl
    
        if(curl) 
        {
            // Set the URL - replace YOUR_API_KEY with your actual key
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?lat=40.7127281&lon=-74.0060152&appid=013e897115d718bd0f5ffbc39108c750");
            
            // Perform the request
            res = curl_easy_perform(curl);
            
            // Clean up
            curl_easy_cleanup(curl);
        }
    }
    else
    {
        cout << "Mode must be Print or Weather" << endl;
        return 1;
    }
    
    return 0;
}



    
   

