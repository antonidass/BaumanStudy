package mooc.vandy.java4android.calculator.logic;

/**
 * Perform the Multiply operation.
 */
public class Multiply {
    private int arg1;
    private int arg2;

    public Multiply() {
        arg1 = 0;
        arg2 = 0;
    }

    public Multiply(int arg1, int arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    public int evaluate() {
        return arg2 * arg1;
    }
}
