<?php

echo "[SERVER]\n";
$server = [];
foreach (["HTTP_USER_AGENT", "REQUEST_METHOD", "REQUEST_URI"] as $key)
{
	$server[$key] = $_SERVER[$key];
}
var_dump($server);
echo "\n";

echo "[GET]\n";
if(!empty($_GET))
{
	var_dump($_GET);
}
else
{
	echo "null\n";
}
echo "\n";

echo "[POST]\n";
// var_dump($_POST);
$json = file_get_contents('php://input');
if(!empty($json))
{
	var_dump(json_decode($json, true));
}
else
{
	echo "null\n";
}
echo "\n";
