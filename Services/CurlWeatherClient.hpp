#ifndef CURLWEATHERCLIENT_H
#define CURLWEATHERCLIENT_H
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "../Interfaces/WeatherClient.hpp"
using namespace std;

struct Main{
    double temp;
};

struct WeatherReport{
    Main main;
};



class CurlWeatherClient : public WeatherClient
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
    ~CurlWeatherClient() override;
    double GetTempFahrenheit() override;
};


#endif