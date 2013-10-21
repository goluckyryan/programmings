#!/usr/bin/perl

#system "date > clock.txt";

open(oldDate,"<","clock.txt");
$oldDate=<oldDate>;
close(oldDate);
print $oldDate;

open(DATE, "date|");
$newDate = <DATE>;
close(DATE);
print $newDate;

$day=substr($oldDate, 7,2);
$hour=substr($oldDate, 11,2);
$min=substr($oldDate, 14,2);
$sec=substr($oldDate, 17,2);

$day2=substr($newDate, 7,2);
$hour2=substr($newDate, 11,2);
$min2=substr($newDate, 14,2);
$sec2=substr($newDate, 17,2);

$diffday  = $day2 - $day;
$diffhour = $hour2- $hour;
$diffmin  = $min2 - $min;
$diffsec  = $sec2 - $sec;

if ($diffsec < 0){
	$diffmin = $diffmin -1;
	$diffsec = 60 + $sec2 - $sec;
}

if ($diffmin < 0){
	$diffhour = $diffhour -1;
	$diffmin = 60 + $diffmin;
}

if ($diffhour< 0){
	$diffday = $diffday -1;
	$diffhour = 24 + $diffhour;
}

print "Time Duration = ".$diffday." day(s), ".$diffhour.":".$diffmin.":".$diffsec."\n";


