<?php
require 'auth.php';

$dataFolder = '../Data/';
$files = array_diff(scandir($dataFolder), array('..', '.'));

echo json_encode(array_values($files));
?>