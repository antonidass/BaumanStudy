package mooc.vandy.java4android.gate.logic;

/**
 * This file defines the Gate class.
 */
public class Gate {
    public static final int IN = 1;
    public static final int OUT = -1;
    public static final int CLOSED = 0;
    private int mySwing;

    public Gate() {
        mySwing = CLOSED;
    }

    public int getSwingDirection() {
        return mySwing;
    }

    public boolean setSwing(int direction) {
        if (direction == 1 || direction == 0 || direction == -1) {
            mySwing = direction;
            return true;
        }
        return false;
    }

    public boolean open(int direction) {
        if (direction == 1 || direction == -1) {
            return setSwing(direction);
        }
        return false;
    }

    public void close() {
        mySwing = CLOSED;
    }

    public int thru(int count) {
        if (mySwing == IN) {
            return count;
        } else if (mySwing == OUT) {
            return -count;
        } else {
            return 0;
        }
    }


    public String toString() {
        String type_swing;

        if (mySwing == CLOSED) {
            return ("This gate is closed");
        }

        if (mySwing == IN) {
            type_swing = new String("enter");
        } else if (mySwing == OUT) {
            type_swing = new String("exit");
        } else {
            return ("This gate has an invalid swing direction");
        }

        return ("This gate is open and swings to " + type_swing + " the pen only");
    }
}
