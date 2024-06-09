<?php
session_start();

function isAuthenticated() {
    return isset($_SESSION['username']);
}

if (!isAuthenticated()) {
    header("Location: login.html");
    exit();
}
?>
