#include "sensor.h"

DHT dht(DHTPIN, DHTTYPE);
OLED display(4, 5);
Servo servo;

// 센서 초기화 및 사용선언
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

// DHT22 온습도 데이터를 sqlColumn 구조체에 넣음
void getDhtData(struct SQL_Column *sqlColumn)
{
    sqlColumn->dhtTemperature = dht.readTemperature();
    sqlColumn->dhtHumidity = dht.readHumidity();
    sqlColumn->strDhtTemperature = String(sqlColumn->dhtTemperature);
    sqlColumn->strDhtHumidity = String(sqlColumn->dhtHumidity);
    sqlColumn->strDhtTemperature.toCharArray(sqlColumn->chrDhtTemperature,sqlColumn->strDhtTemperature.length()+1);
    sqlColumn->strDhtHumidity.toCharArray(sqlColumn->chrDhtHumidity,sqlColumn->strDhtHumidity.length()+1);
}

// LCD clear
void clearLcd()
{
  display.print("                        ",0,0);
  display.print("                        ",1,0);
  display.print("                        ",2,0);
  display.print("                        ",3,0);
}

// LCD 출력
void printLcd(struct SQL_Column *sqlColumn)
{
  display.print(sqlColumn->chrWeather, 0, 0);
  display.print(sqlColumn->chrTemperture,1, 0);
  display.print(sqlColumn->chrHumidity,1, 9);
  display.print("IN ",3,0);
  display.print(sqlColumn->chrDhtTemperature,3,3);
  display.print(sqlColumn->chrDhtHumidity,3, 9);
}

// 모터제어
void moveMotor(String* dbWindowState)
{
  if(dbWindowState->compareTo("open")) { servo.write(OPEN); }
  else { servo.write(CLOSE); } 
}
