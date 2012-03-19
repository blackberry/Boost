#!/usr/bin/perl

use Carp qw(confess);
use POSIX qw(strftime floor);
use Cwd;
use File::Basename; 
use File::Copy;
use File::Path;
use strict;
use Data::Dumper;

if (scalar(@ARGV) < 1) {
    die "Results file required.";
}

my $resultsFile = "";
my $noOutput = 0;
if (scalar(@ARGV) >= 2 && $ARGV[0] == '-n') {
    $noOutput = 1;
    $resultsFile = $ARGV[1];
} else {
    $resultsFile = $ARGV[0];
}
print "Processing $resultsFile\n";

my $goodOutFile = "$resultsFile.good";
my $badOutFile = "$resultsFile.bad";

open(resultsFH, "$resultsFile") or die "Couldn't open $resultsFile";
if (!$noOutput) {
    open(goodFH, ">$goodOutFile") or die "Couldn't open $goodOutFile";
    open(badFH, ">$badOutFile") or die "Couldn't open $badOutFile";
}

my $foundFailure = 0;
my $buf = "";
my $goodCtr = 0;
my $badCtr = 0;
while (my $line = <resultsFH>) {
    chomp($line);
    if ($line =~ /^\.\.\.failed.+$/) {
        # We get a compile or link failure if we don't get a syntax error 
        if ($foundFailure) {
            $badCtr++; 
            $foundFailure = 0;
            $buf = "Compilation failed (#$badCtr)\n".$buf;
            if (!$noOutput) {
                print badFH "$buf\n";
            }
        } else {
            # Start buffering the new failure
            $foundFailure = 1;
            $buf = "$line\n";
        }
    } elsif ($foundFailure) {
        $buf .= "$line\n";
        # Check for end of failure to run the program (expected)
        if ($line =~ /^.+Syntax error: word unexpected.+$/) {
            $goodCtr++; 
            $foundFailure = 0;
            $buf = "Compilation OK (#$goodCtr)\n".$buf;
            if (!$noOutput) {
                print goodFH "$buf\n";
            }
            $buf = "";
        }
    }
}
close(resultsFH);
close(goodFH);
close(badFH);
print "$badCtr failed compilation out of ".($badCtr + $goodCtr)." tests.\n";
if (!$noOutput) {
    print "Wrote $goodOutFile and $badOutFile.\n";
}
