#!/usr/bin/perl



open(DATE, "ls|");
$newDate = <DATE>;
close(DATE);
print $newDate;


