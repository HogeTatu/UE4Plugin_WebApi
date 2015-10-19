<?php

$arr = [
	"int" => 1,
	"float" => 5.5,
	"str" => "test",
	"bool" => true,
	"array" => [1, 2, 3, 4],
	"object" => [
		"foo" => 2,
		"bar" => 4,
	],
];

echo json_encode($arr);
