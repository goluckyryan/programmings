#!/usr/bin/perl

@time = system("date");
print "$time\r";

open(DATA, "<clock.txt");
$oldtime=<DATA>;
print "$oldtime\n";


