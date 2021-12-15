from os import name
import telegram
from telegram.ext import Updater, MessageHandler, Filters, CommandHandler  
from threading import Thread
from datetime import datetime
from dbconn import *
import schedule
import time

access = "API KEY"
secret = "API KEY"
myToken = "API TOKEN"

bot_token = 'API BOT TOKEN'
bot = telegram.Bot(token=bot_token)

chat_id = 'CHAT ID'


date = datetime.now().strftime('%Y/%m/%d') 
feels = ""
cloud = ""
isRain = "" 


def morning_message():
    global cloud
    data = DataBase.getWeatherData()
    weather = str(data[1]) 
    if(weather == "Clear"):
        cloud = "맑으며"
    elif(weather == "Clouds"):
        cloud = "흐리며"
    elif(weather == "Rain"):
        cloud = "비가오며"

    if(float(data[3]) < float(0)):
        feels = "날씨가 추우니 옷을 단단히 입고 나가세요.\n"
    elif(float(data[3]) < float(0) and float(data[7]) > float(4)):
        feels = "날씨가 많이 추우니 옷을 단단히 입고 나가세요.\n"
    else:
        feels = ""
    bot.sendMessage(chat_id=chat_id, text=f'{date}\n좋은 아침이에요!\n현재 날씨는 {cloud}\n기온은 {data[2]}도 이고 습도는 {data[6]}% 입니다.\n'+
                    f'{feels}\n\n현재 방 내부 온도는 {data[8]}도 이며 습도는 {data[9]}% 입니다.')

        
def rainCheck():
    global isRain
    rainData = DataBase.getWeatherData()   
    rainCompare = str(rainData[1])
    
    if(rainCompare == "Rain"):
        if(isRain != rainCompare):
            isRain = rainCompare
            bot.sendMessage(chat_id=chat_id, text=f'비 안내 문자입니다.\n현재 비가와요 우산을 챙기세요!')
    else:
        isRain = rainCompare
            


schedule.every().day.at("07:00").do(morning_message)
# schedule.every().hour.do(rainning_message)
# schedule.every(60).seconds.do(morning_message)
schedule.every(5).seconds.do(rainCheck)

while True:
    try:
        schedule.run_pending()
    except Exception as error:
        print(error)
        bot.sendMessage(chat_id='chat_id', text=f'Code Error! \n {str(error)}')
        pass
    time.sleep(1)
