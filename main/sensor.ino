#include "sensor.h"

DHT dht(DHTPIN, DHTTYPE);
OLED display(4, 5);
Servo servo;

void initSensor()
{
  char chrLcdDisplay[10];
  dht.begin();
  servo.attach(SERVOPIN);
  display.begin();
  display.print("Booting...",0,0);
  display.print("IOT KIT VER", 2,0);
  sprintf(chrLcdDisplay, "%.1f",2.0);
  display.print(chrLcdDisplay,2,8);
}

void getDhtData(struct SQL_Column *sqlColumn)
{
    sqlColumn->dhtTemperature = dht.readTemperature();
    sqlColumn->dhtHumidity = dht.readHumidity();
    sqlColumn->strDhtTemperature = String(sqlColumn->dhtTemperature);
    sqlColumn->strDhtHumidity = String(sqlColumn->dhtHumidity);
    sqlColumn->strDhtTemperature.toCharArray(sqlColumn->chrDhtTemperature,sqlColumn->strDhtTemperature.length()+1);
    sqlColumn->strDhtHumidity.toCharArray(sqlColumn->chrDhtHumidity,sqlColumn->strDhtHumidity.length()+1);
}

void clearLcd()
{
  display.print("                        ",0,0);
  display.print("                        ",1,0);
  display.print("                        ",2,0);
  display.print("                        ",3,0);
}

void printLcd(struct SQL_Column *sqlColumn)
{
  display.print(sqlColumn->chrWeather, 0, 0);
  display.print(sqlColumn->chrTemperture,1, 0);
  display.print(sqlColumn->chrHumidity,1, 9);
  display.print("IN ",3,0);
  display.print(sqlColumn->chrDhtTemperature,3,3);
  display.print(sqlColumn->chrDhtHumidity,3, 9);
}

void moveMotor(String* dbWindowState)
{
  if(dbWindowState->compareTo("open")) { servo.write(OPEN); }
  else { servo.write(CLOSE); } 
}
