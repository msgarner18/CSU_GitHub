#!/bin/bash

./refreshInput.sh

# Remove output on hadoop
$HADOOP_HOME/bin/hadoop fs -rm -r /PA1/outputA1
$HADOOP_HOME/bin/hadoop fs -rm -r /PA1/outputA2
$HADOOP_HOME/bin/hadoop fs -rm -r /PA1/outputB1
$HADOOP_HOME/bin/hadoop fs -rm -r /PA1/outputB2

# Run in yarn mode
$HADOOP_HOME/bin/hadoop jar ngram.jar NgramMapReduce -D mapreduce.framework.name=yarn /PA1/input /PA1/output

./refreshOutput.sh

#END