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

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Main, temp)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(WeatherReport, main)

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

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