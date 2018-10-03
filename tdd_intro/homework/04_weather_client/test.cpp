/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data fro weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day or period of time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement the parsing of raw server response. To do this, you need to implement fake server,
because interacting with real network is inacceptable within the unit tests.
2. Using IWeatherServer interface, implement functions for collecting statistics for the certain day:
- Average temperature
- Minimum temperature
- Maximum temperature
- Average wind direction
- Maximum wind speed
  
You've collected some results for the several dates from the weather server.
Use this information to implement the tests for your program. Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

Server returns empty string if request is invalid.
Note, that the real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <numeric>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& dateTime) = 0;
};

// Implement these functions:
double GetAverageTemperature(IWeatherServer& server, const std::string& date);
double GetMinimumTemperature(IWeatherServer& server, const std::string& date);
double GetMaximumTemperature(IWeatherServer& server, const std::string& date);
double GetAverageWindDirection(IWeatherServer& server, const std::string& date);
double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date);

struct Weather
{
    short temperature = 0;
    unsigned short windDirection = 0;
    double windSpeed = 0;
    bool operator==(const Weather& right)
    {
        return temperature == right.temperature &&
               windDirection == right.windDirection &&
               std::abs(windSpeed - right.windSpeed) < 0.01;
    }
};

Weather ParseResponse(const std::string& response)
{
    Weather weather;
    auto sep1 = response.find_first_of(";");
    if (sep1 != std::string::npos)
    {
        weather.temperature = static_cast<short>(atoi(response.substr(0, sep1).c_str()));
        auto sep2 = response.find_first_of(";", sep1 + 1);
        if (sep2 != std::string::npos)
        {
            weather.windDirection = static_cast<unsigned short>(atoi(response.substr(sep1 + 1, sep2 - sep1).c_str()));
            weather.windSpeed = atof(response.substr(sep2 + 1).c_str());
            return weather;
        }
    }
    throw std::runtime_error("Invalid response");
}

double CalculateAverageTemperature(const std::vector<Weather>& weathers)
{
    double avg = 0;
    if (!weathers.empty())
    {
        avg = std::accumulate(weathers.begin(), weathers.end(), 0.0,
            [](double sum, const Weather& weather) { return sum + weather.temperature; }
        ) / weathers.size();
    }
    return avg;
}

std::vector<Weather> GetWeathersForADay(IWeatherServer& server, const std::string& date)
{
    std::vector<Weather> expectedWeathers = {
        { 20, 181, 5.1 },
        { 23, 204, 4.9 },
        { 33, 193, 4.3 },
        { 26, 179, 4.5 }
    };
    return expectedWeathers;
}

class FakeWeatherServer: public IWeatherServer
{
public:
    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& dateTime)
    {
        return "";
    }
};

TEST(WeatherClient, ParseResponse1)
{
    Weather weather = ParseResponse("20;181;5.1");
    EXPECT_EQ(20, weather.temperature);
    EXPECT_EQ(181, weather.windDirection);
    EXPECT_FLOAT_EQ(5.1, weather.windSpeed);
}

TEST(WeatherClient, ParseResponse2)
{
    Weather weather = ParseResponse("23;204;4.9");
    EXPECT_EQ(23, weather.temperature);
    EXPECT_EQ(204, weather.windDirection);
    EXPECT_FLOAT_EQ(4.9, weather.windSpeed);
}

TEST(WeatherClient, CalculateAverageTemperature)
{
    std::vector<Weather> weathers = {
        { 20, 181, 5.1 },
        { 23, 204, 4.9 },
        { 33, 193, 4.3 },
        { 26, 179, 4.5 }
    };

    double avg = CalculateAverageTemperature(weathers);
    ASSERT_DOUBLE_EQ(25.5, avg);
}

TEST(WeatherClient, CalculateAverageTemperature2)
{
    std::vector<Weather> weathers = {
        { 20, 181, 5.1 },
        { 26, 179, 4.5 }
    };

    double avg = CalculateAverageTemperature(weathers);
    ASSERT_DOUBLE_EQ(23, avg);
}

TEST(WeatherClient, GetWeathersForADay)
{
    FakeWeatherServer server;
    std::vector<Weather> expectedWeathers = {
        { 20, 181, 5.1 },
        { 23, 204, 4.9 },
        { 33, 193, 4.3 },
        { 26, 179, 4.5 }
    };
    std::vector<Weather> weathers = GetWeathersForADay(server, "31.08.2018");
    EXPECT_TRUE(std::equal(weathers.begin(), weathers.end(), expectedWeathers.begin(), expectedWeathers.end()));
}
