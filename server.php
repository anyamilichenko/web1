<?php
    $start_time = microtime(true); //запоминаем время до выполнения
    $r = $_GET['r'];
    $x = $_GET['x'];
    $y = $_GET['y'];
    $out = "";
    $maximum = 10;
    $flag = true;
    $response = "";
    date_default_timezone_set('Europe/Moscow');

    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        if (!preg_match('/^-?\d+(\.|,)?\d*$/', $r) ||
            !preg_match('/^-?\d+(\.|,)?\d*$/', $x) ||
            !preg_match('/^-?\d+(\.|,)?\d*$/', $y))
            $flag = false;


        if ($x < -4 || $x > 4)
            $flag = false;
        if ($r < 1 || $r > 5)
            $flag = false;
        if ($y <= -3 || $y >= 5)
            $flag = false;
        if (strlen($y) > $maximum)
            $flag = false;


        if ((($x * $x + $y * $y) <= ($r/2) * ($r/2) && $x <= 0 && $y >= 0) ||
            ($y +  $x <= $r && $x >= 0 && $y >= 0) ||
            ($x >= 0 && $y <= 0 && $x <= $r && $y >= (-1) * $r)) {
            $out = "Входит";
        } else {
            $out = "Не входит";
        }
        $duration = round((microtime(true) - $start_time), 8) . "sec";

        $response .= $flag;
        $response .= ";";
        $response .= $x;
        $response .= ";";
        $response .= $y;
        $response .= ";";
        $response .= $r;
        $response .= ";";
        $response .= $out;
        $response .= ";";
//        $response .= $timezone_offset;


        $response .= date("Y-m-d H:i:s");
        $response .= ";";
        $response .= $duration;
        $response .= "/";
        echo $response;

}