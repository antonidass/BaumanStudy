package mooc.vandy.java4android.calculator.logic;

/**
 * Perform the Divide operation.
 */
public class Divide {
    private int arg1;
    private int arg2;
    private int result[];


    public Divide() {
        arg1 = 0;
        arg2 = 0;
    }

    public Divide(int arg1, int arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    public int[] evaluate() {
        if (arg2 == 0) {
            return null;
        }

        result = new int[2];

        result[0] = arg1 / arg2;
        result[1] = arg1 % arg2;

        return result;
    }
}
