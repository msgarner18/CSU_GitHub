#!/bin/bash

# Run anytime you want to refresh Hadoop input files with local input files

$HADOOP_HOME/bin/hadoop fs -mkdir /PA2
$HADOOP_HOME/bin/hadoop fs -mkdir /PA2/IOFolders
for inputFile in input TF_IDF
do
    $HADOOP_HOME/bin/hadoop fs -mkdir /PA2/IOFolders/$inputFile
    $HADOOP_HOME/bin/hadoop fs -rm -r /PA2/IOFolders/$inputFile/*
    $HADOOP_HOME/bin/hadoop fs -put IOFolders/$inputFile/* /PA2/IOFolders/$inputFile
done

#END