import java.util.Iterator;

/**
 * java中迭代的实现
 * @param <Item>
 */
public class BagIterator<Item> implements Iterable<Item>{
    private Node first;
    private class Node {
        Item item;
        Node next;
    }
    public void add(Item item){
        Node oldFirst = first;
        first = new Node();
        first.item = item;
        first.next = oldFirst;
    }
    public Iterator<Item> iterator(){ return new ListIterator(); }
    private class ListIterator implements Iterator<Item> {
        private Node current = first;
        public boolean hasNext() { return current != null; }
        /**
         * 向下一个元素，同时返回当前元素
         */
        public Item next() {
            Item item = current;
            current = current.next();
            return item;
        }
    }
}