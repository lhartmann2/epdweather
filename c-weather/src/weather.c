#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "../include/cweather.h"	/* for default (public) visibility */
#include "../lib/jsmn.h"
#include "include/Buffer.h"
#include "include/Parsed_Json.h"
#include "include/check_json_string.h"
#include "include/get_weather_data.h"
#include "include/parse_json.h"
#include "include/set_weather_data.h"
#include "include/read_file.h"
#include "include/search_city.h"
#include "include/errmsg.h"

void c_weather_free(struct c_weather_data *wdata)
{
	if (!wdata)
		return;

	free((char *)wdata->lat);
	free((char *)wdata->lon);
	free((char *)wdata->conditions);
	free((char *)wdata->description);
	free((char *)wdata->temp);
	free((char *)wdata->pressure);
	free((char *)wdata->humidity);
	free((char *)wdata->low);
	free((char *)wdata->high);
	free((char *)wdata->feelsLike);
	free((char *)wdata->icon);

	free(wdata);
}

struct c_weather_data *c_weather_get_data()
{
	char *data;
	char *weather_data;
	struct Parsed_Json *cities;
	struct Parsed_Json *weather;
	struct c_weather_data *wdata = NULL;
	int found;

	//data = read_file("../data/city.json");
	//if (!data) {
	//	errmsg("Failed to read city data from city.json");
	//	return NULL;
	//}

	/*
	 * Parse the json. 209580 is the precomputed number of
	 * tokens that will be used to allocate the memory.
	 */
	//cities = parse_json(data, 209580);
	//if (!cities)
	//	goto out_free_data;

	//found = search_city(city, data, cities->tokens);
	//if (found == -1) {
	//	errmsg("The city with name '%s' was not found in the archive. Please provide another city to search for", city);
	//	goto out_free_cities;
	//}

	weather_data = get_weather_data();
	//if (!weather_data)
	//	goto out_free_cities;

	weather = parse_json(weather_data, 2048);
	if (!weather)
		goto out_free_weather_data;

	wdata = set_weather_data(weather_data, weather);

	free(weather->tokens);
	free(weather);

out_free_weather_data:
	free(weather_data);

//out_free_cities:
//	free(cities->tokens);
//	free(cities);

//out_free_data:
//	free(data);

	return wdata;
}
