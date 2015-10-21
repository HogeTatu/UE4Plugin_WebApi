<?php

echo "[SERVER]\n";
$server = [];
foreach (["HTTP_USER_AGENT", "REQUEST_METHOD", "REQUEST_URI"] as $key)
{
	$server[$key] = $_SERVER[$key];
}
var_dump($server);
echo "\n";

echo "[POST]\n";
$json = file_get_contents('php://input');
if(!empty($json))
{
	var_dump($json);
}
else
{
	echo "null\n";
}
echo "\n";
