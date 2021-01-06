<?php
// Initialize the session
session_start();
 
// Check if the user is logged in, if not then redirect him to login page
if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: login.php");
    exit;
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Добро пожаловать</title>
    <link rel="stylesheet" href="styles.css">
    <!-- <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css"> -->
</head>
<body>
    <div class="top_block">
        
    </div>
    <div class="text-links">
        <p><a href="/index.html" title="Назад на основную страницу">Назад</a></p>
    </div>
    <hr size="4">
    <div class="head">
        <p>Здравствуйте, <b><?php echo htmlspecialchars($_SESSION["username"]); ?></b>. Добро пожаловать в личный кабинет.</p>
    </div>
    <hr size="4">
    <div class="text-links">
        <a href="reset-password.php" class="btn btn-warning">Сменить пароль</a>
        <a href="logout.php" class="btn btn-danger">Выход из аккаунта</a>
    </div>
</body>
</html>

<!-- <!DOCTYPE html>
<html lang="en">
<head>
        <h4><a href="/index.html" >Назад на главную</a></h4>
    <meta charset="UTF-8">
    <title>Добро пожаловать</title>
    <link rel="stylesheet" href="styles.css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.css">
    <style type="text/css">
        body{ font: 14px sans-serif; text-align: center; }
    </style>
</head>
<body>
    <div class="page-header">
        <h1>Здравствуйте, <b><?php echo htmlspecialchars($_SESSION["username"]); ?></b>. Добро пожаловать в личный кабинет.</h1>
    </div>
    <p>
        <a href="reset-password.php" class="btn btn-warning">Сменить пароль</a>
        <a href="logout.php" class="btn btn-danger">Выход из аккаунта</a>
    </p>
</body>
</html> -->
