package mooc.vandy.java4android.calculator.logic;

/**
 * Perform the Add operation.
 */
public class Add {
    private int arg1;
    private int arg2;

    public Add() {
        arg1 = 0;
        arg2 = 0;
    }

    public Add(int arg1, int arg2) {
        this.arg1 = arg1;
        this.arg2 = arg2;
    }

    public int evaluate() {
        return arg1 + arg2;
    }
}
