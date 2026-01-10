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

struct Weather{
    string main;
};

struct WeatherReport{
    Main main;
    vector<Weather> weather;
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
    std::string status;

public:

    CurlWeatherClient();
    ~CurlWeatherClient() override;
    double GetTempFahrenheit() override;
    string GetStatus() override;
};


#endif