<?php
$conn = mysqli_connect("localhost", "ID", "PW", "DB", PORT);
$hashedPassword = password_hash($_POST['password'], PASSWORD_DEFAULT);
//echo $hashedPassword;
$sql = "
    INSERT INTO user
    (id, email, password, created)
    VALUES('{$_POST['id']}','{$_POST['email']}', '{$hashedPassword}', NOW()
    )";

$result = mysqli_query($conn, $sql);

$sql = "CREATE TABLE {$_POST['id']} (
	inTemperature varchar(20) not null,
	inHumidity varchar(20) not null,
	outTemperature varchar(20) not null,
	outHumidity varchar(20) not null,
	dust varchar(20) not null,
	date DATETIME
)";

$result = mysqli_query($conn, $sql);

if ($result === false) {
    echo "저장에 문제가 생겼습니다. 관리자에게 문의해주세요.";
    echo mysqli_error($conn);
} else {
?>
    <script>
        alert("회원가입이 완료되었습니다");
        location.href = "index.php";
    </script>
<?php
}
?>