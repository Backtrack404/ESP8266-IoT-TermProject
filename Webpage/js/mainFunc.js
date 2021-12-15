// <?php
// session_start();
// $conn = mysqli_connect("localhost", "Promotion_Pawn", "Roottoor3881!!", "IoT", 3307);
// $sql = "SELECT * FROM Weather ORDER BY Weather DESC LIMIT 1;";
// $result = mysqli_query($conn, $sql);
// $row = mysqli_fetch_array($result);
// $Weather = $row['Weather'];
// $Temperature = $row['Temperature'];
// $FeelsTemp = $row['FeelsTemp'];
// $MinTemp = $row['MinTemp'];
// $MaxTemp = $row['MaxTemp'];
// $Humidity = $row['Humidity'];
// $Wind = $row['Wind'];
// $innerTemperature = $row['innerTemperature'];
// $innerHumidity = $row['innerHumidity'];
// ?>
$(function () {
    //현재 시간 관련
    var today = new Date();
    var year = today.getFullYear();
    var month = today.getMonth() + 1;
    var date = today.getDate();
    var day = today.getDay();
    switch (day) {
        case 0:
            day = "일";
            break;
        case 1:
            day = "월";
            break;
        case 2:
            day = "화";
            break;
        case 3:
            day = "수";
            break;
        case 4:
            day = "목";
            break;
        case 5:
            day = "금";
            break;
        case 6:
            day = "토";
            break;
    }
    $("#nowTime").append("<h2>" + year + "년" + month + "월" + date + "일 " + day + "요일</h2>");
    var imgArea = document.getElementById("weatherImg");
    var todayWeather = "sunny"
    changeW(todayWeather);
    //날씨 관련 - 클릭시 차례로 바뀌게
    $("#refresh").on("click", function () {
        changeW(todayWeather);
    });
    function changeW(todayWeather){
        switch (todayWeather) {
            case "sunny":
                imgArea.src = "images/sunny_icon.png";
                break;
            case "cloudy":
                imgArea.src = "images/cloudy_icon.png";
                break;
            case "rainy":
                imgArea.src = "images/rainny_icon.png";
                break;
            case "snow":
                imgArea.src = "images/snow_icon.png";
                break;
        }
    }
    //로드시 자동으로 외부온도 값을 태그에 추가하는 부분
    //var temperature ='<?=$Temperature?>'; // 외부온도 값을 저장할 변수 - 임시값으로 지정했음
    var temperature = 10;
    var idTemperature = document.getElementById("temperature");
    idTemperature.innerHTML+="<h5>외부 온도</h5><br>"
    idTemperature.innerText += 'screen: ' + temperature + ' 도';

    //로드시 자동으로 체감온도 값을 태그에 추가하는 부분
    //var feelsTemp = '<?=$FeelsTemp?>'; // 체감온도 값을 저장할 변수 - 임시값으로 지정했음
    var feelsTemp = 10;
    var idFeelsTemp = document.getElementById("feelsTemp");
    idFeelsTemp.innerHTML+="<h5>체감 온도</h5><br>"
    idFeelsTemp.innerText += 'screen : ' + feelsTemp + ' 도';

    //로드시 자동으로 최저온도 값을 태그에 추가하는 부분
    //var minTemp = '<?=$MinTemp?>'; // 최저온도 값을 저장할 변수 - 임시값으로 지정했음
    var minTemp = 10;
    var idMinTemp = document.getElementById("minTemp");
    idMinTemp.innerHTML+="<h5>최저 온도</h5><br>"
    idMinTemp.innerText += 'screen : ' + minTemp + ' 도';

    //로드시 자동으로 최고온도 값을 태그에 추가하는 부분
    //var maxTemp = '<?=$MaxTemp?>'; // 최고온도 값을 저장할 변수 - 임시값으로 지정했음
    var maxTemp = 10;
    var idMaxTemp = document.getElementById("maxTemp");
    idMaxTemp.innerHTML+="<h5>최고 온도</h5><br>"
    idMaxTemp.innerText += 'screen : ' + maxTemp + ' 도';

    //로드시 자동으로 외부습도 값을 태그에 추가하는 부분
    //var humidity = '<?=$Humidity?>';// 외부습도 값을 저장할 변수 - 임시값으로 지정했음
    var humidity = 10;
    var idHumidity = document.getElementById("humidity");
    idHumidity.innerHTML+="<h5>외부 습도</h5><br>"
    idHumidity.innerText += 'screen : ' + humidity + ' %';

    //로드시 자동으로 풍속 값을 태그에 추가하는 부분
    //var wind = '<?=$Wind?>'; // 풍속 값을 저장할 변수 - 임시값으로 지정했음
    var wind = 10;
    var idWind = document.getElementById("wind");
    idWind.innerHTML+="<h5>풍속</h5><br>"
    idWind.innerText += 'screen : ' + wind + ' m/s';

    //로드시 자동으로 내부온도 값을 태그에 추가하는 부분
    //var innerTemperature = '<?=$innerTemperature?>'; // 내부온도 값을 저장할 변수 - 임시값으로 지정했음
    var innerTemperature = 10;
    var idInnerTemperature = document.getElementById("innerTemperature");
    idInnerTemperature.innerHTML+="<h5>내부 온도</h5><br>"
    idInnerTemperature.innerText += 'screen : ' + innerTemperature + ' 도';

    //로드시 자동으로 내부습도 값을 태그에 추가하는 부분
    //var innerHumidity = '<?=$innerHumidity?>';// 외부온도 값을 저장할 변수 - 임시값으로 지정했음
    var innerHumidity = 10;
    var idInnerHumidity = document.getElementById("innerHumidity");
    idInnerHumidity.innerHTML+="<h5>내부 습도</h5><br>"
    idInnerHumidity.innerText += 'screen : ' + innerHumidity + ' %';
})