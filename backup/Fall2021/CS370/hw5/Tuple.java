/*****************************************************************
 * Data Structure (int, char) where you can access either element
 *****************************************************************/
public class Tuple {
    int index;
    char c;

    public Tuple(int _index, char _c) {
        index = _index;
        c = _c;
    }

    public int getIndex() {
        return index;
    }

    public char getC() {
        return c;
    }

    public String toString() {
        return "(" + index + ", " + c + ")";
    }
}