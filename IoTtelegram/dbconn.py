import sys
import pymysql
import numpy as np

host = 'SERVER ADDRESS'
port = int(PORT)
user = 'MySQL ID'
passwd = 'MySQL PASSWORD'
database = 'DATABASE NAME'
autocommit = False

class DataBase:
    def connectDB():
        try:
            conn = pymysql.connect(user = user, password = passwd, host = host,
                                   port = port, database = database, autocommit = autocommit)
        except pymysql.Error as error:
            print(f"Error connection to MariaDB : {error}")
            sys.exit(1)
        return conn
            
    def getWeatherData():
        conn = DataBase.connectDB()

        cur = conn.cursor()
        sql_query_m = "SELECT * FROM Weather ORDER BY num DESC LIMIT 1;"
    
        cur.execute(sql_query_m)
        rowList = cur.fetchall()
        conn.commit()
        cur.close()
        conn.close()
        
        rowArray = np.array(rowList)
        row = rowArray.reshape(-1)
        return row
           

    def insertCloseWindow():
        conn = DataBase.connectDB()

        cur = conn.cursor()
        sql_query_dclose = "INSERT INTO doorState(doorState) VALUES('close');"

        cur.execute(sql_query_dclose)
        conn.commit()
        cur.close()
        conn.close()
        
        
    def insertOpenWindow():
        conn = DataBase.connectDB()
        
        cur = conn.cursor()
        sql_query_dopen = "INSERT INTO doorState(doorState) VALUES('open');"
        
        cur.execute(sql_query_dopen)
        conn.commit()
        cur.close()
        conn.close()           


