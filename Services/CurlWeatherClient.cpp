#include "CurlWeatherClient.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Main, temp)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Weather, main)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WeatherReport, main, weather)

CurlWeatherClient::CurlWeatherClient()
{
    curl = curl_easy_init();
}

CurlWeatherClient::~CurlWeatherClient()
{
    curl_easy_cleanup(curl);
}

double CurlWeatherClient::GetTempFahrenheit()
{
    if (curl)
    {
        const char* key = std::getenv("WEATHER_API_KEY");
        if (!key)
        {
            tempFahrenheit = -1; // signal to Displayer that key didn't get set
        }
        else
        {
            string url = "https://api.openweathermap.org/data/2.5/weather?lat=40.7127281&lon=-74.0060152&appid=" + string(key);

            information.clear(); // needed because every request appends the json to information
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
                return -3; // signal to Displayer that Weather API is down
            }
        }    
    }
    else
    {
        tempFahrenheit = -2; // signal to Displayer that initialization failed
    }
    return tempFahrenheit;
}

std::string CurlWeatherClient::GetStatus()
{
    if (curl)
    {
        const char* key = std::getenv("WEATHER_API_KEY");
        if (!key)
        {
            status = "-1"; // signal to Displayer that key didn't get set
        }
        else
        {
            string url = "https://api.openweathermap.org/data/2.5/weather?lat=40.7127281&lon=-74.0060152&appid=" + string(key);

            information.clear(); // needed because every request appends the json to information
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &information);
            res = curl_easy_perform(curl);
            report = nlohmann::json::parse(information).get<WeatherReport>();
            status = report.weather[0].main; 
            if (res != CURLE_OK)
            {
                return "-3"; // signal to Displayer that Weather API is down
            }
        }    
    }
    else
    {
        status = "-2"; // signal to Displayer that initialization failed
    }
    return status;    
}