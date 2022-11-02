import java.time.Clock;
import java.time.Duration;
import java.time.Instant;
import java.util.NoSuchElementException;

/***********************************************************************
 * Creates a circular buffer whose size is passed as an argument to it.
 **********************************************************************/
public class Bdbuffer {
    private int front;// keeps track of index where letters are removed
    private int rear;// keeps track of index where letters are added
    private Tuple[] buffer;

    public Bdbuffer(int size) {
        front = rear = -1;
        buffer = new Tuple[size];
    }

    /**************************************
     * Synchronized Getters and Setters
     **************************************/

    // ensures that only one process may alter front at a time
    private synchronized void setFront(int newFront) {
        front = newFront;
    }

    private synchronized int getFront() {
        return front;
    }

    // ensures that only one process may alter rear at a time
    private synchronized void setRear(int newRear) {
        rear = newRear;
    }

    private synchronized int getRear() {
        return rear;
    }

    // ensures that only one process may alter buffer at a time
    private synchronized void setBuffer(int index, Tuple t) {
        buffer[index] = t;
    }

    private synchronized Tuple[] getBuffer() {
        return buffer;
    }

    // returns true is buffer is empty
    public synchronized boolean isEmpty() {
        return getFront() == -1;
    }

    // returns true if buffer is full
    public synchronized boolean isFull() {
        return (getRear() + 1) % getBuffer().length == getFront();
    }

    // tries wait and catches exception if it exists
    private synchronized void checkedWait() {
        try {
            wait();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }

    // if buffer is full, waits until buffer is not full and informas producer that
    // enqueue was unsuccessful
    // otherwise, adds letter to buffer, prints out information about the producer
    // that did it, and returns true.
    public synchronized boolean enqueue(Tuple t, int id) {
        if (isFull()) {
            checkedWait();
            return false;
        }
        setRear((getRear() + 1) % getBuffer().length);// increment rear
        setBuffer(rear, t);// buffer[rear] = t
        if (isEmpty())
            setFront(getRear());
        System.out.printf("\033[0;4mProducer %3d inserted %c at index %3d at time\033[0;0m %s\n", id, t.getC(),
                getRear(), getTime());
        System.out.flush();
        notifyAll();// informs other processes that buffer is not empty
        return true;
    }

    // returns (-1, '!'' if buffer is empty.
    // Otherwise, returns the next tuple ready to be dequeued
    public synchronized Tuple peek() {
        if (isEmpty()) {
            checkedWait();
            return new Tuple(-1, '!');
        } else
            return getBuffer()[getFront()];
    }

    // if buffer is empty, waits until buffer is not empty and returns (-1, '!') to
    // signify
    // that dequeue was unsuccessful
    // Otherwise, removes 1 tuple from buffer and prints information about the
    // consumer that did it.
    public synchronized Tuple dequeue(int id) {
        Tuple returnVal = peek();
        if (returnVal.getIndex() != -1) {
            int lastIndex = getFront();
            if (getFront() == getRear()) {
                setFront(-1);
            } else
                setFront((getFront() + 1) % getBuffer().length);

            System.out.printf("Consumer %3d consumed %c at index %3d at time %s\n", id, returnVal.getC(), lastIndex,
                    getTime());
            System.out.flush();
            notifyAll();
            return returnVal;
        }
        return new Tuple(-1, '!');
    }

    // method given to me to print time
    public String getTime() {
        Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
        Instant time = Instant.now(offsetClock);
        String timeString = time.toString();
        timeString = timeString.replace('T', ' ');
        timeString = timeString.replace('Z', ' ');
        return (timeString);
    }
}
