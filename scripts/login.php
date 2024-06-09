<?php
session_start();
$conn = new mysqli('localhost', 'root', '', 'myproject');

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    $stmt = $conn->prepare("SELECT password FROM users WHERE username = ?");
    $stmt->bind_param('s', $username);
    $stmt->execute();
    $stmt->store_result();

    if ($stmt->num_rows > 0) {
        $stmt->bind_result($hash);
        $stmt->fetch();

        if (password_verify($password, $hash)) {
            $_SESSION['username'] = $username;
            header("Location: ../index.html");
        } else {
            echo "Invalid username or password.";
        }
    } else {
        echo "Invalid username or password.";
    }

    $stmt->close();
}

$conn->close();
?>