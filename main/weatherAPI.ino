#include "weatherAPI.h"

void getWeatherData(struct SQL_Column *sqlColumn) 
{
  String strResult;
  
  if (client.connect(SERVER_NAME, 80)) 
  { 
    client.println("GET /data/2.5/weather?id="+CITYID+"&units=metric&APPID="+APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else 
  {
    Serial.println("connection failed"); 
    Serial.println();
  }

  while(client.connected() && !client.available()) delay(1); 
  while (client.connected() || client.available())  
  {
    char clnt_read = client.read(); 
    strResult = strResult+clnt_read;
  }

  client.stop(); 
  strResult.replace('[', ' ');
  strResult.replace(']', ' ');
  Serial.println(strResult);

  char jsonArray [strResult.length()+1];
  strResult.toCharArray(jsonArray,sizeof(jsonArray));
  jsonArray[strResult.length() + 1] = '\0';

  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);
  if (!root.success())
    Serial.println("parseObject() failed");

  { // 외부에서 사용하지 마시오.
    String location = root["name"];
    String country = root["sys"]["country"];
    float temperature = root["main"]["temp"];
    float feels_like = root["main"]["feels_like"];
    float temp_min = root["main"]["temp_min"];
    float temp_max = root["main"]["temp_max"];
    float humidity = root["main"]["humidity"];
    float wind = root["wind"]["speed"];
    String weather = root["weather"]["main"];
    String description = root["weather"]["description"];
    float pressure = root["main"]["pressure"];

    sqlColumn->strWeather = weather; 
    sqlColumn->strTemperature = String(temperature);
    sqlColumn->strHumidity = String(humidity);
    sqlColumn->strWind = String(wind);
    sqlColumn->strFeelsLike = String(feels_like);
    sqlColumn->strTempMin = String(temp_min);
    sqlColumn->strTempMax = String(temp_max);

    weather.toCharArray(sqlColumn->chrWeather, weather.length()+1);
    sprintf(sqlColumn->chrTemperture, "%.2f", temperature);
    sprintf(sqlColumn->chrHumidity, "%.2f", humidity);
  } // 외부에서 사용하지 마시오.

  
}