
import java.util.List;
import java.util.ArrayList;

/********************************************************************************
 * Each instance of a consumer reads a tuple from the buffer, reports the
 * location and the time the tuple was read from the buffer, and appends each
 * tuple to consumedTuples.
 ********************************************************************************/
public class Consumer extends java.lang.Thread {
    Bdbuffer buffer;// used to access letters produced by producers
    List<Tuple> consumedTuples;// contains all letters produced
    int tupleNum;// number of tuples consumer must consume
    int id;// number used to differentiate each consumer instance

    public Consumer(Bdbuffer _buffer, int _tupleNum, int _id) {
        buffer = _buffer;
        consumedTuples = new ArrayList<Tuple>();
        tupleNum = _tupleNum;
        id = _id;
    }

    public List<Tuple> getConsumedTuples() {
        return consumedTuples;
    }

    public String toString() {
        return id + ": " + "tupleNum: " + tupleNum;
    }

    @Override
    public void run() {
        // consume tupleNum tuples
        for (int i = 0; i < tupleNum; i++) {
            // attempt to consume a tuple
            Tuple tuple = buffer.dequeue(id);
            // if it worked, add tuple to consumedTuples
            if (tuple.getIndex() != -1)
                consumedTuples.add(tuple);
            // if it didn't work, try again
            else
                i--;
        }
    }
}