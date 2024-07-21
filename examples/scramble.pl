#!/usr/bin/perl -w
use strict;

my @lines = <>;

fisher_yates_shuffle(\@lines);

print @lines;

sub fisher_yates_shuffle {
  my $array = shift;
  my $i;
  for ($i = @$array; --$i; ) {
    my $j = int rand ($i+1);
    next if $i == $j;
    @$array[$i,$j] = @$array[$j,$i];
  }
}
