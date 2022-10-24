#!/bin/bash

$HADOOP_HOME/bin/hadoop fs -mkdir /PA2/outputSave
$HADOOP_HOME/bin/hadoop fs -rm -r /PA2/outputSave/*

$HADOOP_HOME/bin/hadoop fs -put ~/CS435/PA2/IOFolders/outputs/* /PA2/outputSave

#END