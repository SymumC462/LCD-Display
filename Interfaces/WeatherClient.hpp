#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H
#include <string>

class WeatherClient
{
public:
    virtual ~WeatherClient() = default;
    virtual double GetTempFahrenheit() = 0;
    virtual std::string GetStatus() = 0;
};
#endif