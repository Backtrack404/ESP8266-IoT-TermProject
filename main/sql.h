#ifndef __SQL_H__
#define __SQL_H__

#include "defines.h"
#include "Credentials.h"
#include <MySQL_Generic.h>

#define USING_HOST_NAME true
#if USING_HOST_NAME
  extern const char SERVER[] = "SERVER ADDRESS";
#else
  IPAddress server(IP, IP, IP, IP);
#endif

extern const char USER[] = "MySQL ID";              
extern const char PASSWD[] = "MySQL PW";          

extern const uint16_t SERVER_PORT = PORT;    ;
extern const char DATABASE[] = "DATABASE NAME";          
extern const char INSERT_TABLE[] = "TABLE NAME";     
extern const char SELECT_TABLE[] = "TABLE NAME";
extern const char SELECT_COLUMN[] = "TABLE NAME";

typedef struct SQL_Column 
{
  String strWeather;
  String strFeelsLike;
  String strTempMin; 
  String strTempMax;
  String strTemperature;
  String strHumidity;
  String strWind;

  float dhtTemperature;
  float dhtHumidity;
  String strDhtTemperature;
  String strDhtHumidity;

  char chrWeather[10];
  char chrTemperture[20];
  char chrHumidity[10];
  char chrDhtTemperature[10];
  char chrDhtHumidity[10];

}SQL_Column;

void updateInsertSqlQuery(struct SQL_Column* sqlColumn);
void* connectDB();
void insertDB(struct SQL_Column* sqlColumn);
void getDB_WindowState(String* dbWindowState);

#endif