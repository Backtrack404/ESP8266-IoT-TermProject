#ifndef __WEATHER_API_H__
#define __WEATHER_API_H__

#include <ArduinoJson.h>

extern const String APIKEY = "API KEY";
extern const String CITYID = "1835848"; // Seoul, KR

extern const char SERVER_NAME[]="api.openweathermap.org";

void getWeatherData(struct SQL_Column *sqlColumn);

#endif
