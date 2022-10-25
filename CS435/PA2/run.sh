#!/bin/bash

# run compiled code on hadoop and send output to local files

# refresh input if i flag is set
I_FLAG=false
A_FLAG=false
B_FLAG=false
while getopts 'iab' OPTION; do
  case "$OPTION" in
    i)
      I_FLAG=true
       ;;
    a)
      A_FLAG=true
      ;;
    b)
      B_FLAG=true
      ;;
    ?)
        echo "script usage: $(basename \$0) [-ib]" >&2
        exit 1
      ;;
  esac
done
shift "$(($OPTIND -1))"

for LETTER in "A" "B"
do
  if [ $I_FLAG = true ]; then 
    ./refreshInput.sh
  fi
  
  IOFOLDER=/PA2/IOFolders
  OUTPUTS=$IOFOLDER/outputs

  # remove output
  echo "removing output..."
  $HADOOP_HOME/bin/hadoop fs -mkdir $OUTPUTS
  $HADOOP_HOME/bin/hadoop fs -rm -r $OUTPUTS/*

  # Run in yarn mode
  if [ "$LETTER" = "A" ]; then
    if [ "$A_FLAG" = true ]; then
      echo "Running ProfileA.jar..."
      $HADOOP_HOME/bin/hadoop jar profileA.jar tf/DriverA -D mapreduce.framework.name=yarn $IOFOLDER/input $OUTPUTS/output
    fi
  else
    if [ "$B_FLAG" = true ]; then
      echo "Running ProfileB.jar..."
      $HADOOP_HOME/bin/hadoop jar profileB.jar tf/DriverB -D mapreduce.framework.name=yarn $IOFOLDER/TF_IDF $IOFOLDER/input $OUTPUTS/output
    fi
  fi

  # update output
  echo "updating output..."
  LOCALROOT=~/CSU_GitHub/CS435

  mkdir $LOCALROOT$IOFOLDER
  mkdir $LOCALROOT$OUTPUTS
  for F in freq TF TF_IDF output
  do
    mkdir $LOCALROOT$OUTPUTS/$F
    rm -rf $LOCALROOT$OUTPUTS/$F/*
    $HADOOP_HOME/bin/hadoop fs -get $OUTPUTS/$F/* $LOCALROOT$OUTPUTS/$F
  done
  if [ "$B_FLAG" != true ]; then
    cp -r $LOCALROOT$OUTPUTS/TF_IDF $LOCALROOT$IOFOLDER
  fi
  if [ "$B_FLAG" != "$A_FLAG" ]; then
    break
  fi

done



#END