public class Merge {
    private static Comparable[] aux;
    public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length -1);
    }
    public static void sort(Comparable[] a, int start, int end) {
        if(start >= end) return;
        int mid = (start + end) / 2;
        // 排序左侧数据
        sort(a, start, mid);
        // 排序右侧数据
        sort(a, mid+1, end);
        // 合并结果
        merge(a,start, mid, end);
    }
    public static void merge(Comparable[] a, int start, int mid, int end) {
        int i = start;
        int j = mid + 1;
        // 拷贝数组到成员变量中
        for(int k = start; k <= end; k++) { aux[k] = a[k]; }
        // 将拷贝的成员变量数组进行排序，结果放入传入的原数组中
        for(int k = start; k <= end; k++) {
            if(i > mid) { a[k] = aux[j++]; }
            else if(j > end) { a[k] = aux[i++]; }
            else if(less(aux[j], aux[i])) { a[k] = aux[j++]; }
            else { a[k] = aux[i++]; }
        }
    }
}