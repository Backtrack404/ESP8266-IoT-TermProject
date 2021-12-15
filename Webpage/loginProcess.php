<?php
$conn = mysqli_connect("localhost", "ID", "PW", "DB", PORT);
$email = $_POST['id'];
$password = $_POST['password'];

// DB 정보 가져오기 
$sql = "SELECT * FROM user WHERE id ='{$email}'";
$result = mysqli_query($conn, $sql);

$row = mysqli_fetch_array($result);
$hashedPassword = $row['password'];
$row['id'];

foreach($row as $key => $r){
    echo "{$key} : {$r} <br>";
}

$passwordResult = password_verify($password, $hashedPassword);
if ($passwordResult === true) {
    // 로그인 성공
    session_start();
    $_SESSION['userId'] = $row['id'];
    print_r($_SESSION);
    echo $_SESSION['userId'];
    
?>
    <script>
        alert("로그인에 성공하였습니다.")
        location.href = "index.php";
    </script>
<?php
} else {
    // 로그인 실패 
?>
    <script>
        alert("로그인에 실패하였습니다");
        location.href = "login.php";
    </script>
<?php
}
?>