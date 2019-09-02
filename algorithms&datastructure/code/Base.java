
public abstract class Base<Type> {
    /**
	 * 
	 */
	public abstract void sort();
	/**
	 * 
	 * @param v
	 * @param w
	 * @return
	 */
	public static boolean less(Comparable<T> v, Comparable<T> w) {
		return v.compareTo(w)  < 0;
	}
	/**
	 * 
	 * @param a
	 */
	public static void show(Comparable<T>[] a) {
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
	public static boolean isSorted(Comparable<T>[] a) {
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
	public static void exch(Comparable<T>[] input, int i, int j) {
		Comparable<T> tmp = input[i];
		input[i] = input[j];
		input[j] = tmp;
	}
}