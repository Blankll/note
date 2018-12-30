
public class BST<Key extends Comparable<Key>, Value> {
    private Node root;
    
    private class Node {
        private Key key;
        private Value value;
        private Node left, right;
        private int N; // sub node sum begin from this node

        public Node(Key key, Value value, int N) {
            this.key = key;
            this.value = value;
            this.N = N;
        }
    }
    public int size() {
        return size(root);
    }
    private int size(Node node) {
        if(node == null) return 0;
        else             return node.N;
    }

    public Value get(Key key) {
        return get(root, key);
    }
    private Value get(Node node, Key key) {
        if(null == node) return null;
        int cmp = key.compareTo(node.key);

        if(0 < cmp)      return get(node.right, key);
        else if(0 > cmp) return get(node.left, key);
        else             return node.value;
    }

    public void put(Key key, Value value) {
        root = put(root, key, value);
    }
    private Node put(Node node, Key key, Value value) {
        if(null == node) return new Node(key, value, 1);

        int cmp = key.compareTo(node.key);
        if(0 < cmp) node.right = put(node.right, key, value);
        else if(0 > cmp) node.left = put(node.left, key, value);
        // key is exists, update value
        else node.value = value;

        // update every size in choose insert line
        node.N = size(node.left) + size(node.right) + 1;

        return node;
    }

    public Key min() {
        return min(root);
    }
    private Key min(Node node) {
        if(null == node.left) return node;
        else                  return min(node.left);
    }

    public Key floor(Key key) {
        Node x = floor(root, key);
        if(null == x) return null;
        else         return x.key;
    }
    private Node floor(Node node, Key key) {
        if(null == node) return null;
        int cmp = key.compareTo(node.key);
        if(0 == cmp) return node;
        if(0 > cmp) return floor(node.left, key);
        // 检测右边是否有小于node的值，如果有，就返回最大的那个小于node的值，
        // 如果没有，就返回自身
        Node t = floor(node.right, key);
        if(null != t) return t;
        else          return node;
    }

    public Key select(int level) {
        // 返回排名为k的节点key
        return select(root, level).key;
    }
    private Node select(Node node, int level) {
        if(null == node) return null;
        int t = size(x.left);
        if(t > level) return select(node.left, level);
        else if(t < level) return select(node.right, level-t-1);
        else return node;
    }

    public int rank(Key key) {
        return rank(root, key);
    }
    private int rank(Node node, Key key) {
        if(null == node) return 0;
        int cmp = key.compareTo(node.key);
        if(0 > cmp) return rank(node.left, key);
        else if(0 < cmp) return size(node.left) + rank(node.right, key) + 1;
        else return size(node.left);
    }

    public void deleteMin() {
        root = deleteMin(root);
    }
    private Node deleteMin(Node node) {
        if(null == node.left) return node.right;
        node.left = deleteMin(node.left);
        node.N = size(node.left) + size(node.right) + 1;
        
        return node;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }
    private Node delete(Node node, Key key) {
        if(null == node) return null;
        int cmp = key.compareTo(node.key);
        if(0 < cmp) node.right = delete(node.right, key);
        else if(0 > cmp) node.left = delete(node.left, key);
        else {
            if(null == node.left) return node.right;
            if(null == node.right) return node.left;
            Node t = node;
            node = min(node.right);
            node.right = deleteMin(node.right);
            node.left = t.left;
        }
        node.N = size(node.left) + size(node.right) + 1;

        return node;
    }

    // in order travel
    private void inOrderTravel(Node node) {
        if(null == node) return;
        inOrderTravel(node.left);
        System.out.println("node: key => " + node.key + "value => " + node.value);
        inOrderTravel(node.right);
    }
}
