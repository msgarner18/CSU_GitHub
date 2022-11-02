import java.lang.Exception;
import java.io.*;
import java.util.*;

/********************************************************************************************
 * This is the driver program which will be used to create an instance of the
 * Circular buffer, and create and wait for producer and consumer threads.
 ********************************************************************************************/
class Invoker {
    public static void main(String[] args) {
        validateArgs(args);

        // define randomWithSeed based on seed
        int seed = Integer.parseInt(args[0]);
        Random randomWithSeed = new Random(seed);

        // randomly define needed values based on randomWithSeed
        int bufferSize = randomWithSeed.nextInt(6) + 5;
        int consNum = randomWithSeed.nextInt(4) + 2;
        int prodNum = randomWithSeed.nextInt(4) + 2;
        Bdbuffer buffer = new Bdbuffer(bufferSize);

        // fill tuples with characters in file given by args[1]
        List<Tuple> tuples = fillTuples(args[1]);

        // print randomly defined values to terminal
        printInitVals(bufferSize, tuples.size(), prodNum, consNum);

        // start producers and consumers and print results when done
        produceAndConsume(buffer, prodNum, consNum, tuples);
    }

    // Ensures that arguments are valid
    public static void validateArgs(String[] args) {
        if (args.length != 2) {
            System.out.println("Must supply exactly 2 arguments!");
            System.exit(1);
        }
        try {
            Integer.parseInt(args[0]);
        } catch (java.lang.NumberFormatException e) {
            System.out.println("Argument 1 must be an integer!");
            System.exit(1);
        }
    }

    // returns a tuple with index=index and c=next byte in file
    // on end of file returns tuple index=-1 and c='!''
    public static Tuple readByte(InputStream input, int index) {
        Tuple myTuple = new Tuple(-1, '!');
        try {
            int myByte = input.read();
            if (myByte != -1)
                myTuple = new Tuple(index, (char) (myByte));
        } catch (IOException e) {
            //
        }
        return myTuple;
    }

    // opens file fileName and fills a list of tuples with every byte in the file
    // returns the full tuple
    public static List<Tuple> fillTuples(String fileName) {
        List<Tuple> tuples = new ArrayList<Tuple>();

        try {
            InputStream input = new FileInputStream(fileName);

            for (int i = 0;; i++) {
                Tuple tuple = readByte(input, i);
                if (tuple.getIndex() == -1)
                    break;
                tuples.add(tuple);
            }
        } catch (FileNotFoundException e) {
            System.out.println("Could not open file \"" + fileName + "\"!");
            System.exit(1);
        }

        return tuples;
    }

    // prints arguments provided in desired format
    public static void printInitVals(int bufferSize, int itemNum, int prodNum, int consNum) {
        System.out.println("[Invoker] Bdbuffer Size: " + bufferSize);
        System.out.println("[Invoker] Total Items: " + itemNum);
        System.out.println("[Invoker] No. of producers: " + prodNum + " No. of consumers: " + consNum);
    }

    // creates and returns an array of producers based on:
    // buffer: what buffer the producers should use
    // prodNum: Number of producers you wish to create
    // totTuples: all tuples in your tuple list
    public static Producer[] fillProducers(Bdbuffer buffer, int prodNum, List<Tuple> totTuples) {
        Producer[] producers = new Producer[prodNum];

        int prevTupleNum = 0;
        for (int i = 0; i < prodNum; i++) {
            int tupleNum = totTuples.size() / prodNum;
            if (i == 0)
                tupleNum += totTuples.size() % prodNum;
            List<Tuple> tuples = totTuples.subList(prevTupleNum, prevTupleNum + tupleNum);

            producers[i] = new Producer(buffer, tuples, i + 1);
            prevTupleNum += tupleNum;
        }

        return producers;
    }

    // creates and returns an array of consumers based on:
    // buffer: what buffer the consumers should use
    // consNum: Number of consumers you wish to create
    // totTupleNum: total number of tuples you want consumed
    public static Consumer[] fillConsumers(Bdbuffer buffer, int consNum, int totTupleNum) {
        Consumer[] consumers = new Consumer[consNum];

        for (int i = 0; i < consNum; i++) {
            int tupleNum = totTupleNum / consNum;
            if (i == 0)
                tupleNum += totTupleNum % consNum;
            consumers[i] = new Consumer(buffer, tupleNum, i + 1);
        }

        return consumers;
    }

    // start all threads in array arr. (producer or consumer)
    public static void start(Thread[] arr) {
        for (int i = 0; i < arr.length; i++)
            arr[i].start();
    }

    // join all threads in array arr. (producer or consumer)
    public static void join(Thread[] arr) {
        for (int i = 0; i < arr.length; i++) {
            try {
                arr[i].join();
            } catch (InterruptedException e) {
                System.out.println(e);
                System.exit(1);
            }
        }
    }

    // takes a tupleList and returns it sorted
    public static List<Tuple> sortTupleList(List<Tuple> tupleList) {
        List<Tuple> sortedList = new ArrayList<Tuple>();
        for (int j = 0; j < tupleList.size(); j++) {
            Tuple min = tupleList.get(j);
            for (int i = j; i < tupleList.size(); i++) {
                if (tupleList.get(i).getIndex() < min.getIndex()) {
                    min = tupleList.get(i);
                    Collections.swap(tupleList, i, j);
                }
            }
            sortedList.add(min);
        }
        return sortedList;
    }

    // returns a tuple list that is the combination of all tuple lists in consumers
    public static List<Tuple> combineConsumerTuples(Consumer[] consumers) {
        List<Tuple> combinedTuples = new ArrayList<Tuple>();

        for (int i = 0; i < consumers.length; i++) {
            combinedTuples.addAll(consumers[i].getConsumedTuples());
        }

        return combinedTuples;
    }

    // returns a tuple list that is the combination of all tuples in producers
    public static List<Tuple> combineProducerTuples(Producer[] producers) {
        List<Tuple> combinedTuples = new ArrayList<Tuple>();

        for (int i = 0; i < producers.length; i++) {
            combinedTuples.addAll(producers[i].getProducedTuples());
        }

        return combinedTuples;
    }

    // converts a tuple list into a string where [(0, a), (0 , b)] = "ab"
    public static String TupleListToString(List<Tuple> tupleList) {
        String phrase = "";
        for (int i = 0; i < tupleList.size(); i++) {
            phrase += tupleList.get(i).getC();
        }
        return phrase;
    }

    // using the arguments given, produces and consumes values and
    // prints produced and consumed string if successful
    // buffer: the buffer that the producers and consumers will share
    // prodNum: number of producers
    // consNum: number of consumers
    // tuples: a list of tuples you want consumed
    public static void produceAndConsume(Bdbuffer buffer, int prodNum, int consNum, List<Tuple> tuples) {
        Producer[] producers = fillProducers(buffer, prodNum, tuples);
        Consumer[] consumers = fillConsumers(buffer, consNum, tuples.size());

        start(producers);
        start(consumers);

        join(producers);
        join(consumers);

        String prodString = TupleListToString(sortTupleList(combineProducerTuples(producers)));
        String consString = TupleListToString(sortTupleList(combineConsumerTuples(consumers)));

        if (prodString.equals(consString)) {
            System.out.println("Producer's output:");
            System.out.println(prodString);
            System.out.println("Consumer's output:");
            System.out.println(consString);
        }
    }

}