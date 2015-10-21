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
if(!empty($_POST))
{
	var_dump($_POST);
}
else
{
	echo "null\n";
}
echo "\n";
