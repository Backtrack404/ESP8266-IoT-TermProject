#include "main.h"

SQL_Column sqlColumn;

Task dbUpdate_Task(_30MIN, TASK_FOREVER, &dbUpdateTask);
Scheduler dbUpdateScheduler;

String nowWindowState="NULL";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  initSensor();
  MYSQL_DISPLAY1("\nStarting Basic_Insert_WiFi on", BOARD_NAME);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);
  // Remember to initialize your WiFi module
  #if ( USING_WIFI_ESP8266_AT  || USING_WIFIESPAT_LIB ) 
    #if ( USING_WIFI_ESP8266_AT )
      MYSQL_DISPLAY("Using ESP8266_AT/ESP8266_AT_WebServer Library");
    #elif ( USING_WIFIESPAT_LIB )
      MYSQL_DISPLAY("Using WiFiEspAT Library");
    #endif
    // initialize serial for ESP module
    EspSerial.begin(115200);
    WiFi.init(&EspSerial);
    MYSQL_DISPLAY(F("WiFi shield init done"));
    // check for the presence of the shield
    if (WiFi.status() == WL_NO_SHIELD)
    {
      MYSQL_DISPLAY(F("WiFi shield not present"));
      // don't continue
      while (true);
    }
  #endif
  // Begin WiFi section
  MYSQL_DISPLAY1("Connecting to", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    MYSQL_DISPLAY0(".");
  }
  // print out info about the connection:
  MYSQL_DISPLAY1("Connected to network. My IP address is:", WiFi.localIP());
  MYSQL_DISPLAY3("Connecting to SQL Server @", SERVER, ", Port =", SERVER_PORT);
  MYSQL_DISPLAY5("User =", (char*)USER, ", PW =", (char*)PASSWD, ", DB =", DATABASE);

  dbUpdateScheduler.init();
  Serial.println("Initialized scheduler");
  
  dbUpdateScheduler.addTask(dbUpdate_Task);
  Serial.println("added dbUpdateScheduler");

  dbUpdateScheduler.enable();
  Serial.println("Enabled dbUpdateScheduler");

  clearLcd();
}


void loop()
{
  dbUpdateScheduler.execute();
  String dbWindowState;

  getWeatherData(&sqlColumn); // 날씨 데이터 받아옴
  getDhtData(&sqlColumn);     // 온습도 센서 데이터 읽어옴
  
  printLcd(&sqlColumn);       // LCD 최신버전으로 다시 출력 

  getDB_WindowState(&dbWindowState);  // DB에서 창문 상태 받아옴

  Serial.print("DB창문 상태:" + dbWindowState + "\n");
  Serial.print("현재창문 상태:" + nowWindowState + "\n");

  if(nowWindowState.compareTo(dbWindowState) != SAME)   // 현재 창문상태와 DB창문상태가 다르면
  {
    Serial.print("DB와 현재 상태 다름\n");
    moveMotor(&dbWindowState);           // Moter를 움직여서 DB 창문상태로 만듦
    nowWindowState = dbWindowState;     // 현재상태를 업데이트
  }
  else { Serial.print("DB와 현재 상태 같음\n"); }

  Serial.print("업데이트 현재창문 상태:" + nowWindowState + "\n");
  Serial.print("DB창문 상태:" + dbWindowState + "\n");

  delay(1000);
}

void dbUpdateTask()
{
  getWeatherData(&sqlColumn); // 날씨 데이터 받아옴
  getDhtData(&sqlColumn);     // 온습도 센서 데이터 읽어옴
  
  insertDB(&sqlColumn);       // DB에 넣음
  
  clearLcd();                 // 이전 LCD 화면 지우고
  printLcd(&sqlColumn);       // LCD 최신버전으로 다시 출력 
}
