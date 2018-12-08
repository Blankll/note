
/**
 * 基于堆的优先队列
 * @param <Key>
 */
public class MaxPQ<Key extends Comparable<Key>>{
    private Key[] pq;
    private int N = 0;

    public MaxPQ(int maxN) {
        pq = (Key[]) new Comparable[maxN + 1];
    }
    public void insert(Key v) {
        pq[++N] = v;
        swim(N);
    }
    public Key delMax() {
        Key max = pq[1];
        pq[1] = pq[N];
        pq[N--] = null; // 防止对象游离
        sink(1);

        return max;
    }
    /**
     * 大于父节点的子节点上浮
     * @param k　子节点下标
     */
    private void swim(int k) {
        while(k > 1 && less(k/2, k)) {
            exch(k/2, k);
            k /= 2;
        }
    }
    /**
     * 小于子节点的父节点下沉
     * @param k 父节点下标
     */
    private void sink(int k) {
        sink(pq, k, N);
    }
    private void sink(Comparable<Key>[] a, int k, int n) {
        while(2*k <= n) {
            int j = 2 * k;
            if(j < n && less(j, j+1)) j++; // 寻找最大子节点
            if(!less(k, j)) break; // 比较父节点与最大子节点大小
            exch(k, j);
            k = j;
        }
    }
    public void sort(Comparable[] a) {
        int n = a.length;
        // 从倒数第二层开始，向上下沉元素
        for(int k = n / 2; k >= 1; k--) {
            sink(a, k, n); // 任意序的堆排序成堆有序
        }
        while(n > 1) {
            exch(a, 1, n--); // 将堆有序最大值与最小值交换，堆大小减一
            sink(a, 1, n); // 最小值下沉找到对应的位置,or重新找出堆剩余元素最大值
        }

    }
    public boolean isEmpty() {
        return N == 0;
    }
    public int size() {
        return N;
    }
    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) < 0;
    }
    private void exch(int i, int j) {
        Key t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }
    private void exch(Comparable[] a, int i, int j) {
        Key t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    
}