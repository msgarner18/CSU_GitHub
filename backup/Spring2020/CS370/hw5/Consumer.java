import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Formatter;

/*removes numbers inside of buffer and adds them to sum */
public class Consumer extends java.lang.Thread {
    private Buffer buff;
    private int count;
    private int id;
    private int sum;

    //initializes Consumer
    public Consumer(Buffer buff, int count, int id){
        this.buff = buff;
        this.count = count;
        this.id = id;
        sum = 0;
    }

    //override run method from Thread class. When the comsumer class is started, this method is ran
    @Override
    public void run(){
        //consumes count numbers from buffer
        for(int i = 0; i < count; i++) {
            consume();
        }
    }

    //consumes a number from buffer and adds it to sum
    public void consume() {
        int index = buff.lastRemoved();
        int num = buff.dequeue();
        sum+= num;

        Formatter formatter = new Formatter();
        formatter.format("\033[0;4mConsumer %3d consumed %3d from index %3d at time\033[0;0m %s", id, num, index, getTime());
        
        System.out.println(formatter.out());
        formatter.close();
        System.out.flush();
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