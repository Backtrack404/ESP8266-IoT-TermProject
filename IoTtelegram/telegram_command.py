from os import name
import telegram
from telegram.ext import Updater, MessageHandler, Filters, CommandHandler  
from threading import Thread
from datetime import datetime
from dbconn import *

access = "API KEY"
secret = "API KEY"
myToken = "API TOKEN"

bot_token = 'API BOT TOKEN'
bot = telegram.Bot(token=bot_token)

chat_id = 'CHAT ID'


date = datetime.now().strftime('%Y/%m/%d') 
feels = ""
cloud = ""

#명령어 정의
def help_command(update, context) :
    bot.sendMessage(chat_id=chat_id, text='아침 7시마다 날씨를 자동으로 알려드립니다.\n\n'
                    +'명령어\n'
                    +'\'날씨\' 를 입력하시면 현재 날씨를 알려드립니다.\n'
                    +'\'창문닫아줘\' 를 입력하시면 창문을 닫습니다.\n'
                    +'\'창문열어줘\' 를 입력하시면 창문을 엽니다.\n\n'
                    +'추가적으로 비가 오면 자동으로 비 알람문자를 보내드립니다.\n')
      
# message reply function
def get_message(update, context) :
    global getcode, count, timeframe
    getMsg = update.message.text

    try:
        if getMsg[0:] == '창문닫아줘':
            DataBase.insertCloseWindow()
            update.message.reply_text("창문을 닫습니다.")
            
        elif getMsg[0:] == "창문열어줘":
            DataBase.insertOpenWindow()
            update.message.reply_text("창문을 엽니다.")

        elif getMsg[0:] == "날씨": 
            global cloud, flees, date
            weatherData = DataBase.getWeatherData()
            comp = str(weatherData[1])
            if(comp == "Clear"):
                cloud = "맑으며"
            elif(comp == "Clouds"):
                cloud = "흐리며"
            elif(comp == "Rain"):
                cloud = "비가오며"

            update.message.reply_text(f'{date}\n현재 날씨는 {cloud}\n기온은 {weatherData[2]}도 이고 습도는 {weatherData[6]}% 입니다.'+
                                      f'\n\n현재 방 내부 온도는 {weatherData[8]}도 이며 습도는 {weatherData[9]}% 입니다.')
                       
        else:
            update.message.reply_text(f"{getMsg[0:]}알 수 없는 오류!")
    except:
        update.message.reply_text("명령어 오류!\n문법에 맞지 않는 명령어 입니다.\n /help 명령어를 사용해보세요.")
        


    
#새 메시지 확인
updater = Updater(bot_token, use_context=True)


# 메세지중에서 command 제외
message_handler = MessageHandler(Filters.text & (~Filters.command), get_message) 
updater.dispatcher.add_handler(message_handler)


# 응답 커맨드 정의
help_handler = CommandHandler('help', help_command)
updater.dispatcher.add_handler(help_handler)

updater.start_polling(timeout=1, clean=True)
updater.idle()