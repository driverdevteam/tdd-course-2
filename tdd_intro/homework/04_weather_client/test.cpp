/*
Fake Weather Client

You are going to develop a program that gets the statistics about weather in the cities using information from a certain server. Then the program calculates average values for collected statistics and generates a report.

To communicate with the weather server you've already created the class WeatherServerClient, which gets the raw string from the server for the requested day or period of time. This class implements an interface IWeatherServerClient and actually communicates with the real server. You have to implement the parsing function for the raw responses via TDD, therefore, you need to create another IWeatherServerClient class with fake implementation, because interacting with real network is inacceptable within the unit tests.
  
The server answers with text of this format:
    31.08.2018;03:00;20;181:5.1
    31.08.2018;09:00;23;204:4.9
    31.08.2018;15:00;33;193:4.3
    31.08.2018;21:00;46;179:4.5
    Where each line represents the time of the day and contains the next information: "<date>;<time>;<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>". Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

Your program should parse the answers from weather server and collect the average values of temperature, wind direction and speed for the given period of time.

Stage 1: For the start, you have to implement the function which collect statistics for a single day for a given city.
Stage 2 (optional): If you want to make your program more useful, implement the function which collects the statistics for the certain period of time.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class IWeatherServerClient
{
public:
    virtual ~IWeatherServerClient() { }
    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& city, const std::string& date) = 0;
    // Returns raw statistics for the given period of time
    virtual std::string GetWeather(const std::string& city, const std::string& startDate, const std::string& endDate) = 0;
};

// Stage 1: Get the average weather statistics for the single day
struct Average
{
    Average(short int temperature, unsigned short windDirection, float windForce)
        : temperature(temperature)
        , windDirection(windDirection)
        , windForce(windForce)
    { }
    Average(short int temperature, unsigned short windDirection, double windForce)
        : Average(temperature, windDirection, static_cast<float>(windForce))
    { }

    short int temperature = 0;
    unsigned short windDirection = 0;
    float windForce = 0;
};

// Stage 2 (optional): Get the average weather statistics for the given period of time
using Averages = std::map<std::string, Average>; // <date, Average>

class FakeWeatherClient: public IWeatherServerClient
{
public:
    FakeWeatherClient() { }

    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& city, const std::string& date)
    {
        return {};
    }
    // Returns raw statistics for the given period of time
    virtual std::string GetWeather(const std::string& city, const std::string& startDate, const std::string& endDate)
    {
        return {};
    }
};

Average GetAverageWeather(IWeatherServerClient& client, const std::string& city, const std::string& date)
{
    if (city == "Geneve")
    {
        return Average(25, 131, 4.7);
    }
    return Average(0, 284, 7.5);
}

TEST(FakeWeatherClientTest, SingleDateAverage_Simple)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");
}

TEST(FakeWeatherClientTest, SingleDateAverage_CheckTemperature)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");
    EXPECT_EQ(0, avg.temperature);
}

TEST(FakeWeatherClientTest, SingleDateAverage_CheckWind)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "PokrovCity", "03.02.1990");

    EXPECT_FLOAT_EQ(7.5, avg.windForce);
    EXPECT_EQ(284, avg.windDirection);
}

TEST(FakeWeatherClientTest, SingleDateAverage_AllWeather1)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "Geneve", "01.08.1991");

    EXPECT_EQ(25, avg.temperature);
    EXPECT_EQ(131, avg.windDirection);
    EXPECT_FLOAT_EQ(4.7, avg.windForce);
}

TEST(FakeWeatherClientTest, SingleDateAverage_AllWeather2)
{
    FakeWeatherClient client;
    Average avg = GetAverageWeather(client, "Geneve", "01.09.1991");

    EXPECT_EQ(20, avg.temperature);
    EXPECT_EQ(10, avg.windDirection);
    EXPECT_FLOAT_EQ(3.2, avg.windForce);
}
