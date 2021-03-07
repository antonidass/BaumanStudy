package mooc.vandy.java4android.gate.logic;

import java.util.Random;

import mooc.vandy.java4android.gate.ui.OutputInterface;

/**
 * This class uses your Gate class to manage a herd of snails.  We
 * have supplied you will the code necessary to execute as an app.
 * You must fill in the missing logic below.
 */
public class HerdManager {
    private OutputInterface mOut;
    private Gate mWestGate; // IN
    private Gate mEastGate; // OUT
    private static final int MAX_ITERATIONS = 10;
    public static final int HERD = 24;


    public HerdManager(OutputInterface out,
                       Gate westGate,
                       Gate eastGate) {
        mOut = out;

        mWestGate = westGate;
        mWestGate.open(Gate.IN);

        mEastGate = eastGate;
        mEastGate.open(Gate.OUT);
    }


    void simulateHerd(Random rand) {
        int inHERD = HERD;
        int count_snails;
        rand.setSeed(1234);

        for (int i = 0; i < MAX_ITERATIONS + 1; i++) {
            mOut.println("There are currently " + inHERD + " snails in the pen and " + (HERD - inHERD) + " snails in the pasture");
            if (inHERD == HERD) {
                count_snails = rand.nextInt(HERD) + 1;
                mEastGate.thru(count_snails);
                inHERD -= count_snails;
            }
            else if (inHERD == 0) {
                count_snails = rand.nextInt(HERD) + 1;
                mWestGate.thru(count_snails);
                inHERD += count_snails;
            }
            else if (rand.nextInt(2) == 0) {
//                gate_type = rand.nextInt(2);
                count_snails = rand.nextInt(HERD - inHERD) + 1;
                mWestGate.thru(count_snails);
                inHERD += count_snails;
            }
            else {
                count_snails = rand.nextInt(inHERD) + 1;
                mEastGate.thru(count_snails);
                inHERD -= count_snails;
            }
        }
    }
}
