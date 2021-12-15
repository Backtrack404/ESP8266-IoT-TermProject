<?php
session_start();
$conn = mysqli_connect("localhost", "ID", "PW", "DB", PORT);
$sql = "SELECT * FROM Weather ORDER BY num DESC LIMIT 1;";
$result = mysqli_query($conn, $sql);
$row = mysqli_fetch_array($result);
$Weather = $row['Weather'];
$Temperature = $row['Temperature'];
$FeelsTemp = $row['FeelsTemp'];
$MinTemp = $row['MinTemp'];
$MaxTemp = $row['MaxTemp'];
$Humidity = $row['Humidity'];
$Wind = $row['Wind'];
$innerTemperature = $row['innerTemperature'];
$innerHumidity = $row['innerHumidity'];
?>

<script>
    var Weather = '<?=$Weather?>';
    var Temperature = '<?=$Temperature?>';
    var FeelsTemp = '<?=$FeelsTemp?>';
    var MinTemp = '<?=$MinTemp?>';
    var MaxTemp = '<?=$MaxTemp?>';
    var Humidity = '<?=$Humidity?>';
    var Wind = '<?=$Wind?>';
    var innerTemperature = '<?=$innerTemperature?>';
    var innerHumidity = '<?=$innerHumidity?>';
    console.log(Weather); 
    console.log(Temperature); 
    console.log(FeelsTemp); 
    console.log(MinTemp); 
    console.log(MaxTemp); 
    console.log(Humidity); 
    console.log(Wind); 
    console.log(innerTemperature); 
    console.log(innerHumidity); 
</script>

<script language='javascript'>
  window.setTimeout('window.location.reload()',600000); //10초마다 리플리쉬 시킨다 1000이 1초가 된다.
</script>

<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="chrome">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IoT 날씨</title>
    <script src="js/jquery-3.6.0.min.js"></script>
    <script src="js/ResponsiveSize.js"></script>
    <!--<script src="js/mainFunc.js"></script>-->
    <link rel="stylesheet" href="css/desigh.css?after">

</head>
<body>
    <script>
        function logout() {
            console.log("hello");
            const data = confirm("로그아웃 하시겠습니까?");
            if (data) {
                location.href = "logoutPrcoess.php";
            }

        }
    </script>
    <div id="nowTime" class="nowTime">
        <!--현재 시간 관련-->
    </div>
    <div id="img">
        <img id="weatherImg" src="">
        	<script>
        	var temperature ='<?=$Temperature?>'; // 외부온도 값을 저장할 변수 - 임시값으로 지정했음
    		document.write('<h1 style="color:white;">' + temperature + ' ℃</h1>');
            </script>
            <path fill-rule="evenodd" d="M8 3a5 5 0 1 1-4.546 2.914.5.5 0 0 0-.908-.417A6 6 0 1 0 8 2v1z" />
            <path d="M8 4.466V.534a.25.25 0 0 0-.41-.192L5.23 2.308a.25.25 0 0 0 0 .384l2.36 1.966A.25.25 0 0 0 8 4.466z" />
        </svg>
    </div>
    <br>
    <div id="firstLine">
        <div id="feelsTemp" class="firstState">
            <!--체감 온도 나오는 부분-->
        </div>
        <div id="humidity" class="firstState">
            <!--습도 나오는 부분-->
        </div>
        <div id="wind" class="firstState">
            <!--풍량(바람세기) 나오는 부분-->
        </div>
    </div>
    <div id="secondLine">
        <div id="temperature" class="secondState">
        	<!--외부 온도 나오는 부분-->
        	외부 온도
        	<br>
        	<p style="color:#32a1ff"><?=$Temperature?>℃</p>
        </div>
        <div id="minTemp" class="secondState">
            <!--최저 기온 나오는 부분-->
            최저 온도
        	<br>
        	<p style="color:#32a1ff"><?=$MinTemp?>℃</p>
        </div>
        <div id="maxTemp" class="secondState">
            <!--최고 기온 나오는 부분-->
            최고 온도
        	<br>
        	<p style="color:#32a1ff"><?=$MaxTemp?>℃</p>
        </div>
    </div>
    <div id="thirdLine">
        <div id="innerTemperature" class="thirdState">
            <!--내부온도 나오는 부분-->
            내부 온도
        	<br>
        	<p style="color:#ff6610"><?=$innerTemperature?>℃</p>
        </div>
        <div id="innerHumidity" class="thirdState">
            <!--내부습도 나오는 부분-->
            내부 습도
        	<br>
        	<p style="color:#ff6610"><?=$innerHumidity?>%</p>
        </div>
    </div>
    
<script>
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
    var todayWeather = '<?=$Weather?>';
    changeW(todayWeather);
    //날씨 관련 - 클릭시 차례로 바뀌게
    function changeW(todayWeather){
        switch (todayWeather) {
            case "Clear":
                imgArea.src = "images/sunny_icon.png";
                break;
            case "Clouds":
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
    var feelsTemp = '<?=$FeelsTemp?>'; // 체감온도 값을 저장할 변수 - 임시값으로 지정했음
    var idFeelsTemp = document.getElementById("feelsTemp");
    idFeelsTemp.innerHTML+="<h5>체감:&nbsp</h5>"
    idFeelsTemp.innerText += feelsTemp + '℃';


    //로드시 자동으로 외부습도 값을 태그에 추가하는 부분
    var humidity = '<?=$Humidity?>';// 외부습도 값을 저장할 변수 - 임시값으로 지정했음
    var idHumidity = document.getElementById("humidity");
    idHumidity.innerHTML+="<h5>습도:&nbsp</h5>"
    idHumidity.innerText += humidity + '%';

    //로드시 자동으로 풍속 값을 태그에 추가하는 부분
    var wind = '<?=$Wind?>'; // 풍속 값을 저장할 변수 - 임시값으로 지정했음
    var idWind = document.getElementById("wind");
    idWind.innerHTML+="<h5>풍속:&nbsp</h5>"
    idWind.innerText += wind + 'm/s';
})
</script>
</body>
</html>
