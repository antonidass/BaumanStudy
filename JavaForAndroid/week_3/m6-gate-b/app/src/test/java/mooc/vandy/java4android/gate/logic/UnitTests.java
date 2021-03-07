package mooc.vandy.java4android.gate.logic;

import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

import io.magnum.autograder.junit.Rubric;
import mooc.vandy.java4android.gate.ui.OutputInterface;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * To work on unit tests, switch the Test Artifact in the Build Variants view.
 */
public class UnitTests {
    // Default time out used for all tests. To use the debugger to set
    // breakpoints and for stepping through your code, set this value
    // to 0 disable all time outs.
    final static int TIMEOUT = 100;

    TestingOutputInterface mOutput = new TestingOutputInterface();

    @Rubric(
            value = "testSetGatesIn",
            goal = "The goal of this evaluation is to test SetGatesIn",
            points = 1.0,
            reference = "This Test fails when: The Gate was not set to IN"
    )
    // HerdManager tests
    @Test(timeout = TIMEOUT)
    public void testSetGatesIn() {
        final Gate inGate = new Gate();
        new HerdManager(mOutput,
                inGate,
                new Gate());
        Assert.assertNotEquals(0, inGate.getSwingDirection());
        assertEquals(inGate.getSwingDirection(), Gate.IN);
    }

    @Rubric(
            value = "testSetGatesOut",
            goal = "The goal of this evaluation is to test SetGatesOut",
            points = 1.0,
            reference = "This Test fails when: The Gate was not set to OUT"
    )
    @Test(timeout = TIMEOUT)
    public void testSetGatesOut() {
        final Gate outGate = new Gate();
        final HerdManager herd =
                new HerdManager(mOutput,
                        new Gate(),
                        outGate);
        Assert.assertNotEquals(0, outGate.getSwingDirection());
        assertEquals(outGate.getSwingDirection(), Gate.OUT);
    }

