#define _POSIX_C_SOURCE	200809L		/* for strndup(3) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cweather.h"
#include "../lib/jsmn.h"
#include "include/Parsed_Json.h"
#include "include/check_json_string.h"

static char *set_member(const char *data, struct Parsed_Json *weather, int idx)
{
	jsmntok_t token = weather->tokens[idx + 1];

	return strndup(data + token.start, token.end - token.start);
}

/**
 * Fill out a struct c_weather_data
 *
 * @param char *data The array of chars with the parsed json
 * @param struct Parsed_Json parsed_json contains all the parsed tokens
 *
 * @return struct c_weather_data *
 */
struct c_weather_data *set_weather_data(const char *data,
					struct Parsed_Json *weather)
{
	struct c_weather_data *wdata = calloc(1, sizeof(*wdata));

	for (int i = 1; i < weather->number_of_tokens; i++) {
		jsmntok_t token = weather->tokens[i];
		jsmntok_t ntoken = weather->tokens[i + 1];
		int length = token.end - token.start;
		char string[length + 1];

		strncpy(string, data + token.start, length);
		string[length] = '\0';

		if (check_json_string("lon", string, &token) == 0)
			wdata->lon = set_member(data, weather, i);

		if (check_json_string("lat", string, &token) == 0)
			wdata->lat = set_member(data, weather, i);

		if (check_json_string("main", string, &token) == 0 &&
		    ntoken.type != JSMN_OBJECT)
			wdata->conditions = set_member(data, weather, i);

		if (check_json_string("temp", string, &token) == 0 &&
		    ntoken.type != JSMN_OBJECT)
			wdata->temp = set_member(data, weather, i);

		if (check_json_string("pressure", string, &token) == 0 &&
		    ntoken.type != JSMN_OBJECT)
			wdata->pressure = set_member(data, weather, i);

		if (check_json_string("humidity", string, &token) == 0 &&
		    ntoken.type != JSMN_OBJECT)
			wdata->humidity = set_member(data, weather, i);

		if(check_json_string("description", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->description = set_member(data, weather, i);

		if(check_json_string("temp_min", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->low = set_member(data, weather, i);

		if(check_json_string("temp_max", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->high = set_member(data, weather, i);

		if(check_json_string("feels_like", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->feelsLike = set_member(data, weather, i);

		if(check_json_string("icon", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->icon = set_member(data, weather, i);

		if(check_json_string("wind", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->wind = set_member(data, weather, i);

		if(check_json_string("speed", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->speed = set_member(data, weather, i);

		if(check_json_string("deg", string, &token) == 0 &&
			ntoken.type != JSMN_OBJECT)
			wdata->deg = set_member(data, weather, i);

		
	}

	return wdata;
}