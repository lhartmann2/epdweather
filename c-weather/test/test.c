#include <stdio.h>
#include <stdlib.h>

#include <cweather.h>

int main(void)
{
	printf("Making struct...\n");
	struct c_weather_data *wdata;
	printf("Made struct.\n");
	
	printf("Attempting to get data...\n");
	wdata = c_weather_get_data();
	if(!wdata) {
		printf("exit failure\n");
		exit(EXIT_FAILURE);
	}

	printf("Conditions: %s\n", wdata->conditions);
	printf("Pressure: %s\n", wdata->pressure);
	printf("Humidity: %s\n", wdata->humidity);
	printf("Temp: %s\n", wdata->temp);

	printf("Attempting to free struct...\n");
	c_weather_free(wdata);
	printf("Freed struct.\n");

	return 0;
}
