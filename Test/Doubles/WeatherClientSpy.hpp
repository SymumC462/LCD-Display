#ifndef WEATHERCLIENTSPY_H
#define WEATHERCLIENTSPY_H

#include "../../Interfaces/WeatherClient.hpp"

class WeatherClientSpy : public WeatherClient
{
public:
    WeatherClientSpy() {}
    ~WeatherClientSpy() override {}
    double GetTempFahrenheit() override
    {
        return 2;
    }
};
#endif