#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H

class WeatherClient
{
public:
    virtual ~WeatherClient() = default;
    virtual double GetTempFahrenheit() = 0;
};
#endif