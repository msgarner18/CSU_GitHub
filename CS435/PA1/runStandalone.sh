#!/bin/bash

# ./refreshInput.sh

# Run in local mode
# $HADOOP_HOME/bin/hadoop jar ~/PA1/ngram.jar NgramMapReduce /PA1/input /PA1/output
$HADOOP_HOME/bin/hadoop jar ~/CS435/PA1/ngram.jar NgramMapReduce -D mapreduce.framework.name=local input output

# ./refreshOutput.sh

#END