public class Quick {
    public static void sort(Comparable[] a) {
        StdRandom.shuffle(a);
        sort(a, 0, a.length - 1);
    }
    public static void sort(Comparable[] a, int low, int high) {
        if(high <= low) return;
        /**
         * 将数组切分为左右两份，左侧数据 <= a[flagIndex],
         * 右侧数据 >= a[flagIndex]
         */
        int flagIndex = partition(a, low, high);
        // 递归排序左侧数据
        sort(a, low, flagIndex - 1);
        // 递归排序右侧数据
        sort(a, flagIndex + 1, high);
        // 排序结果在原数组中，不存在合并操作
    }
    /**
     * 以a[low]元素进行切分，通过循环使得小于a[low]的值位于a[low]值的左侧
     * 大于a[low]的值位于a[low]值的右侧
     * 当指针i和指针j相遇时退出循环，
     * 在循环中，a[i]小于a[low]值时，i向上检索
     * a[j]大于a[low]值时，j向下检索
     * 交换a[i]和a[j]使得i左侧的值都不大于a[low]的值，j右侧的值都不小于a[low的值]
     * @param a
     * @param low
     * @param high
     * @return
     */
    public static int partition(Comparable[] a, int low, int high) {
        int i = low;
        int j = high;
        Comparable point = a[low];
        while(true) {
            while(less(a[++i], point)) if(i > high) break;
            while(less(point, a[--j])) if(j < low) break;
            if(i >= j) break; // i, j相遇退出循环
            exch(a, i, j);
        }
        // 使a[low]移动到切分点
        exch(a, low, j);

        return j;
    }
}