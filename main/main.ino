#include "main.h"

// MySQL 
MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

// db에 insert 시킬 구조체
SQL_Column sqlColumn;

// 30분마다 db에 insert
Task dbUpdate_Task(_30MIN, TASK_FOREVER, &dbUpdateTask);
Scheduler dbUpdateScheduler;

// 현재 창문상태를 받을 변수
String nowWindowState="NULL";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  initSensor();
  MYSQL_DISPLAY1("\nStarting Basic_Insert_WiFi on", BOARD_NAME);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);
  #if ( USING_WIFI_ESP8266_AT  || USING_WIFIESPAT_LIB ) 
    #if ( USING_WIFI_ESP8266_AT )
      MYSQL_DISPLAY("Using ESP8266_AT/ESP8266_AT_WebServer Library");
    #elif ( USING_WIFIESPAT_LIB )
      MYSQL_DISPLAY("Using WiFiEspAT Library");
    #endif
    EspSerial.begin(115200);
    WiFi.init(&EspSerial);
    MYSQL_DISPLAY(F("WiFi shield init done"));
    if (WiFi.status() == WL_NO_SHIELD)
    {
      MYSQL_DISPLAY(F("WiFi shield not present"));
      while (true);
    }
  #endif

  MYSQL_DISPLAY1("Connecting to", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    MYSQL_DISPLAY0(".");
  }

  MYSQL_DISPLAY1("Connected to network. IP address is:", WiFi.localIP());
  MYSQL_DISPLAY3("Connecting to SQL Server @", SERVER, ", Port =", SERVER_PORT);
  MYSQL_DISPLAY5("User =", (char*)USER, ", PW =", (char*)PASSWD, ", DB =", DATABASE);

  dbUpdateScheduler.init();
  Serial.println("Initialized scheduler");
  
  dbUpdateScheduler.addTask(dbUpdate_Task);
  Serial.println("dbUpdateScheduler 추가");

  dbUpdateScheduler.enable();
  Serial.println("dbUpdateScheduler 사용");

  clearLcd();
}


void loop()
{
  // dbUpdateTask() 함수 스케줄러 실행
  dbUpdateScheduler.execute();
  String dbWindowState;

  getWeatherData(&sqlColumn); // 날씨 데이터
  getDhtData(&sqlColumn);     // 온습도 센서 데이터
  
  printLcd(&sqlColumn);       // LCD 최신버전으로 다시 출력 

  getDB_WindowState(&dbWindowState);  // DB 창문 상태

  Serial.print("DB창문 상태:" + dbWindowState + "\n");
  Serial.print("현재창문 상태:" + nowWindowState + "\n");

  if(nowWindowState.compareTo(dbWindowState) != SAME) 
  {
    Serial.print("DB와 현재 상태 다름\n");
    moveMotor(&dbWindowState);           
    nowWindowState = dbWindowState;  
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