    @Rubric(
            value="testSimulateHerdOutput",
            goal="The goal of this evaluation is to test SimulateHerdOutput",
            points=3.0,
            reference="This Test fails when: The herd.simulateHerd() output was incorrect"
    )
    @Test(timeout = TIMEOUT)
    public void testSimulateHerdOutput() {

        ArrayList<Integer> expected1 = new ArrayList<>();
        ArrayList<Integer> expected2 = new ArrayList<>();
        ArrayList<Integer> actual = new ArrayList<>();

        HerdManager herd =
                new HerdManager(mOutput,
                        new Gate(),
                        new Gate());
        long seed = Logic.sRANDOM_SEED;

        // Since there are two possible solutions to this assignment
        // depending on the ordering of the statements selected by
        // the rand.nextBoolean() call. Therefore we need to check
        // for the second possible output ordering before we can
        // assume the solution is incorrect.
        int[] expectedOutput1 = {24, 0, 3, 21, 6, 18, 15, 9, 20, 4, 2, 22, 9, 15, 12, 12, 18, 6, 23, 1, 24, 0};
        int[] expectedOutput2 = {24, 0, 3, 21, 0, 24, 13, 11, 21, 3, 7, 17, 1, 23, 0, 24, 24, 0, 1, 23, 14, 10};

        for (int i : expectedOutput1) {
            expected1.add(i);
        }

        for (int i : expectedOutput2) {
            expected2.add(i);
        }

        herd.simulateHerd(new Random(seed));

        String output = mOutput.getOutput();

        try {
            output = output.replaceAll("[^0-9]+\n*", " ");
            Scanner scanner = new Scanner(output);
            while (scanner.hasNextInt()) {
                actual.add(scanner.nextInt());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        assertEquals("Failed to print the expected number of values", expected1.size(),actual.size());
        assertTrue(expected1.equals(actual) || expected2.equals(actual));
    }

    @Rubric(
            value="test24InHerd",
            goal="The goal of this evaluation is to test 24InHerd",
            points=2.0,
            reference="This Test fails when: The Herd didn't maintain 24 snails upon each movement"
   )

    @Test(timeout = TIMEOUT)
    public void test24InHerd() {
        final HerdManager herd =
                new HerdManager(mOutput,
                        new Gate(),
                        new Gate());
        long seed = Logic.sRANDOM_SEED;

        herd.simulateHerd(new Random(seed));

        ArrayList<Integer> actual = new ArrayList<>();

        String output = mOutput.getOutput();

        try {
            output = output.replaceAll("[^0-9]+\n*", " ");
            Scanner scanner = new Scanner(output);
            while (scanner.hasNextInt()) {
                actual.add(scanner.nextInt());
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        int total;

        for (int i = 0; i < actual.size()-1; i += 2) {
            total = actual.get(i) + actual.get(i + 1);
            assertEquals(total, 24);
        }
    }

    //FillTheCorral Tests
    @Rubric(
            value="testAnyCorralAvailable",
            goal="The goal of this evaluation is to test anyCorralAvailable",
            points=2.0,
            reference="This Test fails when anyCorralAvailable() returns the wrong result."
    )
    @Test(timeout = TIMEOUT)
    public void testAnyCorralAvailable() {

        FillTheCorral fill = new FillTheCorral(mOutput);

        int SIZE = 4;
        Gate[] corral = new Gate[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            corral[i] = new Gate();
            corral[i].close();
        }

        assertFalse(fill.anyCorralAvailable(corral));
        corral[0].open(Gate.IN);
        assertTrue(fill.anyCorralAvailable(corral));
        corral[0].open(Gate.OUT);
        assertFalse(fill.anyCorralAvailable(corral));
        corral[0].close();
        assertFalse(fill.anyCorralAvailable(corral));
        corral[3].open(Gate.OUT);
        assertFalse(fill.anyCorralAvailable(corral));
        corral[3].setSwing(Gate.IN);
        assertTrue(fill.anyCorralAvailable(corral));
        corral[3].close();
        assertFalse(fill.anyCorralAvailable(corral));

    }

    @Rubric(
            value="testSetCorralGates",
            goal="The goal of this evaluation is to test setCorralGates",
            points=2.0,
            reference="This Test fails when the gates are not properly set."
    )
    @Test(timeout = TIMEOUT)
    public void testSetCorralGates() {
        FillTheCorral fillCorral = new FillTheCorral(mOutput);
        int SIZE = 4;
        Gate[] corral = new Gate[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            corral[i] = new Gate();
        }
        int seed = Logic.sRANDOM_SEED;
        fillCorral.setCorralGates(corral, new Random(seed));
        /*
          EXPECTED OUTPUT FROM SEED OF Logic.sRANDOM_SEED:
          Gate 0: This gate is open and swings to enter the pen only.
          Gate 1: This gate is open and swings to enter the pen only.
          Gate 2: This gate is open and swings to enter the pen only.
          Gate 3: This gate is open and swings to exit the pen only.
        */
        assertEquals(corral[0].getSwingDirection(), Gate.IN);
        assertEquals(corral[1].getSwingDirection(), Gate.IN);
        assertEquals(corral[2].getSwingDirection(), Gate.IN);
        assertEquals(corral[3].getSwingDirection(), Gate.OUT);
    }

    @Rubric(
            value = "testCorralSnailOutput",
            goal = "The goal of this evaluation is to test CorralSnailOutput",
            points = 3.0,
            reference = "This Test fails when: The corralSnail output was incorrect"
    )
    @Test(timeout = TIMEOUT)
    public void testCorralSnailOutput() {

        TestingOutputInterface mOutput2 = new TestingOutputInterface();
        FillTheCorral fillCorral = new FillTheCorral(mOutput2);

        //ByteArrayOutputStream baos = new ByteArrayOutputStream();
        //PrintStream ps = new PrintStream(baos);

        int SIZE = 4;
        Gate [] corral = new Gate[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            corral[i] = new Gate();
        }
        // don't use setCorralGates() to avoid excess output, rather set the gates directly
        corral[0].setSwing(Gate.IN);
        corral[1].setSwing(Gate.IN);
        corral[2].setSwing(Gate.IN);
        corral[3].setSwing(Gate.OUT);

        int num = fillCorral.corralSnails(corral, new Random(Logic.sRANDOM_SEED));
        assertEquals("corralSnails returned the wrong value", num, 5);

        ArrayList<Integer> expected = new ArrayList<>();
        ArrayList<Integer> actual = new ArrayList<>();

        int [] expectedOutput = {4,2,1,3,1,3,2,1,1,1,5};
        for (int item : expectedOutput) {
            expected.add(item);
        }

        String output = mOutput2.getOutput();

        try {
            output = output.replaceAll("[^0-9]+\n*", " ");
            Scanner scanner = new Scanner(output);
            while (scanner.hasNextInt()) {
                actual.add(scanner.nextInt());
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }

        assertEquals("corralSnails failed to print the expected number of values", expected.size(),actual.size());
        for (int i=0; i<expected.size(); i++) {
            assertEquals("corralSnails output mismatch", expected.get(i).intValue(), actual.get(i).intValue());
        }
        assertEquals(expected, actual);

    }

    @Rubric(
            value = "testEntryDown",
            goal = "The goal of this evaluation is to test EntryDown",
            points = 2.0,
            reference = "This Test fails when: The Movement thru an IN gate decreased number"
    )
    @Test(timeout = TIMEOUT)
    public void testEntryDown() {
        int inPasture = 5;
        Gate entryGate = new Gate();
        entryGate.open(Gate.IN);
        inPasture += entryGate.thru(1);
        assertEquals(6, inPasture);
    }

    @Rubric(
            value = "testExitUp",
            goal = "The goal of this evaluation is to test ExitUp",
            points = 2.0,
            reference = "This Test fails when: The Movement thru an OUT gate increased number"
    )
    @Test(timeout = TIMEOUT)
    public void testExitUp() {
        int inPasture = 5;
        Gate entryGate = new Gate();
        entryGate.open(Gate.OUT);
        inPasture += entryGate.thru(1);
        assertEquals(4, inPasture);
    }

    @Rubric(
            value = "testClosedNone",
            goal = "The goal of this evaluation is to test ClosedNone",
            points = 2.0,
            reference = "This Test fails when: There was movement thru a gate that was closed"
    )
    @Test(timeout = TIMEOUT)
    public void testClosedNone() {

        int inPasture = 5;
        Gate entryGate = new Gate();
        entryGate.close();
        inPasture += entryGate.thru(1);
        assertEquals(5, inPasture);

    }

    private static class TestingOutputInterface implements OutputInterface {
        String output = "";

        public String getOutput() {
            return output;
        }

        @Override
        public ClassToTest getClassToTest() {
            return null;
        }

        @Override
        public void resetText() {
            output = "";
        }

        @Override
        public void print(Object obj) {
            output += (obj != null ? obj.toString() : "null");
        }
    }
}
