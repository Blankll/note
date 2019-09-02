import java.util.Stack;


public class Dijkstra {
    public static void main(String[] args){
        // char[] data = "(1+((2+3)*(4*5)))";
        String[] test = new String[17];
        test[0] = "(";
        test[1] = "1";
        test[2] = "+";
        test[3] = "(";
        test[4] = "(";
        test[5] = "2";
        test[6] = "+";
        test[7] = "3";
        test[8] = ")";
        test[9] = "*";
        test[10] = "(";
        test[11] = "4";
        test[12] = "*";
        test[13] = "5";
        test[14] = ")";
        test[15] = ")";
        test[16] = ")";

        Dijkstra one = new Dijkstra();
        one.evaluate(test);
    }
    public void evaluate(String[] input){
        Stack<String> operations = new Stack<>();
        Stack<Double> values = new Stack<>();
        for(String item : input){
            if(item.equals("("));
            else if(item.equals("+")) operations.push(item);
            else if(item.equals("-")) operations.push(item);
            else if(item.equals("*")) operations.push(item);
            else if(item.equals("/")) operations.push(item);
            else if(item.equals(")")){
                String op = operations.pop();
                double valueOne = values.pop();
                double valueTwo = values.pop();
                if(op.equals("+")) { valueTwo += valueOne; }
                else if(op.equals("-")) {valueTwo -= valueOne; }
                else if(op.equals("*")) { valueTwo *= valueOne; }
                else if(op.equals("/")) { valueTwo /= valueOne; }
                values.push(valueTwo);
            }else values.push(Double.parseDouble(item));
        }
        System.out.println("result:" + values.pop());
    }
}