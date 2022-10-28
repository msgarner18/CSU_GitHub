
$HADOOP_HOME/bin/hadoop com.sun.tools.javac.Main tf/Test/TestMain.java tf/MapReduce/B/job1/SummaryCalculator.java 
if [[ $? -eq 0 ]]; then
    # create jar
    rm test.jar
    jar cf test.jar tf/Test/TestMain*.class tf/MapReduce/B/job1/SummaryCalculator*.class 

    # run
    $HADOOP_HOME/bin/hadoop jar test.jar tf/Test/TestMain -D mapreduce.framework.name=yarn
fi