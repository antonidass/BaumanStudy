package mooc.vandy.java4android.calculator.logic;

/**
 * Perform the Subtract operation.
 */
public class Subtract {
    private int arg1;
    private int arg2;

    public Subtract() {
        arg1 = 0;
        arg2 = 0;
    }

    public Subtract(int arg1, int arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    public int evaluate() {
        return arg1 - arg2;
    }
}
