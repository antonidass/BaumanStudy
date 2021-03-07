package mooc.vandy.java4android.gate.logic;

import java.util.Random;

import mooc.vandy.java4android.gate.ui.OutputInterface;

/**
 * This class uses your Gate class to fill the corral with snails.  We
 * have supplied you will the code necessary to execute as an app.
 * You must fill in the missing logic below.
 */
public class FillTheCorral {
    /**
     * Reference to the OutputInterface.
     */
    private OutputInterface mOut;

    /**
     * Constructor initializes the field.
     */
    FillTheCorral(OutputInterface out) {
        mOut = out;
    }

    public void setCorralGates(Gate[] gate, Random rand) {
        for (int i = 0; i < gate.length; i++) {
            gate[i].setSwing(rand.nextInt(3) - 1);
            mOut.println("Gate" + i + ": " + gate[i].toString());
        }
    }

    public boolean anyCorralAvailable(Gate[] corral) {
        for (int i = 0; i < corral.length; i++) {
            if (corral[i].getSwingDirection() == Gate.IN) {
                return true;
            }
        }
        return false;
    }

    public int corralSnails(Gate[] corral, Random rand) {
        int index, count_move_snails;
        int count_attempts = 0;
        int count_snails = 5;

        while (count_snails != 0) {
            index = rand.nextInt(corral.length);
            count_attempts++;
            count_move_snails = rand.nextInt(count_snails) + 1;
            mOut.println(count_move_snails + " are trying to move through corral " + index);
            count_snails -= corral[index].thru(count_move_snails);
        }

        mOut.println("It took " + count_attempts + " attempts to corral all of the snails");

        return count_attempts;
    }
}
