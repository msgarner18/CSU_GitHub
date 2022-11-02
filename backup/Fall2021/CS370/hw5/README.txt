# README

This package includes the following files.

|-- Invoker.java [This is the driver program which will be used to create an instance of the Circular buffer, and create and wait for producer and consumer threads.] (Skeleton Code provided)
|-- Producer.java [Each instance of a producer generates a single character a-z randomly and inserts it into the buffer, and reports the location and the time the number was inserted into the buffer. Each letter added is appended to producedStr.] (Skeleton Code provided)
|-- Consumer.java [Each instance of a consumer reads a letter from the buffer, reports the location and the time the letter was read from the buffer, and appends each letter to consumerStr.]
|-- Bdbuffer.java [Creates a circular buffer whose size is passed as an argument to it.]
|-- Tuple.java [Data Structure (int, char) where you can access either element]
|-- Makefile [For compiling, and cleaning]
|-- README.txt [This file]

Questions:

1. The problem of producer consumer is solved using Semaphores. - 1 point
   a. Mutex Locks
   b. Semaphores

2. What two functions defined in Java are used for synchronization between producer and consumers in your program? wait() and notifyAll(). - 2 points

3. In which function do you override the body to define the new body of a thread in java? run(). - 1 point

4. Which function is used to wait for a thread to finish and come back to calling program i.e. for a thread to die? join(). - 1 point

NOTE:

Lab systems by default use Java 11 which supports nanosecond timestamp. If after logging in and running 'java -version', it doesn't output version 11, use the following two commands:

    $ export PATH=/usr/lib/jvm/jre-11-openjdk/bin/:$PATH

    $ export LD_LIBRARY_PATH=/usr/lib/jvm/jre-11-openjdk/lib/:$LD_LIBRARY_PATH
