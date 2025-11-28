#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include <cmath>
#include <curl/curl.h>
#include "Services/LCDScreen.hpp"
using namespace std;


/** Next Feature:
 * Epic: When I run the commmand displayWeather, I expect details about the weather (like temperature in 
 * Fahrenheit, percentange of rain, etc.) to show up on the LCD Screen.
 * **/

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;  // Calculate total bytes received
    output->append((char*)contents, totalSize);  // Add data to our string
    return totalSize;  // Tell curl we handled all the data
}

int main(int argc, char* argv[]) {
    LCDScreen lcd;
    if (argc <= 2 && argv[1] == "Print")
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
        lcd.clear();
        string response;
        CURL *curl;
        CURLcode res;
    
        curl = curl_easy_init();  // Initialize curl
    
        if(curl) 
        {
            // Set the URL - replace YOUR_API_KEY with your actual key
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?lat=40.7127281&lon=-74.0060152&appid=013e897115d718bd0f5ffbc39108c750");
            
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            // Perform the request
            res = curl_easy_perform(curl);
            
            // Clean up
            curl_easy_cleanup(curl);
        }
        // cout << response << endl; <-- this printed the full JSON
        // Find where "temp": appears in the string
        size_t tempPos = response.find("\"temp\":");

        if(tempPos != string::npos) {  // Check if we found it
            // Move past "temp": to get to the number
            size_t numberStart = tempPos + 7;  // 7 characters in "temp":
            
            // Find where the number ends (at the comma)
            size_t numberEnd = response.find(",", numberStart);
            
            // Extract just the temperature number
            string tempStr = response.substr(numberStart, numberEnd - numberStart);
            
            // Convert string to number
            double tempKelvin = stod(tempStr);  // stod = string to double
            
            // Convert Kelvin to Fahrenheit
            double tempFahrenheit = (tempKelvin - 273.15) * 9.0/5.0 + 32.0;

            tempFahrenheit = trunc(tempFahrenheit * 100.0) / 100.0;
            cout << "Temperature: " << tempFahrenheit << "°F" << endl;
            lcd.displayStatic("Temp: ");
            string tempFahrenheitInString = to_string(tempFahrenheit);
            tempFahrenheitInString = tempFahrenheitInString.substr(0, 5);
            lcd.displayStatic(tempFahrenheitInString);
            lcd.displayStatic("F");
        }
    }
    else
    {
        cout << "Mode must be Print or Weather" << endl;
        return 1;
    }
    
    return 0;
}



    
   

