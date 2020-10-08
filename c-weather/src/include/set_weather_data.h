#ifndef SET_WEATHER_DATA
#define SET_WEATHER_DATA

#include "../../include/cweather.h"
#include "Parsed_Json.h"

struct c_weather_data *set_weather_data(const char *data,
					struct Parsed_Json *parsed_json);

#endif
