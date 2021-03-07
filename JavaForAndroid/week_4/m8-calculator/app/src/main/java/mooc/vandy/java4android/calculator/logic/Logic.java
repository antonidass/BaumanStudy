package mooc.vandy.java4android.calculator.logic;

import java.util.HashMap;

import mooc.vandy.java4android.calculator.ui.ActivityInterface;

/**
 * Performs an operation selected by the user.
 */
public class Logic implements LogicInterface {
    /**
     * Reference to the Activity output.
     */
    protected ActivityInterface mOut;

    
    /**
     * Constructor initializes the field.
     */
    public Logic(ActivityInterface out) {
        mOut = out;
        
    }

    
    public final static int ADD = 1;
    public final static int SUB = 2;
    public final static int MUL = 3;
    public final static int DIV = 4;

    /**
     * Perform the operation on argumentOne and argumentTwo.
     */
    public void process(int argumentOne, int argumentTwo, int operation) {

        if (operation == ADD) {
            Add add = new Add(argumentOne, argumentTwo);
            mOut.print("" + add.evaluate());
        }
        else if (operation == SUB) {
            Subtract sub = new Subtract(argumentOne, argumentTwo);
            mOut.print("" + sub.evaluate());
        }
        else if (operation == MUL) {
            Multiply mul = new Multiply(argumentOne, argumentTwo);
            mOut.print("" + mul.evaluate());
        }
        else if (operation == DIV) {
            if (argumentTwo == 0) {
                mOut.print("Div by zero attempt");
                return;
            }
            Divide div = new Divide(argumentOne, argumentTwo);

            int res[] = div.evaluate();
            mOut.print(res[0] + " R: " + res[1]);
        }
    }
}
