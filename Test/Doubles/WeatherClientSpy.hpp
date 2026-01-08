#ifndef WEATHERCLIENTSPY_H
#define WEATHERCLIENTSPY_H

#include "../../Interfaces/WeatherClient.hpp"

class WeatherClientSpy : public WeatherClient
{
private:
    double tempFahrenheit;
public:
    WeatherClientSpy() {}
    ~WeatherClientSpy() override {}
    void SetTempFahrenheit(double temp)
    {
        tempFahrenheit = temp;
    }
    double GetTempFahrenheit() override
    {
        return tempFahrenheit;
    }
};
#endif