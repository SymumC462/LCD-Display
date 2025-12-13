#include <iostream>
#include <lgpio.h>
#include <unistd.h>
#include <string>
#include <curl/curl.h>
#include "Services/LCDScreen.hpp"
#include <nlohmann/json.hpp>
using namespace std;

struct Main{
    double temp;
};

struct WeatherReport{
    Main main;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Main, temp)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WeatherReport, main)

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

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
        string information;
        CURL *curl;
        CURLcode res;
        double tempKelvin;
        double tempFahrenheit;
        WeatherReport report;
        

        curl = curl_easy_init();
        if (curl)
        {
            const char* key = std::getenv("WEATHER_API_KEY");
            if (!key)
            {
                std::cerr << "WEATHER_API_KEY didn't get set" << endl;
                return 1;
            }
            
            string url = "https://api.openweathermap.org/data/2.5/weather?lat=40.7127281&lon=-74.0060152&appid=" + string(key);

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &information);
            res = curl_easy_perform(curl);
            report = nlohmann::json::parse(information).get<WeatherReport>();
            tempKelvin = report.main.temp;
            tempFahrenheit = (tempKelvin - 273.15); // to Celsius
            tempFahrenheit = (tempFahrenheit * 1.8) + 32; // to Fahrenheit
            tempFahrenheit = trunc(tempFahrenheit * 100) / 100;

            if (res != CURLE_OK)
            {
                cout << "curl_easy_perform() failed" << endl;
            }
            else 
            {
                lcd.displayStatic("Temp: ");
                lcd.displayStatic(to_string(tempFahrenheit));
                lcd.displayStatic(" F");
            }

            curl_easy_cleanup(curl);

        }
        else 
        {
            cout << "initialization failed." << endl;
        }
        
    }
    else 
    {
        cout << "Mode must be Print or Weather" << endl;
        return 1;
    }
    
    return 0;
}



    
   

