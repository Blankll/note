import java.util.Comparator;
/**
 * 选择排序，每次从未排序的集合中找出最小的元素，将他与最外层循环的元素交换位置，
 * 然后当前元素向下移动一个位置，以此往复
 */
public class Selection {

	public static void main(String[] args) {
		Comparable[] test = {"a","s","d","q","p"};
		sort(test);
		show(test);
	}
	/**
	 * 
	 */
	public static void sort(Comparable[] input) {
		int N = input.length;
		for(int i = 0; i < N; i++) {
			int mini = i;
			for(int j = i+1; j < N; j++) {
				if(less(input[j], input[mini])) mini = j;
			}
			exch(input, mini, i);
		}
		
	}
	/**
	 * 
	 * @param v
	 * @param w
	 * @return
	 */
	public static boolean less(Comparable v, Comparable w) {
		return v.compareTo(w)  < 0;
	}
	/**
	 * 
	 * @param a
	 */
	public static void show(Comparable[] a) {
		for(int i = 0; i < a.length; i++) {
			System.out.print(a[i]+"\t");
		}
		System.out.println();
	}
	/**
	 * 
	 * @param a
	 * @return
	 */
	public static boolean isSorted(Comparable[] a) {
		for(int i = 1; i < a.length; i++) {
			if(less(a[i], a[i-1])) return false;
		}
		return true;
	}
	/**
	 * 
	 * @param input
	 * @param i
	 * @param j
	 */
	public static void exch(Comparable[] input, int i, int j) {
		Comparable tmp = input[i];
		input[i] = input[j];
		input[j] = tmp;
	}
}