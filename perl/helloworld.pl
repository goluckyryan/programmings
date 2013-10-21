#!/usr/bin/perl

print "hi Name\n";

$a=2000;
$b="3";
$x="ha ";

print "\045 \x7F \n";

print $a+$b . "\n";

print $x x $b ."\n";

print "$a+$b\n";

print $a.$b.$x."\n";

for($counter = 1; $counter <= 10; $counter++){
    print "for loop #$counter\n";
}

@array = ("eunice", " ", "like", "apple", 3, 4);

print $array[0].$array[1].$array[2]."\n";

print "@array\n";

@int =(1,3,5,2);

push(@int,10); #add 10 to @int
print "@int\n";

$last = pop(@int); #remove 10 from @int
print "@int\n$last\n";

unshift(@int,0); #add 0 to @int
print "@int\n";


$start = shift(@int); # add 0 to @int
print "@int\n";

sub max{
  if($_[0] > $_[1]){
     $_[0];
  }
  else{
     $_[1];
  }
}

$m = max(10,20);
$m2 = max(50,30);
print "$m\n";
print "$m2\n";

print &max(30,1)."\n";
