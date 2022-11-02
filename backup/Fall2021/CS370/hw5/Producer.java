
import java.util.List;
import java.util.ArrayList;

/*********************************************************************************
 * Each instance of a producer inserts a list of tuples into the buffer, and
 * reports the location and the time the tuple was inserted into the buffer.
 * Each tuple added is appended to producedTuples.
 ********************************************************************************/
public class Producer extends java.lang.Thread {
    // Necessary variables and object declaration
    Bdbuffer buffer;// used to pass produced values to consumers
    List<Tuple> tuples;// list of tuples to insert into buffer
    List<Tuple> producedTuples;// contains all tuples inserted
    int id;// number used to differentiate each producer instance

    public Producer(Bdbuffer _buffer, List<Tuple> _tuples, int _id) {
        // Assign values to the variables
        buffer = _buffer;
        tuples = _tuples;
        producedTuples = new ArrayList<Tuple>();
        id = _id;
    }

    public List<Tuple> getProducedTuples() {
        return producedTuples;
    }

    public String toString() {
        return id + ": " + tuples;
    }

    @Override
    public void run() {
        // insert all tuples
        for (int i = 0; i < tuples.size(); i++) {
            Tuple tuple = tuples.get(i);

            // if enqueue is successful, add tuple to producedTuples
            if (buffer.enqueue(tuple, id))
                producedTuples.add(tuple);
            // if unsuccessful, restart loop to try again
            else
                i--;
        }
    }
}
