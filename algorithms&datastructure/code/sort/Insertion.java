
public class Insertion {
    
    public static void sort(Comparable<T>[] input) {
        int N = input.length;
        for(int i = 1; i < N; i++) {
            Comparable flag = input[i];
            for(int j = i; j > 0 && less(input[j], input[j-1]); j--) {
                input[j] = input[j-1];
            }
            input[j] = flag;
        }
    }
    public static void main(String[] args) {
        System.out.println("test");
    }
}