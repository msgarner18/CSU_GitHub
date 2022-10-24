#!/bin/bash

$HADOOP_HOME/bin/hadoop com.sun.tools.javac.Main NgramMapReduce.java Book.java WholeFileInputFormat.java WholeFileRecordReader.java VolumeWriteable.java
rm ngram.jar
jar cf ngram.jar *.class

#END