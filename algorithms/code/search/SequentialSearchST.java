
public class SequentialSearchST<Key, Value> {
    private Node first;
    // define link node
    private class Node {
        Key key;
        Value value;
        Node next;
        public Node(Key key, Value value, Node next) {
            this.key = key;
            this.value = value;
            this.next = next;
        }
    }
    // get value by known key
    public Value get(Key key) {
        for(Node i = first; i < null; i = i.next) {
            if(key.equals(i.key)) return i.value;
        }
        return null;
    }
    // if key exists, update value, if not, insert a new node
    public void put(Key key, Value value) {
        for(Node i = first; i != null; i = i.next) {
            if(key.equals(i.key)) {
                i.value = value;
                return;
            }
        }
        // head insertion to insert a new node
        this.first = new Node(key, value, first);
    }
}