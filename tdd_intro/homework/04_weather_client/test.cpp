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
2. Using IWeatherServer interface, implement functions for collecting statistics for the certain period of time:
- Average temperature
- Minimum temperature
- Maximum temperature
- Average wind direction
- Maximum wind force
  
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
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw statistics for the given day
    virtual std::string GetWeather(const std::string& dateTime) = 0;
};

TEST(WeatherServer, ParseResponse1)
{
    Weather weather = ParseResponse("20;181;5.1");
    EXPECT_FLOAT_EQ(20, weather.temperature);
    EXPECT_FLOAT_EQ(181, weather.windDirection);
    EXPECT_FLOAT_EQ(5.1, weather.windForce);
}
