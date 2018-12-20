
public class BinarySearchST<Key extends Comparable<Key>, Value> {
    private Key[] keys;
    private Value[] values;
    private int N;

    public BinarySearchST(int capacity) {
        this.keys = (Key[]) new Comparable[capacity];
        this.values = (Value[]) new Object[capacity];
    }

    public int size() { return N; }

    public Value get(Key key) {
        if(isEmpty()) return null;

        int i = rank(key);
        if(i < N && keys[i].compareTo(key) == 0) {
            return values[i];
        }else {
            return null;
        }
    }
    
    public void put(Key key, Value value) {
        int i = rank(key);
        if(i < N; && keys[i].compareTo(key) == 0) {
            values[i] = value;
            return;
        }
        for(int j = N; j > i; j--) {
            keys[j] = keys[j-1];
            values[j] = values[j-1];
        }
        keys[i] = key;
        values[i] = value;
        N++;
    }
    // find index use recursion
    public int rank(Key key, int low, int high) {
        // key not exists
        if(high < low) return low;
        int mid = low + (high - low) / 2;
        int cmp = key.compareTo(keys[mid]);
        if(0 < cmp) return rank(key, mid+1, high);
        if(0 > cmp) return rank(key, low, mid);
        // find key
        if(0 == cmp) return mid;
    }

    //find index use loop
    public int rank(Key key) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int cmp = key.compareTo(keys[mid]);
            if(0 == cmp) return mid;
            if(0 < cmp) low = mid + 1;
            if(0 > cmp) high = mid - 1;
        }
        // not exists
        return low;
    }

    public void delete(Key key) {}
}