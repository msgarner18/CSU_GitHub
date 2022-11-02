/*This Class runs all other classes and holds the main program */
public class Coordinator{
    public static void main(String[] args)
    {
        //Read the arguments(buffer size, elements, ammount of consumers, ammount of producers, seed)
        int bufferSize = Integer.parseInt(args[0]);
        int elements = Integer.parseInt(args[1]);
        int consNum = Integer.parseInt(args[2]);
        int prodNum = Integer.parseInt(args[3]);
        int seed = Integer.parseInt(args[4]);

        //instantiate one buffer
        Buffer b = new Buffer(bufferSize);

        //create prodNum producers
        int pCount = elements/prodNum;//division with truncated remainder
        Producer[] producers = new Producer[prodNum];
        for(int i = 0; i < prodNum; i++) {
            //divide evenly among producers
            pCount = elements/prodNum;
            //if there is a remainder, give it to the first producer
            if(i == 0 ){pCount += elements%prodNum;}
            //start producer
            producers[i] = new Producer(b, pCount, i+1, seed);
            producers[i].start();
        }
        
        //create consNum consumers
        int cCount = elements/consNum;//division with truncated remainder
        Consumer[] consumers = new Consumer[consNum];
        for(int i = 0; i < consNum; i++) {
            //divide evenly among consumers
            cCount = elements/consNum;
            //if there is a remainder, give it to the first consumer
            if(i == 0 ){cCount += elements%consNum;}
            //start consumers
            consumers[i] = new Consumer(b, cCount, i+1);
            consumers[i].start();
        }
        
        //Wait for producers to finish
        for(int i = 0; i < producers.length; i++) {
            try {
                producers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        //Wait for consumers to finish
        for(int i = 0; i < consumers.length; i++) {
            try {
                consumers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        //sum of all producers' sums
        int prodSum = 0;
        for(int i = 0; i < producers.length; i++) {
            prodSum += producers[i].getCheckSum();
        }
        
        //sum of all consumers's sums
        int consSum = 0;
        for(int i = 0; i < consumers.length; i++) {
            consSum += consumers[i].getCheckSum();
        }

        //print sums
        System.out.println();
        System.out.println("Producer(s): finished producing "+elements+" items with checkSum being "+prodSum);
        System.out.println("\033[0;4mConsumer(s): finished producing "+elements+" items with checkSum being "+consSum+"\033[0;0m");
        System.out.flush();
    }
}