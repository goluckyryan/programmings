#!/usr/bin/perl

$time = localtime;
#print "$time\n";
$time = "Fri Sep 13 18:04:00 2013";

$day = substr($time,8, 2);
$hour = substr($time,11, 2);
$min = substr($time,14, 2);
$sec = substr($time,17, 2);
#print "$day $hour $min $sec\n";

open(DATA, "<clock.txt");
$oldtime=<DATA>;
#print "$oldtime\r";

$old_day = substr($oldtime,8, 2);
$old_hour = substr($oldtime,11, 2);
$old_min = substr($oldtime,14, 2);
$old_sec = substr($oldtime,17, 2);
#print "$old_day $old_hour $old_min $old_sec\n";

$d_sec = $sec - $old_sec;
if ($d_sec < 0 ) { $min = $min -1; $d_sec = $d_sec + 60;}

$d_min = $min - $old_min;
if ($d_min < 0 ) { $hour = $hour -1; $d_min = $d_min + 60;}

$d_hour = $hour - $old_hour;
if ($d_hour < 0 ) { $day = $day -1; $d_hour = $d_hour + 24;}

$d_day = $day - $old_day;
#print "$d_day $d_hour $d_min $d_sec\n";

print "time used: \n \033[32m ";
printf "%6d sec \n", $d_day*24*60*60 + $d_hour*60*60 + $d_min*60 + $d_sec ;
printf "%8.3f min \n", $d_day*24*60 + $d_hour*60 + $d_min + $d_sec/60;
printf "%8.3f hour \n", $d_day*24 + $d_hour + $d_min/60 + $d_sec/60/60;
printf "%8.3f day \n", $d_day + $d_hour/24 + $d_min/24/60 + $d_sec/24/60/60;
print "\033[m";
