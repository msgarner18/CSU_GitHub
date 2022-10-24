#!/bin/bash

$HADOOP_HOME/bin/hadoop fs -rm -r /PA1/input/*
$HADOOP_HOME/bin/hadoop fs -mkdir /PA1
$HADOOP_HOME/bin/hadoop fs -mkdir /PA1/input
$HADOOP_HOME/bin/hadoop fs -put input/* /PA1/input

#END