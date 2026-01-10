#ifndef WEATHERCLIENTSPY_H
#define WEATHERCLIENTSPY_H

#include "../../Interfaces/WeatherClient.hpp"
#include <string>

class WeatherClientSpy : public WeatherClient
{
private:
    double tempFahrenheit;
    std::string status;
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
    void SetStatus(std::string status)
    {
        this->status = status;
    }
    std::string GetStatus() override
    {
        return status;
    }
};
#endif