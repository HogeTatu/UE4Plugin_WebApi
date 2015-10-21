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
