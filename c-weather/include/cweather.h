#ifndef _CWEATHER_H_
#define _CWEATHER_H_

#ifdef __cplusplus
extern "C" {
#endif

struct c_weather_data {
	const char *lat;
	const char *lon;
	const char *conditions;
	const char *description;
	const char *temp;
	const char *pressure;
	const char *low;
	const char *high;
	const char *feelsLike;
	const char *humidity;
	const char *icon;
	const char *wind;
	const char *speed;
	const char *deg;
};

#pragma GCC visibility push(default)

extern void c_weather_free(struct c_weather_data *wdata);
extern struct c_weather_data *c_weather_get_data();

#pragma GCC visibility pop

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _CWEATHER_H_ */
