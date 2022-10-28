#!/bin/bash

# rm -rf *.class

ROOT=tf
for LETTER in A B
do
    $HADOOP_HOME/bin/hadoop com.sun.tools.javac.Main $ROOT/Driver$LETTER.java $ROOT/InputClasses/*.java $ROOT/CustomWritables/*.java $ROOT/MapReduce/$LETTER/*/*.java
    if [[ $? -eq 0 ]]; then
        rm profile$LETTER.jar
        jar cf profile$LETTER.jar $ROOT/Driver$LETTER*.class $ROOT/InputClasses/*.class $ROOT/CustomWritables/*.class $ROOT/MapReduce/$LETTER/*/*.class
        # jar cvf $PROFILE.jar -C $PROFILE .
    fi
done

# $HADOOP_HOME/bin/hadoop com.sun.tools.javac.Main *.java
# rm termfreq.jar
# jar cf termfreq.jar *.class

#END