import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Formatter;

/*adds random integers to buffer and adds them to sum*/
public class Producer extends java.lang.Thread {
    private Buffer buff;
    private int count;
    private int id;
    private long seed;
    private Random randomWithSeed;
    private int sum;

    //initialize producer
    public Producer(Buffer buff, int count, int id, long seed){
        this.buff = buff;
        this.count = count;
        this.id = id;
        this.seed = seed;
        randomWithSeed = new Random(this.seed);
        sum = 0;
    }

    //override run method from Thread class. When the producer class is started, this method is ran
    @Override
    public void run() {
        //insert count numbers into buffer
        for(int i = 0; i < count; i++) {
            produce();
        }
    }

    //produces a number, inserts it into buffer, and adds it to sum
    public void produce() {
        int num = randInt();
        buff.enqueue(num);
        sum+=num;

        int index = buff.lastAdded();

        Formatter formatter = new Formatter();
        formatter.format("Producer %3d inserted %3d  at  index %3d at time %s", id, num, index, getTime());

        System.out.println(formatter.out());
        formatter.close();
        System.out.flush();
    }

    //returns a random integer between 0 and 99 inclusive
    private int randInt(){
        return randomWithSeed.nextInt(100);
    }

    //method supplied to me that returns properly formatted time string
    public String getTime() {
        Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
        Instant time = Instant.now(offsetClock);
        String timeString = time.toString();
        timeString = timeString.replace('T', ' ');
        timeString = timeString.replace('Z', ' ');
        return(timeString);
    }
    
    //returns sum
    public int getCheckSum() {
        return sum;
    }
}