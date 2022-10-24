#!/bin/bash
# Get move the output folders from hadoop to local directories

rm -rf output/*
mkdir output
mkdir output/A1
mkdir output/A2
mkdir output/B1
mkdir output/B2

$HADOOP_HOME/bin/hadoop fs -get /PA1/outputA1/* output/A1
$HADOOP_HOME/bin/hadoop fs -get /PA1/outputA2/* output/A2
$HADOOP_HOME/bin/hadoop fs -get /PA1/outputB1/* output/B1
$HADOOP_HOME/bin/hadoop fs -get /PA1/outputB2/* output/B2

#END