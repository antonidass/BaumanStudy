package mooc.vandy.java4android.diamonds.logic;

import mooc.vandy.java4android.diamonds.ui.OutputInterface;

/**
 * This is where the logic of this App is centralized for this assignment.
 * <p>
 * The assignments are designed this way to simplify your early
 * Android interactions.  Designing the assignments this way allows
 * you to first learn key 'Java' features without having to beforehand
 * learn the complexities of Android.
 */
public class Logic
       implements LogicInterface {
    /**
     * This is a String to be used in Logging (if/when you decide you
     * need it for debugging).
     */
    public static final String TAG = Logic.class.getName();

    /**
     * This is the variable that stores our OutputInterface instance.
     * <p>
     * This is how we will interact with the User Interface [MainActivity.java].
     * <p>
     * It is called 'out' because it is where we 'out-put' our
     * results. (It is also the 'in-put' from where we get values
     * from, but it only needs 1 name, and 'out' is good enough).
     */
    private OutputInterface mOut;

    /**
     * This is the constructor of this class.
     * <p>
     * It assigns the passed in [MainActivity] instance (which
     * implements [OutputInterface]) to 'out'.
     */
    public Logic(OutputInterface out){
        mOut = out;
    }

    /**
     * This is the method that will (eventually) get called when the
     * on-screen button labeled 'Process...' is pressed.
     */
    public void process(int size) {
        print_edge(size);

        for (int i = 0; i < size - 1; i++)
            print_main(size, i, 1);

        print_center(size);

        for (int i = size - 1; i > 0; i--) {
            print_main(size, i - 1, 0);
        }

        print_edge(size);
    }

    public void print_str(int count, char sym) {
        for (int i = 0; i < count; i++)
            mOut.print(sym);
    }

    public void print_edge(int size) {
        mOut.print('+');

        print_str(size * 2, '-');

        mOut.println('+');
    }

    public void print_main(int size, int check, int isup) {
        mOut.print('|');

        print_str(size - check - 1, ' ');

        if (isup == 1) {
            mOut.print('/');
        }
        else {
            mOut.print('\\');
        }

        if (check % 2 == 0) {
            print_str(check * 2, '=');
        }
        else {
            print_str(check * 2, '-');
        }

        if (isup == 1)
            mOut.print('\\');
        else
            mOut.print('/');

        print_str(size - check - 1, ' ');
        mOut.println('|');
    }

    public void print_center(int size) {
        mOut.print("|<");

        if (size % 2 == 0) {
            print_str(size * 2 - 2, '-');
        }
        else {
            print_str(size * 2 - 2, '=');
        }

        mOut.println(">|");
    }
}
