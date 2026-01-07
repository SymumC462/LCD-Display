#ifndef CURLWEATHERCLIENT_H
#define CURLWEATHERCLIENT_H
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using namespace std;

struct Main{
    double temp;
};

struct WeatherReport{
    Main main;
};



class CurlWeatherClient
{
private:
    std::string information;
    CURL *curl;
    CURLcode res;
    double tempKelvin;
    double tempFahrenheit;
    WeatherReport report;

public:

    CurlWeatherClient();
    ~CurlWeatherClient();
    double GetTempFahrenheit();
};


#endif