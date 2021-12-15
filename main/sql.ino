#include "sql.h"

MySQL_Connection conn((Client *)&client);

String INSERT_SQL;

void updateInsertSqlQuery(struct SQL_Column* sqlColumn)
{
  INSERT_SQL = String("INSERT INTO ") + DATABASE + "." + INSERT_TABLE + 
  "(Weather, Temperature, FeelsTemp, MinTemp, MaxTemp, Humidity, Wind, innerTemperature, innerHumidity) VALUES ('" 
  + sqlColumn->strWeather + "','" 
  + sqlColumn->strTemperature + "','" 
  + sqlColumn->strFeelsLike + "','" 
  + sqlColumn->strTempMin + "','" 
  + sqlColumn->strTempMax + "','" 
  + sqlColumn->strHumidity + "','" 
  + sqlColumn->strWind + "','" 
  + sqlColumn->strDhtTemperature + "','" 
  + sqlColumn->strDhtHumidity 
  + "')";
}

void insertDB(struct SQL_Column* sqlColumn)
{
  MYSQL_DISPLAY("Connecting...");
  delay(500);
  if (conn.connectNonBlocking(SERVER, SERVER_PORT, (char*)USER, (char*)PASSWD) != RESULT_FAIL)
  {
    delay(500);
    MySQL_Query query_mem = MySQL_Query(&conn);
    if (conn.connected())
    {
      updateInsertSqlQuery(sqlColumn);
      MYSQL_DISPLAY(INSERT_SQL);
      if ( !query_mem.execute(INSERT_SQL.c_str()) ) { MYSQL_DISPLAY("Insert error"); } 
      else { MYSQL_DISPLAY("Data Inserted."); }
    }
    else { MYSQL_DISPLAY("Disconnected from Server. Can't insert."); } 
    conn.close();    // close the connection 
  } 
  else { MYSQL_DISPLAY("\nConnect failed. Trying again on next iteration."); }
}


void getDB_WindowState(String* dbWindowState)
{
  if (conn.connectNonBlocking(SERVER, SERVER_PORT, (char*)USER, (char*)PASSWD) != RESULT_FAIL)
  {
    delay(500);
    MYSQL_DISPLAY("Connecting...");
    delay(500);
    String query = "SELECT * FROM IoT.doorState ORDER BY log DESC LIMIT 1";

    row_values *row = NULL;
    String result;
    
    MySQL_Query query_mem = MySQL_Query(&conn); 
    if ( !query_mem.execute(query.c_str()) )
    {
      MYSQL_DISPLAY("Querying error");
      return;
    }
    query_mem.get_columns();
    row = query_mem.get_next_row();
    result = row->values[1];
    query_mem.close();
    MYSQL_DISPLAY1("dbWindowState: ", result);
    *dbWindowState = result;
    conn.close();  
  }
  else { MYSQL_DISPLAY("\nConnect failed. Trying again on next iteration."); }

}
