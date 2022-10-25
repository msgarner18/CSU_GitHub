#!/bin/bash

# Run anytime you want to refresh Hadoop input files with local input files
echo "refreshing input..."
for File in /PA2 /PA2/IOFolders 
do
    $HADOOP_HOME/bin/hadoop fs -mkdir $File
done
for inputFile in input TF_IDF
do
    $HADOOP_HOME/bin/hadoop fs -mkdir /PA2/IOFolders/$inputFile
    $HADOOP_HOME/bin/hadoop fs -rm -r /PA2/IOFolders/$inputFile/*
    $HADOOP_HOME/bin/hadoop fs -put IOFolders/$inputFile/* /PA2/IOFolders/$inputFile
done

#END