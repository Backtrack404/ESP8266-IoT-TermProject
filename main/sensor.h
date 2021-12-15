#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "OLED.h"
#include "DHT.h"
#include <Wire.h>
#include <Servo.h>

#define DHTPIN 14
#define DHTTYPE DHT22

#define SERVOPIN 2

#define CLOSE 0
#define OPEN 180

void initSensor();
void getDhtData(struct SQL_Column *sqlColumn);
void clearLcd();
void printLcd(struct SQL_Column *sqlColumn);
void moveMotor(String* dbWindowState);

#endif
