#include "CurlWeatherClient.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

CurlWeatherClient::CurlWeatherClient()
{
    curl = curl_easy_init();
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

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &information);
            res = curl_easy_perform(curl);
            report = nlohmann::json::parse(information).get<WeatherReport>();
            tempKelvin = report.main.temp;
            tempFahrenheit = (tempKelvin - 273.15); // to Celsius
            tempFahrenheit = (tempFahrenheit * 1.8) + 32; // to Fahrenheit
            tempFahrenheit = trunc(tempFahrenheit * 100) / 100;
        }    
    }
    else
    {
        tempFahrenheit = -2; // signal to Displayer that initialization failed
    }
}

CurlWeatherClient::~CurlWeatherClient()
{
    curl_easy_cleanup(curl);
}

double CurlWeatherClient::GetTempFahrenheit()
{
    if (res != CURLE_OK)
    {
        return -3; // signal to Displayer that Weather API is down
    }
    else
    {
        return tempFahrenheit;
    }
}